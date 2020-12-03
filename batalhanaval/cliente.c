#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 

#include "batnaval.h"


int sock = 0, valread; 
struct sockaddr_in serv_addr; 
char ataque[10] = "0 0 0";
char buffer[1024]; 
int opt;
char *ip = "127.0.0.1";
char *arq="tabuleiro.txt";
int PORT=8000;


void init_socket()
{
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		exit(0);
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convertendo endereco ip de texto para binario
	if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		exit(0);
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		exit(0); 
	} 
}


int main(int argc, char *argv[]) 
{ 
	int** tabuleiro = matriz2d(10,10);
	int** tiros = matriz2d(10,10);
	char letras[10] = {'a','b','c','d','e','f','g','h','i','j'};
	int x=0, y=0;
	int x_tiro, y_tiro;
	int c;
	int me_acertou=0;
	int acertei_servidor;


	while((c = getopt(argc,argv,"i:p:a:")) != -1) {
		switch(c) {
			case 'i': 
				ip = optarg;
				break;
			case 'p':
				//PORT = str2int(optarg);
				break;
			case 'a':
				arq = optarg;
				break;
			case '?':
				if (optopt == 'i') {
					perror("IP não especificado\n uso: cliente -i <ip> -p <porta> [-a <arquivo>]\n");
					return 1;
				}
				else if(optopt == 'p') {
					perror("Porta não especificada\n uso: cliente -i <ip> -p <porta> [-a <arquivo>]\n");
					return 1;
				}
				else if(optopt == 'a') {
					perror("Arquivo não especificado\n uso: cliente -i <ip> -p <porta> [-a <arquivo>]\n");
					return 1;
				}
			default :
				printf("Parametros não especificados, usando padrão\nuso: cliente -i <ip> -p <porta> [-a <arquivo>]\n");
		}
	}

	init_socket();
	
	//inicia o tabuleiro do cliente
	init(tabuleiro,arq);

	//cliente comeca atacando
	printf("Digite a linha (0-9 ou 'p' para ver o mapa):");
	x = leLetra();
	while (x == 80 || x == 112) {
		mostraTabuleiros(tabuleiro,tiros);
		printf("Digite a linha (0-9 ou 'p' para ver o mapa):");
		x = leLetra();
	}
	printf("Digite a coluna (a-j ou A-J):");
	y = leLetra();

	//guarda coordenadas do tiro para marcar onde acertou e onde errou depois
	x_tiro=x;
	y_tiro=y;

	//cria uma string a ser enviada pelo socket
	snprintf(ataque,8,"%c %c 0",x,y);

	//cliente ataca servidor
	write(sock,ataque,3);
	
	valread = read( sock , buffer, 1024);
	if ( ! valread) {
		printf("Erro de comunicacao no socket\n");
		exit(EXIT_FAILURE);
	}
	while(strcmp(buffer,PERDI)) {
		//servidor ataca cliente
		x = letra2num(buffer[0]);
		y = letra2num(buffer[2]);
		acertei_servidor = buffer[4];

		//marca na matriz de ataque onde atacou N para navio A para agua
		if(acertei_servidor == '1')
			tiros[letra2num(x_tiro)][letra2num(y_tiro)] = 'N';
		else
			tiros[letra2num(x_tiro)][letra2num(y_tiro)] = 'A';

		printf("Servidor atacou em %d %c\n",x,letras[y]);
		if (jogada(x,y,tabuleiro)) {
			printf("Acertou\n");
			me_acertou = 1;
		}
		else {
			printf("Splash\n");
			me_acertou=0;
		} 

		if(terminou(tabuleiro)) {
			write(sock , PERDI , strlen(PERDI)); 
			printf("Servidor Ganhou\n");
			exit(0);
		}

		printf("Digite a linha (0-9 ou 'p' para ver o mapa):");
		x = leLetra();
		while (x == 80 || x == 112) {
			mostraTabuleiros(tabuleiro,tiros);
			printf("Digite a linha (0-9 ou 'p' para ver o mapa):");
			x = leLetra();
		}
		printf("Digite a coluna (a-j ou A-J):");
		y = leLetra();

		x_tiro=x;
		y_tiro=y;

		//cria uma string a ser enviada pelo socket
		snprintf(ataque,8,"%c %c %c",x,y,me_acertou);

		//cliente ataca servidor
		write(sock,ataque,8);

		//servidor ataca cliente
		valread = read( sock , buffer, 1024);
		if ( ! valread) {
			printf("Erro de comunicacao no socket\n");
			exit(EXIT_FAILURE);
		}
	}
	return 0; 
} 

