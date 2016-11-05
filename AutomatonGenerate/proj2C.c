#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define word *(entry+i)

char In[200];
char **entry;
char S[200];
int N;
int i;
int variavel = 0;

void palavras_reservadas();
void e0();
void e1();
void e2();
void e3();
void e4();
void e5();
void e6();

typedef struct {
	char palavra[10];
} private;
private reserva[9];

char** str_split(char* a_str, const char a_delim) {
	char** result = 0;
	size_t count = 0;
	char* tmp = a_str;
	char* last_comma = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;

	/* Count how many elements will be extracted. */
	while (*tmp) {
		if (a_delim == *tmp) {
			count++;
			last_comma = tmp;
		}
		tmp++;
	}

	/* Add space for trailing token. */
	count += last_comma < (a_str + strlen(a_str) - 1);

	/* Add space for terminating null string so caller
	 knows where the list of returned strings ends. */
	count++;

	result = malloc(sizeof(char*) * count);

	if (result) {
		size_t idx = 0;
		char* token = strtok(a_str, delim);

		while (token) {
			assert(idx < count);
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}
		assert(idx == count - 1);
		*(result + idx) = 0;
	}

	return result;
}

int testReserva(char key[]) {
	int j;
	for (j = 0; j < 9; j++) {
		if (strcmp(reserva[j].palavra, key) == 0) {
			printf("P(%d) ", j + 1);

			return 1;
		}
	}
	return 0;
}

int main(int argc, char **argv) {
	//setup das palavras reservadas;
	palavras_reservadas();

	//action
	e0();

	return 0;
}

void palavras_reservadas() {
	strcat(reserva[0].palavra, "if");
	strcat(reserva[1].palavra, "else");
	strcat(reserva[2].palavra, "then");
	strcat(reserva[3].palavra, "goto");
	strcat(reserva[4].palavra, "let");
	strcat(reserva[5].palavra, "print");
	strcat(reserva[6].palavra, "read");
	strcat(reserva[7].palavra, "end");
	strcat(reserva[8].palavra, "of");
	int k;
	puts("Palavras reservadas.");
	for (k = 0; k < 9; k++) {
		printf("%d. %s\n", k , reserva[k].palavra);
	}
	puts("");
}

void e0() {
	gets(In);
	entry = str_split(In, ' ');

	if (entry) {
		for (i = 0; word; i++) {
			if (testReserva(word) == 0) {

				if (('a' <= word[0] && word[0] <= 'z')
						|| ('A' <= word[0] && word[0] <= 'Z')) {
					//		puts("step e1");
					e1();

				} else if ('0' <= word[0] && word[0] <= '9') {
					//		puts("step e2");
					e2();

				} else if (word[0] == ':') {
					//		puts("step e3");
					printf("%c ", word[0]);
					e3();

				} else if (word[0] == '%') {
					//		puts("step e5");
					e5();

				} else {
					//		puts("step e6");
					e6();

				}

			}

			free(word);
		}
		printf("\n");
		free(entry);
	}

	system("pause");
	exit(0);

}

void e1() {
	printf("V(%d) ", variavel);
	variavel ++;
}

void e2() {
	printf("N(%s) ", *(entry + i));
}

void e3() {
	if (*(entry + i)[0] == '=') {
		//step 8
		e4();
	}
}

void e4(int tmp) {
	printf("P(%d)", tmp);
}

void e5() {
	if (*(entry + i)[0] == '\\') {
		if (*(entry + i)[0] == 'n') {
			puts("");
		}
		if (*(entry + i)[0] == '0') {
			puts("Fim");
		}

	}
}

void e6() {
	printf("%s ", *(entry + i));
}
