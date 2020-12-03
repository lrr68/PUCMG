#include <time.h>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

#include "batnaval.h"

int server_fd, new_socket, valread; 
struct sockaddr_in address; 
int addrlen = sizeof(address); 
int PORT=8000;
int opt = 1; 


void init_socket()
{
	// criando socket ipv4, tcp, ip
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	puts("socket criado");
	
	// setando o socket na porta PORT
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	puts("socket setado");
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// setando o socket na porta PORT
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	puts("bind feito");

	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 

	puts("Aguardando conexao");
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 
	puts("Conectado");
}

int main(int argc, char *argv[]) 
{ 
	int** tabuleiro = matriz2d(10,10);

	char ataque[3];
	int x=0,y=0;
	int x_tiro,y_tiro;
	int c;
	int me_acertou;
	int acertei_cliente;
	int filax[8] = {-1};
	int filay[8] = {-1};

	char buffer[1024] = {0}; 
	char letras[10] = {'a','b','c','d','e','f','g','h','i','j'};

	srand(time(NULL));
	init_rand(tabuleiro);

	while((c = getopt(argc,argv,"p:")) != -1) {
		switch(c) {
			case 'p':
				PORT = str2int(optarg);
				break;
			case '?':
				if(optopt == 'p') {
					puts("Porta não específicada\n Uso: servidor -p <porta>\n");
					return 1;
				}
				break;
			default:
					puts("Parametros não específicados\n Usando porta padrão.\nUso: servidor -p <porta>\n");
		}
	}

	init_socket();

	valread = read(new_socket, buffer, 1024); 
	if ( ! valread) {
		printf("Erro de comunicacao no socket\n");
		exit(EXIT_FAILURE);
	}

	while(strcmp(buffer,PERDI)) {
		//cliente ataca servidor
		x = letra2num(buffer[0]);
		y = letra2num(buffer[2]);
		acertei_cliente = letra2num(buffer[4]);
		
		//insere os pontos vizinhos numa fila
		if (acertei_cliente == '1') {
			int i=0;
			for(;i<8 && filax[i] == -1;++i);
			if (i<7) { 
				filax[i] = x+1;
				filax[i+1] = x-1;
			}else if(i<8) {
				filax[i] = x+1;
			}
			i=0;
			for(;i<8 && filay[i] == -1;++i);
			if (i<7) { 
				filay[i] = y+1;
				filay[i+1] = y-1;
			}else if(i<8) {
				filay[i] = y+1;
			}
		}

		char at_cli[256];
		snprintf(at_cli,256,"Cliente atacou em %d %c",x,letras[y]);
		puts(at_cli);

		if (jogada(x,y,tabuleiro)) {
			printf("Acertou\n");
			me_acertou = '1';
		}
		else {
			printf("Splash\n");
			me_acertou = '0';
		}

		if(terminou(tabuleiro)) {
			write(new_socket , PERDI , strlen(PERDI)); 
			printf("Cliente Ganhou\n");
			exit(0);
		}


		//pega um ponto aleatorio ou escolhe um ponto da fila
		if (filax[0] != -1) {
			x_tiro = filax[0];
			//anda a fila
			for(int i=0; i<7 && filax[i+1] != -1; i++) {
				filax[i] = filax[i+1];
				filax[i+1] = -1;
			}

		}else{
			x_tiro = rand() % 10;
		}
		if (filay[0] != -1) {
			y_tiro = filay[0];
			//anda a fila
			for(int i=0; i<7 && filay[i+1] != -1; i++) {
				filay[i] = filay[i+1];
				filay[i+1] = -1;
			}
		}else{
			y_tiro = rand() % 10;
		}

		//cria uma string a ser enviada pelo socket
		//ultimo caractere indica se o jogador me acertou na ultima jogada
		snprintf(ataque,8,"%d %d %c",x_tiro,y_tiro,me_acertou);

		//servidor ataca cliente
		write(new_socket,ataque,strlen(ataque));

		//cliente ataca servidor
		valread = read(new_socket , buffer, 1024);
		if ( ! valread) {
			printf("Erro de comunicacao no socket\n");
			exit(EXIT_FAILURE);
		}
	}

	return 0; 
} 

