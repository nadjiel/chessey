/*

Fazer os eventos especiais, tipo xeque, roque, xeque-mate

Trabalhar em roque() e emXeque()

Ajeitar pecaOponentePraCima(), pra Baixo, pra Direita e pra Esquerda de modo que, ao contrário de agora,
essas funções percorram do centro pra borda do tabuleiro, de modo a detectar a TORRE inimiga mais próxima
da peça a ser examinada se está em cheque

*/

#include<stdio.h>

typedef struct tipoPeca{
	char nome;
	char jogador;
	int jogadas;
}peca;

const int NULO = -1;
const int ERRO = -1;
const int FALSE = 0;
const int TRUE = 1;
const int TAM_NICKNAME = 11;
const int TAM_COMANDO = 3;
const int TAM_CASA = 3;
const int TAM_ENDER = 2;
const int ORDEM = 8;
const char PARTIDA = 'P';
const char CHEGADA = 'C';
const char VAZIO = '_';
const char TORRE = 't';
const char CAVALO = 'c';
const char BISPO = 'b';
const char PEAO = 'p';
const char DAMA = 'D';
const char REI = 'R';

void iniciarTabuleiro(peca tabuleiro[ORDEM][ORDEM]){
	int j, k;
	for(j = 0; j < ORDEM; j++){
		for(k = 0; k < ORDEM; k++){
			tabuleiro[j][k].nome = VAZIO;
			tabuleiro[j][k].jogador = VAZIO;
			tabuleiro[j][k].jogadas = 0;
		}
	}
	
	tabuleiro[0][4].nome = REI;
	tabuleiro[0][4].jogador = '2';
	tabuleiro[0][4].jogadas = 0;
	
	tabuleiro[0][7].nome = TORRE;
	tabuleiro[0][7].jogador = '2';
	tabuleiro[0][7].jogadas = 0;
	
	tabuleiro[0][0].nome = TORRE;
	tabuleiro[0][0].jogador = '2';
	tabuleiro[0][0].jogadas = 0;
	
	tabuleiro[7][4].nome = REI;
	tabuleiro[7][4].jogador = '1';
	tabuleiro[7][4].jogadas = 0;
	
	tabuleiro[7][7].nome = TORRE;
	tabuleiro[7][7].jogador = '1';
	tabuleiro[7][7].jogadas = 0;
	
	tabuleiro[7][0].nome = TORRE;
	tabuleiro[7][0].jogador = '1';
	tabuleiro[7][0].jogadas = 0;
	
	/*
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
	
	for(j = 2; j < 6; j++){
		for(k = 0; k < ORDEM; k++){
			tabuleiro[j][k].nome = VAZIO;
			tabuleiro[j][k].jogador = VAZIO;
		}
	}
	
	for(j = 0; j < 2; j++){
		for(k = 0; k < ORDEM; k++){
			tabuleiro[j][k].jogador = '2';
		}
	}
	
	for(j = 6; j < ORDEM; j++){
		for(k = 0; k < ORDEM; k++){
			tabuleiro[j][k].jogador = '1';
		}
	}
	
	for(j = 0; j < ORDEM; j++){
		for(k = 0; k < ORDEM; k++){
			tabuleiro[j][k].jogadas = 0;
		}
	}
	*/
}

int coordCharPraCoordInt(char coord){
	switch(coord){
		case 'a': return 1-1;
		case 'b': return 2-1;
		case 'c': return 3-1;
		case 'd': return 4-1;
		case 'e': return 5-1;
		case 'f': return 6-1;
		case 'g': return 7-1;
		case 'h': return 8-1;
		case '1': return 1-1;
		case '2': return 2-1;
		case '3': return 3-1;
		case '4': return 4-1;
		case '5': return 5-1;
		case '6': return 6-1;
		case '7': return 7-1;
		case '8': return 8-1;
		default: return ERRO;
	}
}

void casaPraEnder(char casa[TAM_CASA], int ender[TAM_ENDER]){
	ender[0] = coordCharPraCoordInt(casa[1]);
	ender[1] = coordCharPraCoordInt(casa[0]);
}

