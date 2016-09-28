#include <stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<string.h>

//Macros setup, all system commands works only in windows
#define jmp puts("")
#define cls system("cls")
#define green system("color A")
#define max 100


//i used this to generate fastest the files.c
/*
#define input "../In/in.txt"
#define input "in.txt"
*/


//memory reserved
void cmGoto(); //command Goto
void cmFunc(); //command Function


//i decided use the File struct as global variable
FILE *fp;


//made this to make less work using the "intellisense" in Eclipse
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



int main(int argc, char **argv) {
	//used this only to void my inputs
	//freopen(input,"r",stdin);

	//setup to portuguese program
	setlocale(LC_ALL, "Portuguese");

	AFD_M x;
	int i, j; //support variable

	//=======here we start the interactions with the users======
	//symbols setup
	printf("São quantos simbolos: ");
	scanf("%d", &x.qtdAlfabeto);
	jmp;

	//declare whats symbols exists
	for (i = 0; i < x.qtdAlfabeto; i++) {
		printf("Simbolo %d: ", i);
		scanf(" %c", &x.Alfabeto[i]);
	}
	jmp;

	//numbers states define
	printf("São quantos estados: ");
	scanf("%d", &x.qtdEstados);
	jmp;

	//what is the initial state?
	printf("Qual estado inicial: ");
	scanf("%d", &x.e0);
	jmp;

	//how much final states we have?
	printf("Quantos estados finais: ");
	scanf("%d", &x.qtdEstadoFinal);
	jmp;

	//define the final states
	for (i = 0; i < x.qtdEstadoFinal; i++) {
		printf("Defina qual será o Estado Final: ");
		scanf("%d", &x.EstadoFinal[i]);
	}
	jmp;

	//transistion table setup
	for (i = 0; i < x.qtdEstados; i++, jmp) {
		for (j = 0; j < x.qtdAlfabeto; j++) {
			printf("Estado \"e%d\"\nRecebe \"%c\"\nPróximo estado: ", i,
					x.Alfabeto[j]);
			scanf("%d", &x.tbTransition[i][j]);

		}
	}
	jmp;

	//choose what kind command want?
	//1-command function
	//2-command goto
	puts("Escolha o tipo de código:");
	puts("1 - blocos de \"função\"");
	puts("2 - saltos por \"goto\"");
	scanf("%d", &x.bType);
	jmp;

	//this will clean the scanf garbage
	//CrLf
	char dummie;
	while((dummie= getchar()) != '\n' && dummie != EOF);

	//choose the program name
	puts("Qual será o nome do Programa?");
	//scanf("%s", x.programName);
	gets(x.programName);
	jmp;

	//=======user interaction ending.===========

	//============================================
	//this will prepare custom name for the program
	char *filename;
	filename = (char*) malloc(60*sizeof(char));
	sprintf(filename, "./%s.c",x.programName);

	fp = fopen(filename, "wt");
	//============================================


	//option select
	if (x.bType == 1) {
		cmFunc(x);
		fclose(fp);
	}
	if (x.bType == 2) {
		cmGoto(x);
		fclose(fp);
	}

	puts("Arquivo Gerado!");
	printf("Gerado em \"%s\"\n",filename);
	system("pause");
	return 0;
}

