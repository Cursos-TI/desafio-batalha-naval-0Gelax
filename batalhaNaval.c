#include <stdio.h>

#define SHIPSIZE 3
#define SHIPCOUNT 1
#define SHIPSYMBOL '3'
#define mapSizeX 10
#define mapSizeY 10

// Função para mostrar/atualizar o mapa
void showMap(char map[mapSizeX][mapSizeY]) {
  // Limpar a tela antes de mostrar o mapa, caso não funcione, remova o system("clear")
  system("clear");
  // Aqui é para evidenciar o system clear
  
  printf("    "); // Espaço para alinhar com índice da linha
  for (int j = 0; j < mapSizeY; j++) {
      printf("%c ", 'A' + j);  // cuidado com j > 26, pois vai faltar letras;
  }
  printf("\n");

  // Mostrar linhas
  for (int i = 0; i < mapSizeX; i++) {
      printf("%3d ", i);  // Mostra número da linha com largura fixa, da mesma forma que tem no float %2.2f 2 espaços e 2 casas decimais.
      for (int j = 0; j < mapSizeY; j++) {
          printf("%c ", map[i][j]);
      }
      printf("\n");
  }
}

// Função para criar o mapa e resetar o mapa(caso precise futuramente).
void createMap(char map[mapSizeX][mapSizeY]) {
  for (int i = 0; i < mapSizeX; i++) {
    for (int j = 0; j < mapSizeY; j++) {
        map[i][j] = '0';
    }
  }
  showMap(map);
}

// Função para criar navios no mapa
void createShips(char map[mapSizeX][mapSizeY]) {
  // Variáveis para armazenar as informações do navio, ficou dessa forma por que eu lembrei do define tarde demais e deu preguiça;
  int shipSize = SHIPSIZE;       // tamanho do navio
  int shipCount = SHIPCOUNT;     // quantidade de navios
  char shipSymbol = SHIPSYMBOL;  // símbolo do navio

  printf("\nInstruções para posicionar os navios:\n");
  printf("1° O tabuleiro vai de A a J nas colunas e de 0 a 9 nas linhas.\n");
  printf("2° Cada navio ocupa 3 posições.\n");
  printf("3° Digite as coordenadas inicial e final de forma que o navio fique em linha reta ou diagonal.\n");
  printf("4° Exemplos válidos: A 0 até C 0 (horizontal), B 1 até B 3 (vertical), D 3 até F 5 (diagonal).\n\n");
  
  while (shipCount > 0) {
    char colStartChar, colEndChar;
    int rowStart, rowEnd;

    printf("Digite a coordenada INICIAL (ex: A 1): ");
    scanf(" %c %d", &colStartChar, &rowStart);

    printf("Digite a coordenada FINAL (ex: C 1): ");
    scanf(" %c %d", &colEndChar, &rowEnd);

    int colStart = colStartChar - 'A'; // Converter letra para número para facilitar a manipulação
    int colEnd = colEndChar - 'A'; // Converter letra para número para facilitar a manipulação
    int startRow = rowStart;
    int endRow = rowEnd;

    int rowDiff = endRow - startRow;  // diferença de linhas
    int colDiff = colEnd - colStart;  // diferença de colunas

    // Verificar se o navio ocupa exatamente 3 posições em linha reta ou diagonal
    // Depois, embora eu não vá alterar a adaptabilidade desse trecho de acordo com o tamanho do navio.
    if (
      (rowDiff == 0 && (colDiff == 2 || colDiff == -2)) ||
      (colDiff == 0 && (rowDiff == 2 || rowDiff == -2)) ||
      ((rowDiff == 2 || rowDiff == -2) && (colDiff == 2 || colDiff == -2))
    ) {

    // Verificar Movimento
      int rowStep = (rowDiff == 0) ? 0 : 1;
      int colStep = (colDiff == 0) ? 0 : 1;

      int overlap = 0;
      for (int i = 0; i < shipSize; i++) {
        int row = startRow + i * rowStep;
        int column = colStart + i * colStep;
        
      // Verificar se há sobreposição com outro navio
        if (map[row][column] != '0') {
          overlap = 1;
          break;
        }
      }

      if (overlap) {
        printf("Erro: há sobreposição com outro navio ou foi selecionado uma coordenada não válida. Tente novamente.\n");
        continue;
      }

      for (int i = 0; i < shipSize; i++) {
        int row = startRow + i * rowStep;
        int column = colStart + i * colStep;
        map[row][column] = shipSymbol;
      }

      shipCount--;
    } else {
      printf("Erro: o navio deve ocupar exatamente 3 posições em linha reta ou diagonal.\n");
    }
  }
  showMap(map);
}
// Tipos de ataques
const int coneAttack[3][5] = {
  {0, 0, 1, 0, 0},
  {0, 1, 1, 1, 0},
  {1, 1, 1, 1, 1},
};

