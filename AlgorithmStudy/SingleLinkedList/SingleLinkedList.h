#pragma once

typedef struct _Node
{
	int data;
	struct _Node* next;
} Node;

typedef struct _List
{
	Node* head;
	Node* tail;
	int count;
} List;

Node* create_node(int data);
void insert_node(List* list, int data, int index);
void delete_node(List* list, int index);

List* create_list();
void delete_list(List* list);
void delete_all_node(List* list);

Node* get_node(List* list, int index);
void print_node(Node* node);
void print_list(List* list);

int is_empty(List* list);
