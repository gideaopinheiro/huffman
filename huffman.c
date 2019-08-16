// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// typedef unsigned short USV;
// typedef unsigned char  UCV;

// typedef struct data
// {
//     long long int  frequency;
//     void          *value;
// } data_t;


// typedef struct tree
// {
//     int            frequency;
//     UCV            byte;
//     struct tree   *left;
//     struct tree   *right;
// } tree_t;


// tree_t* create_tree()
// {
//     tree_t* new_tree = (tree_t*) malloc(sizeof(tree_t));

//     new_tree->frequency = 0;
//     new_tree->left = new_tree->right = NULL;
//     return new_tree;
// }

// int read_file(char* input_file, data_t** array_freq)
// {
//     printf("%s\n", input_file);
//     FILE* file = fopen(input_file, "rb");
//     fseek(file, 0, SEEK_SET);
//     int count = 0;

//     if (file != NULL)
//     {
//         UCV character;
//         while (fscanf(file, "%c", &character) != EOF)
//         {
//             printf("%c %d\n", character, count++);
//             array_freq[character]->frequency++;
//             array_freq[character]->value++;
//         }
//         return 0;
//     }
//     return 1;
// }

// data_t* create()
// {
//     data_t* new_data = (data_t*) malloc(sizeof(data_t));

//     new_data->frequency = 0;
//     new_data->value     = 0;
//     return new_data;
// }

// void CompressFile(char *input_file, char *Output_file)
// {
//     tree_t* tree       = create_tree();
//     data_t** array_freq = (data_t**) malloc(sizeof(data_t) * 256);

//     int i;
//     for(i = 0; i < 256; i++)
//     {
//         array_freq[i] = create();
//     }

//     if (read_file(input_file, array_freq)) 
//         return;
// }


// int main(int argc, char *argv[])
// {
//     if (argc < 3)
//     {
//         printf("==================================================\n");
//         printf("= Use: [OPTIONS] [ARCHIVE] [ARCHIVE]               \n=\n");
//         printf("= Options:                                         \n");
//         printf("= \t-c\tcompress                                   \n");
//         printf("= \t-d\tdecompress                                 \n=");                                            
//         printf("\n= Example: ./huffman -c input.x Output.hx        \n");
//         printf("==================================================\n");
//         return 0;
//     }

//     if (strcmp("-c", argv[1]) == 0)
//     {
//         if (strstr(argv[3], ".hx"))
//         {
//             CompressFile(argv[2], argv[3]);
//         }
//         else
//         {
//             return 0;
//         }
//     }
    
//     return 0;
// }












































#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE
{
	unsigned char item;
	int frequency;
	struct NODE *left;
	struct NODE *right;
}NODE;

typedef struct HEAP
{
	void *data;
	int size;
	int MAX_SIZE;
}HEAP;

typedef struct TREE
{
	NODE *root;
}TREE;

void swap(void *a, void *b, size_t size)
{
	void *aux = malloc(size);

	memcpy(aux, a, size);
	memcpy(a, b, size);
	memcpy(b, aux, size);
}

int comp_char(const void *a, const void *b)
{
	return (*(unsigned char*)a - *(unsigned char*)b);
} 

NODE * create_node()
{
	NODE *newNode = (NODE*) malloc(sizeof(NODE));
	newNode->frequency = 0;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

HEAP * create_heap(int MAX_SIZE)
{
	HEAP *newHeap = (HEAP*) malloc(sizeof(HEAP));
	newHeap->size = 0;
	newHeap->MAX_SIZE = MAX_SIZE;
	NODE **data = (NODE**) malloc(sizeof(NODE*) * MAX_SIZE);

	for (int i = 0;i < MAX_SIZE;i++)
		data[i] = NULL;

	newHeap->data = data;

	return newHeap;
}

int parentIndex(int i) {return ((i + 1) >> 1) - 1;}
int leftChildIndex(int i) {return ((i + 1) << 1) - 1;}
int rightChildIndex(int i) {return (i + 1) << 1;}

void enqueue(HEAP *heap, NODE *data)
{
	if (heap->size < heap->MAX_SIZE)
	{
		int i, parent;

		i = heap->size;
		heap->size++;
		NODE **d = heap->data;
		d[i] = (NODE*) data;
		parent = parentIndex(i);

		while (i != 0 && d[i]->frequency <= d[parent]->frequency)
		{
			swap(d[i], d[parent], sizeof(NODE));

			i = parent;
			parent = parentIndex(i);
		}
		heap->data = d;
	}
}

void mount_heap(HEAP *heap, unsigned char *v, int size)
{
	NODE *newNode;
	int frequency;

	for (int i = 0;i < size;)
	{
		frequency = 0;
		for(int j = i;j < size;j++)
		{
			if (v[i] == v[j]) frequency++;
			else break;
		}
		printf("i:%d, v[i]:%c, fi:%d\n", i, v[i], frequency);
		newNode = create_node();
		newNode->item = v[i];
		newNode->frequency = frequency;

		enqueue(heap, newNode);

		i += frequency;
	}
}

void min_heapify(HEAP *heap, int i)
{
	int l, r;

	l = leftChildIndex(i);
	r = rightChildIndex(i);

	NODE **d = heap->data;

	if (l < heap->size && d[l]->frequency <= d[i]->frequency)
	{
		swap(d[i], d[l], sizeof(NODE));
		heap->data = d;
		min_heapify(heap, l);
	}
	if (r < heap->size && d[r]->frequency <= d[i]->frequency)
	{
		swap(d[i], d[r], sizeof(NODE));
		heap->data = d;
		min_heapify(heap, r);
	}
}

NODE * dequeue(HEAP *heap)
{
	NODE **d = heap->data;
	NODE *x = d[0];

	heap->size--;
	d[0] = d[heap->size];

	heap->data = d;
	min_heapify(heap, 0);
	return x;
}

NODE * create_tree(HEAP *heap)
{
	NODE *n1, *n2, *newNode;

	while(heap->size > 1)
	{
		n1 = dequeue(heap);
		n2 = dequeue(heap);

		newNode = create_node();
		newNode->item = '*';
		newNode->frequency = n1->frequency + n2->frequency;
		newNode->left = n1;
		newNode->right = n2;

		enqueue(heap, newNode);
	}

	return dequeue(heap);
}

void print_preorder(NODE *node)
{
	if (node == NULL) return;

	printf("%c", node->item);

	print_preorder(node->left);
	print_preorder(node->right);
}

unsigned char *read(unsigned char *v, char name_file[]){
    FILE *file = fopen(name_file, "rb");
    v = (unsigned char *)malloc(1000);
    fread(v, 1, 1000, file);
    //printf("%s\n", bin);
    return v;
}

int main(int argc, char **argv)
{

    unsigned char *buffer;
    buffer = read(buffer, argv[1]);
    printf("PRINTANDO O buffer:\n%s\n", buffer);

    int size = strlen(buffer);
	
	HEAP *heap = create_heap(size);
	unsigned char *v = (unsigned char*) malloc(size);
	memcpy(v, buffer, size);	
	qsort(v, size, 1, comp_char);

	mount_heap(heap, v, size);
	NODE **d = heap->data;
	for (int i = 0;i < heap->size;i++)
	{
		printf("%c\n", d[i]->item);
	}

	TREE *tree = (TREE*) malloc(sizeof(TREE));
	tree->root = create_tree(heap);
	print_preorder(tree->root);
	printf("\n");

	return 0;
}