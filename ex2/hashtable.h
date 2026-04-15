#ifndef HASHTABLE_H
#define HASHTABLE_H

#define TABLE_SIZE 101

struct Node
{
    char name[100];
    char phone[20];
    struct Node *next;
};

/************************************************************
 * Function: init_table
 * Description:
 *      Initializes hash table.
 * Parameters:
 *      None
 * Return:
 *      None
 ************************************************************/
void init_table(void);

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
void insert(char *name, char *phone);

/************************************************************
 * Function: search
 * Description:
 *      Searches for a contact by name.
 * Parameters:
 *      char *name: Contact name
 * Return:
 *      Pointer to node or NULL
 ************************************************************/
struct Node* search(char *name);

/************************************************************
 * Function: delete
 * Description:
 *      Deletes a contact from hash table.
 * Parameters:
 *      char *name: Contact name
 * Return:
 *      None
 ************************************************************/
void delete(char *name);

/************************************************************
 * Function: free_table
 * Description:
 *      Frees all memory in hash table.
 * Parameters:
 *      None
 * Return:
 *      None
 ************************************************************/
void free_table(void);

#endif