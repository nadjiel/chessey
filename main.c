/*
Atualizar turno fazendo o loop principal
Perguntar onde deseja mover a peca
Ajustar comparacoes de ints com o campo .jogador do registro, que eh char
Continuar trabalhando no procedimento perguntarJogada()
*/

#include<stdio.h>

typedef struct tipoPeca{
	char nome;
	char jogador;
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
const char NORTE = 'n';
const char SUL = 's';
const char LESTE = 'l';
const char OESTE = 'o';

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

char coordNumPraCoordLetra(int coord){
	switch(coord){
		case 1: return 'a';
		case 2: return 'b';
		case 3: return 'c';
		case 4: return 'd';
		case 5: return 'e';
		case 6: return 'f';
		case 7: return 'g';
		case 8: return 'h';
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
	int cont = 0;
	printf("    ");
	for(k = 0; k < ORDEM; k++){
		cont++;
		printf("%c  ",coordNumPraCoordLetra(cont));
	}
	printf("\n\n");
	cont = 0;
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

int casaDisponivel(peca tabuleiro[ORDEM][ORDEM], int turno, char casa[TAMANHO_CASA]){
	int j, k;
	j = coordCharPraCoordInt(casa[0]);
	k = coordCharPraCoordInt(casa[1]);
	if(j == ERRO || k == ERRO){
		return FALSE;
	}
	else{
		int vez = verifVez(turno);
		if(tabuleiro[j-1][k-1].jogador == vez){
			return TRUE;
		}
		else{
			return FALSE;
		}
	}
}

char verifPeca(peca tabuleiro[ORDEM][ORDEM], char casa[TAMANHO_CASA]){
	int j = coordCharPraCoordInt(casa[0]) - 1;
	int k = coordCharPraCoordInt(casa[1]) - 1;
	return tabuleiro[j][k].nome;
}

int direcaoDisponivelTorre(peca tabuleiro[ORDEM][ORDEM], int turno, char casa[TAMANHO_CASA], char direcao){
	int j = coordCharPraCoordInt(casa[0]) - 1;
	int k = coordCharPraCoordInt(casa[1]) - 1;
	int vez = verifVez(turno);
	if((direcao != NORTE) || (direcao != SUL) || (direcao != LESTE) || (direcao != OESTE)){
		return FALSE;
	}
	else{
		if((j == 0 || j == 7) || (k == 0 || k == 7)){
			if(direcao == NORTE && j == 0){
				return FALSE;
			}
			else if(direcao == SUL && j == 7){
					 return FALSE;
				 }
				 else if(direcao == LESTE && k == 7){
						  return FALSE;
					  }
					  else if(direcao == OESTE && k == 0){
							   return FALSE;
						   }
		}
		if(direcao == NORTE && tabuleiro[j-1][k].jogador == vez){
			return FALSE;
		}
		else if(direcao == SUL && tabuleiro[j+1][k].jogador == vez){
				 return FALSE;
			 }
			 else if(direcao == LESTE && tabuleiro[j][k+1].jogador == vez){
					  return FALSE;
				  }
				  else if(direcao == OESTE && tabuleiro[j][k-1].jogador == vez){
						   return FALSE;
					   }
					   else{
					   	return TRUE;
					   }
	}
}

void perguntarJogada(peca tabuleiro[ORDEM][ORDEM], int turno){
	char casa[TAMANHO_CASA];
	fflush(stdin);
	printf("\nDigite a coordenada da casa na qual estah a peca que voce quer mexer: ");
	scanf("%s",casa);
	while(casaDisponivel(tabuleiro, turno, casa) == FALSE){
		fflush(stdin);
		printf("Coordenada invalida. Digite outra: ");
		scanf("%s",casa);
	}
	char pecaEscolhida = verifPeca(tabuleiro, casa);
	char direcao;
	if(pecaEscolhida == TORRE){
		fflush(stdin);
		printf("\nPara que direcao voce quer mover a peca? (n, s, l ou o) ");
		scanf("%c",&direcao);
		while(direcaoDisponivelTorre(tabuleiro, turno, casa, direcao) == FALSE){
			fflush(stdin);
			printf("Direcao invalida. Informe uma direcao entre n, s, l e o: ");
			scanf("%c",&direcao);
		}
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
