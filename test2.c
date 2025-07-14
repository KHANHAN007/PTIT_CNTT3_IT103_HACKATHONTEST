#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

typedef struct {
    char number[20];
    char timestamp[30];
} Call;

typedef struct {
    Call data[MAX];
    int top;
} Stack;

typedef struct {
    Call data[MAX];
    int front, rear;
} Queue;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmptyStack(Stack *s) {
    return s->top == -1;
}

int isFullStack(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, Call c) {
    if (!isFullStack(s)) {
        s->data[++(s->top)] = c;
    }
}

Call pop(Stack *s) {
    if (!isEmptyStack(s)) {
        return s->data[(s->top)--];
    }
    Call empty = {"", ""};
    return empty;
}

Call top(Stack *s) {
    if (!isEmptyStack(s)) {
        return s->data[s->top];
    }
    Call empty = {"", ""};
    return empty;
}

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isEmptyQueue(Queue *q) {
    return q->front == -1;
}

int isFullQueue(Queue *q) {
    return (q->rear + 1) % MAX == q->front;
}

void enqueue(Queue *q, Call c) {
    if (!isFullQueue(q)) {
        if (isEmptyQueue(q)) q->front = 0;
        q->rear = (q->rear + 1) % MAX;
        q->data[q->rear] = c;
    }
}

void displayQueue(Queue *q) {
    if (isEmptyQueue(q)) {
        printf("Lich su rong.\n");
        return;
    }
    printf("Lich su cuoc goi:\n");
    int i = q->front;
    while (1) {
        printf("- %s (%s)\n", q->data[i].number, q->data[i].timestamp);
        if (i == q->rear) break;
        i = (i + 1) % MAX;
    }
}

char *getCurrentTime() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    static char buffer[30];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", t);
    return buffer;
}

void CALL(Stack *back, Stack *forward, Queue *history) {
    Call c;
    printf("Nhap so dien thoai: ");
    scanf("%s", c.number);
    strcpy(c.timestamp, getCurrentTime());

    push(back, c);
    enqueue(history, c);
    initStack(forward);
    printf("Da goi so: %s (%s)\n", c.number, c.timestamp);
}

void BACK(Stack *back, Stack *forward) {
    if (back->top < 1) {
        printf("Khong co cuoc goi truoc do.\n");
        return;
    }
    Call last = pop(back);
    push(forward, last);
    Call prev = top(back);
    printf("Quay lai so truoc: %s (%s)\n", prev.number, prev.timestamp);
}

void REDIAL(Stack *back, Stack *forward) {
    if (isEmptyStack(forward)) {
        printf("Khong co so nao de goi lai.\n");
        return;
    }
    Call next = pop(forward);
    push(back, next);
    printf("Goi lai so: %s (%s)\n", next.number, next.timestamp);
}

int main() {
    Stack backStack, forwardStack;
    Queue callHistoryQueue;

    initStack(&backStack);
    initStack(&forwardStack);
    initQueue(&callHistoryQueue);

    char command[10];

    while (1) {
        printf("\nNhap lenh (CALL, BACK, REDIAL, HISTORY, EXIT): ");
        scanf("%s", command);
        if (strcmp(command, "CALL") == 0) {
            CALL(&backStack, &forwardStack, &callHistoryQueue);
        } else if (strcmp(command, "BACK") == 0) {
            BACK(&backStack, &forwardStack);
        } else if (strcmp(command, "REDIAL") == 0) {
            REDIAL(&backStack, &forwardStack);
        } else if (strcmp(command, "HISTORY") == 0) {
            displayQueue(&callHistoryQueue);
        } else if (strcmp(command, "EXIT") == 0) {
            break;
        } else {
            printf("Lenh khong hop le.\n");
        }
    }
    return 0;
}
