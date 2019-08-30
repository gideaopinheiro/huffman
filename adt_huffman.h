#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char BYTE;

typedef struct TREE
{
	int frequency;
	void *item;
	struct TREE *right;
	struct TREE *left;
}TREE;

typedef struct HEAP
{
	void *data;
	int size;
}HEAP;

typedef struct ELEMENT
{
    int frequency;
    BYTE binary[20];
}ELEMENT;

typedef struct HASH
{
    ELEMENT *array[256];
}HASH;