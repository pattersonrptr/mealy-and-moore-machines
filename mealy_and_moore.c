#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool palavra_aceita = true;

void mealy(char *);
void moore(char *);

void clrscr(void);
void fclear(void);

int main() {

    char palavra[50], ch = '\0', op = '\0';

	do {

		do {
			clrscr();
			printf("\nEscolha uma máquina\n\nMealy [0]\nMoore [1]\n");
			fclear();
			scanf("%c", &op);
			
			printf("\n\n");
			
			if(op == '0')
				mealy(palavra);
			else
				if(op == '1') 
					moore(palavra);
			else 
				printf("Opcao invalida %c", op);
					
		} while(op != '1' && op != '0');

		do {

            printf("\n\nLer outra palavra? ( [S] | [n] )");
            fclear(); // Limpa o buffer
            ch = getchar();

		} while (tolower( ch ) != 'n' &&
                 tolower( ch ) != 's');

	} while( tolower( ch ) == 's' );

	return EXIT_SUCCESS;
} // FIM MAIN

// =====================================================================

/**
 * Implementa a máquina de Mealy
*/
void mealy(char * palavra) {
	
	palavra_aceita = true;
	
	printf("Palavra: ");
	fclear();
	scanf("%s", palavra);

	palavra_aceita = true;
	int estado = 0;

	int i = 0;
	for (i = 0; i < strlen(palavra); i++) {

		switch(palavra[i]) {
			case 'a':
				switch(estado) {
					case 0:
						puts("q0 -- a : 0 --> q1");
						estado = 1;
					break;

					case 1:
						puts("q1 -- a : 1 --> q3");
						estado = 3;
					break;

					case 2:
						puts("q2 -- a : 0 --> q3");
						estado = 3;
					break;

					case 3:
						puts("q3 -- a : 1 --> q3");
						estado = 3;
					break;
				}
			break;

			case 'b':
				switch(estado) {
					case 0:
						puts("q0 -- b : 0 --> q3");
						estado = 3;
					break;

					case 1:
						puts("q1 -- b : 1 --> q2");
						estado = 2;
					break;

					case 2:
						puts("q2 -- b : 1 --> q3");
						estado = 3;
					break;

					case 3:
						puts("q3 -- b : 1 --> q0");
						estado = 0;
					break;
				}
			break;

			default:
				printf("\nPalavra rejeitada.\n");
				palavra_aceita = false;
			break;
		}

		if (! palavra_aceita) break;
	}

}

/**
 * Implementa a máquina de Moore
*/
void moore(char * palavra) {
	
	palavra_aceita = true;
	
	printf("Palavra: ");
		fclear();
		scanf("%s", palavra);

	palavra_aceita = true;
	int estado = 0;

	int i = 0;
	for (i = 0; i <= strlen(palavra); i++) {

		switch(estado) {
			case 0:
				printf("0\t");
				
				if (palavra[i] == '\0') break;

				switch(palavra[i]) {
					case 'a':
						printf("q0 -- a --> q1\n");
						estado = 1;
					break;

					case 'b':
						printf("q0 -- b --> q3\n");
						estado = 3;
					break;

					default:
						printf("\nErro: %c. Simbulo não existe no alfabeto\n", palavra[i]);
						palavra_aceita = false;
					break;
				}
			break;

			case 1:
				printf("1\t");

				if (palavra[i] == '\0') break;

				switch(palavra[i]) {
					case 'a':
						printf("q1 -- a --> q3\n");
						estado = 3;
					break;

					case 'b':
						printf("q1 -- b --> q2\n");
						estado = 2;
					break;

					default:
						printf("\nErro: %c. Simbulo não existe no alfabeto\n", palavra[i]);
						palavra_aceita = false;
					break;
				}
			break;

			case 2:
				printf("0\t");
				
				if (palavra[i] == '\0') break;

				switch(palavra[i]) {
					case 'a':
						printf("q2 -- a --> q3\n");
						estado = 3;
					break;

					case 'b':
						printf("q2 -- b --> q3\n");
						estado = 3;
					break;

					default:
						printf("\nErro: %c. Simbulo não existe no alfabeto\n", palavra[i]);
						palavra_aceita = false;
					break;
				}
			break;

			case 3:
				printf("1\t");
				
				if (palavra[i] == '\0') break;

				switch(palavra[i]) {
					case 'a':
						printf("q3 -- a --> q3\n");
						estado = 3;
					break;

					case 'b':
						printf("q3 -- b --> q0\n");
						estado = 0;
					break;

					default:
						printf("\nErro: %c. Simbulo não existe no alfabeto\n", palavra[i]);
						palavra_aceita = false;
					break;
				}
			break;
		}
		if (! palavra_aceita) break;
	}
	
	if (! palavra_aceita ) printf("\nPalavra rejeitada.");
}

/**
* Limpa a tela usando comandos do SO onde foi compilado.
*/
void clrscr(void) {

    #ifdef OS_WINDOWS // Para Windows
        system("cls");
    #else             // Para sistemas Linux e UNIX
       system("clear");
    #endif
}

/**
* Limpa o buffer do teclado usando comandos do SO onde foi compilado.
*/
void fclear(void) {

    #ifdef OS_WINDOWS // Para Windows
        fflush(stdin);
    #else             // Para sistemas Linux e UNIX
       __fpurge(stdin);
    #endif
}
