#include "cabecalho.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {

  // Inicializando lista
  gerenciador g;
  int op;
  init(&g);

  // Menu
  printf("\n# Digite 0 para ajuda\n");
  do{
    printf("\n# Menu\n> ");
    input(&op);
    switch(op){
      case 0:
        help();
      break;
      case 1:
        menuAdd(&g);
      break;
      case 2:
        menuRemove(&g);
      break;
      case 3:
        menuSearch(&g);
      break;
      case 4:
        menuShow(&g);
      break;
      case 5:
        menuUpdateStatus(&g);
      break;
      case -1:
        printf("Encerrando programa...");
      break;
      default:
        printf("(!) Opção inválida\n");
      break;
      
    }
  }
  while(op != -1);

  free(g.tarefas);
  
  return 0;
}