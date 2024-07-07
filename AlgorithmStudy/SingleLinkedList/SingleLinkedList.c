#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include "SingleLinkedList.h"

Node* create_node(int data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;

	return node;
}

void insert_node(List* list, int data, int index)
{
	Node* node = create_node(data);
	Node* prev_node = list->head;
	if (is_empty(list))
	{
		printf("list is empty. insert first.\n");
	}
	else
	{
		if (list->count < index)
		{
			printf("out of range! insert to last.\n");
			prev_node = get_node(list, list->count - 1);
		}
		else
		{
			prev_node = get_node(list, index - 1);
		}
	}

	node->next = prev_node->next;
	prev_node->next = node;
	++list->count;
}

void delete_node(List* list, int index)
{
	if (list->count <= index)
	{
		printf("out of range!\n");
		return;
	}

	Node* prev_node;
	if (index != 0)
	{
		prev_node = get_node(list, index - 1);
	}
	else
	{
		prev_node = list->head;
	}

	Node* del_node = prev_node->next;
	prev_node->next = del_node->next;

	free(del_node);
	--list->count;
}

List* create_list()
{
	List* list = (List*)malloc(sizeof(List));
	list->head = create_node(0);
	list->tail = create_node(0);
	list->count = 0;
	list->head->next = list->tail;
	return list;
}

void delete_list(List* list)
{
	if (list->count != 0)
	{
		delete_all_node(list);
	}

	free(list->head);
	free(list->tail);
	free(list);
}

void delete_all_node(List* list)
{
	if (is_empty(list))
	{
		return;
	}

	Node* del_node = list->head->next;
	Node* next_node;
	while (del_node != list->tail)
	{
		next_node = del_node->next;
		free(del_node);
		del_node = next_node;
	}

	list->count = 0;
}

Node* get_node(List* list, int index)
{
	if (is_empty(list) || list->count <= index)
	{
		printf("out of range!\n");
		return NULL;
	}

	Node* node;

	node = list->head->next;
	for (int i = 0; i < index; ++i)
	{
		node = node->next;
	}

	return node;
}

void print_node(Node* node)
{
	printf("%d ", node->data);
}

void print_list(List* list)
{
	if (is_empty(list))
	{
		printf("list is empty!\n");
		return;
	}

	for (Node* node = list->head->next; node != list->tail; node = node->next)
	{
		print_node(node);
	}
	printf("\n");
}

int is_empty(List* list)
{
	return list->count == 0;
}

int main()
{
	List* list = create_list();
	//print_list(list);

	insert_node(list, 1, 0);
	insert_node(list, 2, 1);
	insert_node(list, 3, 2);
	insert_node(list, 4, 9999);

	//print_list(list);

	delete_node(list, 0);
	delete_node(list, 0);
	delete_all_node(list);
	//print_list(list);

	delete_list(list);
}