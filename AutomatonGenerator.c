#include <stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<string.h>

#define jmp puts("")
#define cls system("cls")
#define green system("color A")

typedef struct {
	int qtdAlfabeto;
	int qtdEstados;
	int e0;
	int qtdEstadoFinal;

} AFD_M;

int main(int argc, char const *argv[]) {

	setlocale(LC_ALL, "Portuguese");

	AFD_M x;
	int bType;
	char programName[100];

	int i, j; // variaveis de auxilio

	//green;
	//cls;

	printf("São quantos simbolos: ");
	scanf("%d", &x.qtdAlfabeto);
	jmp;

	char Alfabeto[x.qtdAlfabeto];

	for (i = 0; i < x.qtdAlfabeto; i++) {
		printf("Simbolo %d: ", i);
		scanf(" %c", &Alfabeto[i]);
	}
	jmp;

	printf("São quantos estados: ");
	scanf("%d", &x.qtdEstados);
	jmp;

	printf("Qual estado inicial: ");
	scanf("%d", &x.e0);
	jmp;

	printf("Quantos estados finais: ");
	scanf("%d", &x.qtdEstadoFinal);
	jmp;

	int EstadoFinal[x.qtdEstadoFinal];
	for (i = 0; i < x.qtdEstadoFinal; i++) {
		printf("Defina qual será o Estado Final: ");
		scanf("%d", &EstadoFinal[i]);
	}
	jmp;
//	cls;

	puts("=========================================");
	puts("||                                     ||");
	puts("|| Guia de preenchimento               ||");
	puts("||                                     ||");
	puts("|| Inserir o número do próximo estado  ||");
	puts("||                                     ||");
	puts("||  -1 para não existente              ||");
	puts("||                                     ||");
	puts("========================================");

	int tbTransition[x.qtdEstados][x.qtdAlfabeto];

	for (i = 0; i < x.qtdEstados; i++) {
		for (j = 0; j < x.qtdAlfabeto; j++) {
			printf(
					"Estado \"e%d\"\nRecebe \"%c\"\nPróximo estado: ",
					i, Alfabeto[j]);
			scanf("%d", &tbTransition[i][j]);

		}
	}

	puts("Escolha o tipo de código:");
	puts("1 - blocos de \"função\"");
	puts("2 - saltos por \"goto\"");
	scanf("%d", &bType);
	jmp;

	puts("Qual será o nome do Programa?");
	scanf("%s", programName);

	char path[200];
	path[0] = '.';
	strcat(path, "/");
	strcat(path, programName);

	//===================================================
	FILE *fp;
//	fp = fopen(path,"wt");
	fp = fopen("trab.c", "wt");

	fprintf(fp, "#include<stdio.h>\n");
	fprintf(fp, "#include<stdlib.h>\n");
	fprintf(fp, "#include<string.h>\n");
	for (i = 0; i < x.qtdEstados; i++) {
		fprintf(fp, "void e%d();\n", i);
	}
	fprintf(fp, "int main( int argc, char const *argv[]){\n");
	fprintf(fp, "    char entrada[200];\n");
	fprintf(fp, "    scanf(\"%%s\",entrada);\n");
	fprintf(fp, "    e%d();\n", x.e0);
	fprintf(fp, "    return 0;\n");
	fprintf(fp, "}\n");
	for (i = 0; i < x.qtdEstados; i++) {
		fprintf(fp, "e%d(){\n", i);
		fprintf(fp, "if(entrada[i]=='null')\n");

		//inserir a lógica de construção dos blocos

		 for(j = 0 ; j < x.qtdAlfabeto ; j++){
			if(tbTransition[i][j] == -1){
				fprintf(fp, "if(entrada[i]=='%c'){\n",tbTransition[i][j]);
				fprintf(fp, "rejeita();\n");
				fprintf(fp, "}\n");
			}else {

			}

		 }

		fprintf(fp, "}\n");
	}

	fclose(fp);

	return 0;
}
