#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int element; // 요소의 타입
typedef struct QueueNode { // 큐의 노드의 타입
	element data;
	struct QueueNode* link;
} QueueNode;
typedef struct { // 큐 ADT 구현
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

// 삽입 함수
void enqueue(LinkedQueueType* q, element data)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	temp->data = data; // 데이터 저장
	temp->link = NULL; // 링크 필드를 NULL
	if (is_empty(q)) { // 큐가 공백이면
		q->front = temp;
		q->rear = temp;
	}
	else { // 큐가 공백이 아니면
		q->rear->link = temp; // 순서가 중요
		q->rear = temp;
	}
}

// 삭제 함수
element dequeue(LinkedQueueType* q)
{
	QueueNode* temp = q->front;
	element data;
	if (is_empty(q)) { // 공백상태
		fprintf(stderr, "스택이 비어있음\n");
		exit(1);
	}
	else {
		data = temp->data; // 데이터를 꺼낸다.
		q->front = q->front->link; // front로 다음노드
		if (q->front == NULL) // 공백 상태
			q->rear = NULL;
		free(temp); // 동적메모리 해제
		return data; // 데이터 반환
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

	int count = 0; // 팀의 개수
	int clock; //시간
	int timer = -1; //대기시간 체크용 타이머
	int minute = 60;
	int resttime = 0; //총 남은 대기시간

	srand(time(NULL));
	//자리가 다차야 대기시간이 시작됨으로
	
	for (clock = 0; clock < minute; clock++) {
		printf("현재시각=%d\n", clock);
		
		if (1)// if( 자리가 전부 찼다면)
		{
			int n = rand() % 3 + 1; //대기시간은 3분이내
			enqueue(&delaytime, n);
			count += 1; //팀의 개수 1증가
			resttime += n;
			timer += 1;
			printf("%d분 대기시간 추가 \n" , n);

			if (time_out(&delaytime , timer))//대기시간이 지나서 상품이 나갔다면
			{
				printf("한팀 주문이 완료되었습니다 \n");
				dequeue(&delaytime);
				count -= 1; //남은 팀의 개수 -1

				resttime -= timer;
				timer = 0; //타이머 0으로 초기화
			}




		}
		else//자리가  다 안찼다면 
		{
			//자리에 추가
		}
		printf("현재 %d팀 대기중 , %d분 대기 \n \n", count, resttime);

	}
	// 실행 결과는 자리가 꽉찼다는 가정.
}
