#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#define MAX_QUEUE_SIZE 100
//�� ����
typedef struct {
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
// �߰� //
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

void list_print(list* arr, int a) {  // ����Ʈ �� ���
    printf("\t\t|\t�� ��ȣ\t\t���� ��ȣ       |\n");

    for (int i = 0; i < a; i++)
        printf("\t\t|  %d.\t    %d\t\t\t  %d\t\t|\n", i + 1, arr[i].cus_num, arr[i].car_num);

}
// �� //
void print_queue() {
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
        printf("1�����̺� %d | 2�����̺� %d | 3�����̺� %d \n", oneCounter, twoCounter, thrCounter);
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

    printf("�� �� �� : %d��\n\n\n", total_customers);
    list* c = (list*)malloc(sizeof(list) * total_customers);
    int menu;
    int z;
    for (int r = 0; r < total_customers; r++) {		 //
        c[r].car_num = rand() % 9000 + 1000;		 // ���� ��ȣ 1000���� 9999 ������ �� list�� ���� 
        c[r].cus_num = r;						     // �� ��ȣ list�� ����
    }
    while (1) {
        printf("\t\t|==================���������===================|\n");
        printf("\n\n1.������ȣ ��������\n2.������ȣ ��������\n3.����ȣ ��������\n4.����ȣ ��������\nDefault.����\n\n");
        rewind(stdin);
        scanf("%d", &menu);
        system("cls");								//������ �ϱ��� �ܼ�â ����
        switch (menu) {
        case 1:
            printf("\t\t|===============������ȣ ��������===============|\n");
            carSORT(c, 0, total_customers - 1);
            list_print(c, total_customers);
            break;
        case 2:
            printf("\t\t|===============������ȣ ��������===============|\n");
            carUPSORT(c, 0, total_customers - 1);
            list_print(c, total_customers);
            break;
        case 3:
            printf("\t\t|===============����ȣ ��������===============|\n");
            cusSORT(c, 0, total_customers - 1);
            list_print(c, total_customers);
            break;
        case 4:
            printf("\t\t|===============����ȣ ��������===============|\n");
            cusUPSORT(c, 0, total_customers - 1);
            list_print(c, total_customers);
            break;
        default:
            printf("���α׷��� �����մϴ�");
            return;
        }
    }
}


int main(void)
{
    print_queue();
    return 0;
}