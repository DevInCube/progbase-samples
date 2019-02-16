#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct __Queue
{
    char ** items;
    int capacity;
    int first;
    int last;
};
typedef struct __Queue Queue;

void Queue_init(Queue * self)
{
    self->capacity = 16;
    self->first = 0;
    self->last = 0;
    self->items = malloc(sizeof(char *) * self->capacity);
}

void Queue_deinit(Queue * self)
{
    free(self->items); 
}

void Queue_enqueue(Queue * self, char * value)
{
    self->items[self->last] = value;
    self->last += 1; 
    if (self->last == self->capacity)
    {
        self->last = 0;
    }
    if (self->last == self->first)
    {
        fprintf(stderr, "Queue is full");
    }
}

char * Queue_dequeue(Queue * self) 
{
    char * value = self->items[self->first];
    self->first += 1;
    if (self->first == self->capacity)
    {
        self->first = 0;
    }
    return value;
}

int Queue_size(Queue * self)
{
    if (self->last >= self->first)
        return self->last - self->first; 
    return self->capacity - self->first + self->last; 
}

void Queue_print(Queue * self)
{
    const int length = Queue_size(self);
    printf("Queue %i:\n", length);
    for (int i = self->first; i < self->last; i++) 
    {
        printf("\"%s\"\n", self->items[i]);
    }
}

int main()
{
    Queue queue;
    Queue_init(&queue);

    Queue_enqueue(&queue, "first");
    Queue_enqueue(&queue, "2nd");
    Queue_enqueue(&queue, "3rd");

    Queue_print(&queue);

    char * take1 = Queue_dequeue(&queue);
    char * take2 = Queue_dequeue(&queue);

    Queue_print(&queue);

    printf("\n%s\n%s\n", take1, take2);

    Queue_deinit(&queue);
    return 0;
}
