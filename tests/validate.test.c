#include "lib/unity/src/unity.h"
#include "duktape.h"
#include <stdlib.h>
#include "validate.h"



void setUp(void) {}    /* Is run before every test, put unit init calls here. */
void tearDown(void) {} /* Is run after every test, put unit clean-up calls here. */


void test_that_print_func_is_available(void)
{
    //GIVEN
    duk_context *ctx = create_heap_default();
  
    //WHEN
    init_duktape_context(ctx,NULL);
    duk_eval_string(ctx,"print('testing')");
    
    //THEN
    duk_require_undefined(ctx,0);
    TEST_ASSERT_EQUAL_INT(0,duk_get_int(ctx,0));
}

void test_that_value_stack_has_last_executed_result(void)
{
    //GIVEN
    duk_context *ctx = create_heap_default();
    //WHEN
    duk_eval_string(ctx,"2+3");
    //THEN
    TEST_ASSERT_EQUAL_INT(5,duk_get_int(ctx,0));
}

int main(void)
{
    UnityBegin("Duktape validation");

    RUN_TEST(test_that_value_stack_has_last_executed_result);
    RUN_TEST(test_that_print_func_is_available);

    UnityEnd();
    return 0;
}