void imprimirTabuleiro(peca tabuleiro[ORDEM][ORDEM]){
	printf("    a  b  c  d  e  f  g  h");
	printf("\n\n");
	int j, k;
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

void lerNickname(char nickname[TAM_NICKNAME]){
	fflush(stdin);
	scanf("%s",nickname);
}

void lerCasa(char casa[TAM_CASA]){
	fflush(stdin);
	scanf("%s",casa);
}

void caixaBaixa(char casa[TAM_CASA]){
	int k;
	for(k = 0; k < TAM_CASA; k++){
		if((casa[k] >= 65) && (casa[k] <= 90)){
			casa[k] += 32;
		}
	}
}

char verifVez(int turno){
	if(turno % 2 == 1){
		return '1';
	}
	else{
		return '2';
	}
}

char verifOponente(char vez){
	if(vez == '1'){
		return '2';
	}
	else{
		return '1';
	}
}

int pecaDaVezPresente(peca tabuleiro[ORDEM][ORDEM], char vez, int j, int k){
	if(tabuleiro[j][k].jogador == vez){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

int enderPartidaDisponivel(peca tabuleiro[ORDEM][ORDEM], char vez, int j, int k){
	if(pecaDaVezPresente(tabuleiro, vez, j, k) == TRUE){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

int enderChegadaDisponivel(peca tabuleiro[ORDEM][ORDEM], char vez, int j, int k){
	if(tabuleiro[j][k].jogador != vez){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

int enderDisponivel(peca tabuleiro[ORDEM][ORDEM], char vez, int ender[TAM_ENDER], char tipoEnder){
	int resultado;
	int j, k;
	j = ender[0];
	k = ender[1];
	
	if(j == ERRO || k == ERRO){
		resultado = FALSE;
	}
	else{
		switch(tipoEnder){
			case 'P': resultado = enderPartidaDisponivel(tabuleiro, vez, j ,k);
					  break;
			case 'C': resultado = enderChegadaDisponivel(tabuleiro, vez, j ,k);
		}
	}
	return resultado;
}

char verifPeca(peca tabuleiro[ORDEM][ORDEM], int ender[TAM_ENDER]){
	int j = ender[0];
	int k = ender[1];
	return tabuleiro[j][k].nome;
}

int contPecasHoriz(peca tabuleiro[ORDEM][ORDEM], int j, int kMaior, int kMenor){
	if(kMaior == kMenor+1){
		return 0;
	}
	else{
		if(tabuleiro[j][kMenor+1].jogador != VAZIO){
			return 1+contPecasHoriz(tabuleiro, j, kMaior, kMenor+1);
		}
		else{
			return contPecasHoriz(tabuleiro, j, kMaior, kMenor+1);
		}
	}
}

int contPecasVerti(peca tabuleiro[ORDEM][ORDEM], int k, int jMaior, int jMenor){
	if(jMaior == jMenor+1){
		return 0;
	}
	else{
		if(tabuleiro[jMenor+1][k].jogador != VAZIO){
			return 1+contPecasVerti(tabuleiro, k, jMaior, jMenor+1);
		}
		else{
			return contPecasVerti(tabuleiro, k, jMaior, jMenor+1);
		}
	}
}

int movHorizDisponivel(peca tabuleiro[ORDEM][ORDEM], int j, int kMaior, int kMenor){
	if(contPecasHoriz(tabuleiro, j, kMaior, kMenor) > 0){
		return FALSE;
	}
	else{
		return TRUE;
	}
}

int movVertiDisponivel(peca tabuleiro[ORDEM][ORDEM], int k, int jMaior, int jMenor){
	if(contPecasVerti(tabuleiro, k, jMaior, jMenor) > 0){
		return FALSE;
	}
	else{
		return TRUE;
	}
}

int movDisponivel_4Direcoes(peca tabuleiro[ORDEM][ORDEM], int enderPartida[TAM_ENDER], int enderChegada[TAM_ENDER]){
	int resultado;
	int j1 = enderPartida[0];
	int k1 = enderPartida[1];
	int j2 = enderChegada[0];
	int k2 = enderChegada[1];
	
	if((j1 != j2) && (k1 != k2)){
		resultado = FALSE;
	}
	
	if(j1 == j2){
		if(k1 > k2){
			resultado = movHorizDisponivel(tabuleiro, j1, k1, k2);
		}
		else{
			resultado = movHorizDisponivel(tabuleiro, j1, k2, k1);
		}
	}
	
	if(k1 == k2){
		if(j1 > j2){
			resultado = movVertiDisponivel(tabuleiro, k1, j1, j2);
		}
		else{
			resultado = movVertiDisponivel(tabuleiro, k1, j2, j1);
		}
	}
	
	return resultado;
}

int contPecasDiagDecres(peca tabuleiro[ORDEM][ORDEM], int jMaior, int jMenor, int kMaior, int kMenor){
	if(jMenor+1 == jMaior && kMenor+1 == kMaior){
		return 0;
	}
	else{
		if(tabuleiro[jMenor+1][kMenor+1].jogador != VAZIO){
			return 1+contPecasDiagDecres(tabuleiro, jMaior, jMenor+1, kMaior, kMenor+1);
		}
		else{
			return contPecasDiagDecres(tabuleiro, jMaior, jMenor+1, kMaior, kMenor+1);
		}
	}
}

int contPecasDiagCres(peca tabuleiro[ORDEM][ORDEM], int jMaior, int jMenor, int kMaior, int kMenor){
	if(jMenor+1 == jMaior && kMaior-1 == kMenor){
		return 0;
	}
	else{
		if(tabuleiro[jMenor+1][kMaior-1].jogador != VAZIO){
			return 1+contPecasDiagCres(tabuleiro, jMaior, jMenor+1, kMaior-1, kMenor);
		}
		else{
			return contPecasDiagCres(tabuleiro, jMaior, jMenor+1, kMaior-1, kMenor);
		}
	}
}

int movDiagDecresDisponivel(peca tabuleiro[ORDEM][ORDEM], int jMaior, int jMenor, int kMaior, int kMenor){
	if(contPecasDiagDecres(tabuleiro, jMaior, jMenor, kMaior, kMenor) > 0){
		return FALSE;
	}
	else{
		return TRUE;
	}
}

int movDiagCresDisponivel(peca tabuleiro[ORDEM][ORDEM], int jMaior, int jMenor, int kMaior, int kMenor){
	if(contPecasDiagCres(tabuleiro, jMaior, jMenor, kMaior, kMenor) > 0){
		return FALSE;
	}
	else{
		return TRUE;
	}
}

int movDisponivel_4Diagonais(peca tabuleiro[ORDEM][ORDEM], int enderPartida[TAM_ENDER], int enderChegada[TAM_ENDER]){
	int resultado = FALSE;
	int j1 = enderPartida[0];
	int k1 = enderPartida[1];
	int j2 = enderChegada[0];
	int k2 = enderChegada[1];
	
	int percorrer;
	
	if(j1 < j2){
		if(k1 < k2){
			for(percorrer = 1; j1+percorrer <= j2; percorrer++){
				if((j1+percorrer == j2) && (k1+percorrer == k2)){
					resultado = movDiagDecresDisponivel(tabuleiro, j2, j1, k2, k1);
				}
			}
		}
		else{
			for(percorrer = 1; j1+percorrer <= j2; percorrer++){
				if((j1+percorrer == j2) && (k1-percorrer == k2)){
					resultado = movDiagCresDisponivel(tabuleiro, j2, j1, k1, k2);
				}
			}
		}
	}
	
	if(j1 > j2){
		if(k1 < k2){
			for(percorrer = 1; j1-percorrer >= j2; percorrer++){
				if((j1-percorrer == j2) && (k1+percorrer == k2)){
					resultado = movDiagCresDisponivel(tabuleiro, j1, j2, k2, k1);
				}
			}
		}
		else{
			for(percorrer = 1; j1-percorrer >= j2; percorrer++){
				if((j1-percorrer == j2) && (k1-percorrer == k2)){
					resultado = movDiagDecresDisponivel(tabuleiro, j1, j2, k1, k2);
				}
			}
		}
	}
	
	return resultado;
}

int movDisponivel_Dama(peca tabuleiro[ORDEM][ORDEM], int enderPartida[TAM_ENDER], int enderChegada[TAM_ENDER]){
	int resultado = FALSE;
	
	if(movDisponivel_4Direcoes(tabuleiro, enderPartida, enderChegada) == TRUE){
		resultado = TRUE;
	}
	if(movDisponivel_4Diagonais(tabuleiro, enderPartida, enderChegada) == TRUE){
		resultado = TRUE;
	}
	
	return resultado;
}

int movDisponivel_Rei(int enderPartida[TAM_ENDER], int enderChegada[TAM_ENDER]){
	int j1 = enderPartida[0];
	int k1 = enderPartida[1];
	int j2 = enderChegada[0];
	int k2 = enderChegada[1];
	
	if(j2 == j1-1 && k2 == k1){
		return TRUE;
	}
	if(j2 == j1-1 && k2 == k1+1){
		return TRUE;
	}
	if(j2 == j1 && k2 == k1+1){
		return TRUE;
	}
	if(j2 == j1+1 && k2 == k1+1){
		return TRUE;
	}
	if(j2 == j1+1 && k2 == k1){
		return TRUE;
	}
	if(j2 == j1+1 && k2 == k1-1){
		return TRUE;
	}
	if(j2 == j1 && k2 == k1-1){
		return TRUE;
	}
	if(j2 == j1-1 && k2 == k1-1){
		return TRUE;
	}
	
	return FALSE;
}

int movDisponivel_8Ls(int enderPartida[TAM_ENDER], int enderChegada[TAM_ENDER]){
	int j1 = enderPartida[0];
	int k1 = enderPartida[1];
	int j2 = enderChegada[0];
	int k2 = enderChegada[1];
	
	if(j2 == j1-2 && k2 == k1-1){
		return TRUE;
	}
	if(j2 == j1-2 && k2 == k1+1){
		return TRUE;
	}
	if(j2 == j1-1 && k2 == k1+2){
		return TRUE;
	}
	if(j2 == j1+1 && k2 == k1+2){
		return TRUE;
	}
	if(j2 == j1+2 && k2 == k1+1){
		return TRUE;
	}
	if(j2 == j1+2 && k2 == k1-1){
		return TRUE;
	}
	if(j2 == j1+1 && k2 == k1-2){
		return TRUE;
	}
	if(j2 == j1-1 && k2 == k1-2){
		return TRUE;
	}
	
	return FALSE;
}

int movDisponivel_Peao(peca tabuleiro[ORDEM][ORDEM], char vez, int enderPartida[TAM_ENDER], int enderChegada[TAM_ENDER]){
	char oponente = verifOponente(vez);
	int j1 = enderPartida[0];
	int k1 = enderPartida[1];
	int j2 = enderChegada[0];
	int k2 = enderChegada[1];
	
	if(vez == '1'){
		if(j2 == j1-2 && k2 == k1){
			if((tabuleiro[j1][k1].jogadas == 0) && (tabuleiro[j1-1][k1].jogador == VAZIO) && (tabuleiro[j2][k2].jogador == VAZIO)){
				return TRUE;
			}
		}
		if(j2 == j1-1 && k2 == k1){
			if(tabuleiro[j2][k2].jogador == VAZIO){
				return TRUE;
			}
		}
		if((j2 == j1-1 && k2 == k1-1) || (j2 == j1-1 && k2 == k1+1)){
			if(tabuleiro[j2][k2].jogador == oponente){
				return TRUE;
			}
		}
		return FALSE;
	}
	
	if(vez == '2'){
		if(j2 == j1+2 && k2 == k1){
			if((tabuleiro[j1][k1].jogadas == 0) && (tabuleiro[j1+1][k1].jogador == VAZIO) && (tabuleiro[j2][k2].jogador == VAZIO)){
				return TRUE;
			}
		}
		if(j2 == j1+1 && k2 == k1){
			if(tabuleiro[j2][k2].jogador == VAZIO){
				return TRUE;
			}
		}
		if((j2 == j1+1 && k2 == k1-1) || (j2 == j1+1 && k2 == k1+1)){
			if(tabuleiro[j2][k2].jogador == oponente){
				return TRUE;
			}
		}
		return FALSE;
	}
}

int pecaLivre_4Direcoes(peca tabuleiro[ORDEM][ORDEM], char vez, int ender[TAM_ENDER]){
	int j = ender[0];
	int k = ender[1];
	int obstaculos = 0;
	
	if(j == 7){
		obstaculos++;
	}
	else{
		if(pecaDaVezPresente(tabuleiro, vez, j+1, k) == TRUE){
			obstaculos++;
		}
	}
	if(k == 7){
		obstaculos++;
	}
	else{
		if(pecaDaVezPresente(tabuleiro, vez, j, k+1) == TRUE){
			obstaculos++;
		}
	}
	if(j == 0){
		obstaculos++;
	}
	else{
		if(pecaDaVezPresente(tabuleiro, vez, j-1, k) == TRUE){
			obstaculos++;
		}
	}
	if(k == 0){
		obstaculos++;
	}
	else{
		if(pecaDaVezPresente(tabuleiro, vez, j, k-1) == TRUE){
			obstaculos++;
		}
	}
	
	if(obstaculos == 4){
		return FALSE;
	}
	else{
		return TRUE;
	}
}

int pecaLivre_4Diagonais(peca tabuleiro[ORDEM][ORDEM], char vez, int ender[TAM_ENDER]){
	int j = ender[0];
	int k = ender[1];
	int obstaculos = 0;
	
	if(j > 0 && j < 7){
		if(k > 0 && k < 7){
			if(pecaDaVezPresente(tabuleiro, vez, j-1, k-1) == TRUE){
				obstaculos++;
			}
			if(pecaDaVezPresente(tabuleiro, vez, j-1, k+1) == TRUE){
				obstaculos++;
			}
			if(pecaDaVezPresente(tabuleiro, vez, j+1, k-1) == TRUE){
				obstaculos++;
			}
			if(pecaDaVezPresente(tabuleiro, vez, j+1, k+1) == TRUE){
				obstaculos++;
			}
		}
		if(k == 0){
			obstaculos += 2;
			if(pecaDaVezPresente(tabuleiro, vez, j-1, k+1) == TRUE){
				obstaculos++;
			}
			if(pecaDaVezPresente(tabuleiro, vez, j+1, k+1) == TRUE){
				obstaculos++;
			}
		}
		if(k == 7){
			obstaculos += 2;
			if(pecaDaVezPresente(tabuleiro, vez, j-1, k-1) == TRUE){
				obstaculos++;
			}
			if(pecaDaVezPresente(tabuleiro, vez, j+1, k-1) == TRUE){
				obstaculos++;
			}
		}
	}
	
	if(j == 0){
		if(k > 0 && k < 7){
			obstaculos += 2;
			if(pecaDaVezPresente(tabuleiro, vez, j+1, k-1) == TRUE){
				obstaculos++;
			}
			if(pecaDaVezPresente(tabuleiro, vez, j+1, k+1) == TRUE){
				obstaculos++;
			}
		}
		if(k == 0){
			obstaculos += 3;
			if(pecaDaVezPresente(tabuleiro, vez, j+1, k+1) == TRUE){
				obstaculos++;
			}
		}
		if(k == 7){
			obstaculos += 3;
			if(pecaDaVezPresente(tabuleiro, vez, j+1, k-1) == TRUE){
				obstaculos++;
			}
		}
	}
	
	if(j == 7){
		if(k > 0 && k < 7){
			obstaculos += 2;
			if(pecaDaVezPresente(tabuleiro, vez, j-1, k-1) == TRUE){
				obstaculos++;
			}
			if(pecaDaVezPresente(tabuleiro, vez, j-1, k+1) == TRUE){
				obstaculos++;
			}
		}
		if(k == 0){
			obstaculos += 3;
			if(pecaDaVezPresente(tabuleiro, vez, j-1, k+1) == TRUE){
				obstaculos++;
			}
		}
		if(k == 7){
			obstaculos += 3;
			if(pecaDaVezPresente(tabuleiro, vez, j-1, k-1) == TRUE){
				obstaculos++;
			}
		}
	}
	
	if(obstaculos == 4){
		return FALSE;
	}
	else{
		return TRUE;
	}
}

int pecaLivre_Monarcas(peca tabuleiro[ORDEM][ORDEM], char vez, int ender[TAM_ENDER]){
	int resultado = FALSE;
	
	if(pecaLivre_4Direcoes(tabuleiro, vez, ender) == TRUE){
		resultado = TRUE;
	}
	if(pecaLivre_4Diagonais(tabuleiro, vez, ender) == TRUE){
		resultado = TRUE;
	}
	
	return resultado;
}

int pecaLivre_8Ls(peca tabuleiro[ORDEM][ORDEM], char vez, int ender[TAM_ENDER]){
	int j = ender[0];
	int k = ender[1];
	int obstaculos = 0;
	
	if(j > 1 && j < 6){
		if(k > 1 && k < 6){
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k-1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k+1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k+2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k+2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k+1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k-1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k-2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k-2);
		}
		if(k == 1){
			obstaculos += 2;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k-1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k+1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k+2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k+2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k+1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k-1);
		}
		if(k == 0){
			obstaculos += 4;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k+1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k+2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k+2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k+1);
		}
		if(k == 6){
			obstaculos += 2;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k+1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k-1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k-2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k-2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k-1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k+1);
		}
		if(k == 7){
			obstaculos += 4;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k-1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k-2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k-2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k-1);
		}
	}
	
	if(j == 1){
		obstaculos += 2;
		if(k > 1 && k < 6){
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k+2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k+2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k+1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k-1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k-2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k-2);
		}
		if(k == 1){
			obstaculos += 2;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k+2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k+2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k+1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k-1);
		}
		if(k == 0){
			obstaculos += 3;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k+2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k+2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k+1);
		}
		if(k == 6){
			obstaculos += 2;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k+1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k-1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k-2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k-2);
		}
		if(k == 7){
			obstaculos += 3;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k-1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k-2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k-2);
		}
	}
	
	if(j == 0){
		obstaculos += 4;
		if(k > 1 && k < 6){
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k+2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k+1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k-1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k-2);
		}
		if(k == 1){
			obstaculos += 1;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k+2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k+1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k-1);
		}
		if(k == 0){
			obstaculos += 2;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k+2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k+1);
		}
		if(k == 6){
			obstaculos += 1;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k+1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k-1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k-2);
		}
		if(k == 7){
			obstaculos += 2;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+2, k-1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k-2);
		}
	}
	
	if(j == 6){
		obstaculos += 2;
		if(k > 1 && k < 6){
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k-2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k-2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k-1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k+1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k+2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k+2);
		}
		if(k == 1){
			obstaculos += 2;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k-1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k+1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k+2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k+2);
		}
		if(k == 0){
			obstaculos += 3;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k+1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k+2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k+2);
		}
		if(k == 6){
			obstaculos += 2;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k-2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k-2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k-1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k+1);
		}
		if(k == 7){
			obstaculos += 3;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j+1, k-2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k-2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k-1);
		}
	}
	
	if(j == 7){
		obstaculos += 4;
		if(k > 1 && k < 6){
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k-2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k-1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k+1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k+2);
		}
		if(k == 1){
			obstaculos += 1;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k-1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k+1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k+2);
		}
		if(k == 0){
			obstaculos += 2;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k+1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k+2);
		}
		if(k == 6){
			obstaculos += 1;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k-2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k-1);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k+1);
		}
		if(k == 7){
			obstaculos += 2;
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-1, k-2);
			obstaculos += pecaDaVezPresente(tabuleiro, vez, j-2, k-1);
		}
	}
	
	if(obstaculos == 8){
		return FALSE;
	}
	else{
		return TRUE;
	}
}

