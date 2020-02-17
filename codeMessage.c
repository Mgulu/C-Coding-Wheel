#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wheel.h"
/* Structure definitions */

/* Function prototypes   */

void openFile(char *fileName,char **twheel);

void decodeMessage(NODE *wheel,int * cipher,int size,char *decodedMessage);
void codeMessage(NODE *wheel,char *cipher,int size,int *ptr);


/*~~~~Main function~~~~~~*/
int main(int argc, char **argv){
  int i;  
  for(i=0 ; i < argc ; i++){
    printf("Parameter Listing %d :  %s \n",i,argv[i]);
    }  
  /* Getting the textFile */
  char *str;
  str = argv[1];
  char *wheel;
  openFile(str,&wheel); 
  /* Making coding wheel */
  NODE *list = NULL;
  NODE* convWheel = (pop(wheel));
  printf("Coding Wheel Values \n");
  printList(convWheel);
  int size;
  /* Decode or Code the message  */
  char *choice = argv[3];
  char *fileName = argv[2];
  FILE *fp;
  fp = fopen(fileName,"w");
  if(*choice == 'C'){    
    /* Gets the message */
    char *messageArg = argv[4];
    size = (int)strlen(messageArg);  
    int codedMessage[size];  
    /* Codes the message */  
    codeMessage(convWheel,messageArg,size,codedMessage);
    /* Writes the message to a file */
    for(i=0;i <size;i++){      
      fprintf(fp, "%d ", codedMessage[i]); 
    }
    fclose(fp);    
  } else if (*choice == 'D') {
    
    int message[argc - 3];
    size =0 ;
    /* Gets all the integers arguments*/
    for(i=4; i <argc;i++){
    sscanf(argv[i], "%d", &message[i-4]); 
    size ++;
    }  
    char decodedMessage[size];
    /* Decodes message */
    decodeMessage(convWheel,message,size,decodedMessage);
    /* Writes the decoded message to a file*/
    for(i=0;i <size;i++){    
      fprintf(fp, "%c", decodedMessage[i]); 
    }
    fclose(fp);
  }    
  return 0;
  } 

void openFile(char *fileName,char **twheel){
  FILE *fp;
  int num_char = -1;
  int num_letters = 0;
  fp = fopen(fileName,"r");
  /* Checks if the files exists*/
  if(fp == NULL){
    printf("NO FILE");
    exit(1);
  }
  char ch;
  /* Counts all the characters, aswell as actual characters that
  will be in the wheel */
  do{
    ch = fgetc(fp);
    num_char ++;
    if(ch == '\n') num_letters++;
  } while(ch != EOF);
  rewind(fp);
  /* Makes a string which has the same length as the amount of
  characters*/
  *twheel = (char *)malloc(sizeof(char)*num_letters);
  int i;
  int o = 0;
  char chr[num_char];
  /* Adds the character to twheel */
  for(i=0;i<num_char;i++){
    fscanf(fp,"%c",&chr[i]);
    if(chr[i] != '\n'){      
      twheel[0][o] = chr[i];
      o++;
    }
  }
  fclose(fp);
}


void decodeMessage(NODE* wheel,int * cipher,int size,char *decodedMessage){
  char decoded[size];
  int i;
  int count; 
  /* Loops through the message to be deocoded*/
  for(i=0;i < size; i++){   
    if(cipher[i] >= 0){
      count = cipher[i];      
      /* Loops until count is zero and its moved the correct 
      amount of steps*/
      while(count != 0){
        wheel = wheel -> nextNode;
        count --;
      }
      decoded[i] = wheel -> value;
    } else {
      count = cipher[i];      
      while(count != 0){
        wheel = wheel -> previousNode;
        count ++;
      }
      decoded[i] = wheel -> value;
    }
  }
  /* Adds the decoded message into decodedMessage*/
  for(i=0;i < size; i++){
    decodedMessage[i] = decoded[i];
  }
}


void codeMessage(NODE* wheel,char *messageArg,int size,int *ptr){
  int decoded[size];
  int i;
  int count ;
  int negcount;
  int sizeWheel = wheelSize(wheel);
  float half = size / 2;
  NODE* prev;

  char cipher[size];
  for(i=0; i <size;i++){
    cipher[i] = messageArg[i];
  }
  /* Loops through all the characters in the message */
  for(i=0;i < size; i++){    
    negcount = 0;
    count = 0;
    prev = wheel;
    /* Moves until the character is found in the wheel (positive) */
    while(wheel -> value != cipher[i]){      
      wheel = wheel -> nextNode;
      count ++; }
    /* Moves until the character is found in the wheel (negative) */
    while(prev -> value != cipher[i]){    
      prev = prev -> previousNode;
      --negcount;
      } 
    /* Checks to see if postive count is greater than half the list or absolute negative count */
    if ((float)count > half && count > abs(negcount)){         
      decoded[i] = negcount;
      } else {
      decoded[i] = count;
      } 
    }
    for(i=0;i < size; i++){
    ptr[i] = decoded[i];
    }
  }





