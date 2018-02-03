#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "dll.h"

#define TESTVAL1 69
#define TESTVAL2 14
#define TESTVAL3 987
#define TESTVAL4 1335
#define TESTPOSITION 10

void test_create(void **state)
{
     Node * testnode = create(TESTVAL1);

     assert_int_equal(TESTVAL1, testnode->data);
     assert_ptr_equal(NULL, testnode->next);
     assert_ptr_equal(NULL, testnode->prev);
     assert_ptr_equal(NULL, destroy(testnode));
}

/* TEST insert at beginning */
void test_insert_at_beginning(void **state)
{
     Node * testnode = create(TESTVAL1);

     testnode = insert_at_beginning(testnode, TESTVAL2);

     assert_int_equal(TESTVAL2, testnode->prev->data);
     assert_ptr_equal(NULL, testnode->next);
     assert_ptr_equal(NULL, destroy(testnode));
}

/* TEST insert at end */
void test_insert_at_end(void **state)
{
     Node * testnode = create(TESTVAL1);

     testnode = insert_at_end(testnode, TESTVAL2);

     assert_int_equal(TESTVAL2, testnode->data);
     assert_ptr_equal(NULL, testnode->next);
     assert_ptr_equal(NULL, destroy(testnode));
}

/* TEST insert at any position */
void test_insert_at_position(void **state)
{
     Node * testnode = create(TESTVAL1);

     testnode = insert_at_end(testnode,TESTVAL1);
     testnode = insert_at_end(testnode,TESTVAL1);
     testnode = insert_at_end(testnode,TESTVAL1);
     testnode = insert_at_end(testnode,TESTVAL1);

     //printAll(testnode);
     //5 nodes
     testnode = insert_at_position(testnode, 5, TESTVAL2);
     //6 nodes
     //printAll(testnode);

     assert_int_equal(TESTVAL2, testnode->prev->data);
     assert_ptr_equal(NULL, testnode->next);
     assert_ptr_equal(NULL, destroy(testnode));
}

//not for external use
void test_remove(void **state)
{
     Node * testnode = create(TESTVAL1);
     assert_int_equal(0, __remove(testnode));
}

void test_destroy(void **state)
{
     Node * testnode = create(TESTVAL1);

     testnode = insert_at_end(testnode,TESTVAL1);
     testnode = insert_at_end(testnode,TESTVAL1);
     testnode = insert_at_end(testnode,TESTVAL1);
     testnode = insert_at_end(testnode,TESTVAL1);

     assert_ptr_equal(NULL, destroy(testnode));
}

/*  TEST delete at beginning */
void test_delete_from_beginning(void **state)
{
     Node * testnode = create(TESTVAL1);

     testnode = insert_at_beginning(testnode, TESTVAL2);
     testnode = delete_from_beginning(testnode);

     assert_int_equal(TESTVAL1, testnode->data);
     assert_ptr_equal(NULL, testnode->next);
     assert_ptr_equal(NULL, testnode->prev);
     assert_ptr_equal(NULL, destroy(testnode));
}
/* TEST delete at end */
void test_delete_at_end(void **state)
{
     Node * testnode = create(TESTVAL1);

     testnode = insert_at_beginning(testnode, TESTVAL2);
     testnode = delete_at_end(testnode);

     assert_int_equal(TESTVAL2, testnode->data);
     assert_ptr_equal(NULL, testnode->next);
     assert_ptr_equal(NULL, testnode->prev);
     assert_ptr_equal(NULL, destroy(testnode));
}

/* TEST delete at any position */
void test_delete_at_position(void **state)
{
     Node * testnode = create(TESTVAL1);

     testnode = insert_at_end(testnode,TESTVAL1);
     testnode = insert_at_end(testnode,TESTVAL1);
     testnode = insert_at_end(testnode,TESTVAL3);
     testnode = insert_at_end(testnode,TESTVAL1);

     //printAll(testnode);
     //5 nodes
     testnode = insert_at_position(testnode, 5, TESTVAL2);
     //6 nodes
     //printAll(testnode);

     assert_int_equal(TESTVAL2, testnode->prev->data);

     testnode = delete_at_position(testnode, 5);

     assert_int_equal(TESTVAL3, testnode->prev->data);
     assert_ptr_equal(NULL, testnode->next);
     assert_ptr_equal(NULL, destroy(testnode));
}

/* TEST peek at a position in the stack's stored data without modification*/
void test_peek_value(void **state)
{
     Node * testnode = create(TESTVAL1);

     testnode = insert_at_beginning(testnode,TESTVAL1);
     testnode = insert_at_beginning(testnode,TESTVAL1);
     testnode = insert_at_beginning(testnode,TESTVAL3);
     testnode = insert_at_beginning(testnode,TESTVAL1);

     assert_int_equal(peek_value(testnode, 2), TESTVAL3);
     assert_ptr_equal(NULL, destroy(testnode));


}
int main(int argc, char **argv)
{
	const struct CMUnitTest tests[] = {
	cmocka_unit_test(test_create),
	cmocka_unit_test(test_insert_at_beginning),
	cmocka_unit_test(test_insert_at_end),
	cmocka_unit_test(test_insert_at_position),
	cmocka_unit_test(test_remove),
	cmocka_unit_test(test_destroy),
	cmocka_unit_test(test_delete_from_beginning),
	cmocka_unit_test(test_delete_at_end),
	cmocka_unit_test(test_delete_at_position),
	cmocka_unit_test(test_peek_value)};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
