#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

struct SLNode {
    int value;
    struct SLNode * next;
};

struct SLList {
    struct SLNode * head;
};

struct Stack {
    struct SLList list;
};

int peekStack(struct Stack * stack);
void pushStack(struct Stack * stack, int value);
int popStack(struct Stack * stack);
bool isEmptyStack(struct Stack * stack);

struct SLNode * newSLNode(int value);
void freeSLNode(struct SLNode * node);

void printSLList(struct SLList * list);
bool insertSLNode(struct SLList * list, int index, int value);
bool removeSLNode(struct SLList * list, int index);

bool par(const char * str) {
    assert(str != NULL);
    struct Stack stack = {NULL};
    while (*str != '\0') {
        if (*str == '(') {
            pushStack(&stack, 0);
        } else if (*str == ')') {
            if (isEmptyStack(&stack)) {
                return false;
            } else {
                popStack(&stack);
            }
        } else {
            assert(0);
        }
        str++;
    }
    if (isEmptyStack(&stack)) return true;
    while (!isEmptyStack(&stack))
        popStack(&stack);
    return false;
}

int main(void) {
    assert(par("(") == 0);
    assert(par("()") == 1);
    assert(par(")(") == 0);
    assert(par("(())") == 1);
    assert(par("(()())") == 1);
    assert(par("())(()") == 0);
    assert(par("()()") == 1);
    return 0;
}

bool isEmptyStack(struct Stack * stack) {
    assert(stack != NULL);
    return stack->list.head == NULL;
}

int peekStack(struct Stack * stack) {
    assert(stack != NULL);
    assert(stack->list.head != NULL);
    return stack->list.head->value;
}

void pushStack(struct Stack * stack, int value) {
    insertSLNode(&stack->list, 0, value);
}

int popStack(struct Stack * stack) {
    assert(stack != NULL);
    assert(stack->list.head != NULL);
    int value = stack->list.head->value;
    removeSLNode(&stack->list, 0);
    return value;
}

bool removeSLNode(struct SLList * list, int index) {
    assert(index >= 0);
    assert(list != NULL);
    if (list->head == NULL) {
        return false;
    } 
    if (index == 0) {
        struct SLNode * temp = list->head;
        list->head = list->head->next;
        freeSLNode(temp);
        return true;
    }
    struct SLNode * pre = list->head;
    for (int k = 0; k < index - 1; k++) {
        pre = pre->next;
        if (pre == NULL || pre->next == NULL) {
            return false;
        }
    }
    struct SLNode * temp = pre->next;
    struct SLNode * aft = temp->next;
    pre->next = aft;
    freeSLNode(temp);
    return true;
}

bool insertSLNode(struct SLList * list, int index, int value) {
    assert(index >= 0);
    assert(list != NULL);
    struct SLNode * head = list->head;
    struct SLNode * vtx = newSLNode(value);
    if (index == 0) {
        vtx -> next = head;
        list->head = vtx;
        return true;
    }
    struct SLNode * pre = head;
    for (int k = 0; k < index - 1; k++) {
        pre = pre->next;
        if (pre == NULL) {
            return false;
        }
    }
    
    vtx->next = pre->next;
    pre->next = vtx;
    return true;
}

void printSLList(struct SLList * list) {
    assert(list != NULL);
    struct SLNode * head = list->head;
    if (head == NULL) {
        puts("(empty)");
        return;
    }
    struct SLNode * temp = head;
    while (temp != NULL) {
        printf("-> %i ", temp->value);
        temp = temp->next;
    }
    puts("");
}

struct SLNode * newSLNode(int value) {
    struct SLNode * node = malloc(sizeof(struct SLNode));
    node->value = value;
    node->next = NULL;
    return node;
}

void freeSLNode(struct SLNode * node) {
    free(node);
}
