#pragma warning disable:4996

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
	int data;
	struct _Node* next;
} Node;

typedef struct _Stack
{
	Node* top;
	int count;
} Stack;

Node* create_node(int data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;

	return node;
}

Stack* create_stack()
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->top = NULL;
	stack->count = 0;

	return stack;
}

int is_empty(Stack* s)
{
	return s->count == 0;
}

void push(Stack* s, int data)
{
	Node* node = create_node(data);
	if (is_empty(s))
	{
		s->top = node;
	}
	else
	{
		node->next = s->top;
		s->top = node;
	}

	++s->count;
}

void pop(Stack* s)
{
	if (is_empty(s))
	{
		return;
	}

	if (s->count == 1)
	{
		free(s->top);
		s->top = NULL;
	}
	else
	{
		Node* del = s->top;
		s->top = s->top->next;
		free(del);
	}

	--s->count;
}

int top(Stack* s)
{
	if (is_empty(s))
	{
		return -1;
	}
	return s->top->data;
}

void delete_stack(Stack* s)
{
	while (!is_empty(s))
	{
		pop(s);
	}

	free(s);
}

int main()
{
	Stack* s = create_stack();
	push(s, 0);
	printf("%d", top(s));
	push(s, 1);
	pop(s);
	pop(s);
	pop(s);
	printf("%d", top(s));

	delete_stack(s);
}