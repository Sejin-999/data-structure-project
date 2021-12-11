#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int element; // ����� Ÿ��
typedef struct QueueNode { // ť�� ����� Ÿ��
	element data;
	struct QueueNode* link;
} QueueNode;
typedef struct { // ť ADT ����
	QueueNode* front, * rear;
} LinkedQueueType;

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

void main() {
	LinkedQueueType delaytime;
	init(&delaytime);

	int count = 0; // ���� ����
	int clock; //�ð�
	int timer = -1; //���ð� üũ�� Ÿ�̸�
	int minute = 60;
	int resttime = 0; //�� ���� ���ð�

	srand(time(NULL));
	//�ڸ��� ������ ���ð��� ���۵�����
	
	for (clock = 0; clock < minute; clock++) {
		printf("����ð�=%d\n", clock);
		
		if (1)// if( �ڸ��� ���� á�ٸ�)
		{
			int n = rand() % 3 + 1; //���ð��� 3���̳�
			enqueue(&delaytime, n);
			count += 1; //���� ���� 1����
			resttime += n;
			timer += 1;
			printf("%d�� ���ð� �߰� \n" , n);

			if (time_out(&delaytime , timer))//���ð��� ������ ��ǰ�� �����ٸ�
			{
				printf("���� �ֹ��� �Ϸ�Ǿ����ϴ� \n");
				dequeue(&delaytime);
				count -= 1; //���� ���� ���� -1

				resttime -= timer;
				timer = 0; //Ÿ�̸� 0���� �ʱ�ȭ
			}




		}
		else//�ڸ���  �� ��á�ٸ� 
		{
			//�ڸ��� �߰�
		}
		printf("���� %d�� ����� , %d�� ��� \n \n", count, resttime);

	}
	// ���� ����� �ڸ��� ��á�ٴ� ����.
}
