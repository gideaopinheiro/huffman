#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE
{
	void  *item;
  	char   binary[10];
	int    frequency;
	struct NODE *left;
	struct NODE *right;
}NODE;

typedef struct HEAP
{
	void *data;
	int   size;
	int   MAX_SIZE;
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

NODE * create_node(unsigned char *character)
{
	NODE *newNode    = malloc(sizeof(NODE));
	unsigned char *c = calloc(1, 2);

	memcpy(c, character, 2);
    newNode->binary[0] = '\0';
	newNode->item      = c;
	newNode->frequency = 0;
	newNode->left      = NULL;
	newNode->right     = NULL;

	return newNode;
}

HEAP * create_heap(int MAX_SIZE)
{
	HEAP *newHeap     = malloc(sizeof(HEAP));
	newHeap->size     = 0;
	newHeap->MAX_SIZE = MAX_SIZE;
	NODE **data       = malloc(sizeof(NODE**) * MAX_SIZE);

	for (int i = 0; i < MAX_SIZE; i++)
		data[i] = NULL;

	newHeap->data = data;

	return newHeap;
}

int parentIndex(int i)     {return ((i + 1) >> 1) - 1;}
int leftChildIndex(int i)  {return ((i + 1) << 1) - 1;}
int rightChildIndex(int i) {return (i + 1) << 1;}

void enqueue(HEAP *heap, NODE *data)
{
	if (heap->size < heap->MAX_SIZE)
	{
		int i, parent;

		i = heap->size;
		heap->size++;
		NODE **d = heap->data;
		d[i] = data;
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

void mount_heap(HEAP *heap, NODE **data, int size)
{
	for (int i = 0, j = 0;j < size;i++)
	{
		if (data[i] != NULL)
		{
			enqueue(heap, data[i]);
			j++;
		}
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
	unsigned char c = '*';

	while(heap->size > 1)
	{
		n1 = dequeue(heap);
		n2 = dequeue(heap);

		newNode = create_node(&c);
		newNode->frequency = n1->frequency + n2->frequency;
		newNode->left = n1;
		newNode->right = n2;

		enqueue(heap, newNode);
	}
	return dequeue(heap);
}

void print_preorder(NODE *node)
{
	if (node != NULL) return;

	printf("%s\n", node->binary);

	print_preorder(node->left);
	print_preorder(node->right);
}

void loop(NODE *node, NODE** data, char *string)
{
	if (node != NULL)
    {
        unsigned char *aux = (unsigned char*) node->item;
        if (*aux == '*')
        {
            
            loop(node->left,  data, strcat(string, "0"));

            int size = strlen(string);
            string[size - 1] = '\0';

            loop(node->right, data, strcat(string, "1"));

            size = strlen(string);
            string[size - 1] = '\0';
        }
        else
        {
            printf("aqui : %s\n", string);
            if (*aux == '\\')
                strcat(data[aux[1]]->binary, string);
            else
                strcat(data[*aux]->binary , string); 
        }  
    }
}

int read_file(FILE *file, unsigned char *buffer, NODE **data)
{
	unsigned char character;
	int nChar = 0;

	for (int i = 0;fscanf(file, "%c", &character) != EOF;i++)
	{
		buffer[i] = character;

		if (data[character] == NULL)
		{
			if (character == '*' || character == '\\')
			{
				unsigned char c[2] = {'\\', character};
				data[character]    = create_node(c);
			}
			else
				data[character] = create_node(&character);
			nChar++;
		}
		data[character]->frequency++;
	}
	return nChar;
}

int compressFile(char* name_file)
{
    NODE         **data;
    long long int  sizeFile;
	unsigned char *buffer;
	int            maxHeapSize;

	FILE *file = fopen(name_file, "rb");

	fseek(file, 0, SEEK_END);
	sizeFile = ftell(file);
	rewind(file);

	buffer = malloc(sizeFile);
	data   = malloc(sizeof(NODE) * 256);

	for (int i = 0;i < 256;i++)
		data[1] = NULL;

	maxHeapSize = read_file(file, buffer, data);
	fclose(file);

    // heap
	HEAP *heap = create_heap(256);
	mount_heap(heap, data, maxHeapSize);

    // tree
	TREE *tree = malloc(sizeof(TREE));
	tree->root = create_tree(heap);

    //print_preorder(tree->root);
	// printf("\n");

    char aux_string[10];
    aux_string[0] = '\0';
    loop(tree->root, data, aux_string);
}

int main(int argc, char **argv)
{

	for (int i=0; i<argc; i++){
		if(strcmp("-c", argv[i])==0){
			compressFile(argv[i+1]);
			return 0;
		}
		if(strcmp("-d", argv[i])){
			/*TODO: decompressFile() FUNCTION
			decompressFile();
			*/
		}
	}

	return 0;
}