#include<stdio.h>
#include<stdlib.h>
char entry[200];
int i;
int debug = 0;

void ee();
void ea();
void eb();
void ec();
void ed();
int main(){
	gets(entry);
	i = 0;
	ee();
	return 0;
}
void ee(){
	if (debug == 1)
		printf("ee -> ");
	ea();
}
void ea(){
	if (debug == 1)
		printf("ea -> ");
	if (entry[i] == 'N' || entry[i] == 'n') {
		i++;
		eb();
	}else if(entry[i] == '('){
		i++;
		ec();
		
	}
	else{
		puts("Rejeita");
		getch();
		exit(0);
	}
}
void eb(){
	if (debug == 1)
		printf("eb -> ");
	if(entry[i]=='\0'){
		puts("Aceita");
		getch();
		exit(0);
	}else if(entry[i]=='S'||entry[i]=='s'){
		i++;
		ea();
	}
	else if(entry[i]==')'||entry[i]==')'){
	}
	else{
		puts("Rejeita");
		getch();
		exit(0);
	}
	
}
void ec(){
	if (debug == 1)
		printf("ec -> ");
	ee();
	ed();
}
void ed(){
	if (debug == 1)
		printf("ed -> ");
	if(entry[i]==')'){
		i++;
		eb();
	}else{
		puts("Rejeita");
		getch();
		exit(0);
	}
}
