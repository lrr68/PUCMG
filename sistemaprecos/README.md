# batalhanaval

Trabalho desenvolvido para a disciplina de redes do primeiro semestre de 2020.
Esse trabalho consistem em um jogo de batalha naval entre cliente e servidor utilizando a biblioteca socket e o padrão TCP.

## Compilação e execução
O programa é compilado pelo makefile usando o comando
	```
	make
	```
Para executar o programa é preciso executar primeiro o servidor e depois o cliente, já que o cliente nao conseguirá se conectar se o servidor nao estiver rodando.
Utilizando o comando seguinte é possível executar o programa em apenas uma instância do shell.
``` 
./servidor [-p <porta>] &
./cliente [-i <ip> -p <porta> [-a <arquivo>]
```

Uma outra forma de executar é usar um shell para o servidor e um shell para o cliente.
```
(shell 1)
./servidor [-p <porta>] 

(shell 2)
./cliente [-i <ip> -p <porta> [-a <arquivo>]
```

Caso nenhum argumento seja passado aos programas, o servidor iniciará na porta padrão 8000, o cliente acessará a porta padrao 8000 com o ip padrao 127.0.0.1 e carregara o tabuleiro do arquivo tabuleiro.txt

## Código

O código é composto por 4 arquivos:
+ servidor.c
+ cliente.c
+ batnaval.h
+ utils.h

### Servidor.c
O arquivo servidor.c é responsável por inicializar o socket e ouvir a porta.
Após inicializar o socket, o servidor fica em espera até algum cliente se conectar na porta.
Feita a conexão, o servidor espera pela mensagem do cliente com as coordenadas de seu ataque.
O servidor executa um loop até que receba do cliente a mensagem "perdi", informando que o cliente perdeu, ou até que o servidor perca o jogo, enviando para o cliente a mensagem "perdi" e finalizando sua execução.
Recebida a mensagem de ataque, o ataque é computado e o servidor devolve uma mensagem para o cliente.
Essa mensagem é da forma "x y 1" onde x e y sao as coordenadas do ataque gerado pelo servidor e 1 é uma flag
dizendo se o ataque anterior do cliente acertou algum navio.

#### Ataque do servidor
O ataque do servidor acontece da seguinte forma: Chuta uma coordenada aleatória na primeira vez, se acertar algum navio, or próximos ataques acontecem nas coordenadas adjacentes ao ponto acertado.
Se errar o tiro, chuta outro ponto aleatório.

### Recebendo um ataque do cliente
Caso a mensagem do cliente não seja "perdi", o servidor computa o ataque marcando um 0 em seu tabuleiro nas coordenadas informadas pelo jogador.

### Cliente.c
O arquivo cliente.c é responsavel por se conectar a porta e realizar os ataques indicados pelo usuário.
Após inicializar o socket, o cliente conecta na porta e espera pela entrada do usuário com as coordenadas de seu ataque.
Após o usuário digitar as coordenadas, o cliente envia para o servidor uma mensagem com as coordenadas do ataque na forma "x y 1" onde x e y são a linha e a coluna do ataque, respectivamente, e 1 é uma flag que indica se o último ataque do servidor acertou.
Depois disso o cliente executa um loop até receber do servidor a mensagem "perdi" informando que o servidor perdeu, ou até que o cliente perca o jogo, enviando para o servidor a mensagem "perdi" e finalizando sua execução.

### Ataque do cliente
O usuário digita as coordenadas de seu ataque, linha (em número) e coluna (em letra) e o cliente monta a mensagem e envia ao servidor. Caso o usuário digite 'p' ao informar a linha, o cliente mostrará na tela a disposição de seu tabuleiro e um mapa de seus acertos no tabuleiro inimigo.

### Recebendo um ataque do servidor
Caso a mensagem enviada pelo servidor não seja "perdi", o cliente computa o ataque marcando um 0 em seu tabuleiro nas coordenadas enviadas pelo servidor.

### Utils.h
Esse arquivo contém funções de IO e utéis para todos os arquivos em geral.

### Batnaval.h
Esse arquivo implementa o jogo de batalha naval em sí. Ele é responsável por computar as jogadas, verificar se o dono do tabuleiro atual perdeu e inicializar os tabuleiros, lendo de um arquivo ou gerando aleatóriamente.
# sistemaprecos
