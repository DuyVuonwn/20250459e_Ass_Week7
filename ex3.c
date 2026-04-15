#include <stdio.h>
#include <string.h>

#define MAX 100

struct Patient
{
    char name[50];
    int priority;
};

struct Patient heap[MAX];
int size = 0;

/************************************************************
 * Function: swap
 * Description:
 *      Swaps two patients.
 * Parameters:
 *      struct Patient *a: first
 *      struct Patient *b: second
 * Return:
 *      None
 ************************************************************/
void swap(struct Patient *a, struct Patient *b)
{
    struct Patient tmp = *a;
    *a = *b;
    *b = tmp;
}

/************************************************************
 * Function: heapify_up
 * Description:
 *      Maintains heap property from bottom to top.
 * Parameters:
 *      int index: index of inserted element
 * Return:
 *      None
 ************************************************************/
void heapify_up(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (heap[parent].priority < heap[index].priority)
        {
            swap(&heap[parent], &heap[index]);
            index = parent;
        }
        else break;
    }
}

/************************************************************
 * Function: heapify_down
 * Description:
 *      Maintains heap property from top to bottom.
 * Parameters:
 *      int index: starting index
 * Return:
 *      None
 ************************************************************/
void heapify_down(int index)
{
    while (1)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < size && heap[left].priority > heap[largest].priority)
            largest = left;
        if (right < size && heap[right].priority > heap[largest].priority)
            largest = right;

        if (largest != index)
        {
            swap(&heap[index], &heap[largest]);
            index = largest;
        }
        else break;
    }
}

/************************************************************
 * Function: push
 * Description:
 *      Inserts a patient into max-heap.
 * Parameters:
 *      struct Patient p: patient to insert
 * Return:
 *      None
 ************************************************************/
void push(struct Patient p)
{
    heap[size] = p;
    heapify_up(size);
    size++;
}

/************************************************************
 * Function: pop
 * Description:
 *      Removes and returns highest priority patient.
 * Parameters:
 *      None
 * Return:
 *      struct Patient
 ************************************************************/
struct Patient pop(void)
{
    struct Patient top = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapify_down(0);
    return top;
}

/************************************************************
 * Function: peek
 * Description:
 *      Returns highest priority patient without removing.
 * Parameters:
 *      None
 * Return:
 *      struct Patient
 ************************************************************/
struct Patient peek(void)
{
    return heap[0];
}

int main()
{
    struct Patient patients[] = {
        {"A", 3},
        {"B", 5},
        {"C", 2},
        {"D", 4},
        {"E", 1}
    };

    int n = 5;

    for (int i = 0; i < n; i++)
    {
        push(patients[i]);
        struct Patient top = peek();
        printf("Top after insert: %s (%d)\n", top.name, top.priority);
    }

    printf("\nOrder of treatment:\n");
    while (size > 0)
    {
        struct Patient p = pop();
        printf("%s (%d)\n", p.name, p.priority);
    }

    return 0;
}