#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 10

typedef int element;
typedef struct { // ť Ÿ��
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

typedef struct
{
    char state[2];
} element2;
typedef struct ListNode
{
    element2 data;
    struct ListNode* link;
} ListNode;

void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

ListNode* insert_first(ListNode* head, element2 value)
{
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}

ListNode* insert(ListNode* head, ListNode* pre, element2 value)
{
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}

ListNode* delete_first(ListNode* head)
{
    ListNode* removed;
    if (head == NULL) return NULL;
    removed = head;
    head = removed->link;
    free(removed);
    return head;
}

ListNode* delete_(ListNode* head, ListNode* pre)
{
    ListNode* removed;
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}

ListNode* search_list(ListNode* head, int n)
{
    ListNode* p = head;
    int i;

    for (i = 0; i < n; i++)
    {
        p = p->link;
    }
    return p;
}

void print_list(ListNode* head)
{
    char number[3] = { '1', '2', '3' };
    for (int i = 0; i < 3; i++)
    {
        printf("|%c| -  ", number[i]);
    }
    printf("NULL \n");

    for (ListNode* p = head; p != NULL; p = p->link)
    {
        printf("| %s | - ", p->data.state);
    }
    printf("NULL \n");
}

// ���� ���� ���� �Լ�
void init_queue(QueueType* q)
{
    q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
    return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ����ť ��� �Լ�
void queue_print(QueueType* q)
{
    if (!is_empty(q)) {
        int i = q->front;
        do {
            i = (i + 1) % (MAX_QUEUE_SIZE);
            printf("%d | ", q->data[i]);
            if (i == q->rear)
                break;
        } while (i != q->front);
    }
    printf("\n\n");
}

// ���� �Լ�
void enqueue(QueueType* q, element item)
{
    if (is_full(q))
        fprintf(stderr, "%s\n", "ť�� ��ȭ�����Դϴ�");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// ���� �Լ�
element dequeue(QueueType* q)
{
    if (is_empty(q))
        fprintf(stderr, "%s\n", "ť�� �����Դϴ�");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

int main(void)
{
    ListNode* head = NULL;
    int element;
    element2 data;
    QueueType queue;

    init_queue(&queue);
    int num = 0;
    int table = 3;
    int i;

    for (i = 0; i < 3; i++)
    {
        strcpy(data.state, "O");
        head = insert_first(head, data);
    }
    print_list(head);
    while (1)
    {
        while (table != 0)
        {
            ListNode* pre = NULL;

            printf("�ڸ��� �����ּ��� : ");
            scanf("%d", &num);
            switch (num)
            {
            case 1:
                head = delete_first(head);
                strcpy(data.state, "X");
                head = insert_first(head, data);
                print_list(head);
                table--;
                break;
            case 2:
                pre = head;
                head = delete_(head, pre);
                strcpy(data.state, "X");
                head = insert(head, pre, data);
                print_list(head);
                table--;
                break;
            case 3:
                pre = head->link;
                head = delete_(head, pre);
                strcpy(data.state, "X");
                head = insert(head, pre, data);
                print_list(head);
                table--;
                break;
            default:
                printf("1,2,3�� �߿� ����ּ���.\n");
                i--;
                break;
            }
        }
        if (table == 0) {
            printf("\n�Ĵ��� �� á���ϴ�. ��⿭�� �̵��մϴ�.");
            break;
        }
    }

    init_queue(&queue);
    printf("\n\n* �Ĵ� ��⿭ *\n\n");
    enqueue(&queue, 5); // ��⿭ �ʱ��ο�
    enqueue(&queue, 7); // ��⿭ �ʱ��ο�
    while (!is_full(&queue) && !is_empty(&queue))
    {
        if (is_empty(&queue)) {
            printf("���� ��⿭�� �����ϴ�. �Ĵ����� ��������.\n");
        }
        if (is_full(&queue)) {
            printf("���� ��⿭�� �� á���ϴ�. ������ ���ּ���.\n");
        }

        printf("�Ĵ� ��� ���� : "); 
        scanf("%d", &element);  // ��⿭ �߰�
        enqueue(&queue, element);
        printf("���� ��⿭ : ");
        queue_print(&queue);

        if (!is_empty(&queue)) // �Ĵ����� ���� (��⿭ ����)
        {
            element = dequeue(&queue);
            printf("%d�� �մ� : �Ĵ����� ��������\n", element);
            printf("���� ��⿭ : ");
            queue_print(&queue);
        }
    }

    printf("�ʹ� ���� ����� ��⿭�� ���԰ų� ��⿭�� ���� ����� ������ �����ϴ�.");

    return 0;
}