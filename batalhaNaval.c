#include <stdio.h>

#define tamNavio 3            // tamanho fixo dos navios até o momento
#define defNavio '3'          // valor representando um navio no tabuleiro
#define defAgua '='           // valor representando água
#define LINHA 11              // tamanho do tabuleiro + Cabeçalho
#define COLUNA 11             // tamanho do tabuleiro + Cabeçalho

int posicionamento(){         //Escolher a posição do bloco do navio a ser colocado
  char entrada;

  printf("\n Digite o caracter do eixo você quer colocar o seu navio?\n (H)Horizontal\n (V)ertical\n (\\)Contra-Diagonal\n (/)Diagonal?\n ");
    while(1) {
      scanf(" %c", &entrada);  // espaço antes do %c ignora lixo do buffer
      entrada = toupper(entrada);

      if (entrada == 'H' || entrada == 'V' || entrada == '\\' || entrada == '/') {
          switch(entrada){
            case 'H':
              printf("Horizontal");
              return 0;
              break;
            case 'V':
              printf("Vertical");
              return 1;
              break;
            case '\\':
              printf("Contra-Diagonal");
              return 2;
              break;
            case '/':
              printf("Diagonal");
              return 3;
              break;
          }
      } else {
          printf( "Comando Inválido! Tente novamente.\n ");
      }
    }
}

int localizacaoY(){           // Posição do Inicio do navio(Queria que fosse o meio, mas já comecei assim)
  char entrada;
  printf("\n Digite a letra da coluna que você quer colocar o seu navio?(A-J)\n ");
  while(1) {
    scanf(" %c", &entrada);  // espaço antes do %c ignora lixo do buffer
    entrada = toupper(entrada);
    if (entrada >= 'A' && entrada <= 'J') {
        printf("Coluna: %c", entrada);
      return entrada - 64;
    } else {
        printf( "Comando Inválido! Tente novamente.\n ");
    }
  }
};

int localizacaoX(){         // Posição do Inicio do navio(Queria que fosse o meio, mas já comecei assim)
  char entrada;
  printf("\n Digite o número da linha que você quer colocar o seu navio?(0-9)\n ");
  while(1){
    scanf(" %c", &entrada);
    if (entrada >= '0' && entrada <= '9'){
      printf("Linha: %d", entrada - 47);
      return entrada - '0' + 1;
    } else {
        printf( "Comando Inválido! Tente novamente.\n ");
    }
  }
}

void exibirTabuleiro(char tabuleiro[11][11]) { // Atualização do Tabuleiro, após o mesmo ter sido criado
    for (int i = 0; i < 11; i++) {
        printf("\n");
        for (int j = 0; j < 11; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
    }
    printf("\n");
}

int posicionarNavio(char tabuleiro[11][11], int tipoPose, int eixoX, int eixoY){ // Aplicar o Navio no mapa

  if (tabuleiro[eixoX][eixoY] != defAgua){ 
  printf("\n Não foi possível posicionar o navio!\n Tente novamente.");
  return 0;
} else {
  switch(tipoPose){
    case 0:
      //horizontal
      for (int i = 0; i < tamNavio; i++){
        if (eixoY >= (LINHA - 2)) {
          tabuleiro[eixoX][COLUNA - 3 + i] = defNavio;
        } else {
          tabuleiro[eixoX][eixoY + i] = defNavio;
        }
      };
    break;
    case 1:
      //vertical
      for (int i = 0; i < tamNavio; i++){
        if (eixoX >= (LINHA - 2)){
          tabuleiro[LINHA - 3 + i][eixoY] = defNavio;
        } else {
          tabuleiro[eixoX + i][eixoY] = defNavio;
        }
      };
    break;
    case 2:
      //contra-diagonal
      for (int i = 0; i < tamNavio; i++){
        if (eixoX >= (LINHA - 2) && eixoY >= (COLUNA - 2)){
          tabuleiro[LINHA - 3 + i][COLUNA - 3 + i] = defNavio;
        } else if (eixoX >= (COLUNA - 2)){
          tabuleiro[LINHA - 3 + i][eixoY + i] = defNavio;
        } else if (eixoY >= (COLUNA - 2)){
          tabuleiro[eixoX + i][COLUNA - 3 + i] = defNavio;
        } else {
          tabuleiro[eixoX + i][eixoY + i] = defNavio;
        }
      };
    break;
    default:
      //diagonal
      for (int i = 0; i < tamNavio; i++){
        if (eixoX <= 2 && eixoY >= 2){
          tabuleiro[3 - i][COLUNA - 3 + i] = defNavio;
        } else if (eixoX >= 2){
          tabuleiro[3 - i][eixoY + i] = defNavio;
        } else if (eixoY >=2){
          tabuleiro[eixoX - i][3 + i] = defNavio;
        } else {
          tabuleiro[eixoX - i][eixoY + i] = defNavio;
        }
      }
    break;
  }
  return 1;
}}

int main() {
  // Inicializa o tabuleiro 10x10.
  char tabuleiro[LINHA][COLUNA] = {{0}};
  int countNavios = 0;

  // Inicializa o tabuleiro com água (0), mas não exibe
  for (int i = 0; i<LINHA; i++){
    for (int j = 0; j<COLUNA; j++){
        if (i == 0 && j == 0){
        tabuleiro[i][j] = ' ';
      } else if (i == 0) {
        tabuleiro[i][j] = 'A' -1 + j;
      } else if (j == 0) {
        tabuleiro[i][j] = '0' + i - 1;
      } else {
        tabuleiro[i][j] = defAgua;
      }
    }
  }

  exibirTabuleiro(tabuleiro);

  while (countNavios < 4){ // Colocar 4 Navios pelo menos. Começa em 0 e vai até 3... logo 4 návios.

    int tipoPose = posicionamento(); // 0 horizontal, 1 vertical, 2 contra-diagonal, 3 diagonal
    int eixoX = localizacaoX(); // Criar Colunas de 1 a 9
    int eixoY = localizacaoY(); // Criar Linhas de A a I

    printf("\n");
    system("clear"); //Apagar o antigo mapa para exibir o novo

    countNavios += posicionarNavio(tabuleiro, tipoPose, eixoX, eixoY);
    exibirTabuleiro(tabuleiro);
    
  }
  return 0;
}