/* simulation with 4 clerks.c */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 100
typedef struct {
	int id;
	int arrival_time;
	int service_time;
} element;

typedef struct {
	element  queue[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;
QueueType queue;

// 초기화 함수
void init(QueueType *q)
{
	q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}
// 포화 상태 검출 함수
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 삽입 함수
void enqueue(QueueType *q, element item)
{
	if (is_full(q)) {
		fprintf(stderr, "큐가 포화상태입니다.\n");
		return;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
// 삭제 함수
element dequeue(QueueType *q)
{
	if (is_empty(q)) {
		fprintf(stderr, "큐가 공백상태입니다.\n");
		exit(1);
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

// [0..1] 사이의 난수 생성 함수
double random()
{
	return rand() / (double)RAND_MAX;
}

// 시뮬레이션에 필요한 여러가지 상태 변수
int duration = 120; // 시물레이션 시간 
					// 하나의 시간 단위에 생성되는 주문 수
double arrival_prob_1 = 0.3; // 11:30~11:45
double arrival_prob_2 = 0.5; // 11:45~12:00
double arrival_prob_3 = 0.8; // 12:00~12:15
double arrival_prob_4 = 0.9; // 12:15~12:30
double arrival_prob_5 = 0.6; // 12:30~12:45
double arrival_prob_6 = 0.5; // 12:45~13:00
double arrival_prob_7 = 0.5; // 13:00~13:15
double arrival_prob_8 = 0.4; // 13:15~13:30

int max_serv_time = 10; // 하나의 고객에 대한 최대 서비스 시간
int clock;

// 시뮬레이션의 결과
int orders;         // 전체고객수
int served_orders;   // 서비스받은 고객수
int waited_time;   // 고객들이 기다린 시간

int service_orders_1 = 0;
int service_orders_2 = 0;
int service_orders_3 = 0;
int service_orders_4 = 0;
int service_orders_5 = 0;
int service_orders_6 = 0;
int service_orders_7 = 0;
int service_orders_8 = 0;

// 랜덤 숫자를 생성하여 주문이 새로 들어왔 판단
int is_customer_arrived(int arrived_time)
{
	if (arrived_time <= 15) {
		if (random() < arrival_prob_1) {
			service_orders_1++;
			return TRUE;
		}
		else return FALSE;
	}
	else if (arrived_time <= 30) {
		if (random() < arrival_prob_2) {
			service_orders_2++;
			return TRUE;
		}
		else return FALSE;
	}
	else if (arrived_time <= 45) {
		if (random() < arrival_prob_3) {
			service_orders_3++;
			return TRUE;
		}
		else return FALSE;
	}
	else if (arrived_time <= 60) {
		if (random() < arrival_prob_4) {
			service_orders_4++;
			return TRUE;
		}
		else return FALSE;
	}
	else if (arrived_time <= 75) {
		if (random() < arrival_prob_5) {
			service_orders_5++;
			return TRUE;
		}
		else return FALSE;
	}
	else if (arrived_time <= 90) {
		if (random() < arrival_prob_6) {
			service_orders_6++;
			return TRUE;
		}
		else return FALSE;
	}
	else if (arrived_time <= 105) {
		if (random() < arrival_prob_7) {
			service_orders_7++;
			return TRUE;
		}
		else return FALSE;
	}
	else {
		if (random() < arrival_prob_8) {
			service_orders_8++;
			return TRUE;
		}
		else return FALSE;
	}

}
// 새로 도착한 고객을 큐에 삽입
void insert_order(int arrival_time)
{
	element order;

	order.id = ++orders;
	order.arrival_time = arrival_time;
	order.service_time = (int)(max_serv_time * random()) + 1;
	enqueue(&queue, order);
	printf("주문서 %d이 %d분에 들어옵니다. 조리시간은 %d분입니다.\n",
		order.id, order.arrival_time, order.service_time);
}
// 큐에서 대기중인 주문서를 꺼내어 조리시간을 반환한다.
int remove_customer_1()
{
	element order;
	int service_time = 0;

	if (is_empty(&queue)) return 0;
	order = dequeue(&queue);
	service_time = order.service_time - 1;
	served_orders++;
	waited_time += clock - order.arrival_time;
	printf("쉐프 1이 %d 분에 주문서 %d의 메뉴를 만들기 시작합니다. 대기시간은 %d분이었습니다.\n",
		clock, served_orders, clock - order.arrival_time);
	return service_time;
}
int remove_customer_2()
{
	element order;
	int service_time = 0;

	if (is_empty(&queue)) return 0;
	order = dequeue(&queue);
	service_time = order.service_time - 1;
	served_orders++;
	waited_time += clock - order.arrival_time;
	printf("쉐프 2가 %d 분에 주문서 %d의 메뉴를 만들기 시작합니다. 대기시간은 %d분이었습니다.\n",
		clock, served_orders, clock - order.arrival_time);
	return service_time;
}
int remove_customer_3()
{
	element order;
	int service_time = 0;

	if (is_empty(&queue)) return 0;
	order = dequeue(&queue);
	service_time = order.service_time - 1;
	served_orders++;
	waited_time += clock - order.arrival_time;
	printf("쉐프 3이 %d 분에 주문서 %d의 메뉴를 만들기 시작합니다. 대기시간은 %d분이었습니다.\n",
		clock, served_orders, clock - order.arrival_time);
	return service_time;
}
int remove_customer_4()
{
	element order;
	int service_time = 0;

	if (is_empty(&queue)) return 0;
	order = dequeue(&queue);
	service_time = order.service_time - 1;
	served_orders++;
	waited_time += clock - order.arrival_time;
	printf("쉐프 4가 %d 분에 주문서 %d의 메뉴를 만들기 시작합니다. 대기시간은 %d분이었습니다.\n",
		clock, served_orders, clock - order.arrival_time);
	return service_time;
}
int remove_customer_5()
{
	element order;
	int service_time = 0;

	if (is_empty(&queue)) return 0;
	order = dequeue(&queue);
	service_time = order.service_time - 1;
	served_orders++;
	waited_time += clock - order.arrival_time;
	printf("쉐프 5가 %d 분에 주문서 %d의 메뉴를 만들기 시작합니다. 대기시간은 %d분이었습니다.\n",
		clock, served_orders, clock - order.arrival_time);
	return service_time;
}
// 통계치를 출력한다.
void print_stat()
{
	printf("손님에게 제공된 메뉴 수 = %d\n", served_orders);
	printf("전체 대기 시간 = %d분\n", waited_time);
	printf("한 주문서당 평군 대기 시간 = %f분\n", (double)waited_time / served_orders);
	printf("아직 대기중인 주문서 = %d\n", orders - served_orders);

	printf("11:30 ~ 11:45 주문 개수 = %d\n", service_orders_1);
	printf("11:45 ~ 12:00 주문 개수 = %d\n", service_orders_2);
	printf("12:00 ~ 12:15 주문 개수 = %d\n", service_orders_3);
	printf("12:15 ~ 12:30 주문 개수 = %d\n", service_orders_4);
	printf("12:30 ~ 12:45 주문 개수 = %d\n", service_orders_5);
	printf("12:45 ~ 13:00 주문 개수 = %d\n", service_orders_6);
	printf("13:00 ~ 13:15 주문 개수 = %d\n", service_orders_7);
	printf("13:15 ~ 13:30 주문 개수 = %d\n", service_orders_8);
}

int monte_simulation(int a, int b, int c, int d, int e) {
	int clerk[5] = { a,b,c,d,e };
	clock = 0;
	int num = 5;
	while (clock < duration) {
		clock++;
		printf("현재시각=%d분\n", clock);
		if (is_customer_arrived(clock)) {
			insert_order(clock);
		}
		if (clerk[0] == 0) {
			clerk[0] = remove_customer_1();
			for (int i = 1; i<num; i++) {
				if (clerk[i]>0) clerk[i]--;
			}
		}
		else if (clerk[1] == 0) {
			clerk[1] = remove_customer_2();
			if (clerk[0]>0) clerk[0]--;
			if (clerk[2]>0) clerk[2]--;
			if (clerk[3]>0) clerk[3]--;
			if (clerk[4]>0) clerk[4]--;
		}
		else if (clerk[2] == 0) {
			clerk[2] = remove_customer_3();
			if (clerk[0]>0) clerk[0]--;
			if (clerk[1]>0) clerk[1]--;
			if (clerk[3]>0) clerk[3]--;
			if (clerk[4]>0) clerk[4]--;
		}
		else if (clerk[3] == 0) {
			clerk[3] = remove_customer_4();
			if (clerk[0]>0) clerk[0]--;
			if (clerk[1]>0) clerk[1]--;
			if (clerk[2]>0) clerk[2]--;
			if (clerk[4]>0) clerk[4]--;
		}
		if (clerk[4] == 0) {
			clerk[4] = remove_customer_5();
			for (int i = 0; i<num-1; i++) {
				if (clerk[i]>0) clerk[i]--;
			}
		}
		else {
			for (int i = 0; i<num; i++) {
				clerk[i]--;
			}
		}
	}
}
// 시뮬레이션 프로그램
void main()
{
	int service_time1 = 0;
	int service_time2 = 0;
	int service_time3 = 0;
	int service_time4 = 0;
	int service_time5 = 0;

	monte_simulation(service_time1, service_time2, service_time3, service_time4, service_time5);
	print_stat();
}