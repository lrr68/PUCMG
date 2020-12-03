#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Cria uma matriz2d de qualquer tamanho usando malloc
int** matriz2d(int x, int y)
{
	int** matriz = (int**) malloc(x * sizeof(int*));
	for(int i = 0; i < x; i++)
		matriz[i] = (int*) malloc(y * sizeof(int*));
	return matriz;
}

int letra2num(char letra)
{
	int num = 0;
	if (letra < 58)
		num = letra-48;
	else if (letra < 91)
		num = letra-65;
	else
		num = letra-97;
	return num;
}

int str2int(char *str)
{
	int t = strlen(str);
	int res = 0;
	for (int i=0; i< t; ++i) {
		res += letra2num(str[i]) * pow(10,t-i-1);
	}
	return res;
}

char leLetra(void)
{
	char linha[3];
	int c;
	int i=0;
	while((c=getchar()) != '\n' && c != EOF && i<3) {
		linha[i] = c;
		++i;
	}
	return linha[0];
}

int leInt(void)
{
	char linha[3];
	int c;
	int i=0;
	while((c=getchar()) != '\n' && c != EOF && i<3) {
		linha[i] = c;
		++i;
	}
	return letra2num(linha[0]);
}
