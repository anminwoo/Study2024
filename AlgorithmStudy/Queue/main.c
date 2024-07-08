#pragma warning disable:4996

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
	int data;
	struct _Node* prev;
	struct _Node* next;
} Node;

typedef struct _Queue
{
	Node* rear;
	int count;
} Queue;

Node* create_node(int data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->prev = NULL;
	node->next = NULL;

	return node;
}

Queue* create_queue()
{
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->rear = create_node(0);
	q->count = 0;

	return q;
}

int is_empty(Queue* q)
{
	return q->count == 0;
}

void push(Queue* q, int data)
{
	Node* node = create_node(data);
	if (is_empty(q))
	{
		node->next = q->rear;
		q->rear->prev = node;
		++q->count;
		return;
	}

	Node* prev = q->rear->prev;
	node->prev = prev;
	prev->next = node;
	node->next = q->rear;
	q->rear->prev = node;
	++q->count;
}

void pop(Queue* q)
{
	if (is_empty(q))
	{
		return;
	}

	Node* del = q->rear->prev;

	if (q->count == 1)
	{
		free(del);
		q->rear->prev = NULL;
		q->count = 0;
		return;
	}

	q->rear->prev = del->prev;
	del->prev->next = q->rear;
	free(del);
	--q->count;
}

int get_data(Queue* q)
{
	if (is_empty(q))
	{
		return 0;
	}

	return q->rear->prev->data;
}

void delete_queue(Queue* q)
{
	while (!is_empty(q))
	{
		pop(q);
	}

	free(q->rear);
	free(q);
}

int main()
{
	Queue* q = create_queue();
	push(q, 1);
	printf("%d", get_data(q));
	push(q, 2);
	printf("%d", get_data(q));
	pop(q);
	printf("%d", get_data(q));
	pop(q);
	printf("%d", get_data(q));
	delete_queue(q);
}