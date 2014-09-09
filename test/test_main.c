#include "unity.h"

// every test file requires this function
// setUp() is called by the generated runner before each test case function
void setUp(void)
{

}    
                       
// every test file requires this function
// tearDown() is called by the generated runner before each test case function
void tearDown(void)
{
}

void test_equal_zero(void)
{
    uint8_t k = 0;

    /* Verify test results */
    TEST_ASSERT_EQUAL(k, 0);
}

void test_equal_twenty(void)
{
    uint8_t k = 20;

    /* Verify test results */
    TEST_ASSERT_EQUAL(k, 20);
}