int pecaLivre_Peao(peca tabuleiro[ORDEM][ORDEM], char vez, int ender[TAM_ENDER]){
	char oponente = verifOponente(vez);
	int j = ender[0];
	int k = ender[1];
	int obstaculos = 0;
	
	if(vez == '1'){
		if(j == 0){
			obstaculos += 3;
		}
		else{
			if(tabuleiro[j-1][k].jogador != VAZIO){
				obstaculos++;
			}
			if(tabuleiro[j-1][k-1].jogador != oponente){
				obstaculos++;
			}
			if(tabuleiro[j-1][k+1].jogador != oponente){
				obstaculos++;
			}
		}
	}
	
	if(vez == '2'){
		if(j == 7){
			obstaculos += 3;
		}
		else{
			if(tabuleiro[j+1][k].jogador != VAZIO){
				obstaculos++;
			}
			if(tabuleiro[j+1][k-1].jogador != oponente){
				obstaculos++;
			}
			if(tabuleiro[j+1][k+1].jogador != oponente){
				obstaculos++;
			}
		}
	}
	
	if(obstaculos == 3){
		return FALSE;
	}
	else{
		return TRUE;
	}
}

int verifPecaLivre(peca tabuleiro[ORDEM][ORDEM], char vez, int ender[TAM_ENDER], char pecaEscolhida){
	if(pecaEscolhida == TORRE){
		if(pecaLivre_4Direcoes(tabuleiro, vez, ender) == FALSE){
			return FALSE;
		}
		else{
			return TRUE;
		}
	}
	if(pecaEscolhida == BISPO){
		if(pecaLivre_4Diagonais(tabuleiro, vez, ender) == FALSE){
			return FALSE;
		}
		else{
			return TRUE;
		}
	}
	if(pecaEscolhida == CAVALO){
		if(pecaLivre_8Ls(tabuleiro, vez, ender) == FALSE){
			return FALSE;
		}
		else{
			return TRUE;
		}
	}
	if(pecaEscolhida == DAMA || pecaEscolhida == REI){
		if(pecaLivre_Monarcas(tabuleiro, vez, ender) == FALSE){
			return FALSE;
		}
		else{
			return TRUE;
		}
	}
	if(pecaEscolhida == PEAO){
		if(pecaLivre_Peao(tabuleiro, vez, ender) == FALSE){
			return FALSE;
		}
		else{
			return TRUE;
		}
	}
}

