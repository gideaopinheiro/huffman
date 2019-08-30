#include <stdio.h>
#include <stdlib.h>

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "../headers.h"

void test_max(void){

    CU_ASSERT(max(0, 2) == 2);
    CU_ASSERT(max(5, 2) == 5);
    CU_ASSERT(max(-2, 6) == 6);
    CU_ASSERT(max(1, 1) == 1);
}

void test_factorial(void){
    CU_ASSERT(factorial(4) == 24);    
    CU_ASSERT(factorial(3) == 6);    
    CU_ASSERT(factorial(5) == 120);    
    CU_ASSERT(factorial(2) == 2);    
}

void function(void){
    CU_initialize_registry();
    CU_pSuite suite = NULL;
    suite = CU_add_suite("FILE_MAIN", 0, 0);
   
    CU_add_test(suite, "max_funciton", test_max);
    CU_add_test(suite, "factorial_function", test_factorial);
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return;
}