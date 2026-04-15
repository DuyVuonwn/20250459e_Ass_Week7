#include <stdio.h>
#include "hashtable.h"

int main()
{
    init_table();

    insert("Alice", "111");
    insert("Bob", "222");
    insert("Charlie", "333");

    struct Node *p = search("Bob");
    if (p)
        printf("Found: %s -> %s\n", p->name, p->phone);

    delete("Bob");

    p = search("Bob");
    if (!p)
        printf("Bob not found\n");

    free_table();
    return 0;
}