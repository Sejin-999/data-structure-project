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
//����
void circle_enqueue(DequeType* q, CosTime item) {
	if (circle_full(q)) {
		circle_error("�̹� �ڸ��� ������� �� á���ϴ�.\n");
	}q->rear = (q->rear + 1) % CIRCLE_MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
//����
CosTime circle_dequeue(DequeType* q) {
	if (circle_empty(q)) {
		circle_error("�ڸ��� ����� �ƹ��� �����ϴ�.\n");
	}q->front = (q->front + 1) % CIRCLE_MAX_QUEUE_SIZE;
	return q->data[q->front];
}
//���� 

void circle_error(char* M) {
	printf("%s\n",M);
	exit(1);
}

//�ʱ�ȭ

void circle_init(DequeType* q) {
	q->front = q->rear = 0;
}

//���� ����
int circle_empty(DequeType* q) {
	return (q->front == q->rear);
}

// ��ȭ ���� ����

int circle_full(DequeType* q) {
	return ((q->rear + 1) % CIRCLE_MAX_QUEUE_SIZE == q->front);
}

// ���

void circle_print(DequeType* q) {
	
}

int main() {
	int open_time = 240;
	int total_wait = 0;
	int total_customers = 0;
	int service_time = 0;
	int service_customer;
	int service_time=0, service_time_2 = 0, service_time_3 = 0, service_time_4 = 0, service_time_5 = 0;
	//int service_time_6 = 0, service_time_7 = 0, service_time_8 = 0, service_time_9 = 0, service_time_10 = 0;//�߰��� ����Ҳ��� ����
	bool table_1 = true, table_2 = true, table_3 = true, table_4 = true, table_5 = true;
	//bool table_6 = true, table_7 = true, table_8 = true, table_9 = true, table_10 = true; // �߰����� ����
	int service_1_time = 0, service_2_time = 0,service_3_time = 0, service_4_time = 0, service_5_time = 0; // ���̺� �Ļ� �ð� ���
	int service_1_cos, service_2_cos, service_3_cos, service_4_cos, service_5_cos;
	DequeType queue;
	circle_init(&queue);
	srand(time(NULL)); //rand()�� �ʱ�ȭ���ִ� ����

	for (int clock = 0; clock < open_time; clock++) {
		//int hour, min;
		//hour = clock / 60;
		//min = clock % 60;  
		printf("\n---------------------����ð� %d��-----------------------\n",clock);
		printf("\n-------------------------���̺���Ȳ--------------<�����:1 ��밡��:0>\n");
		printf("\n 1 : %d | 2 : %d | 3 : %d | 4 : %d | 5 : %d \n", table_1, table_2, table_3, table_4, table_5);
		//printf("\n 6 : %d | 7 : %d | 8 : %d | 9 : %d | 10 : %d \n", table_6, table_7, table_8, table_9, table_10); //�߰����� ����



		if ((rand() % 10) < 3) {
			CosTime cos;
			cos.id = total_customers++; //�� �� �� (1->2->3)
			cos.ariival_time = clock;
			cos.service_time = rand() % 3 + 10; //�Ļ�ð� ����
			circle_enqueue(&queue,cos);
			printf("����ȣ %d : ����Ļ�ð� : %d",cos.id,cos.service_time);
		}

		//table �ڸ� start
		if (service_1_time > 0) {
			printf("1�����̺��� %d�� ���� ������Դϴ�.", service_1_cos);
			service_1_time--;
		}if (service_1_time == 0) {
			printf("1�����̺��� �� ��밡���մϴ�.");
			table_1 = true;
		}
		else if (table_1) {
			if (!circle_empty(&queue)) {	
				CosTime cos = circle_dequeue(&queue);
				service_1_cos = cos.id;
				service_1_time = cos.service_time;

				printf("1�����̺��� %d ���� �Ļ縦 �����մϴ�. ����Ļ�ð��� %d���Դϴ�.", cos.id, clock-cos.ariival_time);
				table_1 = false;
				total_wait += clock - cos.ariival_time;
			}
		}


		//table �ڸ� end
	}
}

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_QUEUE_SIZE 100
//�� ����
typedef struct{
    int id;
    int in_time;
    int service_time;
} element;
// ���� ť
/*=================================================================================*/
typedef struct
{
    element data[MAX_QUEUE_SIZE]; //element Ÿ������ �迭����
    int front, rear;
} QueueType;
//���� ���
void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}
//front, rear �ʱ�ȭ
void init_queue(QueueType* q)
{
    q->front = q->rear = 0;
}
//����ִ��� Ȯ��
int is_empty(QueueType* q)
{
    return (q->front == q->rear);
}
//�������ִ� Ȯ��
int is_full(QueueType* q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
//���� ť
void enqueue(QueueType* q, element item)
{
    if (is_full(q))
    {
        error("��ȭ�����Դϴ�.\n");
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}
//���� ť
element dequeue(QueueType* q)
{
    if (is_empty(q))
    {
        error("��������Դϴ�.\n");
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
    int one_customer, //1�� ���̺� �ð�����
        two_customer,
        thr_customer;
    bool oneCounter = true;
    bool twoCounter = true;
    bool thrCounter = true;
    QueueType q;
    init_queue(&q);
    srand(time(NULL)); //rand()�� �ʱ�ȭ���ִ� ����
    for (int clock = 0; clock < minutes; clock++)
    {

        printf("\n--------------------����ð�=%d��-------------------- (0: �����, 1: ���Ұ�)\n", clock);
        printf("1�����̺� %d | 2�����̺� %d | 3�����̺� %d \n", oneCounter, twoCounter,thrCounter);
        if ((rand() % 10) < 3)
        {
            element customer;
            customer.id = total_customers++; //���� ���ڷ� ��Ī��. ex) �� 1, �� 2
            customer.in_time = clock;
            customer.service_time = rand() % 3 + 5;  //�����ð��� ��������  ����
            enqueue(&q, customer);
            printf("�մ� %d�� %d�п� ���ɴϴ�. ����Ļ�ð� = %d\n", customer.id, customer.in_time, customer.service_time);
        }

        if (one_time > 0) //1�����̺�����
        {
            printf("�մ� %d  1�����̺� �����\n", one_customer);
            one_time--;

            if (one_time == 0)
            {
                printf("(1�����̺� %d�� ���� ��밡���մϴ�.)\n", clock + 1);
                oneCounter = true;
            }
        }
        else if (oneCounter) //1�����̺� �ڸ��������
        {
            if (!is_empty(&q))
            {
                element customer = dequeue(&q);
                one_customer = customer.id;
                one_time = customer.service_time;

                printf("�մ� %d�� %d�п� 1�� ���̺��� �Ļ縦 �����մϴ�. ����Ļ�ð��� %d���Դϴ�.\n", customer.id, clock, clock - customer.in_time);
                oneCounter = false;
                total_wait += clock - customer.in_time;
            }
        }

        if (two_time > 0) //2�����̺�����
        {
            printf("�մ� %d  2�����̺� �����\n", two_customer);
            two_time--;

            if (two_time == 0)
            {
                printf("(2�����̺� %d�� ���� ��밡���մϴ�.)\n", clock + 1);
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
                printf("�մ� %d�� %d�п� 2�� ���̺��� �Ļ縦 �����մϴ�. ����Ļ�ð��� %d���Դϴ�.\n", customer.id, clock, clock - customer.in_time);
                twoCounter = false;
                total_wait += clock - customer.in_time;
            }
        }

        if (thr_time > 0) //3�����̺�����
        {
            printf("3�����̺� �����\n");
            thr_time--;

            if (thr_time == 0)
            {
                printf("(3�����̺� %d�� ���� ��밡���մϴ�.)\n", clock + 1);
                thrCounter = true;
            }
        }
        else if (thrCounter) //3�����̺� �ڸ��������
        {
            if (!is_empty(&q))
            {
                element customer = dequeue(&q);
                one_customer = customer.id;
                thr_time = customer.service_time;

                printf("�մ� %d�� %d�п� 3�� ���̺��� �Ļ縦 �����մϴ�. ����Ļ�ð��� %d���Դϴ�.\n", customer.id, clock, clock - customer.in_time);
                thrCounter = false;
                total_wait += clock - customer.in_time;
            }
        }


    }
    printf("��ü ��� �ð� = %d�� \n", total_wait);
	
}

int main(void)
{
    print_queue();
    return 0;
}