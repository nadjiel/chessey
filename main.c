#include<stdio.h>

const int ORDEM = 8;
const int CARAC_PECAS = 2;
const char VAZIO = '_';
const char TORRE = 't';
const char CAVALO = 'c';
const char BISPO = 'b';
const char PEAO = 'p';
const char DAMA = 'D';
const char REI = 'R';

void iniciarTabuleiro(char tabuleiro[CARAC_PECAS][ORDEM][ORDEM]){
	tabuleiro[0][0][0] = TORRE;
	tabuleiro[0][0][7] = TORRE;
	tabuleiro[0][7][0] = TORRE;
	tabuleiro[0][7][7] = TORRE;
	
	tabuleiro[0][0][1] = CAVALO;
	tabuleiro[0][0][6] = CAVALO;
	tabuleiro[0][7][1] = CAVALO;
	tabuleiro[0][7][6] = CAVALO;
	
	tabuleiro[0][0][2] = BISPO;
	tabuleiro[0][0][5] = BISPO;
	tabuleiro[0][7][2] = BISPO;
	tabuleiro[0][7][5] = BISPO;
	
	tabuleiro[0][0][3] = DAMA;
	tabuleiro[0][7][3] = DAMA;
	
	tabuleiro[0][0][4] = REI;
	tabuleiro[0][7][4] = REI;
	
	int j, k;
	for(k = 0; k < ORDEM; k++){
		tabuleiro[0][1][k] = PEAO;
		tabuleiro[0][6][k] = PEAO;
	}
	
	for(j = ORDEM-6; j < ORDEM-2; j++){
		for(k = 0; k < ORDEM; k++){
			tabuleiro[0][j][k] = VAZIO;
			tabuleiro[1][j][k] = VAZIO;
		}
	}
	
	for(j = 0; j < ORDEM-6; j++){
		for(k = 0; k < ORDEM; k++){
			tabuleiro[1][j][k] = '2';
		}
	}
	
	for(j = ORDEM-2; j < ORDEM; j++){
		for(k = 0; k < ORDEM; k++){
			tabuleiro[1][j][k] = '1';
		}
	}
}

void imprimirTabuleiro(char tabuleiro[CARAC_PECAS][ORDEM][ORDEM]){
	int j, k;
	for(j = 0; j < ORDEM; j++){
		for(k = 0; k < ORDEM; k++){
			printf("%c",tabuleiro[0][j][k]);
			printf("%c ",tabuleiro[1][j][k]);
		}
		printf("\n");
	}
}

void main(){
	
	char tabuleiro[CARAC_PECAS][ORDEM][ORDEM];
	iniciarTabuleiro(tabuleiro);
	imprimirTabuleiro(tabuleiro);
	
	getch();
}
