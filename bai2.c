/*
•You assume to make an address book of mobile telephone_number.
•You declare a structure which can hold at least “name,” “teletelephone_number number,” and “e-mail address”, and make a program which can manage about 100 these data.•(1) Read about 10 from an input file, and store them in a hash table which has an “e-mail address” as a key. Then confirm that the hash table is made. In this exercise, the hash function may always return the same value.•(2)Define the hash function properly, and make the congestion occur as rare as possible
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 11

typedef struct node_t {
    char email_address[50];   //key 
    char name[50];
    char telephone_number[12];
    
    struct node_t * next;
} node;

typedef struct htNode_t
{
    int key;

    struct node_t * next;
} htNode;

htNode hastTable[TABLE_SIZE];

int _chartoInt (char c) {
    int num = c - '0';
    return num;
}

/* Bản đồ mã băm (hascodeMap) */
long int hashcodeMap(char email_address[]) // keyType: email_address address
{   
    int numofchar;
    int z = 33;
    int Pz;  // Pz = Tổng(a_{i}*z^i, i={0..n-1})
    for (int i = 0; i < strlen(email_address); i++)
    {
        char c = email_address[i];
        numofchar = _chartoInt(c);
        Pz += numofchar * z^i;
    }
    return Pz;
}


int compressionMap(long int hashcode) {
    return hashcode % TABLE_SIZE;
}

int HashFunction(char key[]) {
    return compressionMap( hashcodeMap(key) );
}

void Init(htNode hastTable[]) {
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hastTable[i].key = i;
        hastTable[i].next = NULL;
    }
}

node A[10];

void readfile(char *filename, node A[])
{
    FILE * fp = fopen(filename, "r"); 
    int i;
    
	if ( fp == NULL ) printf("Cannot open file %s\n", filename);
    for (i = 0; i < 10; i++)
    {
        fflush(stdin);
        fscanf(fp, "%s %s %s\n", A[i].name, A[i].telephone_number, A[i].email_address);
        A[i].next = NULL;
    }
    fclose(fp);
}

node * makeNew(char name[], char telephone_number[], char email_address[]) {
    node * tmp = (node*)malloc(sizeof(node));
    if(tmp == NULL) printf("Failed allocate memory!\n");

    strcpy(tmp->name, name); strcpy(tmp->telephone_number, telephone_number); strcpy(tmp->email_address, email_address);

    tmp->next = NULL;

    return tmp; 
}

void insert_hT(node x, htNode hastTable[]) {
  
    int bucket = HashFunction(x.email_address);

    htNode nodeRef = hastTable[bucket];

    node * new = makeNew(x.name, x.telephone_number, x.email_address);

    if (nodeRef.next == NULL) nodeRef.next = new;
    else
        {
            node * tmp = nodeRef.next;
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            tmp->next = new;
        }
}


int main() {
    readfile("input.txt", A);
    Init(hastTable);
    for(int i = 0; i < 10; i++) {
	    insert_hT(A[i], hastTable);
    }
    return 0;
}