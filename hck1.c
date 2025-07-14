#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char title[100];
    int credits;
} Course;

typedef struct SingleNode {
    Course data;
    struct SingleNode *next;
} SingleNode;

typedef struct DoubleNode {
    Course data;
    struct DoubleNode *next;
    struct DoubleNode *prev;
} DoubleNode;

SingleNode *createSingleNode(Course c) {
    SingleNode *newNode = (SingleNode*)malloc(sizeof(SingleNode));
    newNode->data = c;
    newNode->next = NULL;
    return newNode;
}

SingleNode* addSingleNode(SingleNode *head) {
    Course c;
    printf("Nhap ID khoa hoc: ");
    scanf("%d", &c.id);
    getchar();
    printf("Nhap ten khoa hoc: ");
    fgets(c.title, sizeof(c.title), stdin);
    c.title[strcspn(c.title, "\n")] = '\0';
    printf("Nhap so tin chi: ");
    scanf("%d", &c.credits);
    getchar();

    SingleNode *newNode = createSingleNode(c);
    if (head == NULL) return newNode;

    SingleNode *temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
    return head;
}

void printSingleNode(SingleNode *head) {
    if (head == NULL) {
        printf("Danh sach khoa hoc rong.\n");
        return;
    }
    printf("Danh sach khoa hoc dang hoc:\n");
    SingleNode *temp = head;
    while (temp != NULL) {
        printf("ID: %d | %s | Tin chi: %d\n", temp->data.id, temp->data.title, temp->data.credits);
        temp = temp->next;
    }
}

SingleNode* deleteSingleNode(SingleNode *head, int id) {
    if (head == NULL) return NULL;
    if (head->data.id == id) {
        SingleNode *temp = head;
        head = head->next;
        free(temp);
        printf("Da xoa khoa hoc co ID %d.\n", id);
        return head;
    }
    SingleNode *current = head;
    while (current->next != NULL && current->next->data.id != id) {
        current = current->next;
    }
    if (current->next != NULL) {
        SingleNode *temp = current->next;
        current->next = temp->next;
        free(temp);
        printf("Da xoa khoa hoc co ID %d.\n", id);
    } else {
        printf("Khong tim thay khoa hoc co ID %d de xoa.\n", id);
    }
    return head;
}

SingleNode* replacerSingleNode(SingleNode *head, int id) {
    if (head == NULL) {
        printf("Danh sach khoa hoc rong.\n");
        return head;
    }
    SingleNode *current = head;
    while (current != NULL) {
        if (current->data.id == id) {
            printf("Nhap ten khoa hoc moi: ");
            fgets(current->data.title, sizeof(current->data.title), stdin);
            current->data.title[strcspn(current->data.title, "\n")] = '\0';
            printf("Nhap so tin chi moi: ");
            scanf("%d", &current->data.credits);
            getchar();
            printf("Da cap nhat khoa hoc co ID %d.\n", id);
            return head;
        }
        current = current->next;
    }
    printf("Khong tim thay khoa hoc co ID %d.\n", id);
    return head;
}

DoubleNode *createNodeDouble(Course c) {
    DoubleNode *newNode = (DoubleNode *) malloc(sizeof(DoubleNode));
    newNode->data = c;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

DoubleNode *initDoubleNode(DoubleNode *headDouble, SingleNode **headSingle, int id) {
    SingleNode *temp = *headSingle;
    SingleNode *prev = NULL;
    while (temp != NULL) {
        if (temp->data.id == id) {
            DoubleNode *newNode = createNodeDouble(temp->data);
            if (headDouble == NULL) {
                headDouble = newNode;
            } else {
                DoubleNode *cur = headDouble;
                while (cur->next != NULL) cur = cur->next;
                cur->next = newNode;
                newNode->prev = cur;
            }
            if (prev == NULL) {
                *headSingle = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Da danh dau khoa hoc ID %d da hoan thanh.\n", id);
            return headDouble;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Khong tim thay khoa hoc co ID %d de danh dau.\n", id);
    return headDouble;
}

void printDoubleNode(DoubleNode *head) {
    if (head == NULL) {
        printf("Danh sach khoa hoc da hoan thanh trong.\n");
        return;
    }
    printf("Danh sach khoa hoc da hoan thanh:\n");
    DoubleNode *temp = head;
    while (temp != NULL) {
        printf("ID: %d | %s | Tin chi: %d\n", temp->data.id, temp->data.title, temp->data.credits);
        temp = temp->next;
    }
}

void sortByCredits(SingleNode *head) {
    if (head == NULL) return;
    int swapped;
    SingleNode *ptr1;
    SingleNode *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data.credits > ptr1->next->data.credits) {
                Course temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    printf("Da sap xep khoa hoc theo so tin chi.\n");
}

void searchByTitle(SingleNode *head, char *title) {
    int found = 0;
    while (head != NULL) {
        if (strcmp(head->data.title, title) == 0) {
            printf("Tim thay khoa hoc: ID: %d | %s | Tin chi: %d\n", head->data.id, head->data.title, head->data.credits);
            found = 1;
        }
        head = head->next;
    }
    if (!found) printf("Khong tim thay khoa hoc co ten '%s'.\n", title);
}

void freeSingleList(SingleNode *head) {
    SingleNode *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void freeDoubleList(DoubleNode *head) {
    DoubleNode *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    SingleNode *headSingle = NULL;
    DoubleNode *headDouble = NULL;
    int choice;

    do {
        printf("\n--- COURSE MANAGER ---\n");
        printf("1. Them khoa hoc.\n");
        printf("2. Hien thi danh sach khoa hoc.\n");
        printf("3. Xoa khoa hoc.\n");
        printf("4. Cap nhat thong tin khoa hoc.\n");
        printf("5. Danh dau khoa hoc da hoan thanh.\n");
        printf("6. Sap xep khoa hoc theo so tin chi.\n");
        printf("7. Tim kiem khoa hoc theo ten.\n");
        printf("8. Hien thi khoa hoc da hoan thanh.\n");
        printf("9. Thoat chuong trinh.\n");
        printf("Chon: ");
        scanf("%d", &choice);
        getchar();

        int id;
        char title[100];

        switch (choice) {
            case 1:
                headSingle = addSingleNode(headSingle);
                break;
            case 2:
                printSingleNode(headSingle);
                break;
            case 3:
                printf("Nhap ID khoa hoc muon xoa: ");
                scanf("%d", &id);
                getchar();
                headSingle = deleteSingleNode(headSingle, id);
                break;
            case 4:
                printf("Nhap ID khoa hoc muon cap nhat: ");
                scanf("%d", &id);
                getchar();
                headSingle = replacerSingleNode(headSingle, id);
                break;
            case 5:
                printf("Nhap ID khoa hoc da hoan thanh: ");
                scanf("%d", &id);
                getchar();
                headDouble = initDoubleNode(headDouble, &headSingle, id);
                break;
            case 6:
                sortByCredits(headSingle);
                break;
            case 7:
                printf("Nhap ten khoa hoc muon tim: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';
                searchByTitle(headSingle, title);
                break;
            case 8:
                printDoubleNode(headDouble);
                break;
            case 9:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 9);
    freeSingleList(headSingle);
    freeDoubleList(headDouble);
    return 0;
}
