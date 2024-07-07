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

int main()
{
	List* list = create_list();

	insert_node(list, 1, 0);
	insert_node(list, 2, 1);
	insert_node(list, 3, 2);

	delete_node(list, 2);
	print_list(list);

	delete_all_node(list);

	insert_node(list, 4, 0);
	print_list(list);

	delete_list(list);
}