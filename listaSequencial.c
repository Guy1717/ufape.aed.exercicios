#include "cabecalho.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int newId =  0;


// Funções Lista
int init(gerenciador* g){
  g->capacidade = 10;
  g->qtdTarefas = 0;
  g->tarefas = malloc(sizeof(tarefa) * g->capacidade);
  return 0;
}

int show(gerenciador* g){

  if(isEmpty(g)){
    printf("(!) Lista vazia\n");
    return -1;
  }
  else{
    printf("\n# Listando tarefas...\n");
    printf("  id |stats|    prazo     |  descricao\n");
    printf("--------------------------------------\n");
    for(int i = 0; i < size(g); i++){
      tarefa task = g->tarefas[i];
      printf("· %d  |  %d  |  %s  |  %s\n", task.id, task.status, task.prazo, task.descricao);
    }
  }
  return 0;
}

int showFilter(gerenciador* g, int status){
  if(isEmpty(g)){
    printf("(!) Lista vazia\n");
    return -1;
  }
    
  else{
    printf("\n# Listando tarefas filtradas...\n");
    printf("  id |stats|    prazo     |  descricao\n");
    printf("--------------------------------------\n");
    for(int i = 0; i < size(g); i++){
      if(g->tarefas[i].status == status){
        tarefa task = g->tarefas[i];
        printf("· %d  |  %d  |  %s  |  %s\n", task.id, task.status, task.prazo, task.descricao);
      }
    }
  }
    
  return 0;
}

int isEmpty(gerenciador* g){
  return size(g) == 0;
}

int size(gerenciador* g){
  return g->qtdTarefas;
}

int addAtEnd(gerenciador* g, tarefa t){
  
  checkMemory(g);

  g->tarefas[g->qtdTarefas++] = t;

  return 0;  
}

int addAtBeginning(gerenciador* g, tarefa t){

  checkMemory(g);
  if(g){
    for(int i = size(g) ; i > 0 ; i--)
      g->tarefas[i] = g->tarefas[i-1];

    g->tarefas[0] = t;
    g->qtdTarefas++;
  }
  else
    return -1;

  return 0;
}

int addAtIndex(gerenciador* g, tarefa t, int index){

  checkMemory(g);

  for(int i = size(g) ; i > index ; i--){
    g->tarefas[i] = g->tarefas[i-1];
  }

  g->tarefas[index] = t;
  g->qtdTarefas++;

  return 0;  
}

int removeAtIndex(gerenciador* g, int index){
  if(isEmpty(g))
    return -1;
  else{
    if(index < size(g) && index >= 0){ // Se index válido
      for(int i = index ; i < size(g); i++)
        g->tarefas[i] = g->tarefas[i+1]; // Reordena elementos
      g->qtdTarefas--;
      return 0;  
    }
    else
      return -1;
  }
}

int removeById(gerenciador* g, int id){
  if(isEmpty(g))
    return -1;
  else{
    for(int i=0 ; i<size(g) ; i++){
      if(g->tarefas[i].id == id){
        if(!removeAtIndex(g, i))
          return 0;
      }
    }
  }

  return -1;
}

int search(gerenciador* g, int id){
  if(isEmpty(g)){
    printf("(!) Lista vazia\n");
    return -1;
  }
  else{
    for(int i = 0; i < size(g); i++){
      if(g->tarefas[i].id == id) 
        return i; // Retorna index, caso exista
    }
  }
  return -1;
}

int isFull(gerenciador* g){
  return size(g) == g->capacidade;
}

int increaseMemory(gerenciador* g){
  g->tarefas = realloc(g->tarefas, (g->capacidade += 10) * sizeof(tarefa));
  return 0;  
}

int checkMemory(gerenciador* g){
  if(isFull(g))
    increaseMemory(g);

  if(g)
    return 0;
  else
    return -1;
}

// Menu
void help(){
  printf("= = = = = = = = = = = = = = = =\n");
  printf("(1) · Adicionar tarefa\n");
  printf("(2) · Remover tarefa\n");
  printf("(3) · Buscar tarefa\n");
  printf("(4) · Listar tarefas\n");
  printf("(5) · Atualizar status tarefa\n");
  printf("\n");
  printf("(-1) · Encerrar programa\n");
  printf("= = = = = = = = = = = = = = = =\n");
}

