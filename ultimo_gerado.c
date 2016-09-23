#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void e0();
void e1();
void e2();
void e3();
void aceita();
void rejeita();
char entrada[200];
int i = 0;



int main( int argc, char const *argv[]){

    scanf("%s",entrada);
    e0();
    return 0;
}
e0(){
	if(entrada[i]=='null'){
		rejeita();
	}
	if(entrada[i]=='a'){
		i++;
		rejeita();
	}
	if(entrada[i]=='b'){
		e0();
	}
	if(entrada[i]=='c'){
		e1();
	}
}
e1(){
	if(entrada[i]=='null'){
		rejeita();
	}
	if(entrada[i]=='a'){
		e0();
	}
	if(entrada[i]=='b'){
		e0();
	}
	if(entrada[i]=='c'){
		e2();
	}
}
e2(){
	if(entrada[i]=='null'){
		rejeita();
	}
	if(entrada[i]=='a'){
		i++;
		rejeita();
	}
	if(entrada[i]=='b'){
		e1();
	}
	if(entrada[i]=='c'){
		e3();
	}
}
e3(){
	if(entrada[i]=='null'){
		rejeita();
	}
	if(entrada[i]=='a'){
		e3();
	}
	if(entrada[i]=='b'){
		e3();
	}
	if(entrada[i]=='c'){
		e3();
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
