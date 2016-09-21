#include <stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<string.h>

#define jmp puts("")
#define cls system("cls")
#define green system("color A")

typedef struct{
	int qtdAlfabeto;
	int qtdEstados;
	int e0;
	int qtdEstadoFinal;
	
}AFD_M;

int main( int argc, char const *argv[])
{

	
	setlocale(LC_ALL,"Portuguese");
	
	AFD_M x;
	int bType;
	char programName[100];
	
	int i,j; // variaveis de auxilio
	
	green;
	cls;
	
	puts("São quantos simbolos?");
	scanf("%d", &x.qtdAlfabeto);
	jmp;
	
	char Alfabeto[x.qtdAlfabeto];
	for(i = 0; i< x.qtdAlfabeto; i++)
	{
		printf("Simbolo %d: ",i);
		scanf("%d",Alfabeto[i]);
	}
	jmp;
		
	puts("São quantos estados?");
	scanf("%d",&x.qtdEstados);
	jmp;
	
	puts("Qual estado inicial?");
	scanf("%d",&x.e0);
	jmp;
	
	puts("Quantos estados finais?");
	scanf("%d",&x.qtdEstadoFinal);
	jmp;
	
	int EstadoFinal[x.qtdEstadoFinal];
	for(i = 0 ; i < x.qtdEstadoFinal ; i ++)
	{
		printf("Defina qual será o Estado Final %d: ", i );
		scanf("%d",&EstadoFinal[i]);
	}
	
	cls;
	
	
	
	puts("=========================================");
	puts("||                                     ||");
	puts("|| Guia de preenchimento               ||");
	puts("||                                     ||");
	puts("|| Inserir o número do próximo estado  ||");
	puts("||                                     ||");
	puts("========================================");
	
	int tbTransition[x.qtdEstados][x.qtdAlfabeto];
	
	for (i = 0 ; i < x.qtdEstados ; i++)
	{
		for(j = 0 ; j < x.qtdAlfabeto ; j++)
		{
			printf("Para o Estado e%d \nQuando receber simbolo \"%c\"\nDeve ir para qual estado?",i,Alfabeto[j]);
			scanf("%d",&tbTransition[i][j]);
			
		}
	}
	
	puts("Escolha o tipo de código:");
	puts("1 - blocos de \"função\"");
	puts("2 - saltos por \"goto\"");
	scanf("%d",&bType);
	jmp;
	
	puts("Qual será o nome do Programa?");
	scanf("%s",programName);
	
	char path[200];
	strcat(path,"./");
	strcat(path,programName);
	
	
	//===================================================
	// pier aula
	FILE *fp;
	fopen(path,"wt");
	fprintf(fp,"#include<stdio.h>");
	fprintf(fp,"#include<stdlib.h>");
	fprintf(fp,"#include<string.h>");
	for(i = 0 ; i < x.qtdEstados ; i++)
	{
		fprintf(fp,"void e%d",i);
	}
	fprintf(fp,"int main( int argc, char const *argv[]){");
	fprintf(fp,"}");
	
	
	for(i = 0 ; i < x.qtdEstados ; i++)
	{
		for(j = 0 ; j < x.qtdAlfabeto ; j++)
		{
			if(tbTransition[i][j] == -1);
			
			if(tbTransition[i][j] == -1);
			
			if(tbTransition[i][j] == -1);
			
		}
	}
	
	
	return 0;
}
