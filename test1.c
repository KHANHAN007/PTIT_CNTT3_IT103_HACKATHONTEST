#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int id;
    char title[100];
    int credit;
} Course;

typedef struct {
    Course data;
    struct SingleNode *next;
} SingleNode;

typedef struct {
    Course data;
    struct DoubleNode *next;
    struct DoubleNode *prev;
} DoubleNode;

SingleNode *singleHead = NULL;
DoubleNode *doubleHead = NULL;

SingleNode *createSingleNode(int id, char title[100], int credit) {
    SingleNode *newNode = (SingleNode *) malloc(sizeof(SingleNode));
    newNode->data.id = id;
    strcpy(newNode->data.title, title);
    newNode->data.credit = credit;
    newNode->next = NULL;
    return newNode;
}

SingleNode *initSingleNode(SingleNode *head) {
    Course course;
    printf("Nhap id khoa hoc: ");
    scanf("%d", &course.id);
    printf("Nhap ten khoa hoc: ");
    scanf("%s", course.title);
    course.title[strcspn(course.title, "\n")] = '\0';
    printf("Nhap so tin chi: ");
    scanf("%d", &course.credit);
    SingleNode *newNode = createSingleNode(course.id, course.title, course.credit);
    if (head == NULL) {
        return newNode;
    }
    SingleNode *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

void printNode(SingleNode *singleHead, DoubleNode *doubleHead) {
    if (singleHead == NULL) {
        printf("Danh sach khoa hoc dang hoc rong.\n");
    } else {
        printf("=== Danh sach khoa dang hoc ===\n");
        printf("%-5s | %-30s | %-7s\n", "ID", "Title", "Credits");
        printf("-----------------------------------------------------------\n");
        while (singleHead != NULL) {
            printf("%-5d | %-30s | %-7d\n", singleHead->data.id, singleHead->data.title, singleHead->data.credit);
            singleHead = singleHead->next;
        }
        printf("-----------------------------------------------------------\n\n");
    }

    if (doubleHead == NULL) {
        printf("Danh sach khoa hoc da hoan thanh rong.\n");
    } else {
        printf("=== Danh sach khoa hoc da hoan thanh ===\n");
        printf("%-5s | %-30s | %-7s\n", "ID", "Title", "Credits");
        printf("-----------------------------------------------------------\n");
        while (doubleHead != NULL) {
            printf("%-5d | %-30s | %-7d\n", doubleHead->data.id, doubleHead->data.title, doubleHead->data.credit);
            doubleHead = doubleHead->next;
        }
        printf("-----------------------------------------------------------\n\n");
    }
}

SingleNode *deleteSingleNode(SingleNode *head, int id) {
    if (head == NULL) {
        printf("Danh sach khoa hoc rong.\n");
        exit(0);
    }
    SingleNode *current = head;
    SingleNode *prev = NULL;
    while (current != NULL) {
        if (current->data.id == id) {
            if (prev == NULL) {
                head = current->next;
                free(current);
                return head;
            }
            prev->next = current->next;
            free(current);
            return head;
        }
        prev = current;
        current = current->next;
    }
    printf("Khong tim thay khoa hoc nay.\n");
    return head;
}

SingleNode *replacerSingleNode(SingleNode *head, int id) {
    if (head == NULL) {
        printf("Danh sach khoa hoc rong.\n");
        return head;
    }
    SingleNode *current = head;
    while (current != NULL) {
        if (current->data.id == id) {
            printf("Nhap ten khoa hoc moi: ");
            scanf("%s", current->data.title);
            current->data.title[strcspn(current->data.title, "\n")] = '\0';
            printf("Nhap so tin chi moi: ");
            scanf("%d", &current->data.credit);
            return head;
        }
        current = current->next;
    }
    printf("Khong tim thay khoa hoc nay.\n");
    return head;
}

DoubleNode *createDoubleNode(int id, char title[100], int credit) {
    DoubleNode *newNode = (DoubleNode *) malloc(sizeof(DoubleNode));
    newNode->data.id = id;
    strcpy(newNode->data.title, title);
    newNode->data.credit = credit;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

DoubleNode *initDoubleNode(SingleNode **singleHead, DoubleNode *doubleHead) {
    if (*singleHead == NULL) {
        printf("Khong co khoa nao da hoan thanh");
        exit(0);
    }
    int id;
    printf("Nhap id khoa hoc muon hoan thanh: ");
    scanf("%d", &id);
    SingleNode *current = *singleHead;
    SingleNode *prev = NULL;
    while (current != NULL) {
        if (current->data.id == id) {
            DoubleNode *newNode = createDoubleNode(current->data.id, current->data.title, current->data.credit);
            if (doubleHead == NULL) {
                doubleHead = newNode;
            } else {
                DoubleNode *temp = doubleHead;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newNode;
                newNode->prev = temp;
            }
            if (prev == NULL) {
                *singleHead = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Da danh dau khoa hoc %d la hoan thanh.\n", id);
            return doubleHead;
        }
        prev = current;
        current = current->next;
    }
    printf("Khong tim thay khoa hoc nay.\n");
    return doubleHead;
}

void sortCourse() {
    if (!singleHead && !singleHead->next) {
        return;
    }
    for (SingleNode *i = singleHead; i != NULL; i = i->next) {
        for (SingleNode *j = singleHead; j != NULL; j = j->next) {
            if (i->data.credit > j->data.credit) {
                int temp = i->data.credit;
                i->data.credit = j->data.credit;
                j->data.credit = temp;
            }
        }
    }
    printf("Danh sach khoa hoc da sap xep theo so tin chi.\n");
}

void searchCourse() {
    if (singleHead == NULL && doubleHead == NULL) {
        printf("Danh sach rong.\n");
        return;
    }
    char name[100];
    printf("Nhap tu khoa ten khoa hoc: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    int found = 0;
    SingleNode *current = singleHead;
    while (current != NULL) {
        if (strcmp(current->data.title, name) == 0) {
            printf("Khoa hoc \"%s\" dang hoc.\n", current->data.title);
            found = 1;
        }
        current = current->next;
    }
    DoubleNode *current2 = doubleHead;
    while (current2 != NULL) {
        if (strcmp(current2->data.title, name) == 0) {
            printf("Khoa hoc \"%s\" da hoan thanh.\n", current2->data.title);
            found = 1;
        }
        current2 = current2->next;
    }
    if (!found) {
        printf("Khoa hoc \"%s\" khong ton tai.\n", name);
    }
}


int main() {
    int choice, id;
    do {
        printf("\n--- COURSE MANAGER ---\n");
        printf("1. Them khoa hoc.\n");
        printf("2. Hien thi danh sach khoa hoc.\n");
        printf("3. Xoa khoa hoc.\n");
        printf("4. Sua khoa hoc.\n");
        printf("5. Danh dau khoa hoc da hoan thanh\n");
        printf("6. Sap xep khoa hoc theo so tin chi\n");
        printf("7. tim kiem khoa hoc theo ten\n");
        printf("8. Thoat chuong trinh\n");
        printf("Chon: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                singleHead = initSingleNode(singleHead);
                break;
            case 2:
                printNode(singleHead, doubleHead);
                break;
            case 3:
                printf("Nhap id khoa hoc muon xoa: ");
                scanf("%d", &id);
                singleHead = deleteSingleNode(singleHead, id);
                break;
            case 4:
                printf("Nhap id khoa hoc muon sua: ");
                scanf("%d", &id);
                singleHead = replacerSingleNode(singleHead, id);
                break;
            case 5:
                doubleHead = initDoubleNode(&singleHead, doubleHead);
                break;
            case 6:
                sortCourse();
                break;
            case 7:
                searchCourse();
                break;
            case 8:
                free(singleHead);
                free(doubleHead);
                break;

            default:
                printf("Chon khong hop le.\n");
        }
    } while (choice != 8);
}
