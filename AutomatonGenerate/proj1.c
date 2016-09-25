#include <stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<string.h>

#define jmp puts("")
#define cls system("cls")
#define green system("color A")
#define max 100

 #define input "../In/in.txt"
 #define output "../OutputGenerated/GeradoTeste.c"

/*
#define input "in.txt"
#define output "GeradoTeste.c"
*/

FILE *fp;

typedef struct {
	int qtdAlfabeto;
	int qtdEstados;
	int e0;
	int qtdEstadoFinal;

	char Alfabeto[max];
	int EstadoFinal[max];

	int bType;

	int tbTransition[max][max];

	char programName[max];

} AFD_M;

void cmGoto();
void cmFunc();

int main(int argc, char **argv) {

	//freopen(input,"r",stdin);
	setlocale(LC_ALL, "Portuguese");

	AFD_M x;
	int i, j;

	//inicio da interface de escolhas
	printf("São quantos simbolos: ");
	scanf("%d", &x.qtdAlfabeto);
	jmp;

	for (i = 0; i < x.qtdAlfabeto; i++) {
		printf("Simbolo %d: ", i);
		scanf(" %c", &x.Alfabeto[i]);
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

	for (i = 0; i < x.qtdEstadoFinal; i++) {
		printf("Defina qual será o Estado Final: ");
		scanf("%d", &x.EstadoFinal[i]);
	}
	jmp;

	for (i = 0; i < x.qtdEstados; i++, jmp) {
		for (j = 0; j < x.qtdAlfabeto; j++) {
			printf("Estado \"e%d\"\nRecebe \"%c\"\nPróximo estado: ", i,
					x.Alfabeto[j]);
			scanf("%d", &x.tbTransition[i][j]);

		}
	}
	jmp;

	puts("Escolha o tipo de código:");
	puts("1 - blocos de \"função\"");
	puts("2 - saltos por \"goto\"");
	scanf("%d", &x.bType);
	jmp;

	puts("Qual será o nome do Programa?");
	scanf("%s", x.programName);
	jmp;

	// Fim da interface de entrada.

	//Gerar Arquivos

	if (x.bType == 1) {
		fp = fopen(output, "wt");
		cmFunc(x);
		fclose(fp);
	}
	if (x.bType == 2) {
		fp = fopen(output, "wt");
		cmGoto(x);
		fclose(fp);
	}

	//Fim da geração

	system("pause");
	return 0;
}

void cmFunc(AFD_M bdFunc) {

	int i, j, equal;
	fprintf(fp, "#include<stdio.h>\n");
	fprintf(fp, "#include<stdlib.h>\n");
	fprintf(fp, "#include<string.h>\n");
	for (i = 0; i < bdFunc.qtdEstados; i++) {
		fprintf(fp, "void e%d();\n", i);
	}
	fprintf(fp, "void aceita();\n");
	fprintf(fp, "void rejeita();\n");
	fprintf(fp, "char entrada[200];\n");
	fprintf(fp, "int i = 0;\n\n");

	fprintf(fp, "int main( int argc, char const *argv[]){\n");
	fprintf(fp, "\n");
	fprintf(fp, "    scanf(\"%%s\",entrada);\n");
	fprintf(fp, "    e%d();\n", bdFunc.e0);
	fprintf(fp, "    return 0;\n");
	fprintf(fp, "}\n");

	for (i = 0; i < bdFunc.qtdEstados; i++) {

		for (j = 0; j < bdFunc.qtdEstadoFinal; j++) {
			if (i == bdFunc.EstadoFinal[j]) {
				equal = j;
				break;
			} else {
				equal = -1;
			}
		}

		fprintf(fp, "void e%d() {\n", i);
		fprintf(fp, "	if(entrada[i] == 'null') {\n");
		if (equal != -1) {
			if (i == bdFunc.EstadoFinal[equal]) {
				fprintf(fp, "		aceita();\n");
			} else {
				fprintf(fp, "		rejeita();\n");
			}
		}
		fprintf(fp, "	}\n");

		//inserir a lógica de construção dos blocos

		for (j = 0; j < bdFunc.qtdAlfabeto; j++) {
			if (bdFunc.tbTransition[i][j] == -1) {
				fprintf(fp, "	if (entrada[i] == '%c') {\n", bdFunc.Alfabeto[j]);
				fprintf(fp, "		rejeita();\n");
				fprintf(fp, "	}\n");
			} else {
				fprintf(fp, "	if (entrada[i] == '%c') {\n", bdFunc.Alfabeto[j]);
				fprintf(fp, "		i++;\n");
				fprintf(fp, "		e%d();\n", bdFunc.tbTransition[i][j]);
				fprintf(fp, "	}\n");
			}

		}

		fprintf(fp, "}\n");
	}
	fprintf(fp, "void aceita(){\n");
	fprintf(fp, "	puts(\"Aceita\");\n");
	fprintf(fp, "	exit(0);\n");
	fprintf(fp, "}\n\n");

	fprintf(fp, "void rejeita(){\n");
	fprintf(fp, "	puts(\"Rejeita\");\n");
	fprintf(fp, "	exit(0);\n");
	fprintf(fp, "}\n");
}

void cmGoto(AFD_M x) {

}
