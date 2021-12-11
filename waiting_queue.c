#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10
typedef int element;
typedef struct { // ť Ÿ��
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
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
	printf("���� �Ĵ� ��� ���� = ", q->front, q->rear);
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

void queue_print2(QueueType* q)
{
	printf("���� �Ĵ� ��� ���� = ", q->front, q->rear);
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
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// ���� �Լ�
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

int main(void)
{
	QueueType queue;
	int element;
	init_queue(&queue);
	printf("* �Ĵ� ��⿭ *\n\n");
	enqueue(&queue, 5); // ��⿭ �ʱ��ο�
	enqueue(&queue, 7); // ��⿭ �ʱ��ο�
	while (!is_full(&queue)&&!is_empty(&queue))
	{
		if (is_empty(&queue)) {
			printf("���� ��⿭�� �����ϴ�. �Ĵ����� ��������.\n");
		}
		if (is_full(&queue)) {
			printf("���� ��⿭�� �� á���ϴ�. ������ ���ּ���.\n");
		}

		printf("�Ĵ� ��� ���� : ");
		scanf("%d", &element);
		enqueue(&queue, element);
		queue_print(&queue);

		if (!is_empty(&queue)) //�ڸ��� ����� <- �Ĵ� �ڸ��� ����
		{
			element = dequeue(&queue);
			printf("%d�� �մ� : �Ĵ����� ��������\n", element);
			queue_print(&queue);
		}
	}

	printf("�ʹ� ���� ����� ��⿭�� ���԰ų� ��⿭�� ���� ����� ������ �����ϴ�.");

	return 0;
}