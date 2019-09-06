#include <stdio.h>
#include <stdlib.h>

#include "adt_huffman.h"
#include "headers.h"

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_create_node(){
    BYTE *letter = 'A';
    int frequency = 7;
    TREE *new_node  = create_node(letter, frequency);
    CU_ASSERT_PTR_NOT_NULL(new_node);
}

int main(){  
    CU_initialize_registry();
    CU_pSuite suite = NULL;
    
    suite = CU_add_suite("HUFFMAN TESTING", 0, 0);

    CU_add_test(suite, "TESTING_CREATE_NODE", test_create_node);
    CU_add_test(suite, "TESTING_CREATE_HEAP", test_create_heap);
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    
    return 0;
}