void menuAdd(gerenciador* g){
  char desc[50], prazo[11];
  int opAdd, index;
  
  printf("\n# Adicionar tarefa...\n");

   
  printf("(1) · Adicionar ao início\n");
  printf("(2) · Adicionar ao fim\n");
  printf("(3) · Adicionar na posição...\n");
  
  printf("\n>> ");
  input(&opAdd);

  printf(">> Descrição: ");
  fgets(desc, sizeof(desc), stdin); // Obtém descrição

  do{
    printf(">> Prazo (DD-MM-YYYY): ");
    fgets(prazo, sizeof(prazo), stdin);
  }while(strlen(prazo) != 10); // Enquanto não tiver 10 caracteres

  tarefa task = newTask(desc, prazo);

  switch(opAdd){
    case 1:
      addAtBeginning(g, task);
    break;
    case 2:
      addAtEnd(g, task);
    break;
    case 3:
      printf("> Posição: ");
      scanf("%d", &index);
      addAtIndex(g, task, index);
    break;
    default:
      printf("(!) Opção inválida\n");

  }  
}

void menuRemove(gerenciador* g){
  int opRemove, itemId, itemIndex;
  
  printf("\n# Remover elemento...\n");
  printf("(1) · Por id\n");
  printf("(2) · Na posição...\n");

  printf(">> ");
  input(&opRemove);

  switch(opRemove){
    case 1:
      printf(">> Id: ");
      input(&itemId);
      if(!removeById(g, itemId)) // caso retorne 0
        printf("· Elemento removido!\n");
      else
        printf("(!) Houve um erro na remoção!\n");
    break;
    case 2:
      printf(">> Índice: ");
      input(&itemIndex);
      if(!removeAtIndex(g, itemIndex)) // caso retorne 0
        printf("· Elemento removido!\n");
      else
        printf("(!) Houve um erro na remoção!\n");
    break;
    default:
      printf("(!) Opção inválida\n");
    break;
  }
  
}

void menuSearch(gerenciador* g){
  int itemId, itemIndex;
  
  printf("\n# Buscar item\n");
  
  printf("\n> Id: ");
  input(&itemId);
  
  itemIndex = search(g, itemId);
  
  if(itemIndex != -1)
    printf("· Item de id %d na posição %d", itemId, itemIndex);
    
}

void menuUpdateStatus(gerenciador* g){
  printf("\n# Atualizar status da tarefa\n");
  int itemId, itemIndex, newStatus;
  tarefa* task;

  printf("\n> Id: ");
  input(&itemId);
  
  itemIndex = search(g, itemId);
  
  if(itemIndex != -1){ // Caso o item exista
    task = &g->tarefas[itemIndex];
    
    printf("\n> Status: ");
    input(&newStatus);

    *task = updateTaskStatus(*task, newStatus);

    printf("· Status atualizado!\n");
  }
  else
    printf("(!) Item não encontrado na atualização\n");
    
}

void menuShow(gerenciador* g){
  printf("\n# Listar tarefas...\n");
  printf("(1) · Listar todas\n");
  printf("(2) · Listar por status\n");

  int opShow, status;
  printf("\n>> ");
  input(&opShow);

  switch(opShow){
    case 1:
      show(g);
    break;
    case 2:
      printf(">> Status: ");
      input(&status);
      
      showFilter(g, status);
    break;
    default:
    printf("(!) Opção inválida\n");
  }
  
}

void input(int* op){
  scanf("%d", op);

  char temp;
  scanf("%c", &temp);
}

// Funções tarefa
tarefa newTask(char desc[50], char prazo[11]){
  tarefa task;
  task.id = ++newId;
  task.status = 0;
  strcpy(task.descricao, desc);
  strcpy(task.prazo, prazo);

  return task;
}
tarefa updateTaskStatus(tarefa task, int status){
  task.status = status;
  return task;
};
