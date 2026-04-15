#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 101

struct Node
{
    char name[100];
    char phone[20];
    struct Node *next;
};

struct Node *buckets[TABLE_SIZE];

/************************************************************
 * Function: hash
 * Description:
 *      Computes hash value for a string using polynomial method.
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
 * Function: insert
 * Description:
 *      Inserts a new contact into hash table.
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
 *      Pointer to node if found, else NULL
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
            printf("Deleted: %s\n", name);
            return;
        }
        prev = p;
        p = p->next;
    }

    printf("Not found: %s\n", name);
}

/************************************************************
 * Function: display
 * Description:
 *      Displays all contacts in hash table.
 * Parameters:
 *      None
 * Return:
 *      None
 ************************************************************/
void display(void)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        struct Node *p = buckets[i];
        while (p)
        {
            printf("%s -> %s\n", p->name, p->phone);
            p = p->next;
        }
    }
}

int main()
{
    // insert at least 8 contacts
    insert("Alice", "111");
    insert("Bob", "222");
    insert("Charlie", "333");
    insert("David", "444");
    insert("Eve", "555");
    insert("Frank", "666");
    insert("Grace", "777");
    insert("Hannah", "888");

    printf("=== All contacts ===\n");
    display();

    // search at least 3 names
    char *names[] = {"Alice", "Eve", "Zoe"};
    for (int i = 0; i < 3; i++)
    {
        struct Node *p = search(names[i]);
        if (p)
            printf("Found: %s -> %s\n", p->name, p->phone);
        else
            printf("Not found: %s\n", names[i]);
    }

    // delete 2 contacts
    delete("Bob");
    delete("David");

    printf("\n=== After deletion ===\n");
    display();

    return 0;
}