const int crossAttack[3][5] = {
  {0, 0, 1, 0, 0},
  {1, 1, 1, 1, 1},
  {0, 0, 1, 0, 0},
};

const int octaAttack[3][5] = {
  {0, 0, 1, 0, 0},
  {0, 1, 1, 1, 0},
  {0, 0, 1, 0, 0},
};

// Função para aplicar o ataque e retornar quantos acertos realizou
int applyAttack(char map[mapSizeX][mapSizeY], int x, int y, const int pattern[3][5]) {
  int lifeLoss = 0;
  
  // Ajustar as coordenadas para que o ataque seja centralizado na posição (x, y)
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      if (pattern[i][j] == 1) {
        int dx = x + i - 1;
        int dy = y + j - 1;

        // Verificar aonde o ataque vai ser aplicado e se é um acerto ou não
        // Caso seja qualquer coisa diferente de 0 3 vai ser ignorado, assim evitando que atinja fora do mapa ou em um navio já atingido.
        if (dx >= 0 && dx < mapSizeX && dy >= 0 && dy < mapSizeY) {
          if (map[dx][dy] == '0') {
            map[dx][dy] = 'M';
          } else if (map[dx][dy] == SHIPSYMBOL) {
            // Se for um navio, marca como atingido e reduz 1 ponto de vida.
            map[dx][dy] = 'X';
            lifeLoss++;
          }
        }
      }
    }
  }
  return lifeLoss;
}

void gameStart(char map[mapSizeX][mapSizeY]){
  int vida = SHIPSIZE * SHIPCOUNT;
  int atkType = 0;
  printf("Jogo iniciado!\n");
  
  do{
    
    system("clear");
    showMap(map);
    
    printf("Vida do adversário: %d\n", vida);
    
    printf("\nEscolha o tipo de ataque que deseja realizar (C é a coordenada inicial, X são as áreas atingidas):\n");

    printf("\n1 - Ataque em **cone**:\n");
    printf("  0 0 X 0 0\n");
    printf("  0 X C X 0\n");
    printf("  X X X X X\n");

    printf("\n2 - Ataque em **cruz**:\n");
    printf("  0 0 X 0 0\n");
    printf("  X X C X X\n");
    printf("  0 0 X 0 0\n");

    printf("\n3 - Ataque em **octaedro**:\n");
    printf("  0 0 X 0 0\n");
    printf("  0 X C X 0\n");
    printf("  0 0 X 0 0\n");
    
    do {
        printf("\nDigite o número correspondente ao tipo de ataque:\n");
        scanf("%d", &atkType);
        if (atkType < 1 || atkType > 3) {
            printf("Opção inválida. Tente novamente.\n");
        };
    } while(atkType < 1 || atkType > 3);

    printf("Digite a coordenada INICIAL (ex: A 1): ");
    char colChar;
    int row;
    scanf(" %c %d", &colChar, &row);
    int col = colChar - 'A'; // Converter letra para número para facilitar a manipulação.
    if (row < 0 || row >= mapSizeX || col < 0 || col >= mapSizeY){
      printf("Coordenada inválida. Tente novamente.\n");
      continue;
    }
    col -= 1; // ajuste de índice para o mapa;
    
    switch(atkType){
      case 1:
        vida -= applyAttack(map, row, col, coneAttack);
        break;
      case 2:
        vida -= applyAttack(map, row, col, crossAttack);
        break;
      case 3:
        vida -= applyAttack(map, row, col, octaAttack);
        break;
    }
  } while(vida>0);
  
  
  showMap(map);
  printf("\nVocê venceu!\n\n");
}

int main() {
  char map[mapSizeX][mapSizeY];

  createMap(map);
  createShips(map);
  gameStart(map);
  
  return 0;
}
