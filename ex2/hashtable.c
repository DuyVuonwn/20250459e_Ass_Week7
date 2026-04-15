#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

static struct Node *buckets[TABLE_SIZE];

/************************************************************
 * Function: hash
 * Description:
 *      Computes hash value for a string.
 * Parameters:
 *      char *str: Input string
 * Return:
 *      Hash index
 ************************************************************/
unsigned int hash(char *str)
{
    unsigned int h = 0;
    while (*str)
        h = h * 31 + *str++;
    return h % TABLE_SIZE;
}

/************************************************************
 * Function: init_table
 * Description:
 *      Initializes hash table.
 * Parameters:
 *      None
 * Return:
 *      None
 ************************************************************/
void init_table(void)
{
    for (int i = 0; i < TABLE_SIZE; i++)
        buckets[i] = NULL;
}

/************************************************************
 * Function: insert
 * Description:
 *      Inserts a contact into hash table.
 * Parameters:
 *      char *name: Contact name
 *      char *phone: Phone number
 * Return:
 *      None
 ************************************************************/
void insert(char *name, char *phone)
{
    unsigned int h = hash(name);

    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);

    newNode->next = buckets[h];
    buckets[h] = newNode;
}

/************************************************************
 * Function: search
 * Description:
 *      Searches for a contact by name.
 * Parameters:
 *      char *name: Contact name
 * Return:
 *      Pointer to node or NULL
 ************************************************************/
struct Node* search(char *name)
{
    unsigned int h = hash(name);
    struct Node *p = buckets[h];

    while (p)
    {
        if (strcmp(p->name, name) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

/************************************************************
 * Function: delete
 * Description:
 *      Deletes a contact from hash table.
 * Parameters:
 *      char *name: Contact name
 * Return:
 *      None
 ************************************************************/
void delete(char *name)
{
    unsigned int h = hash(name);
    struct Node *p = buckets[h];
    struct Node *prev = NULL;

    while (p)
    {
        if (strcmp(p->name, name) == 0)
        {
            if (prev)
                prev->next = p->next;
            else
                buckets[h] = p->next;

            free(p);
            return;
        }
        prev = p;
        p = p->next;
    }
}

/************************************************************
 * Function: free_table
 * Description:
 *      Frees all memory in hash table.
 * Parameters:
 *      None
 * Return:
 *      None
 ************************************************************/
void free_table(void)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        struct Node *p = buckets[i];
        while (p)
        {
            struct Node *tmp = p;
            p = p->next;
            free(tmp);
        }
        buckets[i] = NULL;
    }
}