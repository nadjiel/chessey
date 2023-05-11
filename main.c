/*
Atualizar turno fazendo o loop principal
Descobrir qual eh a peca escolhida
Perguntar onde deseja mover a peca
Melhorar a funcao casaDisponivel
*/

#include<stdio.h>

typedef struct tipoPeca{
	char nome;
	char jogador;
}peca;

const int FALSE = 0;
const int TRUE = 1;
const int TAMANHO_NICKNAME = 11;
const int TAMANHO_CASA = 3;
const int ORDEM = 8;
const char VAZIO = '_';
const char TORRE = 't';
const char CAVALO = 'c';
const char BISPO = 'b';
const char PEAO = 'p';
const char DAMA = 'D';
const char REI = 'R';

void iniciarTabuleiro(peca tabuleiro[ORDEM][ORDEM]){
	tabuleiro[0][0].nome = TORRE;
	tabuleiro[0][7].nome = TORRE;
	tabuleiro[7][0].nome = TORRE;
	tabuleiro[7][7].nome = TORRE;
	
	tabuleiro[0][1].nome = CAVALO;
	tabuleiro[0][6].nome = CAVALO;
	tabuleiro[7][1].nome = CAVALO;
	tabuleiro[7][6].nome = CAVALO;
	
	tabuleiro[0][2].nome = BISPO;
	tabuleiro[0][5].nome = BISPO;
	tabuleiro[7][2].nome = BISPO;
	tabuleiro[7][5].nome = BISPO;
	
	tabuleiro[0][3].nome = DAMA;
	tabuleiro[7][3].nome = DAMA;
	
	tabuleiro[0][4].nome = REI;
	tabuleiro[7][4].nome = REI;
	
	int j, k;
	for(k = 0; k < ORDEM; k++){
		tabuleiro[1][k].nome = PEAO;
		tabuleiro[6][k].nome = PEAO;
	}
	
	for(j = ORDEM-6; j < ORDEM-2; j++){
		for(k = 0; k < ORDEM; k++){
			tabuleiro[j][k].nome = VAZIO;
			tabuleiro[j][k].jogador = VAZIO;
		}
	}
	
	for(j = 0; j < ORDEM-6; j++){
		for(k = 0; k < ORDEM; k++){
			tabuleiro[j][k].jogador = '2';
		}
	}
	
	for(j = ORDEM-2; j < ORDEM; j++){
		for(k = 0; k < ORDEM; k++){
			tabuleiro[j][k].jogador = '1';
		}
	}
}

void imprimirTabuleiro(peca tabuleiro[ORDEM][ORDEM]){
	int j, k;
	for(j = 0; j < ORDEM; j++){
		for(k = 0; k < ORDEM; k++){
			printf("%c",tabuleiro[j][k].nome);
			printf("%c ",tabuleiro[j][k].jogador);
		}
		printf("\n");
	}
}

void lerNickname(char nickname[TAMANHO_NICKNAME]){
	fflush(stdin);
	printf("Informe seu nickname (de 1 a 10 caracteres e sem espaco): ");
	scanf("%s",nickname);
}

int casaDisponivel(peca tabuleiro[ORDEM][ORDEM], int turno, char casa[TAMANHO_CASA]){
	int j, k;
	switch(casa[0]){
		case 'a': j = 1;
				  break;
		case 'b': j = 2;
				  break;
		case 'c': j = 3;
				  break;
		case 'd': j = 4;
				  break;
		case 'e': j = 5;
				  break;
		case 'f': j = 6;
				  break;
		case 'g': j = 7;
				  break;
		case 'h': j = 8;
	}
	switch(casa[1]){
		case '1': k = 1;
				  break;
		case '2': k = 2;
				  break;
		case '3': k = 3;
				  break;
		case '4': k = 4;
				  break;
		case '5': k = 5;
				  break;
		case '6': k = 6;
				  break;
		case '7': k = 7;
				  break;
		case '8': k = 8;
	}
	int vez;
	if(turno % 2 == 1){
		vez = 1;
	}
	else{
		vez = 2;
	}
	if(tabuleiro[j][k].jogador == vez){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

void perguntarJogada(peca tabuleiro[ORDEM][ORDEM], int turno){
	char casa[TAMANHO_CASA];
	fflush(stdin);
	printf("Digite a coordenada da casa na qual estah a peca que voce quer mexer: ");
	scanf("%s",casa);
	while(casaDisponivel(tabuleiro, turno, casa) == FALSE){
		fflush(stdin);
		printf("Coordenada invalida. Digite outra: ");
		scanf("%s",casa);
	}
}

void main(){
	
	peca tabuleiro[ORDEM][ORDEM];
	iniciarTabuleiro(tabuleiro);
	char jogador1[TAMANHO_NICKNAME];
	char jogador2[TAMANHO_NICKNAME];
	lerNickname(jogador1);
	printf("\n");
	lerNickname(jogador1);
	printf("\n\n");
	int turno = 1;
	imprimirTabuleiro(tabuleiro);
	
	getch();
}
