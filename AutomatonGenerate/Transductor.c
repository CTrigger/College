/*
 * 	Author: Ricardo Kim
 * 	Year Date: 2017
 *  	Details: college homework transductor 
 *	Teacher: Pier Richetti
 * */

#include<stdio.h>
#include<conio.h>
#include<locale.h>
#include<string.h>

char TempS[200];
int TempN;
char TempC;

char entrada[999];
//definir o tamanho máximo da variavel em uma matriz 200x200
char variaveis[200][200];
int qtdVariaveis = 0;
int boolPalavraReservada = 0;

int index1 = 0;
char palavrasReservadas [][10] = {
		"if",
		"let",
		"then",
		"printf",
		"of",
		"else",
		"goto",
		"read",
		"end"
};
char sinais [][3]={
		">",
		"<",
		"=",
		"=",
		"!",
		":=",
		"(",
		")",
		"%"
};

void e1();
void e2();
void e3();
void e4();
void e5();
void e6();

int main(int argc, char **argv) {
	setlocale(LC_ALL,"portuguese");
	puts("Digite uma linha:");
	gets(entrada);
	puts("Saída");

	while(entrada[index1] != 0){
		if(
			'a' <= entrada[index1] && entrada[index1] <= 'z' ||
			'A' <= entrada[index1] && entrada[index1] <= 'Z'
		){
			e1();
			
		}else if (
			'0' <= entrada[index1] && entrada[index1] <= '9'
		) {
			e2();
			
		}else if (entrada[index1] == ':') {
			e3();//produz ':'
		}else if (entrada[index1] == '%') {
			e6();
		}else {
			e5();
		}
		index1++;
	}
	puts("\n");

	//Palavras Reservadas:
	puts("Palavras Reservadas");
	int i;
	for (i = 0; i < 9; i++) {
		printf("%d: %s\n",i,palavrasReservadas[i]);
	}

	//Variaveis
	puts("\nVariáveis");
	for( i = 0 ; i < qtdVariaveis ; i++ ){
		printf("%d: %s\n", i, variaveis[i]);
	}
	puts("");
	getch();
	return 0;
}

//e1 Concluído
void e1(){
	int i = 0;
	
	//==========================================
	//             Limpa TempS
	//==========================================
	for (i = 0; i < 200; i++){
		TempS[i] = '#';
	}

	//==========================================
	//Associa palavra temporariamente em TempS
	//==========================================
	i = 0;
	while (
		(
			'a' <= entrada[index1] && entrada[index1] <= 'z' ||
			'A' <= entrada[index1] && entrada[index1] <= 'Z' ||
			'0' <= entrada[index1] && entrada[index1] <= '9' 
		) &&
		entrada[index1] != ' ' && entrada[index1] != '\0'
	)
	{
		TempS[i] = entrada[index1];
		i++;
		index1++;
	}
	index1--;
	TempS[i] = 0;
	
	//==========================================
	//Verificar se TempS é parte das palavras reservadas
	//==========================================
	int iPalavras;
	boolPalavraReservada = 0;
	for (iPalavras = 0; iPalavras < 9; iPalavras++) {
		if (strlen(palavrasReservadas[iPalavras]) == strlen(TempS) && strcmp(TempS,palavrasReservadas[iPalavras]) == 0 ) {
			//printf("TempS: %s - V(%d)\n",TempS,iPalavras);
			printf( "P(%d) ",iPalavras);
			boolPalavraReservada = 1;
		}
	}
	
	//==========================================
	//Verificar se TempS já não está na tabela de variáveis
	//==========================================
	if (boolPalavraReservada == 0) {
		//Primeira Palavra a ser cadastrada
		if (qtdVariaveis == 0) {
			//copiar variavel para tabela de variaveis quando for a primeira
			int c;
			for (c = 0; variaveis[qtdVariaveis][c] = TempS[c]; c++);
			variaveis[qtdVariaveis][c + 1] = 0;
			printf("V(%d) ",qtdVariaveis);
			qtdVariaveis++;
			
		} 
		else {
			//busca se palavra já está na lista
 			int svariaveis = 0;
 			while(strcmp(variaveis[svariaveis],TempS) != 0 && svariaveis < 200){
 				//if(strcmp(variaveis[svariaveis + 1],TempS) == 0)
 				//	printf("V(%d) ",svariaveis);
 				svariaveis++;
 			}
 			
			//não foi encontrado palavra igual
			//cadastrar na tabela de variaveis
			if (svariaveis == 200){
				for (svariaveis = 0 ; variaveis[qtdVariaveis][svariaveis] = TempS[svariaveis]; svariaveis++);
				printf("V(%d) ",qtdVariaveis);
				qtdVariaveis ++;
			}else{
				printf("V(%d) ",svariaveis);
			}
		}
	}



}

//e2 Concluído
void e2(){	
	//Limpa TempN
	TempN = 0;
	
	//Recebe entrada em TempN
	while (
		(
			'0' <= entrada[index1] && entrada[index1] <= '9' 
		) &&
		entrada[index1] != ' ' && entrada[index1] != '\0'
	)
	{
		TempN =  (TempN * 10) + (entrada[index1] - '0');
		index1++;
	}
	index1--;
	printf("N(%d) ",TempN);
	
}

//e3 concluído
void e3(){
	printf("%c",entrada[index1]);
	if(entrada[index1+1] == '=')
		e4();
	else
		printf(" ");
}

//e4 concluido
void e4(){
	index1++;
	printf("%c ",entrada[index1]);

}

//e5 Concluido
void e5(){
	TempC = entrada[index1];
	printf("%c ",TempC);
}

//e6 Concluido
void e6(){
	while(entrada[index1] != '\n'){
		index1++;
	}
}