void buscarOponentePraCima(peca tabuleiro[ORDEM][ORDEM], char oponente, char peca, int j, int k, int enderOponente[TAM_ENDER]){
	if(j == 0){
	}
	else if((tabuleiro[j-1][k].nome == peca) && (tabuleiro[j-1][k].jogador == oponente)){
		 	enderOponente[0] = j-1;
		 	enderOponente[1] = k;
		 }
		 else{
		 	buscarOponentePraCima(tabuleiro, oponente, peca, j-1, k, enderOponente);
		 }
}

void buscarOponentePraDireita(peca tabuleiro[ORDEM][ORDEM], char oponente, char peca, int j, int k, int enderOponente[TAM_ENDER]){
	if(k == 7){
	}
	else if((tabuleiro[j][k+1].nome == peca) && (tabuleiro[j][k+1].jogador == oponente)){
		 	enderOponente[0] = j;
		 	enderOponente[1] = k+1;
		 }
		 else{
		 	buscarOponentePraDireita(tabuleiro, oponente, peca, j, k+1, enderOponente);
		 }
}

void buscarOponentePraBaixo(peca tabuleiro[ORDEM][ORDEM], char oponente, char peca, int j, int k, int enderOponente[TAM_ENDER]){
	if(j == 7){
	}
	else if((tabuleiro[j+1][k].nome == peca) && (tabuleiro[j+1][k].jogador == oponente)){
		 	enderOponente[0] = j+1;
		 	enderOponente[1] = k;
		 }
		 else{
		 	buscarOponentePraBaixo(tabuleiro, oponente, peca, j+1, k, enderOponente);
		 }
}

