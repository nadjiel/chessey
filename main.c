/*
Atualizar turno fazendo o loop principal
Continuar trabalhando no procedimento perguntarJogada()
Fazer casos nos quais outras pecas foram escolhidas
Fazer os eventos especiais, tipo xeque, roque
Elaborar se as pecas escolhidas nao sao torres estao livres ou presas, tal como se um movimento escolhido para ser realizado com elas seria possível
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
const int TAMANHO_NICKNAME = 11;
const int TAMANHO_CASA = 3;
const int TAMANHO_ENDER = 2;
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

void casaPraEnder(char casa[TAMANHO_CASA], int ender[TAMANHO_ENDER]){
	ender[0] = coordCharPraCoordInt(casa[1]);
	ender[1] = coordCharPraCoordInt(casa[0]);
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

void lerCasa(char casa[TAMANHO_CASA]){
	fflush(stdin);
	scanf("%s",casa);
}

char verifVez(int turno){
	if(turno % 2 == 1){
		return '1';
	}
	else{
		return '2';
	}
}

char vezIntPraVezChar(int vez){
	switch(vez){
		case 1: return '1';
		case 2: return '2';
	}
}

int enderPartidaDisponivel(peca tabuleiro[ORDEM][ORDEM], char vez, int enderPartida[TAMANHO_ENDER], int j, int k){
	if(tabuleiro[j][k].jogador == vez){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

int enderChegadaDisponivel(peca tabuleiro[ORDEM][ORDEM], char vez, int enderChegada[TAMANHO_ENDER], int j, int k){
	if(tabuleiro[j][k].jogador != vez){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

int enderDisponivel(peca tabuleiro[ORDEM][ORDEM], char vez, int ender[TAMANHO_ENDER], char tipoEnder){
	int j, k;
	j = ender[0];
	k = ender[1];
	int resultado;
	if(j == ERRO || k == ERRO){
		return FALSE;
	}
	else{
		switch(tipoEnder){
			case 'P': resultado = enderPartidaDisponivel(tabuleiro, vez, ender, j ,k);
						  break;
			case 'C': resultado = enderChegadaDisponivel(tabuleiro, vez, ender, j ,k);
		}
		return resultado;
	}
}

char verifPeca(peca tabuleiro[ORDEM][ORDEM], int ender[TAMANHO_ENDER]){
	int j = ender[0];
	int k = ender[1];
	return tabuleiro[j][k].nome;
}

int movHorizDisponivel(peca tabuleiro[ORDEM][ORDEM], int j, int kMaior, int kMenor){
	int percorrer;
	for(percorrer = ++kMenor; percorrer < kMaior; percorrer++){
		if((tabuleiro[j][percorrer].jogador == '1') || (tabuleiro[j][percorrer].jogador == '2')){
			return FALSE;
		}
		else{
			return TRUE;
		}
	}
}

int movVertiDisponivel(peca tabuleiro[ORDEM][ORDEM], int k, int jMaior, int jMenor){
	int percorrer;
	for(percorrer = ++jMenor; percorrer < jMaior; percorrer++){
		if((tabuleiro[percorrer][k].jogador == '1') || (tabuleiro[percorrer][k].jogador == '2')){
			return FALSE;
		}
		else{
			return TRUE;
		}
	}
}

int movDisponivel_4Direcoes(peca tabuleiro[ORDEM][ORDEM], int enderPartida[TAMANHO_ENDER], int enderChegada[TAMANHO_ENDER]){
	if((enderPartida[0] != enderChegada[0]) && (enderPartida[1] != enderChegada[1])){
		return FALSE;
	}
	int j1 = enderPartida[0];
	int j2 = enderChegada[0];
	int k1 = enderPartida[1];
	int k2 = enderChegada[1];
	int percorrer;
	int resultado;
	if(j1 == j2){
		if(k1 > k2){
			resultado = movHorizDisponivel(tabuleiro, j1, k1, k2);
		}
		else{
			resultado = movHorizDisponivel(tabuleiro, j1, k2, k1);
		}
		return resultado;
	}
	if(k1 == k2){
		if(j1 > j2){
			resultado = movVertiDisponivel(tabuleiro, k1, j1, j2);
		}
		else{
			resultado = movVertiDisponivel(tabuleiro, k1, j2, j1);
		}
		return resultado;
	}
}

int haPecaJogadorAtual(peca tabuleiro[ORDEM][ORDEM], char vez, int j, int k){
	if(tabuleiro[j][k].jogador == vez){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

int pecaLivre_4Direcoes(peca tabuleiro[ORDEM][ORDEM], char vez, int ender[TAMANHO_ENDER]){
	int j = ender[0];
	int k = ender[1];
	int pecasBloqueando = 0;
	pecasBloqueando += haPecaJogadorAtual(tabuleiro, vez, j+1, k);
	pecasBloqueando += haPecaJogadorAtual(tabuleiro, vez, j, k+1);
	pecasBloqueando += haPecaJogadorAtual(tabuleiro, vez, j-1, k);
	pecasBloqueando += haPecaJogadorAtual(tabuleiro, vez, j, k-1);
	if(pecasBloqueando == 4){
		return FALSE;
	}
	else{
		return TRUE;
	}
}

void perguntarJogada(peca tabuleiro[ORDEM][ORDEM], char vez, int enderPartida[TAMANHO_ENDER], int enderChegada[TAMANHO_ENDER]){
	char casaPartida[TAMANHO_CASA];
	printf("\nQual peca voce quer mexer? ");
	lerCasa(casaPartida);
	casaPraEnder(casaPartida, enderPartida);
	char pecaEscolhida;
	int pecaLivre;
	do{
		while(enderDisponivel(tabuleiro, vez, enderPartida, PARTIDA) == FALSE){
			printf("Coordenada invalida. Digite outra: ");
			lerCasa(casaPartida);
			casaPraEnder(casaPartida, enderPartida);
		}
		pecaEscolhida = verifPeca(tabuleiro, enderPartida);
		if(pecaEscolhida == TORRE){
			if(pecaLivre_4Direcoes(tabuleiro, vez, enderPartida) == FALSE){
				pecaLivre = FALSE;
			}
			else{
				pecaLivre = TRUE;
			}
		}
		
		
		
	}while(pecaLivre == FALSE);
	
	char casaChegada[TAMANHO_CASA];
	printf("\nPara qual casa voce quer mecher essa peca? ");
	lerCasa(casaChegada);
	casaPraEnder(casaChegada, enderChegada);
	int movDisponivel;
	do{
		while(enderDisponivel(tabuleiro, vez, enderChegada, CHEGADA) == FALSE){
			printf("Coordenada invalida. Digite outra: ");
			lerCasa(casaChegada);
			casaPraEnder(casaChegada, enderChegada);
		}
		if(pecaEscolhida == TORRE){
			if(movDisponivel_4Direcoes(tabuleiro, enderPartida, enderChegada) == FALSE){
				movDisponivel = FALSE;
			}
			else{
				movDisponivel = TRUE;
			}
		}
		
		
		
	}while(movDisponivel == FALSE);
}

void efetuarJogada(peca tabuleiro[ORDEM][ORDEM], int enderPartida[TAMANHO_ENDER], int enderChegada[TAMANHO_ENDER]){
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
	int enderPartida[TAMANHO_ENDER];
	int enderChegada[TAMANHO_ENDER];
	perguntarJogada(tabuleiro, vez, enderPartida, enderChegada);
	efetuarJogada(tabuleiro, enderPartida, enderChegada);
}

void main(){
	
	peca tabuleiro[ORDEM][ORDEM];
	iniciarTabuleiro(tabuleiro);
	char jogador1[TAMANHO_NICKNAME];
	char jogador2[TAMANHO_NICKNAME];
	/*
	lerNickname(jogador1);
	printf("\n");
	lerNickname(jogador2);
	*/
	int turno = 0;
	
	int loopInfinito = TRUE;
	
	do{
		printf("\n\n");
		turno++;
		char vez = verifVez(turno);
		imprimirTabuleiro(tabuleiro);
		efetuarTurno(tabuleiro, vez);
		
	}while(loopInfinito == TRUE);
	
	getch();
}
