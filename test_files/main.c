#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "../compressor.c"


void test_tree(){
    BYTE letter = 'A';
    short frequency = 7;
    TREE *new_node = create_node(letter, frequency);

    CU_ASSERT_PTR_NOT_NULL(new_node); /*Checking if new_node is NULL*/
    CU_ASSERT_EQUAL('A', get_node_item(new_node)); /*Checking if tree's element is equal to 'A' */
    CU_ASSERT_EQUAL(frequency, new_node->frequency); 
    CU_ASSERT_PTR_NULL(new_node->left);
    CU_ASSERT_PTR_NULL(new_node->right);
    
    BYTE letter1 = 'C';
    short frequency1 = 10;

    new_node->left = create_node(letter1, frequency1);
    /*Here we expect the pointer to the right child to still be null and the left child to point to the last node created.*/
    CU_ASSERT_PTR_NOT_NULL(new_node->left);
    CU_ASSERT_PTR_NULL(new_node->right);
    CU_ASSERT_EQUAL(frequency1, new_node->left->frequency);

    BYTE letter2 = 'D';
    short frequency2 = 9;

    new_node->right = create_node(letter2, frequency2);

    CU_ASSERT_EQUAL('D', get_node_item(new_node->right));
    CU_ASSERT_PTR_NOT_NULL(new_node->right);
    CU_ASSERT_EQUAL(frequency2, new_node->right->frequency);

}

void test_heap(){
    HEAP *new_heap = create_heap();
    
    CU_ASSERT_EQUAL(0, new_heap->size);
    CU_ASSERT_PTR_NOT_NULL(new_heap);

    BYTE letter = 'C';
    short frequency = 4;
    TREE *new_tree = create_node(letter, frequency);
    enqueue(new_heap, new_tree);
    
    CU_ASSERT_PTR_NOT_NULL(new_tree);
    CU_ASSERT_EQUAL('C', get_node_item(new_tree));
    CU_ASSERT_EQUAL(1, new_heap->size);

    dequeue(new_heap);

    CU_ASSERT_NOT_EQUAL(1, new_heap);

}

int main(){  
    if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

    CU_pSuite suite = NULL;
    
    suite = CU_add_suite("HUFFMAN TESTING", NULL, NULL); //a pointer to an initialization function, a pointer to a cleanup function
    if (NULL == suite) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    /*Adding a test case to the tree.*/
    if(NULL == CU_add_test(suite, "TESTING_CREATE_NODE", test_tree)){
        CU_cleanup_registry();
        return CU_get_error();
    }

    /*Adding a test case to the heap.*/
    if(NULL == CU_add_test(suite, "HEAP_TEST", test_heap)){
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE); /*to check the parametres*/
    CU_basic_run_tests();
    CU_cleanup_registry();
    
    return 0;
}