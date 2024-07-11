#pragma disable warning:4996

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
	int data;
} Node;

typedef struct _Heap
{
	Node arr[100];
	int size;
} Heap;

int is_empty(Heap* heap)
{
	return heap->size == 0;
}

void insert(Heap* heap, int data)
{
	int cnt = heap->size + 1;
	while ((cnt != 1) && (data > heap->arr[cnt / 2].data))
	{
		heap->arr[cnt] = heap->arr[cnt / 2];
		cnt /= 2;
	}

	heap->arr[cnt].data = data;
	++heap->size;
}

void delete(Heap* heap)
{
	if (is_empty(heap))
	{
		return;
	}

	int data = heap->arr[heap->size--].data;
	int pos = 1;
	int child = 2;

	while (child <= heap->size)
	{
		if ((child < heap->size) && (heap->arr[child].data < heap->arr[child + 1].data))
		{
			++child;
		}

		if (data >= heap->arr[child].data)
		{
			break;
		}

		heap->arr[pos] = heap->arr[child];
		pos = child;
		child *= 2;
	}

	heap->arr[pos].data = data;
}

int get_top(Heap* heap)
{
	if (is_empty(heap))
	{
		return -1;
	}

	return heap->arr[1].data;
}

int main()
{
	Heap heap;
	heap.size = 0;
	insert(&heap, 1);
	insert(&heap, 2);
	printf("%d", get_top(&heap));
	delete(&heap);
	printf("%d", get_top(&heap));
	insert(&heap, 1);
	insert(&heap, 3);
	printf("%d", get_top(&heap));
	delete(&heap);
	printf("%d", get_top(&heap));
	delete(&heap);
}