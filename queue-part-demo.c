#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#define MAX_QUEUE_SIZE 100
//고객 정보
typedef struct {
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
// 추가 //
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

void list_print(list* arr, int a) {  // 리스트 값 출력
    printf("\t\t|\t고객 번호\t\t차량 번호       |\n");

    for (int i = 0; i < a; i++)
        printf("\t\t|  %d.\t    %d\t\t\t  %d\t\t|\n", i + 1, arr[i].cus_num, arr[i].car_num);

}
// 끝 //
void print_queue() {
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
        printf("1번테이블 %d | 2번테이블 %d | 3번테이블 %d \n", oneCounter, twoCounter, thrCounter);
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

    printf("총 고객 수 : %d명\n\n\n", total_customers);
    list* c = (list*)malloc(sizeof(list) * total_customers);
    int menu;
    int z;
    for (int r = 0; r < total_customers; r++) {		 //
        c[r].car_num = rand() % 9000 + 1000;		 // 차량 번호 1000에서 9999 무작위 수 list에 대입 
        c[r].cus_num = r;						     // 고객 번호 list에 대입
    }
    while (1) {
        printf("\t\t|==================입출차목록===================|\n");
        printf("\n\n1.차량번호 내림차순\n2.차량번호 오름차순\n3.고객번호 내림차순\n4.고객번호 오름차순\nDefault.종료\n\n");
        rewind(stdin);
        scanf("%d", &menu);
        system("cls");								//정렬을 하기전 콘솔창 정리
        switch (menu) {
        case 1:
            printf("\t\t|===============차량번호 내림차순===============|\n");
            carSORT(c, 0, total_customers - 1);
            list_print(c, total_customers);
            break;
        case 2:
            printf("\t\t|===============차량번호 오름차순===============|\n");
            carUPSORT(c, 0, total_customers - 1);
            list_print(c, total_customers);
            break;
        case 3:
            printf("\t\t|===============고객번호 내림차순===============|\n");
            cusSORT(c, 0, total_customers - 1);
            list_print(c, total_customers);
            break;
        case 4:
            printf("\t\t|===============고객번호 오름차순===============|\n");
            cusUPSORT(c, 0, total_customers - 1);
            list_print(c, total_customers);
            break;
        default:
            printf("프로그램을 종료합니다");
            return;
        }
    }
}


int main(void)
{
    print_queue();
    return 0;
}