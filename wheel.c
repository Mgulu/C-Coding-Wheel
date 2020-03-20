#include "wheel.h"
/*functions */

static void addNode(NODE** root,char val){
  /* If there is no root node it creates a new node and sets
  it as the root Node */
  if (*root == NULL){
    NODE* tempNode = (NODE *)malloc(sizeof ( NODE ));
    tempNode -> value = val;
    tempNode -> nextNode = tempNode;
    tempNode -> previousNode = tempNode;
    *root = tempNode;    
  } else {   
  /* Sets the new nodes nextNode to be the root node and its 
  previousNode to be the node before it  
  */
    NODE *endNode = (*root) -> previousNode;
    NODE* tempNode = (NODE *)malloc(sizeof ( NODE ));
    tempNode -> value = val;
    tempNode -> previousNode = endNode;
    tempNode -> nextNode = *root;
    (*root) -> previousNode = tempNode;   
    endNode -> nextNode = tempNode;       
  }
}


extern void printList(NODE* n) { 
  /* Loops through until it returns to the root */
    NODE* og = n;
    do{
      printf("%c",n->value);
      n = n -> nextNode;
    } while(n != og );
} 


extern int wheelSize(NODE* n) { 
  /* Loops through until it returns to the root*/
    NODE* og = n;
    int size = 0;
    do{
      n = n -> nextNode;
      size ++;
    } while(n != og );
    return size;
} 

extern NODE *pop(char *wheel){
  /* Loops through adding each character in wheel into the 
  linkedList then returns it */
  int i;
  NODE* list = NULL;  
  int length = (int)strlen(wheel);  
  for(i=0;i < length;i++){
    addNode(&list,wheel[i]);
  }  
  return list;
} 
