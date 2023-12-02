#include <stdio.h>

typedef struct {
  int id;
  char descricao[50];
  int status;
  char prazo[11]; // Formato DD-MM-AAAA
} tarefa;

typedef struct {
  tarefa *tarefas;
  int qtdTarefas;
  int capacidade;
} gerenciador;

// Lista
int init(gerenciador* g);
int show(gerenciador* g);
int showFilter(gerenciador* g, int status);
int isEmpty(gerenciador* g);
int size(gerenciador* g);

int addAtEnd(gerenciador* g, tarefa t);
int addAtBeginning(gerenciador* g, tarefa t);
int addAtIndex(gerenciador* g, tarefa t, int index);
int removeAtIndex(gerenciador* g, int index);
int removeById(gerenciador* g, int id);
int search(gerenciador* g, int id);

int isFull(gerenciador* g);
int increaseMemory(gerenciador* g);
int checkMemory(gerenciador *g);

// Tarefas
tarefa newTask(char desc[50], char prazo[11]);
tarefa updateTaskStatus(tarefa task, int status);

// Menu
void help();
void input();
void menuAdd(gerenciador* g);
void menuRemove(gerenciador* g);
void menuSearch(gerenciador* g);
void menuUpdateStatus(gerenciador* g);
void menuShow(gerenciador* g);
