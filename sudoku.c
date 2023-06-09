#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
  for(int k = 0; k < 9; k++)
  {
    int fila[10] = {0};
    int columna[10] = {0};
    int matriz[10] = {0}; 
    
    for(int j = 0; j < 9; j++)
    {
      if(n->sudo[k][j] != 0)
      {
        if(fila[n->sudo[k][j]] == 1) return 0;
        else fila[n->sudo[k][j]] = 1;
      }
      
      if(n->sudo[j][k] != 0)
      {
        if(columna[n->sudo[j][k]] == 1) return 0;
        else columna[n->sudo[j][k]] = 1;
      }
      
      int i = 3*(k/3) + (j/3);
      int d = 3*(k%3) + (j%3);
      
      if(n->sudo[i][d] != 0)
      {
        if(matriz[n->sudo[i][d]] == 1) return 0;
        else matriz[n->sudo[i][d]] = 1;
      }
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  int encontrado = 0;
  for(int k = 0; k < 9; k++)
  {
    for(int j = 0; j < 9; j++)
      {
        if(n->sudo[k][j] == 0)
        {
          encontrado = 1;
          for(int i = 1; i <= 9; i++)
            {
              Node *nuevo = copy(n);
              nuevo->sudo[k][j] = i;
              if(is_valid(nuevo) == 1) pushBack(list, nuevo);
            }
          return list;
        }
      }
    if(encontrado == 1) break;
  }
  return list;
}


int is_final(Node* n){
  for(int k = 0; k < 9; k++)
  {
    for(int j = 0; j < 9; j++)
    {
      if(n->sudo[k][j] == 0) return 0;
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack *s = createStack();
  push(s, initial);
  while(is_empty(s) != 1)
  {
      Node *primero = top(s);
      pop(s);
      if(is_final(primero) == 1) return primero;
      List *listaAdyacentes = get_adj_nodes(primero);
      Node *aux = first(listaAdyacentes);
      while(aux != NULL)
      {
        push(s, aux);
        aux = next(listaAdyacentes);
      }
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/