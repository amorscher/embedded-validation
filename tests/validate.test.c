#include "lib/unity/src/unity.h"
#include <stdlib.h>

void setUp (void) {} /* Is run before every test, put unit init calls here. */
void tearDown (void) {} /* Is run after every test, put unit clean-up calls here. */

void first_test(void)
{
  TEST_ASSERT_NOT_NULL(NULL);
}

int main(void)
{
   UnityBegin("Duktape validation");

   RUN_TEST(first_test);

   UnityEnd();
   return 0;
}