# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <stdlib.h>
#include <windows.h> // 콘솔창 정리를 위한 헤더



typedef struct {
	int id;
	int aryival_time;
	int service_time;
} element;


#define MAX_QUEUE_SIZE 5
typedef struct {
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;


void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}


int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}


int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}


void queue_print(QueueType* q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int high = q->front;
		do {
			high = (high + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[high]);
			if (high == q->rear)
				break;
		} while (high != q->front);
	}
	printf("\n");
}


void enqueue(QueueType* q, element item)
{	
	
	if (is_full(q))
		printf("현재 만석입니다.\n\n");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}


element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}


element peek(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
//=========================== 여기서 부터 208줄까지=====================================
typedef struct list { // 차량 번호와 고객번호를 받는 구조체
	int car_num;
	int cus_num;
}list;
void SWAP(list* arr, int a, int b)
{
	list temp;
	temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void carSORT(list* arr, int left, int right) { //차량번호에 대한 퀵정렬 내림차순
	if (left < right)						   // 차량 번호는 랜덤으로 입력받기때문에 효율이 좋은 퀵정렬 사용
	{
		int key = left;
		int high = left + 1;
		int j = right;
		//엇갈리지 않을동안
		while (high <= j)
		{
			while (high <= right && arr[high].car_num >= arr[key].car_num)
				high++;
			while (j > left && arr[j].car_num <= arr[key].car_num)
				j--;
			//엇갈리면 j와 key값 교체
			if (high > j)
				SWAP(arr, j, key);
			//엇갈리지않으면 high와 j 교체
			else
				SWAP(arr, high, j);
		}
		//각각 정렬된 수의 전, 후 에서 똑같이 순환반복
		carSORT(arr, left, j - 1);
		carSORT(arr, j + 1, right);
	}
}
void carUPSORT(list* arr, int left, int right) { //차량번호에 대한 퀵정렬 오름차순
	if (left < right)						   
	{
		int key = left;
		int high = left + 1;
		int j = right;
		
		while (high <= j)
		{
			while (high <= right && arr[high].car_num < arr[key].car_num)
				high++;
			while (j > left && arr[j].car_num > arr[key].car_num)
				j--;
			
			if (high > j)
				SWAP(arr, j, key);
			
			else
				SWAP(arr, high, j);
		}
		
		carUPSORT(arr, left, j - 1);
		carUPSORT(arr, j + 1, right);
	}
}
void cusSORT(list* arr, int left, int right) {//고객 번호에 대한 퀵정렬 내림차순
	if (left < right)                         //고객 번호는 랜덤으로 입력받은 차량번호를 정리하고 나서 무작위로 섞이기 때문에 퀵정렬 사용
	{
		int key = left;
		int high = left + 1;
		int j = right;
		
		while (high <= j)
		{
			while (high <= right && arr[high].cus_num >= arr[key].cus_num)
				high++;
			while (j > left && arr[j].cus_num <= arr[key].cus_num)
				j--;
			
			if (high > j)
				SWAP(arr, j, key);
			
			else
				SWAP(arr, high, j);
		}
		cusSORT(arr, left, j - 1);
		cusSORT(arr, j + 1, right);
	}
}
void cusUPSORT(list* arr, int left, int right) {//고객 번호에 대한 퀵정렬 오름차순
	if (left < right)                         
	{
		int key = left;
		int high = left + 1;
		int j = right;
		
		while (high <= j)
		{
			while (high <= right && arr[high].cus_num < arr[key].cus_num)
				high++;
			while (j > left && arr[j].cus_num > arr[key].cus_num)
				j--;
			
			if (high > j)
				SWAP(arr, j, key);
			
			else
				SWAP(arr, high, j);
		}
		
		cusUPSORT(arr, left, j - 1);
		cusUPSORT(arr, j + 1, right);
	}
}
//==================퀵정렬 끝 ===========================

void list_print(list *arr,int a) {  // 리스트 값 출력
	printf("|\t고객 번호\t\t차량 번호       |\n");
	
	for (int i = 0; i < a; i++)
		printf("|  %d.\t    %d\t\t\t  %d\t\t|\n",i+1,arr[i].cus_num, arr[i].car_num);
	
}
//
int main(void)
{
	int minutes = 60;
	int total_wait = 0;
	int total_customers = 0;
	int service_time = 0;
	int service_customer;
	
	QueueType queue;
	init_queue(&queue);
	printf("asd\n");
	srand(time(NULL));
	for (int clock = 0; clock < minutes; clock++) {
		printf("현재시각=%d\n", clock);
		if ((rand() % 10) < 3) {
			element customer;
			customer.id = total_customers++;
			customer.aryival_time = clock;
			customer.service_time = rand() % 3 + 1;
			enqueue(&queue, customer, customer.service_time);
			printf("고객 %d이 %d분에 들어옵니다. 업무처리시간= %d분\n",
				customer.id, customer.aryival_time, customer.service_time);
		}
		if (service_time > 0) {
			printf("고객 %d 업무처리중입니다. \n", service_customer);
			service_time--;
		}
		else {
			if (!is_empty(&queue)) {
				element customer = dequeue(&queue);
				service_customer = customer.id;
				service_time = customer.service_time;
				printf("고객 %d이 %d분에 업무를 시작합니다. 대기시간은 %d분이었습니다.\n",
					customer.id, clock, clock - customer.aryival_time);
				total_wait += clock - customer.aryival_time;
			}
		}
	}
	//=================================== 정렬 메뉴 ===========================================
	printf("총 고객 수%d\n", total_customers);
	list* c = (list*)malloc(sizeof(list) * total_customers);
	int menu;
	int z;
	for (int r = 0; r < total_customers; r++) {		 //
		c[r].car_num = rand() % 9000 + 1000;		 // 차량 번호 1000에서 9999 무작위 수 list에 대입 
		c[r].cus_num = r;						     // 고객 번호 list에 대입
	}	
	while (1) {
		printf("|==================입출차목록===================|\n");
		printf("\n\n1.차량번호 내림차순\n2.차량번호 오름차순\n3.고객번호 내림차순\n4.고객번호 오름차순\nDefault.종료\n\n");
		rewind(stdin);
		scanf("%d", &menu);
		system("cls");								//정렬을 하기전 콘솔창 정리
		switch (menu) {
			case 1: 
				printf("|===============차량번호 내림차순===============|\n");
				carSORT(c, 0, total_customers - 1);
				list_print(c, total_customers);
				break;
			case 2:
				printf("|===============차량번호 오름차순===============|\n");
				carUPSORT(c, 0, total_customers - 1);
				list_print(c, total_customers);
				break;
			case 3:
				printf("|===============고객번호 내림차순===============|\n");
				cusSORT(c, 0, total_customers - 1);
				list_print(c, total_customers);
				break;
			case 4:
				printf("|===============고객번호 오름차순===============|\n");
				cusUPSORT(c, 0, total_customers - 1);
				list_print(c, total_customers);
				break;
			default: 
				printf("프로그램을 종료합니다");
				return;
		}
	}
	return 0;
}

