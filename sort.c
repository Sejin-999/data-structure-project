# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <stdlib.h>
#include <windows.h> // �ܼ�â ������ ���� ���



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
		printf("���� �����Դϴ�.\n\n");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}


element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}


element peek(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
//=========================== ���⼭ ���� 208�ٱ���=====================================
typedef struct list { // ���� ��ȣ�� ����ȣ�� �޴� ����ü
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

void carSORT(list* arr, int left, int right) { //������ȣ�� ���� ������ ��������
	if (left < right)						   // ���� ��ȣ�� �������� �Է¹ޱ⶧���� ȿ���� ���� ������ ���
	{
		int key = left;
		int high = left + 1;
		int j = right;
		//�������� ��������
		while (high <= j)
		{
			while (high <= right && arr[high].car_num >= arr[key].car_num)
				high++;
			while (j > left && arr[j].car_num <= arr[key].car_num)
				j--;
			//�������� j�� key�� ��ü
			if (high > j)
				SWAP(arr, j, key);
			//�������������� high�� j ��ü
			else
				SWAP(arr, high, j);
		}
		//���� ���ĵ� ���� ��, �� ���� �Ȱ��� ��ȯ�ݺ�
		carSORT(arr, left, j - 1);
		carSORT(arr, j + 1, right);
	}
}
void carUPSORT(list* arr, int left, int right) { //������ȣ�� ���� ������ ��������
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
void cusSORT(list* arr, int left, int right) {//�� ��ȣ�� ���� ������ ��������
	if (left < right)                         //�� ��ȣ�� �������� �Է¹��� ������ȣ�� �����ϰ� ���� �������� ���̱� ������ ������ ���
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
void cusUPSORT(list* arr, int left, int right) {//�� ��ȣ�� ���� ������ ��������
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
//==================������ �� ===========================

void list_print(list *arr,int a) {  // ����Ʈ �� ���
	printf("|\t�� ��ȣ\t\t���� ��ȣ       |\n");
	
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
		printf("����ð�=%d\n", clock);
		if ((rand() % 10) < 3) {
			element customer;
			customer.id = total_customers++;
			customer.aryival_time = clock;
			customer.service_time = rand() % 3 + 1;
			enqueue(&queue, customer, customer.service_time);
			printf("�� %d�� %d�п� ���ɴϴ�. ����ó���ð�= %d��\n",
				customer.id, customer.aryival_time, customer.service_time);
		}
		if (service_time > 0) {
			printf("�� %d ����ó�����Դϴ�. \n", service_customer);
			service_time--;
		}
		else {
			if (!is_empty(&queue)) {
				element customer = dequeue(&queue);
				service_customer = customer.id;
				service_time = customer.service_time;
				printf("�� %d�� %d�п� ������ �����մϴ�. ���ð��� %d���̾����ϴ�.\n",
					customer.id, clock, clock - customer.aryival_time);
				total_wait += clock - customer.aryival_time;
			}
		}
	}
	//=================================== ���� �޴� ===========================================
	printf("�� �� ��%d\n", total_customers);
	list* c = (list*)malloc(sizeof(list) * total_customers);
	int menu;
	int z;
	for (int r = 0; r < total_customers; r++) {		 //
		c[r].car_num = rand() % 9000 + 1000;		 // ���� ��ȣ 1000���� 9999 ������ �� list�� ���� 
		c[r].cus_num = r;						     // �� ��ȣ list�� ����
	}	
	while (1) {
		printf("|==================���������===================|\n");
		printf("\n\n1.������ȣ ��������\n2.������ȣ ��������\n3.����ȣ ��������\n4.����ȣ ��������\nDefault.����\n\n");
		rewind(stdin);
		scanf("%d", &menu);
		system("cls");								//������ �ϱ��� �ܼ�â ����
		switch (menu) {
			case 1: 
				printf("|===============������ȣ ��������===============|\n");
				carSORT(c, 0, total_customers - 1);
				list_print(c, total_customers);
				break;
			case 2:
				printf("|===============������ȣ ��������===============|\n");
				carUPSORT(c, 0, total_customers - 1);
				list_print(c, total_customers);
				break;
			case 3:
				printf("|===============����ȣ ��������===============|\n");
				cusSORT(c, 0, total_customers - 1);
				list_print(c, total_customers);
				break;
			case 4:
				printf("|===============����ȣ ��������===============|\n");
				cusUPSORT(c, 0, total_customers - 1);
				list_print(c, total_customers);
				break;
			default: 
				printf("���α׷��� �����մϴ�");
				return;
		}
	}
	return 0;
}

