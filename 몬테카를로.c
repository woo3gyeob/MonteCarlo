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

// �ʱ�ȭ �Լ�
void init(QueueType *q)
{
	q->front = q->rear = 0;
}
// ���� ���� ���� �Լ�
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}
// ��ȭ ���� ���� �Լ�
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// ���� �Լ�
void enqueue(QueueType *q, element item)
{
	if (is_full(q)) {
		fprintf(stderr, "ť�� ��ȭ�����Դϴ�.\n");
		return;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
// ���� �Լ�
element dequeue(QueueType *q)
{
	if (is_empty(q)) {
		fprintf(stderr, "ť�� ��������Դϴ�.\n");
		exit(1);
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

// [0..1] ������ ���� ���� �Լ�
double random()
{
	return rand() / (double)RAND_MAX;
}

// �ùķ��̼ǿ� �ʿ��� �������� ���� ����
int duration = 120; // �ù����̼� �ð� 
					// �ϳ��� �ð� ������ �����Ǵ� �ֹ� ��
double arrival_prob_1 = 0.3; // 11:30~11:45
double arrival_prob_2 = 0.5; // 11:45~12:00
double arrival_prob_3 = 0.8; // 12:00~12:15
double arrival_prob_4 = 0.9; // 12:15~12:30
double arrival_prob_5 = 0.6; // 12:30~12:45
double arrival_prob_6 = 0.5; // 12:45~13:00
double arrival_prob_7 = 0.5; // 13:00~13:15
double arrival_prob_8 = 0.4; // 13:15~13:30

int max_serv_time = 10; // �ϳ��� ���� ���� �ִ� ���� �ð�
int clock;

// �ùķ��̼��� ���
int orders;         // ��ü����
int served_orders;   // ���񽺹��� ����
int waited_time;   // ������ ��ٸ� �ð�

int service_orders_1 = 0;
int service_orders_2 = 0;
int service_orders_3 = 0;
int service_orders_4 = 0;
int service_orders_5 = 0;
int service_orders_6 = 0;
int service_orders_7 = 0;
int service_orders_8 = 0;

// ���� ���ڸ� �����Ͽ� �ֹ��� ���� ���� �Ǵ�
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
// ���� ������ ���� ť�� ����
void insert_order(int arrival_time)
{
	element order;

	order.id = ++orders;
	order.arrival_time = arrival_time;
	order.service_time = (int)(max_serv_time * random()) + 1;
	enqueue(&queue, order);
	printf("�ֹ��� %d�� %d�п� ���ɴϴ�. �����ð��� %d���Դϴ�.\n",
		order.id, order.arrival_time, order.service_time);
}
// ť���� ������� �ֹ����� ������ �����ð��� ��ȯ�Ѵ�.
int remove_customer_1()
{
	element order;
	int service_time = 0;

	if (is_empty(&queue)) return 0;
	order = dequeue(&queue);
	service_time = order.service_time - 1;
	served_orders++;
	waited_time += clock - order.arrival_time;
	printf("���� 1�� %d �п� �ֹ��� %d�� �޴��� ����� �����մϴ�. ���ð��� %d���̾����ϴ�.\n",
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
	printf("���� 2�� %d �п� �ֹ��� %d�� �޴��� ����� �����մϴ�. ���ð��� %d���̾����ϴ�.\n",
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
	printf("���� 3�� %d �п� �ֹ��� %d�� �޴��� ����� �����մϴ�. ���ð��� %d���̾����ϴ�.\n",
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
	printf("���� 4�� %d �п� �ֹ��� %d�� �޴��� ����� �����մϴ�. ���ð��� %d���̾����ϴ�.\n",
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
	printf("���� 5�� %d �п� �ֹ��� %d�� �޴��� ����� �����մϴ�. ���ð��� %d���̾����ϴ�.\n",
		clock, served_orders, clock - order.arrival_time);
	return service_time;
}
// ���ġ�� ����Ѵ�.
void print_stat()
{
	printf("�մԿ��� ������ �޴� �� = %d\n", served_orders);
	printf("��ü ��� �ð� = %d��\n", waited_time);
	printf("�� �ֹ����� �� ��� �ð� = %f��\n", (double)waited_time / served_orders);
	printf("���� ������� �ֹ��� = %d\n", orders - served_orders);

	printf("11:30 ~ 11:45 �ֹ� ���� = %d\n", service_orders_1);
	printf("11:45 ~ 12:00 �ֹ� ���� = %d\n", service_orders_2);
	printf("12:00 ~ 12:15 �ֹ� ���� = %d\n", service_orders_3);
	printf("12:15 ~ 12:30 �ֹ� ���� = %d\n", service_orders_4);
	printf("12:30 ~ 12:45 �ֹ� ���� = %d\n", service_orders_5);
	printf("12:45 ~ 13:00 �ֹ� ���� = %d\n", service_orders_6);
	printf("13:00 ~ 13:15 �ֹ� ���� = %d\n", service_orders_7);
	printf("13:15 ~ 13:30 �ֹ� ���� = %d\n", service_orders_8);
}

int monte_simulation(int a, int b, int c, int d, int e) {
	int clerk[5] = { a,b,c,d,e };
	clock = 0;
	int num = 5;
	while (clock < duration) {
		clock++;
		printf("����ð�=%d��\n", clock);
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
// �ùķ��̼� ���α׷�
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