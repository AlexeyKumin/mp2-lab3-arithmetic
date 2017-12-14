// тесты для стека

#include "stack.h"
#include <gtest.h>

template <class T>
class TestStacks : public testing::Test {
protected:
	Stack<T> st1;
public:
	TestStacks() : st1(10) {
		for (int i = 0; i < st1.getSize(); i++)
			st1.push((T)i);	
	}
	virtual ~TestStacks() {}
};
typedef ::testing::Types<int, double, char> MyTypes;
TYPED_TEST_CASE(TestStacks, MyTypes);

TEST(Stack, can_create_stack_with_positive_lenght)
{
	ASSERT_NO_THROW(Stack<double> st(5));
}

TEST(Stack, can_create_stack_with_lenght_more_max)
{
	ASSERT_ANY_THROW(Stack<double> st(6000));
}

TEST(Stack, can_create_stack_with_negative_lenght)
{
	ASSERT_ANY_THROW(Stack<double> st(-5));
}

TEST(Stack, can_not_delete_if_stack_is_empty)
{
	Stack<double> st;
	ASSERT_ANY_THROW(st.pop());
}

TYPED_TEST(TestStacks, can_copy_stack)
{
	Stack<MyTypes> st1(5);
	ASSERT_NO_THROW(Stack<MyTypes> st2(st1));
}

TYPED_TEST(TestStacks, can_get_quantity)
{
	EXPECT_EQ(10, st1.getSize());
}

TYPED_TEST(TestStacks, can_push_element_and_view_top)
{
	st1.push(0);
	EXPECT_EQ(11, st1.getTop());
	EXPECT_EQ(0, st1.view());
}

TYPED_TEST(TestStacks, can_pop_element)
{
	int s = st1.pop();
	EXPECT_EQ(9, s);
	EXPECT_EQ(9, st1.getTop());
}

TYPED_TEST(TestStacks, can_check_emptiness)
{
	EXPECT_EQ(false, st1.isempty());
}

TYPED_TEST(TestStacks, can_clean_steck)
{
	st1.clear();
	EXPECT_EQ(true, st1.isempty());
}
