#ifndef  HEADERS_H
#define  HEADERS_H

#define True 1
#define False 0

#include "adt_huffman.h"

BYTE mount_char(BYTE binary[]);

void write_decompress_binary(TREE *tree, FILE *input_file, char output_file_name[], int trash_size);

TREE *create_node(BYTE element, int frequency);

BYTE get_node_item(TREE *node);

HEAP * create_heap();

int parentIndex(int i);

int leftChildIndex(int i);

int rightChildIndex(int i);

void enqueue(HEAP *heap, TREE *node);

void min_heapify(HEAP *heap, int i);

TREE * dequeue(HEAP *heap);

void count_frequency(FILE *file, HASH *hash);

void mount_heap(HEAP *heap, HASH *hash);

TREE * create_huffman_tree(HEAP *heap);

HASH* create_hash();

void binary_read(TREE *node, HASH* hash, char *string);

void get_tree(TREE *huff, BYTE string[], int *len);

int get_tree_size(TREE *huff);

int is_bit_i_set(BYTE c, int i);

BYTE set_bit(BYTE c, int i);

int getTrashLength(HASH* hash);

void write_header(FILE* output_file, HASH* hash, TREE* tree);

void write_new_binary(FILE *input_file,FILE *output_file , HASH *hash);

void write_file(TREE* tree, HASH* hash, FILE *input_file, char input_file_name[]);

void compress_file(FILE *input_file, char *file_name);

int *getHeader(FILE *input_file);

void decompress_file(FILE *input_file);

#endif
