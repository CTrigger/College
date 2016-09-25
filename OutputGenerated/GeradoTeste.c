#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void e0();
void e1();
void e2();
void aceita();
void rejeita();
char entrada[200];
int i = 0;



int main( int argc, char const *argv[]){

    scanf("%s",entrada);
    e0();
    return 0;
}
e0() {
	if(entrada[i] == 'null') {
		rejeita();
	}
	if (entrada[i] == 'a') {
		i++;
		rejeita();
	}
	if (entrada[i] == 'b') {
		i++;
		rejeita();
	}
	if (entrada[i] == 'c') {
		i++;
		e1();
	}
}
e1() {
	if(entrada[i] == 'null') {
		rejeita();
	}
	if (entrada[i] == 'a') {
		i++;
		rejeita();
	}
	if (entrada[i] == 'b') {
		i++;
		e1();
	}
	if (entrada[i] == 'c') {
		i++;
		e2();
	}
}
e2() {
	if(entrada[i] == 'null') {
		aceita();
	}
	if (entrada[i] == 'a') {
		i++;
		e2();
	}
	if (entrada[i] == 'b') {
		i++;
		e2();
	}
	if (entrada[i] == 'c') {
		i++;
		rejeita();
	}
}
aceita(){
	puts("Aceita");
	exit(0);
}

rejeita(){
	puts("Rejeita");
	exit(0);
}
