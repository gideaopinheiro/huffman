#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char BYTE;

//###################
// STRUCT NODE 
typedef struct TREE
{
	int frequency;
	void *item;
	struct TREE *next;
	struct TREE *right;
	struct TREE *left;
}TREE;

typedef struct ELEMENT
{
    int frequency;
    BYTE binary[20];
}ELEMENT;

typedef struct HASH
{
    ELEMENT *array[256];
}HASH;

// STRUCT PRIORITY QUEUE
typedef struct PQ
{
	TREE *head;
}PQ;
//##################

// THIS FUNCTION CREAT A NODE
TREE *creat_node(BYTE element, int frequency)
{
	BYTE *item_aux = (BYTE*) malloc(sizeof(BYTE));
	*item_aux = element;

	TREE *new_node = malloc(sizeof(TREE));
	new_node->frequency = frequency;

	new_node->next = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->item = item_aux;

	return new_node;
}

// THIS FUNCTION RETURN THE ITEM OF THE NODE
BYTE get_node_item(TREE *node){
	BYTE *item = (BYTE*) node->item;
	return *item;
}

PQ *creat_queue()
{
	PQ *new_queue = malloc(sizeof(PQ));
	new_queue->head = NULL;
	return new_queue;
}

//THIS FUNCTION COUNT A BYTE FRENQUENCY
void count_frequency(FILE *file, HASH *hash)
{
	BYTE element;
	//fseek(file, 0, SEEK_END);
	while(fscanf(file,"%c", &element) != EOF)
	{
		hash->array[element]->frequency++;
	}
}

//THIS FUNCTION DEQUEUE A NODE
TREE *dequeue(PQ *queue)
{
	TREE *aux = queue->head;
	queue->head = aux->next;
	return aux;
}

//THIS FUNCTION ENQUEUE A NODE
void enqueue(PQ *queue, TREE *node)
{
	if(queue->head == NULL){
		queue->head = node;
	}else{
		TREE *current = queue->head;
		if (current->frequency > node->frequency)
		{
			node->next = queue->head;
			queue->head = node;
			return;
		}
		while((current->next != NULL) && (current->next->frequency < node->frequency))
		{
			current = current->next;
		}
		node->next = current->next;
		current->next = node;
	}
}

//THIS FUNCTION ENQUEUE ALL ARRAY ELEMENTS
void enqueue_array(PQ *queue, HASH* hash)
{
	for(int i = 0; i < 256; i++)
	{
        if (hash->array[i]->frequency > 0)
        {
		    TREE *aux = creat_node(i, hash->array[i]->frequency);
		    enqueue(queue, aux);
        }
	}
}

// THIS FUNCTION CREAT A HUFFMAN TREE
TREE *creat_huffman_tree(PQ *queue)
{
	TREE *h = queue->head;
	while(h->next != NULL)
	{
		TREE *l = dequeue(queue);
		TREE *r = dequeue(queue);

		TREE *new_node = creat_node('*',l->frequency + r->frequency);

		new_node->left = l;
		new_node->right = r;

		enqueue(queue, new_node);
		h = queue->head;
	}
	return h;
}

HASH* create_hash()
{
    HASH* hash = (HASH*) malloc(sizeof(HASH));
    
    for (int i = 0; i < 256; i++)
    {
        hash->array[i] = (ELEMENT*) malloc(sizeof(ELEMENT));
        
        hash->array[i]->frequency = 0;
        hash->array[i]->binary[0] = '\0';
    }
    return hash;
}

// THIS FUNCTION BINARY READ
void binary_read(TREE *node, HASH* hash, char *string)
{
	if (node != NULL)
    {
        BYTE *aux = (BYTE*) node->item;
        if (*aux == '*')
        { 
            binary_read(node->left,  hash, strcat(string, "0"));

            int size = strlen(string);
            string[size - 1] = '\0';

            binary_read(node->right, hash, strcat(string, "1"));

            size = strlen(string);
            string[size - 1] = '\0';
        }
        else
        {
            printf("%c : %s\n",*aux, string);
            strcat(hash->array[*aux]->binary, string); 
        }  
    }
}

