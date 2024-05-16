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

void iniciarEnCero(int *array, int large){
   for(int i = 0; i < large; i++){
      array[i] = 0;
   }
}

int filasValidas(Node *n){
   int array[10];

   for(int i = 0; i < 9; i++){
      iniciarEnCero(array, 10);
      for(int j = 0; j < 9; j++){
         if(array[n->sudo[i][j]] == 0)
            array[n->sudo[i][j]] = 1;
         else 
            return 0;
      }
   }
   return 1;
}

int columnasValidas(Node *n){
   int array[10];

   for(int j = 0; j < 9; j++){
      iniciarEnCero(array, 10);
      for(int i = 0; i < 9; i++){
         if(array[n->sudo[i][j]] == 0)
            array[n->sudo[i][j]] = 1;
         else 
            return 0;
      }
   }
   return 1;
}
/*
int subMatricesValidas(Node *n){
   int array[10];
   iniciarEnCero(array, 10);
   return 1;
}*/

int is_valid(Node* n){
    if(filasValidas(n) && columnasValidas(n))
       return 1;
    return 0;
}

void buscar_casilla_vacia(Node *n, int *fil, int *col){
   int i, j;
   for(i = 0; i < 9; i++){
      for(j = 0; j < 9 ; j++){
         if(n->sudo[i][j] == 0){
            *fil = i;
            *col = j;
            return;;
         }
      }
   }
   *fil = 9;
}

List* get_adj_nodes(Node* n){
    List* list=createList();
    int i,j;

    buscar_casilla_vacia(n, &i, &j);
    if(i == 9) return list;

    for(int aux = 1; aux <= 9; aux++){
       Node *node_adj = copy(n);
       node_adj->sudo[i][j] = aux;
       pushBack(list, node_adj);
    }   
    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
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