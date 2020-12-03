# MLP

Implementação de um multilayer perceptron em C e paralelização utilizando o OpenMP.
Implementado por Laura Nunes, Lucca Augusto e Richard Mariano.

## como compilar e rodar o codigo:

O script gera\_base.py pode ser usado para gerar uma base no formato que usamos para testar
+ python gera\_base.py > entrada.txt

### para compilar o programa use o comando
	gcc -o mlp mlp.c -fopenmp

### para rodar o programa use o comando 
	./mlp

### O arquivo saida.txt foi a saída gerada pelo programa sequencial para a entrada entrada.txt
### O arquivo saida\_p.txt foi a saída gerada pelo programa paralelo para a entrada entrada.txt
