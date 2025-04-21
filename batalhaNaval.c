#include <stdio.h>
#include <ctype.h>

#define tamNavio 3         // tamanho fixo dos navios até o momento
#define defNavio '3'         // valor representando um navio no tabuleiro
#define defAgua '='          // valor representando água
#define defAcerto 'X'        // valor representando um acerto
#define defErro 'M'          // valor representando um erro
#define LINHA 11             // tamanho do tabuleiro + Cabeçalho
#define COLUNA 11          // tamanho do tabuleiro + Cabeçalho
#define HABILIDADE 5        // Range de habilidades

int posicionamento(){
  char entrada;

  printf("\n Digite o caracter do eixo você quer colocar o seu navio?\n (H)Horizontal\n (V)ertical\n (\\)Contra-Diagonal\n (/)Diagonal?\n ");
    while(1) {
      scanf(" %c", &entrada);  // espaço antes do %c ignora lixo do buffer
      entrada = toupper(entrada);

      if (entrada == 'H' || entrada == 'V' || entrada == '\\' || entrada == '/') {
          switch(entrada){
            case 'H':
              printf(" Horizontal");
              return 0;
              break;
            case 'V':
              printf(" Vertical");
              return 1;
              break;
            case '\\':
              printf(" Contra-Diagonal");
              return 2;
              break;
            case '/':
              printf(" Diagonal");
              return 3;
              break;
          }
      } else {
          printf( "Comando Inválido! Tente novamente.\n ");
      }
    }
}

int localizacaoY(){
  char entrada;
  printf("\n Digite a letra da coluna da cordenada?(A-J)\n ");
  while(1) {
    scanf(" %c", &entrada);  // espaço antes do %c ignora lixo do buffer
    entrada = toupper(entrada);
    if (entrada >= 'A' && entrada <= 'J') {
        printf(" Coluna: %c", entrada);
      return entrada - 64;
    } else {
        printf( "Comando Inválido! Tente novamente.\n ");
    }
  }
};

int localizacaoX(){
  char entrada;
  printf("\n Digite o número da linha da cordenada?(0-9)\n ");
  while(1){
    scanf(" %c", &entrada);
    if (entrada >= '0' && entrada <= '9'){
      printf(" Linha: %d", entrada - '0');
      return entrada - '0' + 1;
    } else {
        printf( "Comando Inválido! Tente novamente.\n ");
    }
  }
}

void exibirTabuleiro(char tabuleiro[11][11]) {
    for (int i = 0; i < 11; i++) {
        printf("\n");
        for (int j = 0; j < 11; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
    }
    printf("\n");
}

int posicionarNavio(char tabuleiro[11][11], int tipoPose, int eixoX, int eixoY){

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

int selecaoDeAtaque(){
  printf("\n Digite o tipo de ataque ao qual quer realizar?\n (1)Cone\n (2)Cruz\n (3)Octaedro\n ");
  int entrada = 0;
  scanf(" %d", &entrada);
  do {
    scanf(" %d", &entrada);
    if (entrada < 1 || entrada > 3) {
      printf("Comando Inválido! Tente novamente.\n ");
    };
  } while (entrada < 1 || entrada > 3);
  switch(entrada){
    case 1:
      printf(" Cone");
      return 1;
      break;
    case 2:
      printf(" Cruz");
      return 2;
      break;
    default:
      printf(" Octaedro");
      return 3;
      break;
  }
};

void criarAtaque(int habilidade[HABILIDADE][HABILIDADE], int tipo){
  int centro = HABILIDADE/2;
  switch(tipo){
    case 1:
      // Cone
      for(int i = 0; i < HABILIDADE; i++){
        for(int j = 0; j < HABILIDADE; j++){
          if (j >= centro - i && j <= centro + i && i <= centro){
            habilidade[i][j] = 1;
          } else {
            habilidade[i][j] = 0;
          }
        }
      }
      break;
    case 2:
      // Cruz
      for(int i = 0; i < HABILIDADE; i++){
        for(int j = 0; j < HABILIDADE; j++){
          if ( i == centro || j == centro){
            habilidade[i][j] = 1;
          } else {
            habilidade[i][j] = 0;
          }
        }  
      }
      break;
    default:
      // Octaedro
      for(int i = 0; i < HABILIDADE; i++){
        for(int j = 0; j < HABILIDADE; j++){
          if (i == centro || j == centro || i == j || i + j == HABILIDADE - 1){
            habilidade[i][j] = 1;
          } else {
            habilidade[i][j] = 0;
          }
        }
      }
      break;
  }  
}

void aplicarAtaque( char tabuleiro[LINHA][COLUNA], 
                    int habilidade[HABILIDADE][HABILIDADE], 
                    int eixoX, int eixoY, int *vida){
  
  int centro = HABILIDADE/2;

  for(int i = 0; i < HABILIDADE; i++){
    for(int j = 0; j < HABILIDADE; j++){
      int x = eixoX + i - centro;
      int y = eixoY + j - centro;

      if (x >= 0 && x < LINHA && y >= 0 && y < COLUNA){
        if (habilidade[i][j] == 1 && tabuleiro[x][y] == defAgua) {
          tabuleiro[x][y] = defErro;
        } else if (habilidade[i][j] == 1 && tabuleiro[x][y] == defNavio) {
          (*vida)--;
          tabuleiro[x][y] = defAcerto;
        }
      }
    }
  }
};
  
int main() {
  // Inicializa o tabuleiro 10x10.
  char tabuleiro[LINHA][COLUNA] = {{0}};
  int habilidade[HABILIDADE][HABILIDADE] = {{0}};
  int countNavios = 0;
  int vida = 0;

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

  while (countNavios < 4){

    int tipoPose = posicionamento(); // 0 horizontal, 1 vertical, 2 contra-diagonal, 3 diagonal
    printf("\n Agora escolha a localização do navio:");
    int eixoX = localizacaoX(); // Criar Colunas de 1 a 9
    int eixoY = localizacaoY(); // Criar Linhas de A a I

    printf("\n");
    #ifdef _WIN32
      system("cls");
    #else
      system("clear");
    #endif


    countNavios += posicionarNavio(tabuleiro, tipoPose, eixoX, eixoY);
    vida += tamNavio;
    exibirTabuleiro(tabuleiro);
  }

  int end = 0; // variável de finalização do jogo;

  while (vida != 0) {
    int tipo = selecaoDeAtaque();
    int eixoX = localizacaoX();
    int eixoY = localizacaoY();
    criarAtaque(habilidade, tipo);
    
    //verificarAtaque(habilidade);
    aplicarAtaque(tabuleiro, habilidade, eixoX, eixoY, &vida);

    printf("\n");
    #ifdef _WIN32
      system("cls");
    #else
      system("clear");
    #endif

    
    exibirTabuleiro(tabuleiro);
  }
  printf("\n Você venceu!");
  // Coordenadas iniciais do primeiro navio
  return 0;
}

