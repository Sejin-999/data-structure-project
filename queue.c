/*
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define CIRCLE_MAX_QUEUE_SIZE 100

typedef int element;
typedef struct DequeType {
	CosTime data[CIRCLE_MAX_QUEUE_SIZE];
	int front, rear;
}DequeType;

typedef struct element {
	int id;
	int ariival_time;
	int service_time;
}CosTime;
//삽입
void circle_enqueue(DequeType* q, CosTime item) {
	if (circle_full(q)) {
		circle_error("이미 자리에 사람들이 꽉 찼습니다.\n");
	}q->rear = (q->rear + 1) % CIRCLE_MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
//삭제
CosTime circle_dequeue(DequeType* q) {
	if (circle_empty(q)) {
		circle_error("자리에 사람이 아무도 없습니다.\n");
	}q->front = (q->front + 1) % CIRCLE_MAX_QUEUE_SIZE;
	return q->data[q->front];
}
//오류 

void circle_error(char* M) {
	printf("%s\n",M);
	exit(1);
}

//초기화

void circle_init(DequeType* q) {
	q->front = q->rear = 0;
}

//공백 검출
int circle_empty(DequeType* q) {
	return (q->front == q->rear);
}

// 포화 상태 검출

int circle_full(DequeType* q) {
	return ((q->rear + 1) % CIRCLE_MAX_QUEUE_SIZE == q->front);
}

// 출력

void circle_print(DequeType* q) {
	
}

int main() {
	int open_time = 240;
	int total_wait = 0;
	int total_customers = 0;
	int service_time = 0;
	int service_customer;
	int service_time=0, service_time_2 = 0, service_time_3 = 0, service_time_4 = 0, service_time_5 = 0;
	//int service_time_6 = 0, service_time_7 = 0, service_time_8 = 0, service_time_9 = 0, service_time_10 = 0;//추가로 사용할꺼면 열기
	bool table_1 = true, table_2 = true, table_3 = true, table_4 = true, table_5 = true;
	//bool table_6 = true, table_7 = true, table_8 = true, table_9 = true, table_10 = true; // 추가사용시 열기
	int service_1_time = 0, service_2_time = 0,service_3_time = 0, service_4_time = 0, service_5_time = 0; // 테이블별 식사 시간 담기
	int service_1_cos, service_2_cos, service_3_cos, service_4_cos, service_5_cos;
	DequeType queue;
	circle_init(&queue);
	srand(time(NULL)); //rand()를 초기화해주는 역할

	for (int clock = 0; clock < open_time; clock++) {
		//int hour, min;
		//hour = clock / 60;
		//min = clock % 60;  
		printf("\n---------------------현재시각 %d분-----------------------\n",clock);
		printf("\n-------------------------테이블현황--------------<사용중:1 사용가능:0>\n");
		printf("\n 1 : %d | 2 : %d | 3 : %d | 4 : %d | 5 : %d \n", table_1, table_2, table_3, table_4, table_5);
		//printf("\n 6 : %d | 7 : %d | 8 : %d | 9 : %d | 10 : %d \n", table_6, table_7, table_8, table_9, table_10); //추가사용시 열기



		if ((rand() % 10) < 3) {
			CosTime cos;
			cos.id = total_customers++; //고객 총 수 (1->2->3)
			cos.ariival_time = clock;
			cos.service_time = rand() % 3 + 10; //식사시간 설정
			circle_enqueue(&queue,cos);
			printf("고객번호 %d : 예상식사시간 : %d",cos.id,cos.service_time);
		}

		//table 자리 start
		if (service_1_time > 0) {
			printf("1번테이블은 %d번 고객이 사용중입니다.", service_1_cos);
			service_1_time--;
		}if (service_1_time == 0) {
			printf("1번테이블이 곧 사용가능합니다.");
			table_1 = true;
		}
		else if (table_1) {
			if (!circle_empty(&queue)) {	
				CosTime cos = circle_dequeue(&queue);
				service_1_cos = cos.id;
				service_1_time = cos.service_time;

				printf("1번테이블에서 %d 고객이 식사를 시작합니다. 예상식사시간은 %d분입니다.", cos.id, clock-cos.ariival_time);
				table_1 = false;
				total_wait += clock - cos.ariival_time;
			}
		}


		//table 자리 end
	}
}

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_QUEUE_SIZE 100
//고객 정보
typedef struct{
    int id;
    int in_time;
    int service_time;
} element;
// 원형 큐
/*=================================================================================*/
typedef struct
{
    element data[MAX_QUEUE_SIZE]; //element 타입으로 배열선언
    int front, rear;
} QueueType;
//에러 출력
void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}
//front, rear 초기화
void init_queue(QueueType* q)
{
    q->front = q->rear = 0;
}
//비어있는지 확인
int is_empty(QueueType* q)
{
    return (q->front == q->rear);
}
//가득차있는 확인
int is_full(QueueType* q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
//삽입 큐
void enqueue(QueueType* q, element item)
{
    if (is_full(q))
    {
        error("포화상태입니다.\n");
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}
//삭제 큐
element dequeue(QueueType* q)
{
    if (is_empty(q))
    {
        error("공백상태입니다.\n");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}
/*=================================================================================*/

void print_queue(){
    int minutes = 60;
    int total_wait = 0;
    int total_customers = 0;
    int one_time = 0,
        two_time = 0,
        thr_time = 0;
    int one_customer, //1번 테이블 시간저장
        two_customer,
        thr_customer;
    bool oneCounter = true;
    bool twoCounter = true;
    bool thrCounter = true;
    QueueType q;
    init_queue(&q);
    srand(time(NULL)); //rand()를 초기화해주는 역할
    for (int clock = 0; clock < minutes; clock++)
    {

        printf("\n--------------------현재시각=%d분-------------------- (0: 사용중, 1: 사용불가)\n", clock);
        printf("1번테이블 %d | 2번테이블 %d | 3번테이블 %d \n", oneCounter, twoCounter,thrCounter);
        if ((rand() % 10) < 3)
        {
            element customer;
            customer.id = total_customers++; //고객을 숫자로 지칭함. ex) 고객 1, 고객 2
            customer.in_time = clock;
            customer.service_time = rand() % 3 + 5;  //업무시간을 랜덤으로  조정
            enqueue(&q, customer);
            printf("손님 %d이 %d분에 들어옵니다. 예상식사시간 = %d\n", customer.id, customer.in_time, customer.service_time);
        }

        if (one_time > 0) //1번테이블사용중
        {
            printf("손님 %d  1번테이블 사용중\n", one_customer);
            one_time--;

            if (one_time == 0)
            {
                printf("(1번테이블 %d분 부터 사용가능합니다.)\n", clock + 1);
                oneCounter = true;
            }
        }
        else if (oneCounter) //1번테이블 자리비었을때
        {
            if (!is_empty(&q))
            {
                element customer = dequeue(&q);
                one_customer = customer.id;
                one_time = customer.service_time;

                printf("손님 %d이 %d분에 1번 테이블에서 식사를 시작합니다. 예상식사시간은 %d분입니다.\n", customer.id, clock, clock - customer.in_time);
                oneCounter = false;
                total_wait += clock - customer.in_time;
            }
        }

        if (two_time > 0) //2번테이블사용중
        {
            printf("손님 %d  2번테이블 사용중\n", two_customer);
            two_time--;

            if (two_time == 0)
            {
                printf("(2번테이블 %d분 부터 사용가능합니다.)\n", clock + 1);
                twoCounter = true;
            }
        }
        else if (twoCounter)
        {
            if (!is_empty(&q))
            {
                element customer = dequeue(&q);
                two_customer = customer.id;
                two_time = customer.service_time;
                printf("손님 %d이 %d분에 2번 테이블에서 식사를 시작합니다. 예상식사시간은 %d분입니다.\n", customer.id, clock, clock - customer.in_time);
                twoCounter = false;
                total_wait += clock - customer.in_time;
            }
        }

        if (thr_time > 0) //3번테이블사용중
        {
            printf("3번테이블 사용중\n");
            thr_time--;

            if (thr_time == 0)
            {
                printf("(3번테이블 %d분 부터 사용가능합니다.)\n", clock + 1);
                thrCounter = true;
            }
        }
        else if (thrCounter) //3번테이블 자리비었을때
        {
            if (!is_empty(&q))
            {
                element customer = dequeue(&q);
                one_customer = customer.id;
                thr_time = customer.service_time;

                printf("손님 %d이 %d분에 3번 테이블에서 식사를 시작합니다. 예상식사시간은 %d분입니다.\n", customer.id, clock, clock - customer.in_time);
                thrCounter = false;
                total_wait += clock - customer.in_time;
            }
        }


    }
    printf("전체 대기 시간 = %d분 \n", total_wait);
	
}

int main(void)
{
    print_queue();
    return 0;
}