void buscarOponentePraEsquerda(peca tabuleiro[ORDEM][ORDEM], char oponente, char peca, int j, int k, int enderOponente[TAM_ENDER]){
	if(k == 0){
	}
	else if((tabuleiro[j][k-1].nome == peca) && (tabuleiro[j][k-1].jogador == oponente)){
		 	enderOponente[0] = j;
		 	enderOponente[1] = k-1;
		 }
		 else{
		 	buscarOponentePraEsquerda(tabuleiro, oponente, peca, j, k-1, enderOponente);
		 }
}

void buscarOponentePraNord(peca tabuleiro[ORDEM][ORDEM], char oponente, char peca, int j, int k, int enderOponente[TAM_ENDER]){
	if(j == 0 || k == 7){
	}
	else if((tabuleiro[j-1][k+1].nome == peca) && (tabuleiro[j-1][k+1].jogador == oponente)){
		 	enderOponente[0] = j-1;
		 	enderOponente[1] = k+1;
		 }
		 else{
		 	buscarOponentePraNord(tabuleiro, oponente, peca, j-1, k+1, enderOponente);
		 }
}

void buscarOponentePraSude(peca tabuleiro[ORDEM][ORDEM], char oponente, char peca, int j, int k, int enderOponente[TAM_ENDER]){
	if(j == 7 || k == 7){
	}
	else if((tabuleiro[j+1][k+1].nome == peca) && (tabuleiro[j+1][k+1].jogador == oponente)){
		 	enderOponente[0] = j+1;
		 	enderOponente[1] = k+1;
		 }
		 else{
		 	buscarOponentePraSude(tabuleiro, oponente, peca, j+1, k+1, enderOponente);
		 }
}

void buscarOponentePraSudo(peca tabuleiro[ORDEM][ORDEM], char oponente, char peca, int j, int k, int enderOponente[TAM_ENDER]){
	if(j == 7 || k == 0){
	}
	else if((tabuleiro[j+1][k-1].nome == peca) && (tabuleiro[j+1][k-1].jogador == oponente)){
		 	enderOponente[0] = j+1;
		 	enderOponente[1] = k-1;
		 }
		 else{
		 	buscarOponentePraSudo(tabuleiro, oponente, peca, j+1, k-1, enderOponente);
		 }
}

void buscarOponentePraNoro(peca tabuleiro[ORDEM][ORDEM], char oponente, char peca, int j, int k, int enderOponente[TAM_ENDER]){
	if(j == 0 || k == 0){
	}
	else if((tabuleiro[j-1][k-1].nome == peca) && (tabuleiro[j-1][k-1].jogador == oponente)){
		 	enderOponente[0] = j-1;
		 	enderOponente[1] = k-1;
		 }
		 else{
		 	buscarOponentePraNoro(tabuleiro, oponente, peca, j-1, k-1, enderOponente);
		 }
}

