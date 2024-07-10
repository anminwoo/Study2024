#pragma warning disable:4996

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
	int data;
	struct _Node* prev;
	struct _Node* next;
} Node;

typedef struct _List
{
	Node* head;
	Node* tail;
	int count;
} List;

Node* create_node(int data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->prev = NULL;
	node->next = NULL;

	return node;
}

List* create_list()
{
	List* list = (List*)malloc(sizeof(List));
	list->head = create_node(0);
	list->tail = create_node(0);
	list->count = 0;
	list->head->next = list->tail;
	list->tail->prev = list->head;

	return list;
}

int is_empty(List* list)
{
	return list->count == 0;
}

Node* get_node(List* list, int index)
{
	if (index == -1)
	{
		return list->head;
	}

	if (is_empty(list) || list->count <= index)
	{
		return NULL;
	}

	Node* node = list->head->next;
	if (index < list->count)
	{
		for (int i = 0; i < index; ++i)
		{
			node = node->next;
		}
	}

	return node;
}

void insert_node(List* list, int data, int index)
{
	Node* node = create_node(data);
	Node* prev_node;

	if (list->count <= index)
	{
		prev_node = list->tail->prev;
	}
	else
	{
		prev_node = get_node(list, index - 1);
	}

	node->prev = prev_node;
	node->next = prev_node->next;
	prev_node->next = node;
	node->next->prev = node;

	++list->count;
}

void delete_node(List* list, int index)
{
	if (list->count <= index)
	{
		return;
	}

	Node* del_node = get_node(list, index);
	Node* prev_node = del_node->prev;
	Node* next_node = del_node->next;
	prev_node->next = next_node;
	next_node->prev = prev_node;

	free(del_node);

	--list->count;
}

void delete_all_node(List* list)
{
	Node* del_node = list->head->next;
	Node* next_node;
	while (del_node != list->tail)
	{
		next_node = del_node->next;
		free(del_node);
		del_node = next_node;
	}

	list->head->next = list->tail;
	list->tail->prev = list->head;
}

void delete_list(List* list)
{
	delete_all_node(list);
	free(list->head);
	free(list->tail);
	free(list);
}

void print_node(Node* node)
{
	printf("%d ", node->data);
}

void print_list(List* list)
{
	if (is_empty(list))
	{
		return;
	}

	for (Node* node = list->head->next; node != list->tail; node = node->next)
	{
		print_node(node);
	}

	printf("\n");
}

void push_front(List* list, int data)
{
	insert_node(list, data, 0);
}

void push_back(List* list, int data)
{
	insert_node(list, data, list->count);
}

void pop_front(List* list)
{
	if (is_empty(list))
	{
		return;
	}

	delete_node(list, 0);
}

void pop_back(List* list)
{
	if (is_empty(list))
	{
		return;
	}

	delete_node(list, list->count - 1);
}

int get_front(List* list)
{
	if (is_empty(list))
	{
		return -1;
	}

	return list->head->next->data;
}

int get_back(List* list)
{
	if (is_empty(list))
	{
		return -1;
	}

	return list->tail->prev->data;
}

int main()
{
	List* list = create_list();
	pop_front(list);
	pop_back(list);

	push_back(list, 0);

	pop_front(list);

	push_back(list, 1);
	push_front(list, -1);

	pop_front(list);

	print_list(list);


	delete_list(list);
}