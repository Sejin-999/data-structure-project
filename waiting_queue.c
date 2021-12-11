#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10
typedef int element;
typedef struct { // 큐 타입
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
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
	printf("현재 식당 대기 순서 = ", q->front, q->rear);
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
	printf("현재 식당 대기 순서 = ", q->front, q->rear);
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
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

int main(void)
{
	QueueType queue;
	int element;
	init_queue(&queue);
	printf("* 식당 대기열 *\n\n");
	enqueue(&queue, 5); // 대기열 초기인원
	enqueue(&queue, 7); // 대기열 초기인원
	while (!is_full(&queue)&&!is_empty(&queue))
	{
		if (is_empty(&queue)) {
			printf("현재 대기열은 없습니다. 식당으로 들어오세요.\n");
		}
		if (is_full(&queue)) {
			printf("현재 대기열이 꽉 찼습니다. 다음에 와주세요.\n");
		}

		printf("식당 대기 순서 : ");
		scanf("%d", &element);
		enqueue(&queue, element);
		queue_print(&queue);

		if (!is_empty(&queue)) //자리가 생기면 <- 식당 자리와 조합
		{
			element = dequeue(&queue);
			printf("%d번 손님 : 식당으로 들어오세요\n", element);
			queue_print(&queue);
		}
	}

	printf("너무 많은 사람이 대기열에 들어왔거나 대기열이 없어 사용할 이유가 없습니다.");

	return 0;
}