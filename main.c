/*
Atualizar turno fazendo o loop principal
Continuar trabalhando no procedimento perguntarJogada()
Fazer casos nos quais outras pecas foram escolhidas
Fazer os eventos especiais, tipo xeque, roque
*/

#include<stdio.h>

typedef struct tipoPeca{
	char nome;
	char jogador;
	int jogadas;
}peca;

const int ERRO = 0;
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
	
	for(j = 0; j < ORDEM; j++){
		for(k = 0; k < ORDEM; k++){
			tabuleiro[j][k].jogadas = 0;
		}
	}
}

int coordCharPraCoordInt(char coord){
	switch(coord){
		case 'a': return 1;
		case 'b': return 2;
		case 'c': return 3;
		case 'd': return 4;
		case 'e': return 5;
		case 'f': return 6;
		case 'g': return 7;
		case 'h': return 8;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		default: return ERRO;
	}
}

void imprimirTabuleiro(peca tabuleiro[ORDEM][ORDEM]){
	int j, k;
	printf("    a  b  c  d  e  f  g  h");
	printf("\n\n");
	int cont = 0;
	for(j = 0; j < ORDEM; j++){
		cont++;
		printf("%d   ",cont);
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

int verifVez(int turno){
	if(turno % 2 == 1){
		return 1;
	}
	else{
		return 2;
	}
}

char vezIntPraVezChar(int vez){
	switch(vez){
		case 1: return '1';
		case 2: return '2';
	}
}

int casaPartidaDisponivel(peca tabuleiro[ORDEM][ORDEM], int turno, char casa[TAMANHO_CASA]){
	int j, k;
	j = coordCharPraCoordInt(casa[1]);
	k = coordCharPraCoordInt(casa[0]);
	if(j == ERRO || k == ERRO){
		return FALSE;
	}
	else{
		int vez = verifVez(turno);
		if(tabuleiro[j-1][k-1].jogador == vezIntPraVezChar(vez)){
			return TRUE;
		}
		else{
			return FALSE;
		}
	}
}

int casaChegadaDisponivel(peca tabuleiro[ORDEM][ORDEM], int turno, char casa[TAMANHO_CASA]){
	int j, k;
	j = coordCharPraCoordInt(casa[1]);
	k = coordCharPraCoordInt(casa[0]);
	if(j == ERRO || k == ERRO){
		return FALSE;
	}
	else{
		int vez = verifVez(turno);
		if(tabuleiro[j-1][k-1].jogador != vezIntPraVezChar(vez)){
			return TRUE;
		}
		else{
			return FALSE;
		}
	}
}

char verifPeca(peca tabuleiro[ORDEM][ORDEM], char casa[TAMANHO_CASA]){
	int j = coordCharPraCoordInt(casa[1]) - 1;
	int k = coordCharPraCoordInt(casa[0]) - 1;
	return tabuleiro[j][k].nome;
}

int movimentoDisponivelTorre(peca tabuleiro[ORDEM][ORDEM], char casaPartida[TAMANHO_CASA], char casaChegada[TAMANHO_CASA]){
	if((casaPartida[0] != casaChegada[0]) && (casaPartida[1] != casaChegada[1])){
		return FALSE;
	}
	if(casaPartida[0] == casaChegada[0]){
		int jInicial = coordCharPraCoordInt(casaPartida[1]) - 1;
		int jFinal = coordCharPraCoordInt(casaChegada[1]) - 1;
		int k = coordCharPraCoordInt(casaPartida[0]) - 1;
		if(jInicial > jFinal){
			for(jInicial++; jInicial > jFinal; jInicial--){
				if((tabuleiro[jInicial][k].jogador == '1') || (tabuleiro[jInicial][k].jogador == '2')){
					return FALSE;
				}
			}
		}
		if(jInicial < jFinal){
			for(jInicial++; jInicial < jFinal; jInicial++){
				if((tabuleiro[jInicial][k].jogador == '1') || (tabuleiro[jInicial][k].jogador == '2')){
					return FALSE;
				}
			}
		}
	}
	if(casaPartida[1] == casaChegada[1]){
		int kInicial = coordCharPraCoordInt(casaPartida[0]) - 1;
		int kFinal = coordCharPraCoordInt(casaChegada[0]) - 1;
		int j = coordCharPraCoordInt(casaPartida[1]) - 1;
		if(kInicial > kFinal){
			for(kInicial++; kInicial > kFinal; kInicial--){
				if((tabuleiro[j][kInicial].jogador == '1') || (tabuleiro[j][kInicial].jogador == '2')){
					return FALSE;
				}
			}
		}
		if(kInicial < kFinal){
			for(kInicial++; kInicial < kFinal; kInicial++){
				if((tabuleiro[j][kInicial].jogador == '1') || (tabuleiro[j][kInicial].jogador == '2')){
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}

void perguntarJogada(peca tabuleiro[ORDEM][ORDEM], int turno){
	char casaPartida[TAMANHO_CASA];
	fflush(stdin);
	printf("\nDigite a coordenada da casa na qual estah a peca que voce quer mexer: ");
	scanf("%s",casaPartida);
	while(casaPartidaDisponivel(tabuleiro, turno, casaPartida) == FALSE){
		fflush(stdin);
		printf("Coordenada invalida. Digite outra: ");
		scanf("%s",casaPartida);
	}
	char pecaEscolhida = verifPeca(tabuleiro, casaPartida);
	char casaChegada[TAMANHO_CASA];
	fflush(stdin);
	printf("\nPara qual casa voce quer mecher essa peca? ");
	scanf("%s",casaChegada);
	int movimentoDisponivel;
	do{
		while(casaChegadaDisponivel(tabuleiro, turno, casaChegada) == FALSE){
			fflush(stdin);
			printf("Coordenada invalida. Digite outra: ");
			scanf("%s",casaChegada);
		}
		if(pecaEscolhida == TORRE){
			if(movimentoDisponivelTorre(tabuleiro, casaPartida, casaChegada) == FALSE){
				movimentoDisponivel = FALSE;
			}
			else{
				movimentoDisponivel = TRUE;
			}
		}
		
		
		
	}while(movimentoDisponivel == FALSE);
}

void main(){
	
	peca tabuleiro[ORDEM][ORDEM];
	iniciarTabuleiro(tabuleiro);
	char jogador1[TAMANHO_NICKNAME];
	char jogador2[TAMANHO_NICKNAME];
	lerNickname(jogador1);
	printf("\n");
	lerNickname(jogador2);
	printf("\n\n");
	int turno = 1;
	imprimirTabuleiro(tabuleiro);
	perguntarJogada(tabuleiro, turno);
	
	getch();
}
