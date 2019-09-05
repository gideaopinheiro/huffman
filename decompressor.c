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
	printf("%d %d\n",trash_size, tree_size );
	
	return (header);
}

char *getTree(FILE *input_file, int len_tree){
	BYTE *tree = malloc(len_tree);
	fseek(input_file, 2, SEEK_SET);

	for(int i=0; i < len_tree; i++){
		fscanf(input_file, "%c", &tree[i]);
	}
	return (tree);	
}

TREE *buildTree(BYTE *tree, int *i){
	TREE *new_node;

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

BYTE mount_char(BYTE binary[])
{
	BYTE item = 0;
	for (int i = 0; binary[i] != '\0'; i++)
	{
		if (binary[i] == '1')
		{
			item = set_bit(item, 7-i);
		}
	}
	return item;
}

int len_file(FILE *file){
	fseek(file, 0, SEEK_END);
	int len = ftell(file);
	rewind(file);
	return len;
}

void write_decompress_binary(TREE *tree, FILE *input_file, char output_file_name[], int trash_size)
{
	FILE *output_file = fopen(output_file_name, "wb");
	BYTE elemet, elemet2;

	TREE *root = tree;
	int i = -1;
	fscanf(input_file, "%c", &elemet2);
	while(True)
	{
		if(i < 0){
			i = 7;
			elemet = elemet2;
			if(fscanf(input_file, "%c", &elemet2) == EOF) break;
		}
		
		printf("%c == ", elemet);
		while(root->left != NULL)
		{
			if (is_bit_i_set(elemet,i))
			{
				root = root->right;
			}
			else
			{
			 	root = root->left;
			}
			i--;
			if (i < 0) break;
		}
		if (root->left == NULL)
		{
			printf("%c\n", get_node_item(root));
			fprintf(output_file, "%c", get_node_item(root));
			root = tree;
		}
	}
	printf("\n\n\n\n%d     %d",trash_size,i);
	while(i - trash_size  >= 0)
	{
		printf("aqui 2\n");
		while(root->left != NULL)
		{
			if (is_bit_i_set(elemet,i))
			{
				root = root->right;
			}
			else
			{
			 	root = root->left;
			}
			i--;
			if (i < 0) break;
		}
		//if (root->left == NULL)
		//{
			printf("%c\n", get_node_item(root));
			fprintf(output_file, "%c", get_node_item(root));
			root = tree;
		//}
	}

	fclose(output_file);
}


void decompress_file(FILE *input_file)
{
	int *info_header = getHeader(input_file);
	BYTE *string_tree = getTree(input_file, info_header[1]);

	int i =0;
	TREE *tree = buildTree(string_tree, &i);

	//FILE *output_file = fopen("descompressed.txt", "wb");

	print_pre_order(tree);
	printf("\n");

	char output_file_name[20];
	printf("please enter with the output file name\n");
	scanf(" %s", output_file_name);

	write_decompress_binary(tree, input_file, output_file_name, info_header[0]);
	printf("saida\n");

	return;
}