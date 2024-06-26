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

int filValidas(Node *n){
   int array[10];

   for(int i = 0; i < 9; i++){
      iniciarEnCero(array, 10);
      for(int j = 0; j < 9; j++){
         if(n->sudo[i][j] == 0) continue;
         array[n->sudo[i][j]]++;
         if(array[n->sudo[i][j]] > 1) return 0;
      }
   }
   return 1;
}

int colValidas(Node *n){
   int array[10];

   for(int j = 0; j < 9; j++){
      iniciarEnCero(array, 10);
      for(int i = 0; i < 9; i++){
         if(n->sudo[i][j] == 0) continue;
         array[n->sudo[i][j]]++;
         if(array[n->sudo[i][j]] > 1) return 0;
      }
   }
   return 1;
}

int subMValidas(Node *n){
   int array[10];
   int p,i,j;

   for(int k = 0; k < 9; k++){
      iniciarEnCero(array, 10);
      for(p = 0; p < 9; p++){
          i=3*(k/3) + (p/3);
          j=3*(k%3) + (p%3);
         
          if(n->sudo[i][j] == 0) continue;
          array[n->sudo[i][j]]++;
          if(array[n->sudo[i][j]] > 1) return 0;
      }
   }
   return 1;
}

int is_valid(Node* n){
    if(filValidas(n) && colValidas(n) && subMValidas(n))
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
       if(is_valid(node_adj))
         pushBack(list, node_adj);
    }   
    return list;
}


int is_final(Node* n){
    for(int i = 0; i < 9; i++){
       for(int j = 0; j < 9; j++){
          if(n->sudo[i][j] == 0) return 0;
       }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
   Stack *pila = createStack();
   Node *n = (Node *) malloc(sizeof(Node));
   push(pila, initial);

   while(top(pila) != NULL){
      (*cont)++;
      n = top(pila);
      pop(pila);

      if(is_final(n)) return n;
      
      List *adj_nodes = get_adj_nodes(n);
      Node *aux = first(adj_nodes);
      while(aux){
         push(pila, aux);
         aux = next(adj_nodes);
      }
      free(n);
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