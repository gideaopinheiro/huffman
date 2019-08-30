#include <stdio.h>
#include <stdlib.h>
#include "../adt_huffman.h"
#include "../headers.h"

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_create_node(){
    unsigned char letter = 'A';
    ELEMENT * new_node = create_node(&letter);
   
    CU_ASSERT_EQUAL(letter, *(unsigned char*)new_node->item);
    CU_ASSERT_EQUAL('\0', new_node->binary[0]);
    CU_ASSERT_EQUAL(0, new_node->frequency);
    CU_ASSERT_EQUAL(NULL, new_node->left);
    CU_ASSERT_EQUAL(NULL, new_node->right);
    
    unsigned char letter2 = '/';
    ELEMENT * new_node2 = create_node(&letter2);
   
    CU_ASSERT_EQUAL(letter2, *(unsigned char*)new_node2->item);
    CU_ASSERT_EQUAL('\0', new_node2->binary[0]);
    CU_ASSERT_EQUAL(0, new_node2->frequency);
    CU_ASSERT_EQUAL(NULL, new_node2->left);
    CU_ASSERT_EQUAL(NULL, new_node2->right);

}

void test_create_heap(){
    HEAP * new_heap = create_heap(256);

    CU_ASSERT_EQUAL(256, new_heap->MAX_SIZE);
    CU_ASSERT_EQUAL(0, new_heap->size);
    
}

void RUN_TEST_CASES(void){
    CU_initialize_registry();
    CU_pSuite suite = NULL;
    
    suite = CU_add_suite("HUFFMAN TESTING", 0, 0);

    CU_add_test(suite, "TESTING_CREATE_NODE", test_create_node);
    CU_add_test(suite, "TESTING_CREATE_HEAP", test_create_heap);
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return;
}