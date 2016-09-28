#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char entrada[200];
int i = 0;

int main( int argc, char const *argv[]){

    scanf("%s",entrada);
    goto e0;

	e0: 
		if(entrada[i] == 'null') {
			goto rejeita;
		}

		if (entrada[i] == 'a') {
			goto rejeita;
		}

		if (entrada[i] == 'b') {
			goto rejeita;
		}

		if (entrada[i] == 'c') {
			i++;
			goto e1;
		}

	e1: 
		if(entrada[i] == 'null') {
			goto rejeita;
		}

		if (entrada[i] == 'a') {
			goto rejeita;
		}

		if (entrada[i] == 'b') {
			i++;
			goto e1;
		}

		if (entrada[i] == 'c') {
			i++;
			goto e2;
		}

	e2: 
		if(entrada[i] == 'null') {
			goto aceita;
		}

		if (entrada[i] == 'a') {
			i++;
			goto e2;
		}

		if (entrada[i] == 'b') {
			i++;
			goto e2;
		}

		if (entrada[i] == 'c') {
			goto rejeita;
		}

	aceita:
		puts("Aceita");
		return 0;


	rejeita:
		puts("Rejeita");
		return 0;

    return 0;
}
