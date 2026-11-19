
#include <stdio.h>
#include <stdlib.h>
typedef struct nodeCreation
{
    int data;
    struct nodeCreation *next;
} node;

// Array Queue
void enqueueArray(int value, int array[], int *rear) {
    array[++(*rear)] = value;
}
int dequeueArray(int array[], int *front) {
    return array[(*front)++];
}

// Array Stack
void pushArray(int value, int stack[], int *top) {
    stack[++(*top)] = value;
}
int popArray(int stack[], int *top) {
    return stack[(*top)--];
}

// Linked List Queue
void enqueueLinked(node *s, int value) {
    while (s->next != NULL) {
        s = s->next;
    }
    s->next = (node*) malloc(sizeof(node));
    s->next->data = value;
    s->next->next = NULL;
}
int dequeueLinked(node *s) {
    node *temp = s->next;
    int value = temp->data;
    s->next = temp->next;
    free(temp);
    return value;
}

// Linked List Stack
void pushLinked(node *s, int value) {
    node *newNode = (node*) malloc(sizeof(node));
    newNode->data = value;
    newNode->next = s->next;
    s->next = newNode;
}
int popLinked(node *s) {
    node *temp = s->next;
    int value = temp->data;
    s->next = temp->next;
    free(temp);
    return value;
}

// Display Queue
void showQueueArray(int front, int rear, int array[]) {
    if (front > rear) {
        printf("Empty");
    } else {
        for (int i = front; i <= rear; ++i) {
            printf("%d", array[i]);
            if (i == rear) printf("\n");
            else printf(" ");
        }
    }
}
void showQueueLinked(node *s) {
    if (s->next == NULL) {
        printf("Empty");
    } else {
        while (s->next != NULL) {
            printf("%d", s->next->data);
            s = s->next;
            if (s->next == NULL) printf("\n");
            else printf(" ");
        }
    }
}

// Display Stack
void showStackArray(int top, int stack[]) {
    if (top == -1) {
        printf("Empty");
    } else {
        for (int i = top; i >= 0; --i) {
            printf("%d", stack[i]);
            if (i == 0) printf("\n");
            else printf(" ");
        }
    }
}
void showStackLinked(node *s) {
    if (s->next == NULL) {
        printf("Empty");
    } else {
        while (s->next != NULL) {
            printf("%d", s->next->data);
            s = s->next;
            if (s->next == NULL) printf("\n");
            else printf(" ");
        }
    }
}

int main(void) {
    int N, Q;
    scanf("%d %d", &N, &Q);
    int arrayQueue[N+Q+5];
    int arrayStack[N+Q+5];
    int front = 0;
    int rear = -1;
    int top = -1;
    node *queueFirst = (node*) malloc(sizeof(node));
    node *stackFirst = (node*) malloc(sizeof(node));
    queueFirst->next = NULL;
    stackFirst->next = NULL;
    for (int i = 0; i < N; ++i) {
        int x;
        scanf("%d", &x);
        enqueueArray(x, arrayQueue, &rear);
        enqueueLinked(queueFirst, x);
    }
    for (int i = 0; i < Q; ++i) {
        char operation[20];
        scanf("%s", operation);
        if (operation[0] == 'A') {
            int x;
            scanf("%d", &x);
            enqueueArray(x, arrayQueue, &rear);
            enqueueLinked(queueFirst, x);
        }
        else if (operation[0] == 'S') {
            if (front > rear) {
                printf("SERVE: Not Possible\n");
            } else {
                int value = dequeueArray(arrayQueue, &front);
                dequeueLinked(queueFirst);
                pushArray(value, arrayStack, &top);
                pushLinked(stackFirst, value);
            }
        }
        else if (operation[0] == 'R') {
            if (top == -1) {
                printf("REOPEN: Not Possible\n");
            } else {
                int value = popArray(arrayStack, &top);
                popLinked(stackFirst);
                enqueueArray(value, arrayQueue, &rear);
                enqueueLinked(queueFirst, value);
            }
        }
    }
    printf("Array Queue: ");
    showQueueArray(front, rear, arrayQueue);
    printf("Linked Queue: ");
    showQueueLinked(queueFirst);
    printf("Array Stack: ");
    showStackArray(top, arrayStack);
    printf("Linked Stack: ");
    showStackLinked(stackFirst);
    return 0;
}
