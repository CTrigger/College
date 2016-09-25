#include <stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<string.h>

#define jmp puts("")
#define cls system("cls")
#define green system("color A")

#define input "../In/in.txt"
#define output "../OutputGenerated/GeradoTeste.c"

typedef struct {
	int qtdAlfabeto;
	int qtdEstados;
	int e0;
	int qtdEstadoFinal;

} AFD_M;

int main(int argc, char const *argv[]) {

	setlocale(LC_ALL, "Portuguese");
	freopen(input,"r",stdin);

	AFD_M x;
	int bType;
	char programName[100];

	int i, j; // variaveis de auxilio

	//green;
	//cls;

	printf("S�o quantos simbolos: ");
	scanf("%d", &x.qtdAlfabeto);
	jmp;

	char Alfabeto[x.qtdAlfabeto];

	for (i = 0; i < x.qtdAlfabeto; i++) {
		printf("Simbolo %d: ", i);
		scanf(" %c", &Alfabeto[i]);
	}
	jmp;

	printf("S�o quantos estados: ");
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
		printf("Defina qual ser� o Estado Final: ");
		scanf("%d", &EstadoFinal[i]);
	}
	jmp;
//	cls;

	puts("=========================================");
	puts("||                                     ||");
	puts("|| Guia de preenchimento               ||");
	puts("||                                     ||");
	puts("|| Inserir o n�mero do pr�ximo estado  ||");
	puts("||                                     ||");
	puts("||  -1 para n�o existente              ||");
	puts("||                                     ||");
	puts("========================================");

	int tbTransition[x.qtdEstados][x.qtdAlfabeto];

	for (i = 0; i < x.qtdEstados; i++,jmp) {
		for (j = 0; j < x.qtdAlfabeto; j++) {
			printf("Estado \"e%d\"\nRecebe \"%c\"\nPr�ximo estado: ", i,
					Alfabeto[j]);
			scanf("%d", &tbTransition[i][j]);

		}
	}

	puts("Escolha o tipo de c�digo:");
	puts("1 - blocos de \"fun��o\"");
	puts("2 - saltos por \"goto\"");
	scanf("%d", &bType);
	jmp;

	puts("Qual ser� o nome do Programa?");
	scanf("%s", programName);
	int equal;
	char path[200];
	path[0] = '.';
	strcat(path, "/");
	strcat(path, programName);

	//===================================================
	FILE *fp;
//	fp = fopen(path,"wt");
	fp = fopen(output, "wt");

	fprintf(fp, "#include<stdio.h>\n");
	fprintf(fp, "#include<stdlib.h>\n");
	fprintf(fp, "#include<string.h>\n");
	for (i = 0; i < x.qtdEstados; i++) {
		fprintf(fp, "void e%d();\n", i);
	}
	fprintf(fp, "void aceita();\n");
	fprintf(fp, "void rejeita();\n");
	fprintf(fp, "char entrada[200];\n");
	fprintf(fp, "int i = 0;\n\n\n\n");
	fprintf(fp, "int main( int argc, char const *argv[]){\n");
	fprintf(fp, "\n");
	fprintf(fp, "    scanf(\"%%s\",entrada);\n");
	fprintf(fp, "    e%d();\n", x.e0);
	fprintf(fp, "    return 0;\n");
	fprintf(fp, "}\n");

	for (i = 0; i < x.qtdEstados; i++) {

		for (j = 0; j < x.qtdEstadoFinal; j++) {
			if (i == EstadoFinal[j]) {
				equal = j;
				break;
			} else {
				equal = -1;
			}
		}


		fprintf(fp, "e%d() {\n", i);
		fprintf(fp, "	if(entrada[i] == 'null') {\n");
		if (i == EstadoFinal[equal]) {
			fprintf(fp, "		aceita();\n");
		} else {
			fprintf(fp, "		rejeita();\n");
		}
		fprintf(fp, "	}\n");

		//inserir a l�gica de constru��o dos blocos

		for (j = 0; j < x.qtdAlfabeto; j++) {
			if (tbTransition[i][j] == -1) {
				fprintf(fp, "	if (entrada[i] == '%c') {\n", Alfabeto[j]);
				fprintf(fp, "		rejeita();\n");
				fprintf(fp, "	}\n");
			} else {
				fprintf(fp, "	if (entrada[i] == '%c') {\n", Alfabeto[j]);
				fprintf(fp, "		i++;\n");
				fprintf(fp, "		e%d();\n", tbTransition[i][j]);
				fprintf(fp, "	}\n");
			}

		}

		fprintf(fp, "}\n");
	}
	fprintf(fp, "aceita(){\n");
	fprintf(fp, "	puts(\"Aceita\");\n");
	fprintf(fp, "	exit(0);\n");
	fprintf(fp, "}\n\n");

	fprintf(fp, "rejeita(){\n");
	fprintf(fp, "	puts(\"Rejeita\");\n");
	fprintf(fp, "	exit(0);\n");
	fprintf(fp, "}\n");

	fclose(fp);

	return 0;
}