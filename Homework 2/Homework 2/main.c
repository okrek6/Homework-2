//
//  main.c
//  Homework 2
//
//  Created by Brendan Krekeler on 7/3/18.
//  Copyright © 2018 Brendan Krekeler. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct struct_bank
{
	int accn_num;
  char *name;
	float amount;
	struct struct_bank *nextNode;
}Bank, *ptrToBank;

Bank * build_list(char* filename);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

Bank * create_node(int accn, char *n,float amt)
{
//malloc in here as well

  //ptrToBank head = NULL;
  ptrToBank newNode;
  //ptrToBank currNode = NULL;

  newNode = malloc(sizeof(Bank));

    if(newNode == NULL)
    {
        printf("\n Couldn't create Node \n");
        return NULL;
    }

    if(newNode != NULL){

    newNode->accn_num = accn;
    newNode-> name = n;// string copy which is strcopy
    newNode-> amount = amt;
    newNode->nextNode = NULL;

  //    if (head == NULL) {
  //        head = newNode;
  //    } else {
  //        while (currNode->nextNode != NULL) {
  //          currNode = currNode ->nextNode;
  //      }
  //      currNode -> nextNode = newNode;
  //    }
  //  return head;


}
    return newNode;
}

Bank * insert_node(Bank* head, Bank* node){

}


//This function takes pointer head that points to the beginning of the linked list and inserts the node at the end of the list.

Bank* build_list(char* filename){
        //malloc in here for char and free it inside of here aswell.
        //fscanf the size out and then use another fscanf to get the account names.


        FILE *file = fopen(filename, "r");

        if (file == NULL){
            perror("file could not be opened");
            exit(1);
        }

        ptrToBank head = NULL;


        int accountNumber, accountName, accountAmount;
    while(fscanf(file, "%d %d %d", &accountName, &accountAmount, &accountNumber ) == 3){

            ptrToBank newPtr; //this points to the new node
            ptrToBank currPtr = NULL; //this points to current node in list
            //create node
            //

            newPtr = malloc(sizeof(Bank));

            if (newPtr != NULL)
            {
                newPtr->accn_num = x;
                newPtr->y = y;

                newPtr->nextNode = NULL;
                currPtr = start;

                if (head == NULL) {
                    start = newPtr;

                } else {

                    while (currPtr->nextNode != NULL) {
                        currPtr = currPtr->nextNode;
                    }
                    currPtr -> nextNode = newPtr;
                }
            }
        }
        fclose(file);
        return head;
    }

    //    for loop in here to fscanf the accounts using the size from the input file


int check_list(Bank* head, char *n, int accn, float amt){

}

Bank* update_list(char *str, Bank* head){

}

Bank* delete_node( Bank* head){

  ptrToBank curraNode = NULL;
  ptrToBank tempNode = NULL;

  while (start->x == x)
  {
      tempNode = start;
      start = start->nextNode;
      free(tempNode);
  }
  for(curraNode = start; curraNode != NULL; curraNode = curraNode->nextNode){
      while (curraNode->nextNode != NULL && curraNode->nextNode->x == x) {
          tempNode = curraNode->nextNode;
          curraNode ->nextNode = tempNode->nextNode;
          free(tempNode);
      }
  }
}

int write_output(char * str, bank*head)

void print_list(bank *head )
