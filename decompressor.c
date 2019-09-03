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

char *getTree(FILE *input_file, int len_tree){
	BYTE *tree = malloc(len_tree);
	fseek(input_file, 2, SEEK_SET);
	for(int i=0; i < len_tree; i++){
		fscanf(input_file, "%c", &tree[i]);
		printf("%c", tree[i]);
	}
	printf("\n");
	return (tree);	
}

TREE *buildTree(BYTE *tree, int *i){
	TREE *new_node;
	//new_node = malloc(sizeof(TREE));
	
	if(tree[*i] != '*'){
		if(tree[*i] == '\\') *i += 1; 
		new_node = create_node(tree[*i], 0);
		*i += 1;

		return new_node;
	}
	new_node = create_node(tree[*i], 0);
	
	*i += 1;
	new_node->left = buildTree(tree, i);
	new_node->right = buildTree(tree, i);
	
	return new_node;
}

void print_pre_order(TREE *tree){
	if(tree != NULL){
		printf("%c", *(char *)tree->item);
		print_pre_order(tree->left);
		print_pre_order(tree->right);
	}
	return;
}


void decompress_file(FILE *input_file)
{
	int *info_header = getHeader(input_file);
	BYTE *string_tree = getTree(input_file, info_header[1]);
	printf("\n\n\n\n");
	TREE *tree = buildTree(string_tree, 0);
	print_pre_order(tree);
	printf("\n");
	return;
}