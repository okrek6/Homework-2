//
//  main.c
//  Homework 2
//
//  Created by Brendan Krekeler on 7/3/18.
//  Copyright © 2018 Brendan Krekeler. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strcpy

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
    
    if (argc != 4) {
        printf("ERROR! Insufficent arguments");
        exit(1);
    }
    
    ptrToBank bankPtr;
    ptrToBank newBankPtr;
    ptrToBank deletedBankPtr;
    ptrToBank temp;
    
    bankPtr = (build_list(argv[1]));
    printf("\nCreated Link List\n\n");
    print_list(bankPtr);
    printf("\n");
    
    newBankPtr = (update_list(argv[2], bankPtr));
    printf("\nLinked List after update operation\n\n");
    print_list(newBankPtr);
    printf("\n");
    
    deletedBankPtr = (delete_node(newBankPtr));
    printf("Linked List after delete operation\n\n");
    print_list(deletedBankPtr);
    printf("\n");
    write_output(argv[3], deletedBankPtr);
    
    
    
    while (deletedBankPtr != NULL ){
        
        temp = deletedBankPtr->nextNode;
        free(deletedBankPtr->name);
        free(deletedBankPtr);
        deletedBankPtr = temp;
    }
    
}

Bank * create_node(int accn, char *n,float amt)
{
    
    ptrToBank newNode;
    newNode = malloc(sizeof(Bank));
    newNode->name = malloc(sizeof(char) * 30); // you have to malloc for names seperately because it's a char pointer not a char array
    
    if(newNode == NULL)
    {
        printf("\n Couldn't create Node \n");
        return NULL;
    }
    
    if(newNode != NULL){
        
        newNode->accn_num = accn;
        //newNode->name = n;// string copy which is strcopy
        strcpy(newNode->name, n); // using strcpy to copy from n to name. n will have to be malloced for outside of this function
        newNode->amount = amt;
        newNode->nextNode = NULL;
        
    }
    
    
    return newNode;
    
}

Bank * insert_node(Bank* headNode, Bank* newNode){
    
    ptrToBank lastNode;
    
    if (newNode == NULL)
    {
        printf("Error, Could not insert account");
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
    //This function takes the input file name (accounts.txt), opens the input file, reads the user information from the file pass it to create_node function. After that it call insert_node function with the created node (by the create_node) function and the pointer “head” pointing at the beginning of the linked list.At the end function returns the “head” pointer.
    
    int accountNumber;
    //char *accountName = 0; Dont initializet these to zero. Initialize them to NULL.
    char *accountName = malloc(sizeof(char) * 30); // You need to have space for strcpy to work right
    float accountAmount;
    int size;
    int i;
    
    FILE *file = fopen(filename, "r");
    
    if (file == NULL){
        perror("File could not be opened");
        exit(1);
    }
    
    ptrToBank head = NULL;
    
    fscanf(file, "%d", &size);
    
    for (i = 0; i < size; i++) {
        
        fscanf(file, "%d %s %f", &accountNumber, accountName, &accountAmount );
        
        ptrToBank newNode = NULL; // Initialize this to NULL instead of zero and then call create_node and insert_node
        
        //if (newNode != NULL){
        
        newNode = (create_node(accountNumber, accountName, accountAmount));
        head = insert_node(head, newNode);
        
        //  }
    }
    
    free(accountName);
    
    fclose(file);
    return head;
}

int check_list(Bank* head, char *n, int accn, float amt){

    ptrToBank temp;
    
    temp = head;
    
    while (temp != NULL){
        if (temp->accn_num == accn)
        {
            if (temp->amount != amt) {
                temp->amount += amt;
            }
            return  1;
        }
        temp = temp -> nextNode;
    }
    return 0;
    //This function uses the information from the update.txt file and checks if the account information (s, accn and amt) is already present in the linked list or not. If the account is already present then it update the total amount for that account (as explained above) and returns 1 otherwise 0 and an error message is printed out indicating that the account is not in the linked list.  Pointer “head” is used to traverse the linked list.
}

Bank* update_list(char *filename, Bank* head){
    
    int i, accn, size;
    char *n = NULL;
    float amt;
    
    FILE *file = fopen(filename, "r");
    
    if (file == NULL){
        perror("File could not be opened");
        exit(1);
    }
    
    fscanf(file, "%d", &size);
    
    n = malloc(sizeof(char)*30);
    
    for (i = 0; i<size; i++) {
        
        fscanf(file, "%d %s %f", &accn, n, &amt);
        
        if (check_list(head, n, accn, amt) == 0){
            head = insert_node(head, create_node(accn, n, amt));
        }
    }
    
    free(n);
    fclose(file);
    
    return head;
    
}

Bank* delete_node( Bank* head){
    
    ptrToBank curraNode = NULL;
    ptrToBank tempNode = NULL;
    
    while (head->amount < 0)
    {
        tempNode = head;
        head = head->nextNode;
        free(tempNode->name);
        free(tempNode);
    }
    for(curraNode = head; curraNode != NULL; curraNode = curraNode->nextNode){
        while (curraNode->nextNode != NULL && curraNode->nextNode->amount < 0) {
            tempNode = curraNode->nextNode;
            curraNode ->nextNode = tempNode->nextNode;
            free(tempNode->name);
            free(tempNode);
        }
    }
    return head;
}

int write_output(char *filename, Bank*head){
    
    FILE *file = fopen(filename, "w");
    
    if (file == NULL){
        perror("File could not be opened");
        exit(1);
    }
    
    ptrToBank temp = NULL;
    
    temp = head;
    
    while (temp != NULL){
        
        fprintf(file, "%d %s %.2f\n", temp->accn_num, temp->name, temp->amount );
        
        temp = temp->nextNode;
    }
    
    fclose(file);
    
    return 0;
}

void print_list(Bank *head ){
    
    ptrToBank temp;
    
    temp = head;
    
    while (temp != NULL )
    {
        printf("%d %s %.2f\n", temp->accn_num, temp->name, temp->amount);
        temp = temp->nextNode;
    }
}
