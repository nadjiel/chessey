/*

Fazer os eventos especiais, tipo xeque, roque, xeque-mate, captura-en-passent

Melhorar movHorizDisponivel()
Melhorar movVertiDisponivel()
Melhorar movDiagDecrescDisponivel()
Melhorar movDiagCrescDisponivel()

*/

#include<stdio.h>

typedef struct tipoPeca{
	char nome;
	char jogador;
	int jogadas;
}peca;

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

int movHorizDisponivel(peca tabuleiro[ORDEM][ORDEM], int j, int kMaior, int kMenor){
	int percorrer;
	int contPecas = 0;
	for(percorrer = kMenor+1; percorrer < kMaior; percorrer++){
		if((tabuleiro[j][percorrer].jogador == '1') || (tabuleiro[j][percorrer].jogador == '2')){
			contPecas++;
		}
	}
	if(contPecas > 0){
		return FALSE;
	}
	else{
		return TRUE;
	}
}

int movVertiDisponivel(peca tabuleiro[ORDEM][ORDEM], int k, int jMaior, int jMenor){
	int percorrer;
	int contPecas = 0;
	for(percorrer = jMenor+1; percorrer < jMaior; percorrer++){
		if((tabuleiro[percorrer][k].jogador == '1') || (tabuleiro[percorrer][k].jogador == '2')){
			contPecas++;
		}
	}
	if(contPecas > 0){
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

int movDiagDecresDisponivel(peca tabuleiro[ORDEM][ORDEM], int jMaior, int jMenor, int kMaior, int kMenor){
	int contPecas = 0;
	int percorrerJ, percorrerK = kMenor;
	for(percorrerJ = jMenor+1; percorrerJ < jMaior; percorrerJ++){
		percorrerK++;
		if(tabuleiro[percorrerJ][percorrerK].jogador != VAZIO){
			contPecas++;
		}
	}
	if(contPecas > 0){
		return FALSE;
	}
	else{
		return TRUE;
	}
}

int movDiagCresDisponivel(peca tabuleiro[ORDEM][ORDEM], int jMaior, int jMenor, int kMaior, int kMenor){
	int contPecas = 0;
	int percorrerJ, percorrerK = kMenor;
	for(percorrerJ = jMaior-1; percorrerJ > jMenor; percorrerJ--){
		percorrerK++;
		if(tabuleiro[percorrerJ][percorrerK].jogador != VAZIO){
			contPecas++;
		}
	}
	if(contPecas > 0){
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

int verifMovDisponivel(peca tabuleiro[ORDEM][ORDEM], char vez, int enderPartida[TAM_ENDER], int enderChegada[TAM_ENDER], char pecaEscolhida){
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
		if(movDisponivel_Rei(enderPartida, enderChegada) == FALSE){
			return FALSE;
		}
		else{
			return TRUE;
		}
	}
	if(pecaEscolhida == PEAO){
		if(movDisponivel_Peao(tabuleiro, vez, enderPartida, enderChegada) == FALSE){
			return FALSE;
		}
		else{
			return TRUE;
		}
	}
}

void perguntarJogada(peca tabuleiro[ORDEM][ORDEM], char vez, int enderPartida[TAM_ENDER], int enderChegada[TAM_ENDER]){
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
	int movDisponivel = verifMovDisponivel(tabuleiro, vez, enderPartida, enderChegada, pecaEscolhida);
	while((enderDisponivel(tabuleiro, vez, enderChegada, CHEGADA) == FALSE) || (movDisponivel == FALSE)){
		printf("Coordenada invalida. Digite outra: ");
		lerCasa(casaChegada);
		caixaBaixa(casaChegada);
		casaPraEnder(casaChegada, enderChegada);
		movDisponivel = verifMovDisponivel(tabuleiro, vez, enderPartida, enderChegada, pecaEscolhida);
	}
}

void efetuarJogada(peca tabuleiro[ORDEM][ORDEM], int enderPartida[TAM_ENDER], int enderChegada[TAM_ENDER]){
	int j1 = enderPartida[0];
	int k1 = enderPartida[1];
	int j2 = enderChegada[0];
	int k2 = enderChegada[1];
	
	tabuleiro[j2][k2] = tabuleiro[j1][k1];
	tabuleiro[j2][k2].jogadas++;
	tabuleiro[j1][k1].nome = VAZIO;
	tabuleiro[j1][k1].jogador = VAZIO;
	tabuleiro[j1][k1].jogadas = 0;
}

void efetuarTurno(peca tabuleiro[ORDEM][ORDEM], char vez){
	int enderPartida[TAM_ENDER];
	int enderChegada[TAM_ENDER];
	
	perguntarJogada(tabuleiro, vez, enderPartida, enderChegada);
	efetuarJogada(tabuleiro, enderPartida, enderChegada);
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
	int turno = 0;
	char vez;
	char vencedor;
	
	char jogador1[TAM_NICKNAME];
	char jogador2[TAM_NICKNAME];
	
	printf("Informe seu nickname, jogador 1 (de 1 a 10 caracteres e sem espaco): ");
	lerNickname(jogador1);
	printf("\nInforme seu nickname, jogador 2 (de 1 a 10 caracteres e sem espaco): ");
	lerNickname(jogador2);
	
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
			efetuarTurno(tabuleiro, vez);
		}
	}while(vencedor == VAZIO);
	
	getch();
}
