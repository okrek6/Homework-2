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


//prototypes
Bank * build_list(char* filename);
Bank * create_node(int accn, char *n,float amt);
Bank * insert_node(Bank* head, Bank* node);
int check_list(Bank* head, char *n, int accn, float amt);
Bank* update_list(char *str, Bank* head);
Bank* delete_node( Bank* head);
int write_output(char * str, Bank*head);
void print_list(Bank *head );

int main(int argc, char * argv[]) {
//     It calls  build_list, update_list and delete_node functions and after each function calls print_list to print the linked list content. At the end it calls the write_output function.
    
    ptrToBank bankPtr;
 //   Bank newBankPtr;
 //   Bank deletedBankPtr;
    
    bankPtr = (build_list(argv[1]));
    print_list(bankPtr);
//    newBankPtr = *(update_list(argv[2], &bankPtr));
//    print_list(&newBankPtr);
//    deletedBankPtr = *(delete_node(&newBankPtr));
//    print_list(&deletedBankPtr);
//    write_output(argv[3], &deletedBankPtr);
    
}

Bank * create_node(int accn, char *n,float amt)
{

    ptrToBank newNode;
    newNode = malloc(sizeof(Bank));

    if(newNode == NULL)
    {
        printf("\n Couldn't create Node \n");
        return NULL;
    }

    if(newNode != NULL){

    newNode->accn_num = accn;
    newNode->name = n;// string copy which is strcopy
    newNode->amount = amt;
    newNode->nextNode = NULL;

}
    return newNode;
}

Bank * insert_node(Bank* headNode, Bank* newNode){

    ptrToBank lastNode;
    
    if (newNode == NULL)
    {
        printf("fail");
    }

    newNode->nextNode = NULL;
    
    if ( headNode == NULL)
    {
        headNode = newNode;
        return headNode;
    }
    
    lastNode = headNode;
    while (lastNode->nextNode) {
        lastNode = lastNode -> nextNode;
    }
    lastNode -> nextNode = newNode;
    
    return headNode;

//This function takes pointer head that points to the beginning of the linked list and inserts the node at the end of the list.
}

Bank* build_list(char* filename){
        //fscanf the size out and then use another fscanf to get the account names.
//This function takes the input file name (accounts.txt), opens the input file, reads the user information from the file pass it to create_node function. After that it call insert_node function with the created node (by the create_node) function and the pointer “head” pointing at the beginning of the linked list.At the end function returns the “head” pointer.

    int accountNumber;
    char *accountName = 0;
    float accountAmount;
    int size;
    int i;
    
    FILE *file = fopen(filename, "r");

    if (file == NULL){
        perror("file could not be opened");
        exit(1);
    }

    ptrToBank head = NULL;
    
    fscanf(file, "%d", &size);
    
    for (i = 0; i < size; i++) {
        
        fscanf(file, "%s %f %d", accountName, &accountAmount, &accountNumber );

        ptrToBank newNode = 0;
        
        if (newNode != NULL){
        
        newNode = (create_node(accountNumber, accountName, accountAmount));
        head = insert_node(head, newNode);
            
            }
        }
    
    free(accountName);
    
    fclose(file);
        return head;
}

//int check_list(Bank* head, char *n, int accn, float amt){
//
//}
//
//Bank* update_list(char *str, Bank* head){
//
//}

Bank* delete_node( Bank* head){

  ptrToBank curraNode = NULL;
  ptrToBank tempNode = NULL;

  while (head->accn_num < 0)
  {
      tempNode = head;
      head = head->nextNode;
      free(tempNode);
  }
  for(curraNode = head; curraNode != NULL; curraNode = curraNode->nextNode){
      while (curraNode->nextNode != NULL && curraNode->nextNode->amount < 0) {
          tempNode = curraNode->nextNode;
          curraNode ->nextNode = tempNode->nextNode;
          free(tempNode);
      }
  }
    return head;
}

//int write_output(char * str, Bank*head){
//}

void print_list(Bank *head ){
    printf("hello");
        ptrToBank temp;
        
        temp = head;
        
        while (temp != NULL )
        {
            printf("%d %s %f\n", temp->accn_num, temp->name, temp->amount);
            temp = temp->nextNode;
        }
}
