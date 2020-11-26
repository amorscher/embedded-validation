#include "lib/unity/src/unity.h"
#include "duktape.h"
#include <stdlib.h>
#include "validate.h"

extern void duk_dump_context_stdout(duk_context *ctx);

void setUp(void) {}    /* Is run before every test, put unit init calls here. */
void tearDown(void) {} /* Is run after every test, put unit clean-up calls here. */

void test_that_print_func_is_available(void)
{
    //GIVEN
    duk_context *ctx = create_heap_default();

    //WHEN
    init_duktape_context(ctx, NULL);
    duk_eval_string(ctx, "print('testing')");

    //THEN
    duk_require_undefined(ctx, 0);
    TEST_ASSERT_EQUAL_INT(0, duk_get_int(ctx, 0));
}

void test_that_object_can_be_used_as_parameter_first(void)
{
    //GIVEN
    duk_context *ctx = create_heap_default();
    init_duktape_context(ctx, NULL);
    //read the json file
    read_json_file(ctx, "./testdata/config.json");
    
    //create the function
    duk_eval_string(ctx, "function test(objectParam){\
     print('Moduleid:'+objectParam.id);\
     return 'returned';\
     }");
     //pop undefined from the function
     duk_pop(ctx);
    //put the global object to the value stack
    duk_push_global_object(ctx);
    //put it to the first place
    duk_insert(ctx, 0);
    //get the funtion
    duk_get_prop_string(ctx, 0, "test");
    //put it to the second place
    duk_insert(ctx, 1);

    //WHEN
    //call the function
    duk_pcall(ctx, 1);

    //THEN
    TEST_ASSERT_EQUAL_STRING("returned", duk_get_string(ctx, -1));
}


void test_that_object_can_be_used_as_parameter_last(void)
{
    //GIVEN
    duk_context *ctx = create_heap_default();
    init_duktape_context(ctx, NULL);

    duk_eval_string(ctx, "function test(objectParam){\
     print('Moduleid:'+objectParam.id);\
     return 'returned';\
     }");
     //pop the undefined from the function
     duk_pop(ctx);

    //push the global object to the stack
    duk_push_global_object(ctx);
    //get the test function
    duk_get_prop_string(ctx, -1, "test");
   
    //WHEN

    //read the json configuration
    read_json_file(ctx, "./testdata/config.json");
    //call the function
    duk_pcall(ctx, 1);

    //THEN
    TEST_ASSERT_EQUAL_STRING("returned", duk_get_string(ctx, -1));
}

void test_that_json_file_can_be_read(void)
{
    //GIVEN
    duk_context *ctx = create_heap_default();
    init_duktape_context(ctx, NULL);

    //WHEN
    read_json_file(ctx, "./testdata/config.json");

    //THEN
    // we want to have an object on the stack
    duk_require_object(ctx, 0);
    //we extract a propery value from it and put it on the stack
    duk_get_prop_string(ctx, 0, "id");
    //we check the extracted property
    TEST_ASSERT_EQUAL_STRING("di124", duk_get_string(ctx, -1));
}

void test_that_js_file_can_be_read(void)
{
    //GIVEN
    duk_context *ctx = create_heap_default();
    init_duktape_context(ctx, NULL);

    //WHEN
    evaluate_js_file(ctx, "./testdata/example.js");

    //THEN
    TEST_ASSERT_EQUAL_STRING("result", duk_get_string(ctx, -1));
}


void test_handling_json_string(void)
{
    //GIVEN
    duk_context *ctx = create_heap_default();

    //WHEN
    char *json = "{\"prop1\": \"propValue\"}";
    duk_push_string(ctx, json);
    duk_json_decode(ctx, -1);

    //THEN
    // we want to have an object on the stack
    duk_require_object(ctx, 0);
    //we extract a propery value from it and put it on the stack
    duk_get_prop_string(ctx, 0, "prop1");
    //we check the extracted property
    TEST_ASSERT_EQUAL_STRING("propValue", duk_get_string(ctx, -1));
}

void test_that_value_stack_has_last_executed_result(void)
{
    //GIVEN
    duk_context *ctx = create_heap_default();

    //WHEN
    duk_eval_string(ctx, "2+3");

    //THEN
    TEST_ASSERT_EQUAL_INT(5, duk_get_int(ctx, 0));
}

int main(void)
{
    UnityBegin("Duktape validation");

    RUN_TEST(test_that_value_stack_has_last_executed_result);
    RUN_TEST(test_that_print_func_is_available);
    RUN_TEST(test_handling_json_string);
    RUN_TEST(test_that_json_file_can_be_read);
    RUN_TEST(test_that_object_can_be_used_as_parameter_first);
    RUN_TEST(test_that_object_can_be_used_as_parameter_last);
    RUN_TEST(test_that_js_file_can_be_read);

    UnityEnd();
    return 0;
}