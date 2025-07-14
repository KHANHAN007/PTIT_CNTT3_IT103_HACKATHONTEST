#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char phoneNumber[20];
    time_t callTime;
} Call;

typedef struct StackNode {
    Call data;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
} Stack;

void initStack(Stack* s) {
    s->top = NULL;
}

int isStackEmpty(Stack* s) {
    return s->top == NULL;
}

void push(Stack* s, Call c) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = c;
    newNode->next = s->top;
    s->top = newNode;
}

Call pop(Stack* s) {
    if (isStackEmpty(s)) {
        Call emptyCall;
        emptyCall.phoneNumber[0] = '\0';
        emptyCall.callTime = 0;
        return emptyCall;
    }
    StackNode* temp = s->top;
    Call c = temp->data;
    s->top = temp->next;
    free(temp);
    return c;
}

Call peek(Stack* s) {
    if (isStackEmpty(s)) {
        Call emptyCall;
        emptyCall.phoneNumber[0] = '\0';
        emptyCall.callTime = 0;
        return emptyCall;
    }
    return s->top->data;
}
void freeStack(Stack* s) {
    while (!isStackEmpty(s)) {
        pop(s);
    }
}
typedef struct QueueNode {
    Call data;
    struct QueueNode* next;
} QueueNode;
typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;
void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}
int isQueueEmpty(Queue* q) {
    return q->front == NULL;
}
void enqueue(Queue* q, Call c) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = c;
    newNode->next = NULL;
    if (isQueueEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}
Call dequeue(Queue* q) {
    if (isQueueEmpty(q)) {
        Call emptyCall;
        emptyCall.phoneNumber[0] = '\0';
        emptyCall.callTime = 0;
        return emptyCall;
    }
    QueueNode* temp = q->front;
    Call c = temp->data;
    q->front = temp->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return c;
}
void freeQueue(Queue* q) {
    while (!isQueueEmpty(q)) {
        dequeue(q);
    }
}
void printCall(Call c) {
    char timeStr[30];
    struct tm *tm_info = localtime(&c.callTime);
    strftime(timeStr, 30, "%Y-%m-%d %H:%M:%S", tm_info);
    printf("So dien thoai: %s | Thoi gian: %s\n", c.phoneNumber, timeStr);
}
void clearStack(Stack* s) {
    freeStack(s);
}
int main() {
    Stack callBackStack, callForwardStack;
    Queue callHistoryQueue;
    initStack(&callBackStack);
    initStack(&callForwardStack);
    initQueue(&callHistoryQueue);
    char command[20];
    int running = 1;
    while (running) {
        printf("\nNhap lenh (CALL, BACK, REDIAL, HISTORY, EXIT): ");
        scanf("%s", command);

        if (strcmp(command, "CALL") == 0) {
            Call newCall;
            printf("Nhap so dien thoai: ");
            scanf("%s", newCall.phoneNumber);
            newCall.callTime = time(NULL);
            push(&callBackStack, newCall);
            enqueue(&callHistoryQueue, newCall);
            clearStack(&callForwardStack);
            printf("Da goi so moi: ");
            printCall(newCall);

        } else if (strcmp(command, "BACK") == 0) {
            StackNode *temp = callBackStack.top;
            if (temp != NULL && temp->next != NULL) {
                Call popped = pop(&callBackStack);
                push(&callForwardStack, popped);

                Call current = peek(&callBackStack);
                printf("So dien thoai hien tai sau khi quay lai: ");
                printCall(current);
            } else {
                printf("Khong co cuoc goi nao truoc do.\n");
            }
        } else if (strcmp(command, "REDIAL") == 0) {
            if (!isStackEmpty(&callForwardStack)) {
                Call redialCall = pop(&callForwardStack);
                push(&callBackStack, redialCall);
                printf("Go lai so: ");
                printCall(redialCall);
            } else {
                printf("Khong co so nao de goi lai.\n");
            }
        } else if (strcmp(command, "HISTORY") == 0) {
            if (isQueueEmpty(&callHistoryQueue)) {
                printf("Lich su cuoc goi trong.\n");
            } else {
                printf("Lich su cuoc goi:\n");
                QueueNode *cur = callHistoryQueue.front;
                while (cur != NULL) {
                    printCall(cur->data);
                    cur = cur->next;
                }
            }
        } else if (strcmp(command, "EXIT") == 0) {
            running = 0;
            printf("Thoat chuong trinh.\n");
        } else {
            printf("Lenh khong hop le. Vui long nhap lai.\n");
        }
    }
    freeStack(&callBackStack);
    freeStack(&callForwardStack);
    freeQueue(&callHistoryQueue);
    return 0;
}
