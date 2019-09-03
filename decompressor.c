#include "adt_huffman.h"
#include "headers.h"

int *getHeader(FILE *input_file)
{
	int *header = (int *)malloc(2*sizeof(int));
	unsigned char header_info, temp;

	int trash_size=0, tree_size=0;
	fscanf(input_file, "%c", &header_info);
	trash_size = header_info >> 5;

	temp = (header_info << 3);
	tree_size = temp >> 3;
	fscanf(input_file, "%c", &header_info);
	tree_size = (tree_size << 8) | header_info;

	header[0] = trash_size;
	header[1] = tree_size;
	
	return (header);
}

char *getTree()

void decompress_file(FILE *input_file)
{
	int *info = getHeader(input_file);
	int *char = getTree(input_file, );
	printf("%d: %d\n", info[0], info[1]);
	return;
}