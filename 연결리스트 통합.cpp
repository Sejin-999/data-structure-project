#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef int element; // ����� Ÿ��
typedef struct QueueNode { // ť�� ����� Ÿ��
	element data;
	struct QueueNode* link;
} QueueNode;
typedef struct { // ť ADT ����
	QueueNode* front, * rear;
} LinkedQueueType;

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

void init(LinkedQueueType* q) {
	q->front = NULL;
	q->rear = NULL;
}

int is_empty(LinkedQueueType* q) {
	return (q->front == NULL);

}

void print_queue(LinkedQueueType* q) {
	QueueNode* p = q->front;
	while (p != NULL) {
		printf("%d ->", p->data);
		p = p->link;
	}
	printf("\n");
}

// ���� �Լ�
void enqueue(LinkedQueueType* q, element data)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	temp->data = data; // ������ ����
	temp->link = NULL; // ��ũ �ʵ带 NULL
	if (is_empty(q)) { // ť�� �����̸�
		q->front = temp;
		q->rear = temp;
	}
	else { // ť�� ������ �ƴϸ�
		q->rear->link = temp; // ������ �߿�
		q->rear = temp;
	}
}

// ���� �Լ�
element dequeue(LinkedQueueType* q)
{
	QueueNode* temp = q->front;
	element data;
	if (is_empty(q)) { // �������
		fprintf(stderr, "������ �������\n");
		exit(1);
	}
	else {
		data = temp->data; // �����͸� ������.
		q->front = q->front->link; // front�� �������
		if (q->front == NULL) // ���� ����
			q->rear = NULL;
		free(temp); // �����޸� ����
		return data; // ������ ��ȯ
	}
}
int time_out(LinkedQueueType* q, int n) {
	if (q->front->data == n) {
		return 1;
	}
	else
		return 0;
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

void print_list(ListNode* head)
{
	char number[3] = { '1', '2', '3' };
	for (int i = 0; i < 3; i++)
	{
		printf("|%c��| -  ", number[i]);
	}
	printf("NULL \n");

	for (ListNode* p = head; p != NULL; p = p->link)
	{
		printf("| %s | - ", p->data.state);
	}
	printf("NULL \n");
}

int main(void) {
	LinkedQueueType delaytime;
	init(&delaytime);

	ListNode* head = NULL;
	element2 data;
	int num = 0;
	int table = 3;
	int i;

	int count = 0; // ���� ����
	int clock; //�ð�
	int timer = -1; //���ð� üũ�� Ÿ�̸�
	int minute = 60;
	int resttime = 0; //�� ���� ���ð�

	srand(time(NULL));
	//�ڸ��� ������ ���ð��� ���۵�����

	for (i = 0; i < 3; i++)
	{
		strcpy_s(data.state, "O");
		head = insert_first(head, data);
	}
	print_list(head);

	while (table != 0)
	{
		ListNode* pre = NULL;
		table--;

		printf("���̺��� ���ϼ��� : ");
		scanf_s("%d", &num);
		switch (num)
		{
		case 1:
			head = delete_first(head);
			strcpy_s(data.state, "X");
			head = insert_first(head, data);
			print_list(head);
			break;
		case 2:
			pre = head;
			head = delete_(head, pre);
			strcpy_s(data.state, "X");
			head = insert(head, pre, data);
			print_list(head);
			break;
		case 3:
			pre = head->link;
			head = delete_(head, pre);
			strcpy_s(data.state, "X");
			head = insert(head, pre, data);
			print_list(head);
			break;
		default:
			printf("1,2,3�� �߿� ���Ͻʽÿ�.\n");
			i--;
			break;
		}
		printf("\n�μ��Դϴ�. ��⿭�� �̵��մϴ�.");
	}
	while(1)
	{
		for (clock = 0; clock < minute; clock++)
		{
			printf("����ð�=%d\n", clock);
			int n = rand() % 3 + 1; //���ð��� 3���̳�
			enqueue(&delaytime, n);
			count += 1; //���� ���� 1����
			resttime += n;
			timer += 1;
			printf("%d�� ���ð� �߰� \n", n);

			if (time_out(&delaytime, timer))//���ð��� ������ ��ǰ�� �����ٸ�
			{
				printf("���� �ֹ��� �Ϸ�Ǿ����ϴ� \n");
				dequeue(&delaytime);
				count -= 1; //���� ���� ���� -1

				resttime -= timer;
				timer = 0; //Ÿ�̸� 0���� �ʱ�ȭ
			}
			printf("���� %d�� ����� , %d�� ��� \n \n", count, resttime);

		}
	}
	// ���� ����� �ڸ��� ��á�ٴ� ����.
	}
