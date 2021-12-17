#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 10

typedef int element;
typedef struct { // 큐 타입
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

// 공백 상태 검출 함수
void init_queue(QueueType* q)
{
    q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType* q)
{
    return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType* q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 원형큐 출력 함수
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

// 삽입 함수
void enqueue(QueueType* q, element item)
{
    if (is_full(q))
        fprintf(stderr, "%s\n", "큐가 포화상태입니다");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType* q)
{
    if (is_empty(q))
        fprintf(stderr, "%s\n", "큐가 공백입니다");
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

            printf("자리를 정해주세요 : ");
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
                printf("1,2,3번 중에 골라주세요.\n");
                i--;
                break;
            }
        }
        if (table == 0) {
            printf("\n식당이 꽉 찼습니다. 대기열로 이동합니다.");
            break;
        }
    }

    init_queue(&queue);
    printf("\n\n* 식당 대기열 *\n\n");
    enqueue(&queue, 5); // 대기열 초기인원
    enqueue(&queue, 7); // 대기열 초기인원
    while (!is_full(&queue) && !is_empty(&queue))
    {
        if (is_empty(&queue)) {
            printf("현재 대기열은 없습니다. 식당으로 들어오세요.\n");
        }
        if (is_full(&queue)) {
            printf("현재 대기열이 꽉 찼습니다. 다음에 와주세요.\n");
        }

        printf("식당 대기 순서 : "); 
        scanf("%d", &element);  // 대기열 추가
        enqueue(&queue, element);
        printf("현재 대기열 : ");
        queue_print(&queue);

        if (!is_empty(&queue)) // 식당으로 진입 (대기열 삭제)
        {
            element = dequeue(&queue);
            printf("%d번 손님 : 식당으로 들어오세요\n", element);
            printf("현재 대기열 : ");
            queue_print(&queue);
        }
    }

    printf("너무 많은 사람이 대기열에 들어왔거나 대기열이 없어 사용할 이유가 없습니다.");

    return 0;
}