void cmFunc(AFD_M bdFunc) {

	int i, j, equal;

	//include libraries
	fprintf(fp, "#include<stdio.h>\n");
	fprintf(fp, "#include<stdlib.h>\n");
	fprintf(fp, "#include<string.h>\n");

	//reservas de endereço
	for (i = 0; i < bdFunc.qtdEstados; i++) {
		fprintf(fp, "void e%d();\n", i);
	}
	fprintf(fp, "void aceita();\n");
	fprintf(fp, "void rejeita();\n");

	//variaveis globais
	fprintf(fp, "char entrada[200];\n");
	fprintf(fp, "int i = 0;\n\n");

	//int main
	fprintf(fp, "int main( int argc, char const *argv[]){\n");
	fprintf(fp, "\n");
	fprintf(fp, "    scanf(\"%%s\",entrada);\n");
	fprintf(fp, "    e%d();\n", bdFunc.e0);
	fprintf(fp, "    return 0;\n");
	fprintf(fp, "}\n");

	//gera todos os estados definidos
	for (i = 0; i < bdFunc.qtdEstados; i++) {

		//busca estados finais possíveis
		for (j = 0; j < bdFunc.qtdEstadoFinal; j++) {
			if (i == bdFunc.EstadoFinal[j]) {
				equal = j;
				break;
			} else {
				equal = -1;
			}
		}

		//cria bloco
		fprintf(fp, "void e%d() {\n", i);
		fprintf(fp, "	if(entrada[i] == '\\0') {\n");
		if (i == bdFunc.EstadoFinal[equal] && equal != -1) {
			fprintf(fp, "		aceita();\n");
		} else {
			fprintf(fp, "		rejeita();\n");
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

	//blocos finais
	fprintf(fp, "void aceita(){\n");
	fprintf(fp, "	puts(\"Aceita\");\n");
	fprintf(fp, "	exit(0);\n");
	fprintf(fp, "}\n\n");

	fprintf(fp, "void rejeita(){\n");
	fprintf(fp, "	puts(\"Rejeita\");\n");
	fprintf(fp, "	exit(0);\n");
	fprintf(fp, "}\n");
}

void cmGoto(AFD_M bdGoto) {
	int i, j, equal;

	// include libraries
	fprintf(fp, "#include<stdio.h>\n");
	fprintf(fp, "#include<stdlib.h>\n");
	fprintf(fp, "#include<string.h>\n");

	//Global Variable
	fprintf(fp, "char entrada[200];\n");
	fprintf(fp, "int i = 0;\n\n");


	//int main
	fprintf(fp, "int main( int argc, char const *argv[]){\n");
	fprintf(fp, "\n");
	fprintf(fp, "    scanf(\"%%s\",entrada);\n");
	fprintf(fp, "    goto e%d;\n\n", bdGoto.e0);


		//lógica GOTO
		for (i = 0; i < bdGoto.qtdEstados; i++) {

			//busca estados validos
			for (j = 0; j < bdGoto.qtdEstadoFinal; j++) {
				if (i == bdGoto.EstadoFinal[j]) {
					equal = j;
					break;
				} else {
					equal = -1;
				}
			}

			//goto Estado
			fprintf(fp, "	e%d: \n", i);

			//goto Estado Ending?
			fprintf(fp, "		if(entrada[i] == '\\0') {\n");
			if (i == bdGoto.EstadoFinal[equal] && equal != -1) {
				fprintf(fp, "			goto aceita;\n");
			} else {
				fprintf(fp, "			goto rejeita;\n");
			}
			fprintf(fp, "		}\n\n");

			//goto check
			for (j = 0; j < bdGoto.qtdAlfabeto; j++) {
				if (bdGoto.tbTransition[i][j] == -1) {
					fprintf(fp, "		if (entrada[i] == '%c') {\n", bdGoto.Alfabeto[j]);
					fprintf(fp, "			goto rejeita;\n");
					fprintf(fp, "		}\n\n");
				} else {
					fprintf(fp, "		if (entrada[i] == '%c') {\n", bdGoto.Alfabeto[j]);
					fprintf(fp, "			i++;\n");
					fprintf(fp, "			goto e%d;\n", bdGoto.tbTransition[i][j]);
					fprintf(fp, "		}\n\n");
				}

			}

		}


		//Goto Final
		fprintf(fp, "	aceita:\n");
		fprintf(fp, "		puts(\"Aceita\");\n");
		fprintf(fp, "		return 0;\n");
		fprintf(fp, "\n\n");

		fprintf(fp, "	rejeita:\n");
		fprintf(fp, "		puts(\"Rejeita\");\n");
		fprintf(fp, "		return 0;\n");
		fprintf(fp, "\n");

	//end program
	fprintf(fp, "    return 0;\n");
	fprintf(fp, "}\n");


}
