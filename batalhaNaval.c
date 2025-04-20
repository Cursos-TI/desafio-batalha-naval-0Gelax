#include <stdio.h>

#define tamNavio 3         // tamanho fixo dos navios até o momento
#define defNavio '1'         // valor representando um navio no tabuleiro
#define defAgua '0'          // valor representando água

int posicionamento(){
  char entrada;

  printf("\n Digite o caracter do eixo você quer colocar o seu navio? (H)Horizontal, (V)ertical (\\)Contra-Diagonal ou (/)Diagonal?\n ");
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

int localizacaoY(){
  char entrada;
  printf("\n Digite a letra da coluna que você quer colocar o seu navio?(A-I)\n ");
  while(1) {
    scanf(" %c", &entrada);  // espaço antes do %c ignora lixo do buffer
    entrada = toupper(entrada);
    if (entrada >= 'A' && entrada <= 'I') {
        printf("Coluna: %c", entrada);
      return entrada - 64;
    } else {
        printf( "Comando Inválido! Tente novamente.\n ");
    }
  }
};

int localizacaoX(){
  char entrada;
  printf("\n Digite o número da linha que você quer colocar o seu navio?(1-9)\n ");
  while(1){
    scanf(" %c", &entrada);
    if (entrada >= '1' && entrada <= '9'){
      printf("Linha: %d", entrada - 48);
      return entrada - 48;
    } else {
        printf( "Comando Inválido! Tente novamente.\n ");
    }
  }
}

int main() {

  // Inicializa o tabuleiro 10x10.
  char * tabuleiro[10][10] = {{0}};

  // Inicializa o tabuleiro com água (0), mas não exibe
  for (int i = 0; i<10; i++){
    printf("\n");
    for (int j = 0; j<10; j++){
        if (i == 0 && j == 0){
        tabuleiro[i][j] = ' ';
      } else if (i == 0) {
        tabuleiro[i][j] = 'A' -1 + j;
      } else if (j == 0) {
        tabuleiro[i][j] = '0' + i;
      } else {
        tabuleiro[i][j] = defAgua;
      }
      printf("%c ", tabuleiro[i][j]);
    }
  }

  // Coordenadas iniciais do primeiro navio
  int tipoPose = posicionamento(); // 0 horizontal, 1 vertical, 2 contra-diagonal, 3 diagonal
  int eixoX = localizacaoX(); // Criar Colunas de 1 a 9
  int eixoY = localizacaoY(); // Criar Linhas de A a I

    printf("\n");
    system("clear");

  switch(tipoPose){
    case 0:
      for (int i = 0; i < tamNavio; i++){
        if (eixoY >= 8) {
          tabuleiro[eixoX][7 + i] = defNavio;
        } else {
          tabuleiro[eixoX][eixoY + i] = defNavio;
        }
      };
    break;
    case 1:
      for (int i = 0; i < tamNavio; i++){
        if (eixoX >= 8){
          tabuleiro[7 + i][eixoY] = defNavio;
        } else {
          tabuleiro[eixoX + i][eixoY] = defNavio;
        }
      };
    break;
    case 2:
      for (int i = 0; i < tamNavio; i++){
        if (eixoX >= 8 && eixoY >= 8){
          tabuleiro[7 + i][7 + i] = defNavio;
        } else if (eixoX >= 8){
          tabuleiro[7 + i][eixoY + i] = defNavio;
        } else if (eixoY >= 8){
          tabuleiro[eixoX + i][7 + i] = defNavio;
        } else {
          tabuleiro[eixoX + i][eixoY + i] = defNavio;
        }
      };
    break;
    default:
      for (int i = 0; i < tamNavio; i++){
        if (eixoX <= 2 && eixoY >= 2){
          tabuleiro[3 - i][7 + i] = defNavio;
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
  
  for (int i = 0; i<10; i++){
    printf("\n");
    for (int j = 0; j<10; j++){
      printf("%c ", tabuleiro[i][j]);
    }
  }

  return 0;
}