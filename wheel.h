#ifndef WHEEL_H
#define WHEEL_H



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* Structure definitions */
struct anode
  {
    char value;
    struct anode *nextNode;
    struct anode *previousNode;
  }; typedef struct anode NODE;

/* Function Prototypes */
extern void addNode(NODE** root,char val);
extern void printList(NODE* n);
extern int wheelSize(NODE* n);
extern NODE *pop(char *wheel);

#endif


