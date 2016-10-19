#include<stdio.h>
#include<string.h>

void e0();
void e1();
void e2();
void e3();
void e4();
void e5();
void e6();

char In;
char S[200];
int N;
int i = 0;

int main(int argc, char **argv) {

	e0();

	return 0;
}

void e0() {
	while (scanf("%c ", &In) != EOF) {

		if (('a' <= In && In <= 'z') || ('A' <= In && In <= 'Z')) {
			//step 1
			S[i] = In;
			i++;
			e1();
		} else if ('0' <= In && In <= '9') {
			//step 4
			N = atoi(In);
			e2();
		} else if (In == ':') {
			//step 7
			printf("%c", In);
			e3();
		} else if (In == '%') {
			e5();
		} else {
			e6();
		}

	}
}

void e1() {
	while (scanf("%c ", &In) != ' ') {
		if (('a' <= In && In <= 'z') || ('A' <= In && In <= 'Z')
				|| ('0' <= In && In <= '9')) {
			//step 2
			S[i] = In;
			i++;
		} else {
			break;
		}

	}
	//step 3
	//printf processo de saida

	e0();
}

void e2() {
	//step 5
	scanf("%c ", &In);
	if ('0' <= In && In <= '9') {
		N = N * 10 + atoi(In);
		e2();
	} else {
		//step 6
		printf("N(%d)", N);
	}
	e0();

}

void e3() {
	scanf("%c ", &In);
	if (In == '=') {
		//step 8
		e4();
	}
	e0();
}

void e4() {
	printf("%c", In);
	e0();
}

void e5() {
	scanf("%c ", &In);
	if (In == '\\') {
		scanf("%c ", &In);
		if (In == 'n') {
			puts ("");
		}
		if (In == '0'){
			puts ("Fim");
		}

	}
	e0();
}

void e6() {
	printf("C(%c)", In);
	e0();
}
