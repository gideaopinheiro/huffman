#include <stdio.h>
#include <stdlib.h>

typedef struct HEAP
{
	int *data;
	int size;
	int maxSize;
}HEAP;

typedef struct NODE
{
	int priority;
	struct NODE *next;
}NODE;

typedef struct PQ
{
	NODE *head;
}PQ;

NODE * create_node(void)
{
	NODE *newNode = malloc(sizeof(NODE));
	newNode->next = NULL;

	return newNode;
}

void swap_int(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

int parentIndex(int i) {return ((i + 1) >> 1) - 1;}

int leftChildIndex(int i) {return ((i + 1) << 1) - 1;}

int rightChildIndex(int i) {return (i + 1) << 1;}

HEAP * create_heap(int maxSize)
{
	HEAP *newHeap = malloc(sizeof(HEAP));
	newHeap->data = malloc(sizeof(int) * maxSize);
	newHeap->size = 0;
	newHeap->maxSize = maxSize;

	return newHeap;
}

PQ * create_pq(void)
{
	PQ *queue = malloc(sizeof(PQ));
	queue->head = NULL;
}

int enqueue_heap(HEAP *heap, int item)
{
	int i, p, comparisons;

	i = heap->size;
	heap->size++;
	
	heap->data[i] = item;
	p = parentIndex(i);
	comparisons = 1;

	while (i != 0 && heap->data[i] > heap->data[p])
	{
		swap_int(&heap->data[i], &heap->data[p]);

		i = p;
		p = parentIndex(i);

		comparisons++;
	}
	return comparisons;
}

int enqueue_pq(PQ *queue, int priority)
{
	NODE *newNode, *current;
	int comparisons;

	newNode = create_node();
	newNode->priority = priority;

	current = queue->head;
	comparisons = 1;

	if (current == NULL)
		queue->head = newNode;
	else if (current->priority < newNode->priority)
	{
		newNode->next = current;
		queue->head = newNode;
		comparisons++;
	}
	else
	{
		while (current->next != NULL && current->next->priority > newNode->priority)
		{
			current = current->next;
			comparisons++;
		}
	
		newNode->next = current->next;
		current->next = newNode;
	}
	return comparisons;
}

void max_heapify(HEAP *heap, int i)
{
	int l, r;

	l = leftChildIndex(i);
	r = rightChildIndex(i);

	if ((l < heap->size) && (heap->data[l] > heap->data[i]))
	{
		swap_int(&heap->data[i], &heap->data[l]);

		max_heapify(heap, l);
	}
	if ((r < heap->size) && (heap->data[r] > heap->data[i]))
	{
		swap_int(&heap->data[i], &heap->data[r]);

		max_heapify(heap, r);
	}
}

int dequeue_heap(HEAP *heap)
{
	int aux = heap->data[0];

	heap->size--;
	heap->data[0] = heap->data[heap->size];

	max_heapify(heap, 0);
	
	return aux;
}

int dequeue_pq(PQ *queue)
{
	NODE *aux = queue->head;

	int item = aux->priority;

	queue->head = aux->next;
	free(aux);

	return item;
}

int main(void)
{
	int n, x;

	printf("How many insertions do you want?\n-> ");
	scanf("%d", &n);

	HEAP *heap = create_heap(n);
	PQ *queue = create_pq();

	FILE *f = fopen("result.csv", "w");
	fprintf(f, "%s", "Index;Linked List;Heap\n");
	int comparisons;

	for (int i = 1;i <= n;i++)
	{
		x = rand();
		fprintf(f, "%d;", i);
		comparisons = enqueue_pq(queue, x);
		fprintf(f, "%d;", comparisons);
		comparisons = enqueue_heap(heap, x);
		fprintf(f, "%d\n", comparisons);
	}

	fclose(f);

	return 0;
}