// THIS FUNCTION PRINT A TREE IN PRE ORDER
void get_tree(TREE *huff, char string[])
{
	if (huff != NULL)
	{
        BYTE aux[2];
        aux[0] = get_node_item(huff);
        aux[1] = '\0';

        if (huff->left == NULL)
        {
            if (aux[0] == '*')
                strcat(string, "\\*");

            else if (aux[0] == '\\')
                strcat(string, "\\\\");
            else
            strcat(string, aux);
        }
        else
            strcat(string, aux);

		get_tree(huff->left, string);
		get_tree(huff->right, string);
	}
}

int is_bit_i_set(BYTE c, int i)
{
    BYTE mask = 1 << i;
    return mask & c;
}
BYTE set_bit(BYTE c, int i)
{
    BYTE mask = 1 << i;
    return mask | c;
}

int getTrashLength(HASH* hash)
{
    long int trash = 0;
    for (int i = 0; i < 256; i++)
    {
        trash += strlen(hash->array[i]->binary) * hash->array[i]->frequency;
    }
    return (trash % 8);
}

void write_cabecario(FILE* output_file, HASH* hash, TREE* tree)
{
    int trash = getTrashLength(hash);
    printf("trash: %d\n", trash);
    BYTE binary[2] = {0};

    binary[0] = trash << 5;
    //todo pegar o bi da function
    
    char pre_order_tree[10000];
    pre_order_tree[0] = '\0';

    get_tree(tree, pre_order_tree);

    int size_tree = strlen(pre_order_tree);

    binary[0] |= size_tree >> 8;
    binary[1] = size_tree;

    fwrite(binary, 1, 2, output_file);

    fwrite(pre_order_tree, 1, size_tree, output_file);

    //todo get the bit da planta

    //fwrite(, )
}

void write_new_binary(FILE *input_file,FILE *output_file , HASH *hash)
{
	BYTE element;
    BYTE new_byte = 0;
	fseek(input_file, 0, SEEK_SET);
    int i = 0;

	while(fscanf(input_file,"%c", &element) != EOF)
	{
        int j = 0;
        while(hash->array[element]->binary[i] != '\0')
        {     
            if(hash->array[element]->binary[j] == '1');
                new_byte = set_bit(new_byte,7-j);
            j++;
        }
        printf("%d ", new_byte);
	}
    printf("\n");
}

void write_file(TREE* tree, HASH* hash,FILE *input_file)
{
    FILE* output_file;
    char output_file_name[1000];

    scanf("%s", output_file_name);
    strcat(output_file_name, ".huff");

    output_file = fopen(output_file_name, "wb");

    write_cabecario(output_file, hash, tree);

    write_new_binary(input_file,output_file,hash);
}

int main(void)
{
	FILE *input_file;
	PQ *queue = creat_queue();
	TREE *huffman_tree = NULL;

	while(1)
	{
		printf("ENTRE COM O NOME DO ARQUIVO PARA COMPACTAR\n==> ");
		char input_file_name[256];
		scanf("%s", input_file_name);

		input_file = fopen(input_file_name, "rb");
		fseek(input_file, 0, SEEK_SET);

		if (input_file == NULL)
		{
			printf("ALGO DEU ERRADO =(\n");
		}else break;
	}
    char string_binary[256];
    string_binary[0] = '\0';
	HASH* hash = create_hash();

	count_frequency(input_file, hash);

	enqueue_array(queue, hash);

	huffman_tree = creat_huffman_tree(queue);

    binary_read(huffman_tree, hash, string_binary);

	//print_pre_order(huffman_tree)

    write_file(huffman_tree, hash, input_file);
}