int pecaAdversariaPresente(peca tabuleiro[ORDEM][ORDEM], char peca, char oponente, int j, int k){
	if((tabuleiro[j][k].nome == peca) && (tabuleiro[j][k].jogador == oponente)){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

int ameacadaPor_4Direcoes(peca tabuleiro[ORDEM][ORDEM], char oponente, char pecaOponente, int j, int k){
	int enderOponente[TAM_ENDER];
	enderOponente[0] = NULO;
	enderOponente[1] = NULO;
	
	buscarOponentePraCima(tabuleiro, oponente, pecaOponente, j, k, enderOponente);
	if(enderOponente[0] != NULO){
		if(movVertiDisponivel(tabuleiro, k, j, enderOponente[0]) == TRUE){
			return TRUE;
		}
	}
	enderOponente[0] = NULO;
	enderOponente[1] = NULO;
	buscarOponentePraDireita(tabuleiro, oponente, pecaOponente, j, k, enderOponente);
	if(enderOponente[1] != NULO){
		if(movHorizDisponivel(tabuleiro, j, enderOponente[1], k) == TRUE){
			return TRUE;
		}
	}
	enderOponente[0] = NULO;
	enderOponente[1] = NULO;
	buscarOponentePraBaixo(tabuleiro, oponente, pecaOponente, j, k, enderOponente);
	if(enderOponente[0] != NULO){
		if(movVertiDisponivel(tabuleiro, k, enderOponente[0], j) == TRUE){
			return TRUE;
		}
	}
	enderOponente[0] = NULO;
	enderOponente[1] = NULO;
	buscarOponentePraEsquerda(tabuleiro, oponente, pecaOponente, j, k, enderOponente);
	if(enderOponente[1] != NULO){
		if(movHorizDisponivel(tabuleiro, j, k, enderOponente[1]) == TRUE){
			return TRUE;
		}
	}
	
	return FALSE;
}

int ameacadaPor_4Diagonais(peca tabuleiro[ORDEM][ORDEM], char oponente, char pecaOponente, int j, int k){
	int enderOponente[TAM_ENDER];
	enderOponente[0] = NULO;
	enderOponente[1] = NULO;
	
	buscarOponentePraNord(tabuleiro, oponente, pecaOponente, j, k, enderOponente);
	if(enderOponente[0] != NULO){
		if(movDiagCresDisponivel(tabuleiro, j, enderOponente[0], enderOponente[1], k) == TRUE){
			return TRUE;
		}
	}
	enderOponente[0] = NULO;
	enderOponente[1] = NULO;
	buscarOponentePraSude(tabuleiro, oponente, pecaOponente, j, k, enderOponente);
	if(enderOponente[0] != NULO){
		if(movDiagDecresDisponivel(tabuleiro, enderOponente[0], j, enderOponente[1], k) == TRUE){
			return TRUE;
		}
	}
	enderOponente[0] = NULO;
	enderOponente[1] = NULO;
	buscarOponentePraSudo(tabuleiro, oponente, pecaOponente, j, k, enderOponente);
	if(enderOponente[0] != NULO){
		if(movDiagCresDisponivel(tabuleiro, enderOponente[0], j, k, enderOponente[1]) == TRUE){
			return TRUE;
		}
	}
	enderOponente[0] = NULO;
	enderOponente[1] = NULO;
	buscarOponentePraNoro(tabuleiro, oponente, pecaOponente, j, k, enderOponente);
	if(enderOponente[0] != NULO){
		if(movDiagDecresDisponivel(tabuleiro, j, enderOponente[0], k, enderOponente[1]) == TRUE){
			return TRUE;
		}
	}
	
	return FALSE;
}

int ameacadaPorTorre(peca tabuleiro[ORDEM][ORDEM], char oponente, int j, int k){
	if(ameacadaPor_4Direcoes(tabuleiro, oponente, TORRE, j, k) == TRUE){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

int ameacadaPorBispo(peca tabuleiro[ORDEM][ORDEM], char oponente, int j, int k){
	if(ameacadaPor_4Diagonais(tabuleiro, oponente, BISPO, j, k) == TRUE){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

int ameacadaPorCavalo(peca tabuleiro[ORDEM][ORDEM], char oponente, int j, int k){
	int atacantes = 0;
	
	if(j > 1 && j < 6){
		if(k > 1 && k < 6){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k+2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k+2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k-2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k-2);
		}
		if(k == 1){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k+2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k+2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k-1);
		}
		if(k == 0){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k+2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k+2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k+1);
		}
		if(k == 6){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k-2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k-2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k+1);
		}
		if(k == 7){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k-2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k-2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k-1);
		}
	}
	
	if(j == 1){
		if(k > 1 && k < 6){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k+2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k+2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k-2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k-2);
		}
		if(k == 1){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k+2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k+2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k-1);
		}
		if(k == 0){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k+2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k+2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k+1);
		}
		if(k == 6){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k-2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k-2);
		}
		if(k == 7){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k-2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k-2);
		}
	}
	
	if(j == 0){
		if(k > 1 && k < 6){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k+2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k-2);
		}
		if(k == 1){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k+2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k-1);
		}
		if(k == 0){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k+2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k+1);
		}
		if(k == 6){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k-2);
		}
		if(k == 7){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+2, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k-2);
		}
	}
	
	if(j == 6){
		if(k > 1 && k < 6){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k-2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k-2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k+2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k+2);
		}
		if(k == 1){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k+2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k+2);
		}
		if(k == 0){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k+2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k+2);
		}
		if(k == 6){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k-2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k-2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k+1);
		}
		if(k == 7){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j+1, k-2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k-2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k-1);
		}
	}
	
	if(j == 7){
		if(k > 1 && k < 6){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k-2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k+2);
		}
		if(k == 1){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k+2);
		}
		if(k == 0){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k+2);
		}
		if(k == 6){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k-2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k+1);
		}
		if(k == 7){
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-1, k-2);
			atacantes += pecaAdversariaPresente(tabuleiro, CAVALO, oponente, j-2, k-1);
		}
	}
	
	if(atacantes > 0){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

int ameacadaPorDama(peca tabuleiro[ORDEM][ORDEM], char oponente, int j, int k){
	if(ameacadaPor_4Direcoes(tabuleiro, oponente, DAMA, j, k) == TRUE){
		return TRUE;
	}
	if(ameacadaPor_4Diagonais(tabuleiro, oponente, DAMA, j, k) == TRUE){
		return TRUE;
	}
	
	return FALSE;
}

int ameacadaPorRei(peca tabuleiro[ORDEM][ORDEM], char oponente, int j, int k){
	int atacantes = 0;
	
	if(j > 0 && j < 7){
		if(k > 0 && k < 7){
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j-1, k);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j-1, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j+1, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j+1, k);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j+1, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j-1, k-1);
		}
		if(k == 0){
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j-1, k);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j-1, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j+1, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j+1, k);
		}
		if(k == 7){
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j+1, k);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j+1, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j-1, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j-1, k);
		}
	}
	
	if(j == 0){
		if(k > 0 && k < 7){
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j+1, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j+1, k);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j+1, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j, k-1);
		}
		if(k == 0){
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j+1, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j+1, k);
		}
		if(k == 7){
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j+1, k);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j+1, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j, k-1);
		}
	}
	
	if(j == 7){
		if(k > 0 && k < 7){
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j-1, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j-1, k);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j-1, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j, k+1);
		}
		if(k == 0){
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j-1, k);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j-1, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j, k+1);
		}
		if(k == 7){
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j-1, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, REI, oponente, j-1, k);
		}
	}
	
	if(atacantes > 0){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

int ameacadaPorPeao(peca tabuleiro[ORDEM][ORDEM], char oponente, int j, int k){
	int atacantes = 0;
	
	if(tabuleiro[j][k].jogador == '1'){
		if(j == 0){
			return FALSE;
		}
		else{
			atacantes += pecaAdversariaPresente(tabuleiro, PEAO, oponente, j-1, k-1);
			atacantes += pecaAdversariaPresente(tabuleiro, PEAO, oponente, j-1, k+1);
		}
	}
	
	if(tabuleiro[j][k].jogador == '2'){
		if(j == ORDEM-1){
			return FALSE;
		}
		else{
			atacantes += pecaAdversariaPresente(tabuleiro, PEAO, oponente, j+1, k+1);
			atacantes += pecaAdversariaPresente(tabuleiro, PEAO, oponente, j+1, k-1);
		}
	}
	
	if(atacantes > 0){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

int emXeque(peca tabuleiro[ORDEM][ORDEM], char oponente, int j, int k){
	if(ameacadaPorTorre(tabuleiro, oponente, j, k) == TRUE){
		return TRUE;
	}
	if(ameacadaPorBispo(tabuleiro, oponente, j, k) == TRUE){
		return TRUE;
	}
	if(ameacadaPorCavalo(tabuleiro, oponente, j, k) == TRUE){
		return TRUE;
	}
	if(ameacadaPorDama(tabuleiro, oponente, j, k) == TRUE){
		return TRUE;
	}
	if(ameacadaPorRei(tabuleiro, oponente, j, k) == TRUE){
		return TRUE;
	}
	if(ameacadaPorPeao(tabuleiro, oponente, j, k) == TRUE){
		return TRUE;
	}
	
	return FALSE;
}

int roque(peca tabuleiro[ORDEM][ORDEM], char vez, int enderPartida[TAM_ENDER], int enderChegada[TAM_ENDER]){
	char oponente = verifOponente(vez);
	int j1 = enderPartida[0];
	int k1 = enderPartida[1];
	int j2 = enderChegada[0];
	int k2 = enderChegada[1];
	
	if(tabuleiro[j1][k1].jogadas == 0){
		if((j2 == j1 && k2 == k1+2) && (movHorizDisponivel(tabuleiro, j1, k2, k1) == TRUE)){
			if((tabuleiro[j2][k2+1].nome == TORRE) && (tabuleiro[j2][k2+1].jogador == vez) && (tabuleiro[j2][k2+1].jogadas == 0)){
				if(emXeque(tabuleiro, oponente, j1, k1) == TRUE){
					return FALSE;
				}
				if(emXeque(tabuleiro, oponente, j2, k2-1) == TRUE){
					return FALSE;
				}
				if(emXeque(tabuleiro, oponente, j2, k2) == TRUE){
					return FALSE;
				}
				return TRUE;
			}
		}
		
		if((j2 == j1 && k2 == k1-2) && (movHorizDisponivel(tabuleiro, j1, k1, k2-2) == TRUE)){
			if((tabuleiro[j2][k2-2].nome == TORRE) && (tabuleiro[j2][k2-2].jogador == vez) && (tabuleiro[j2][k2-2].jogadas == 0)){
				if(emXeque(tabuleiro, oponente, j1, k1) == TRUE){
					return FALSE;
				}
				if(emXeque(tabuleiro, oponente, j2, k2+1) == TRUE){
					return FALSE;
				}
				if(emXeque(tabuleiro, oponente, j2, k2) == TRUE){
					return FALSE;
				}
				if(emXeque(tabuleiro, oponente, j2, k2-1) == TRUE){
					return FALSE;
				}
				return TRUE;
			}
		}
	}
	
	return FALSE;
}

int capturaEnPassant(peca tabuleiro[ORDEM][ORDEM], char vez, int enderPartidaAnt[TAM_ENDER], int enderChegadaAnt[TAM_ENDER], int enderPartida[TAM_ENDER], int enderChegada[TAM_ENDER]){
	int j1Ant = enderPartidaAnt[0];
	int k1Ant = enderPartidaAnt[1];
	int j2Ant = enderChegadaAnt[0];
	int k2Ant = enderChegadaAnt[1];
	
	int j1 = enderPartida[0];
	int k1 = enderPartida[1];
	int j2 = enderChegada[0];
	int k2 = enderChegada[1];
	
	if(vez == '1'){
		if((j2 == j1-1 && k2 == k1-1) || (j2 == j1-1 && k2 == k1+1)){
			if((tabuleiro[j2][k2].jogador == VAZIO) && (tabuleiro[j2+1][k2].nome == PEAO)){
				if((j1Ant == j2-1 && k1Ant == k2) && (j2Ant == j2+1 && k2Ant == k2)){
					return TRUE;
				}
			}
		}
	}
	
	if(vez == '2'){
		if((j2 == j1+1 && k2 == k1-1) || (j2 == j1+1 && k2 == k1+1)){
			if((tabuleiro[j2][k2].jogador == VAZIO) && (tabuleiro[j2-1][k2].nome == PEAO)){
				if((j1Ant == j2+1 && k1Ant == k2) && (j2Ant == j2-1 && k2Ant == k2)){
					return TRUE;
				}
			}
		}
	}
	
	return FALSE;
}

int verifMovDisponivel(peca tabuleiro[ORDEM][ORDEM], char vez, int enderPartidaAnt[TAM_ENDER], int enderChegadaAnt[TAM_ENDER], int enderPartida[TAM_ENDER], int enderChegada[TAM_ENDER], char pecaEscolhida){
	if(pecaEscolhida == TORRE){
		if(movDisponivel_4Direcoes(tabuleiro, enderPartida, enderChegada) == FALSE){
			return FALSE;
		}
		else{
			return TRUE;
		}
	}
	if(pecaEscolhida == BISPO){
		if(movDisponivel_4Diagonais(tabuleiro, enderPartida, enderChegada) == FALSE){
			return FALSE;
		}
		else{
			return TRUE;
		}
	}
	if(pecaEscolhida == CAVALO){
		if(movDisponivel_8Ls(enderPartida, enderChegada) == FALSE){
			return FALSE;
		}
		else{
			return TRUE;
		}
	}
	if(pecaEscolhida == DAMA){
		if(movDisponivel_Dama(tabuleiro, enderPartida, enderChegada) == FALSE){
			return FALSE;
		}
		else{
			return TRUE;
		}
	}
	if(pecaEscolhida == REI){
		if(movDisponivel_Rei(enderPartida, enderChegada) == TRUE){
			return TRUE;
		}
		if(roque(tabuleiro, vez, enderPartida, enderChegada) == TRUE){
			return TRUE;
		}
		return FALSE;
	}
	if(pecaEscolhida == PEAO){
		if(movDisponivel_Peao(tabuleiro, vez, enderPartida, enderChegada) == TRUE){
			return TRUE;
		}
		if(capturaEnPassant(tabuleiro, vez, enderPartidaAnt, enderChegadaAnt, enderPartida, enderChegada) == TRUE){
			return TRUE;
		}
		return FALSE;
	}
}

void perguntarJogada(peca tabuleiro[ORDEM][ORDEM], char vez, int enderPartidaAnt[TAM_ENDER], int enderChegadaAnt[TAM_ENDER], int enderPartida[TAM_ENDER], int enderChegada[TAM_ENDER]){
	char casaPartida[TAM_CASA];
	printf("\nQual peca voce quer mexer? ");
	lerCasa(casaPartida);
	caixaBaixa(casaPartida);
	casaPraEnder(casaPartida, enderPartida);
	char pecaEscolhida = verifPeca(tabuleiro, enderPartida);
	int pecaLivre = verifPecaLivre(tabuleiro, vez, enderPartida, pecaEscolhida);
	while((enderDisponivel(tabuleiro, vez, enderPartida, PARTIDA) == FALSE) || (pecaLivre == FALSE)){
		printf("Coordenada invalida. Digite outra: ");
		lerCasa(casaPartida);
		caixaBaixa(casaPartida);
		casaPraEnder(casaPartida, enderPartida);
		pecaEscolhida = verifPeca(tabuleiro, enderPartida);
		pecaLivre = verifPecaLivre(tabuleiro, vez, enderPartida, pecaEscolhida);
	}
	
	char casaChegada[TAM_CASA];
	printf("\nPara qual casa voce quer mecher essa peca? ");
	lerCasa(casaChegada);
	caixaBaixa(casaChegada);
	casaPraEnder(casaChegada, enderChegada);
	int movDisponivel = verifMovDisponivel(tabuleiro, vez, enderPartidaAnt, enderChegadaAnt, enderPartida, enderChegada, pecaEscolhida);
	while((enderDisponivel(tabuleiro, vez, enderChegada, CHEGADA) == FALSE) || (movDisponivel == FALSE)){
		printf("Coordenada invalida. Digite outra: ");
		lerCasa(casaChegada);
		caixaBaixa(casaChegada);
		casaPraEnder(casaChegada, enderChegada);
		movDisponivel = verifMovDisponivel(tabuleiro, vez, enderPartidaAnt, enderChegadaAnt, enderPartida, enderChegada, pecaEscolhida);
	}
}

void efetuarJogada(peca tabuleiro[ORDEM][ORDEM], char vez, int enderPartidaAnt[TAM_ENDER], int enderChegadaAnt[TAM_ENDER], int enderPartida[TAM_ENDER], int enderChegada[TAM_ENDER]){
	int j1 = enderPartida[0];
	int k1 = enderPartida[1];
	int j2 = enderChegada[0];
	int k2 = enderChegada[1];
	
	if(capturaEnPassant(tabuleiro, vez, enderPartidaAnt, enderChegadaAnt, enderPartida, enderChegada) == TRUE){
		if(vez == '1'){
			tabuleiro[j2+1][k2].nome = VAZIO;
			tabuleiro[j2+1][k2].jogador = VAZIO;
			tabuleiro[j2+1][k2].jogadas = 0;
		}
		if(vez == '2'){
			tabuleiro[j2-1][k2].nome = VAZIO;
			tabuleiro[j2-1][k2].jogador = VAZIO;
			tabuleiro[j2-1][k2].jogadas = 0;
		}
	}
	
	if(roque(tabuleiro, vez, enderPartida, enderChegada) == TRUE){
		if(k2 == k1+2){
			tabuleiro[j2][k2-1] = tabuleiro[j2][k2+1];
			tabuleiro[j2][k2+1].nome = VAZIO;
			tabuleiro[j2][k2+1].jogador = VAZIO;
			tabuleiro[j2][k2+1].jogadas = 0;
		}
		if(k2 == k1-2){
			tabuleiro[j2][k2+1] = tabuleiro[j2][k2-2];
			tabuleiro[j2][k2-2].nome = VAZIO;
			tabuleiro[j2][k2-2].jogador = VAZIO;
			tabuleiro[j2][k2-2].jogadas = 0;
		}
	}
	
	enderPartidaAnt[0] = enderPartida[0];
	enderPartidaAnt[1] = enderPartida[1];
	enderChegadaAnt[0] = enderChegada[0];
	enderChegadaAnt[1] = enderChegada[1];
	
	tabuleiro[j2][k2] = tabuleiro[j1][k1];
	tabuleiro[j2][k2].jogadas++;
	tabuleiro[j1][k1].nome = VAZIO;
	tabuleiro[j1][k1].jogador = VAZIO;
	tabuleiro[j1][k1].jogadas = 0;
}

void efetuarTurno(peca tabuleiro[ORDEM][ORDEM], char vez, int enderPartidaAnt[TAM_ENDER], int enderChegadaAnt[TAM_ENDER]){
	int enderPartida[TAM_ENDER];
	int enderChegada[TAM_ENDER];
	
	perguntarJogada(tabuleiro, vez, enderPartidaAnt, enderChegadaAnt, enderPartida, enderChegada);
	efetuarJogada(tabuleiro, vez, enderPartidaAnt, enderChegadaAnt, enderPartida, enderChegada);
}

int xequeMate(peca tabuleiro[ORDEM][ORDEM]){
	int j, k;
	int contReis = 0;
	
	for(j = 0; j < ORDEM; j++){
		for(k = 0; k < ORDEM; k++){
			if(tabuleiro[j][k].nome == REI){
				contReis++;
			}
		}
	}
	
	if(contReis == 1){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

char verifVencedor(peca tabuleiro[ORDEM][ORDEM]){
	int j, k;
	
	if(xequeMate(tabuleiro) == TRUE){
		for(j = 0; j < ORDEM; j++){
			for(k = 0; k < ORDEM; k++){
				if(tabuleiro[j][k].nome == REI){
					return tabuleiro[j][k].jogador;
				}
			}
		}
	}
	
	return VAZIO;
}

void lerPeca(char *peca){
	fflush(stdin);
	scanf("%c",&(*peca));
}

int pecaValida(char peca){
	switch(peca){
		case 't': return TRUE;
		case 'c': return TRUE;
		case 'b': return TRUE;
		case 'D': return TRUE;
		default: return FALSE;
	}
}

int peaoPromovivel(peca tabuleiro[ORDEM][ORDEM]){
	int k;
	for(k = 0; k < ORDEM; k++){
		if(tabuleiro[0][k].nome == PEAO){
			return TRUE;
		}
		if(tabuleiro[7][k].nome == PEAO){
			return TRUE;
		}
	}
	
	return FALSE;
}

void promoverPeao(peca tabuleiro[ORDEM][ORDEM]){
	char peca;
	int k;
	
	if(peaoPromovivel(tabuleiro) == TRUE){
		printf("\nPara que peca deseja promover seu peao? ");
		lerPeca(&peca);
		while(pecaValida(peca) == FALSE){
			printf("Peca invalida. Digite outra: ");
			lerPeca(&peca);
		}
		
		for(k = 0; k < ORDEM; k++){
			if(tabuleiro[0][k].nome == PEAO){
				tabuleiro[0][k].nome = peca;
			}
			if(tabuleiro[7][k].nome == PEAO){
				tabuleiro[0][k].nome = peca;
			}
		}
	}
}

void main(){
	peca tabuleiro[ORDEM][ORDEM];
	iniciarTabuleiro(tabuleiro);
	int enderPartidaAnt[TAM_ENDER];
	enderPartidaAnt[0] = NULO;
	enderPartidaAnt[1] = NULO;
	int enderChegadaAnt[TAM_ENDER];
	enderChegadaAnt[0] = NULO;
	enderChegadaAnt[1] = NULO;
	int turno = 0;
	char vez;
	char vencedor;
	
	char jogador1[TAM_NICKNAME];
	char jogador2[TAM_NICKNAME];
	
	/*Testar funções*/
	printf("%d\n",emXeque(tabuleiro, '2', 3, 3));
	
	/*
	printf("Informe seu nickname, jogador 1 (de 1 a 10 caracteres e sem espaco): ");
	lerNickname(jogador1);
	printf("\nInforme seu nickname, jogador 2 (de 1 a 10 caracteres e sem espaco): ");
	lerNickname(jogador2);
	*/
	
	do{
		promoverPeao(tabuleiro);
		
		turno++;
		vez = verifVez(turno);
		
		printf("\n\n");
		imprimirTabuleiro(tabuleiro);
		
		vencedor = verifVencedor(tabuleiro);
		switch(vencedor){
			case '1': printf("\n\n\nPARABENS %s, VOCE GANHOU A PARTIDA!\n\n\n\n\n\n\n\n\n\n",jogador1);
					  break;
			case '2': printf("\n\n\nPARABENS %s, VOCE GANHOU A PARTIDA!\n\n\n\n\n\n\n\n\n\n",jogador2);
		}
		
		if(vencedor == VAZIO){
			efetuarTurno(tabuleiro, vez, enderPartidaAnt, enderChegadaAnt);
		}
	}while(vencedor == VAZIO);
	
	getch();
}
