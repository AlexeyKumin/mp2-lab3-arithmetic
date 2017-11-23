// тесты для стека

#include "stack.h"
#include <gtest.h>

class TestStacks : public ::testing::Test {
protected:
	Stack<int> st1;
public:
	TestStacks() : st1(10) {
		for (int i = 0; i < st1.getSize(); i++)
			st1.push(i);	
	}
	~TestStacks() {}
};


TEST(Stack, can_create_stack_with_positive_lenght)
{
	ASSERT_NO_THROW(Stack<int> st(5));
}

TEST(Stack, can_create_stack_with_lenght_more_max)
{
	ASSERT_ANY_THROW(Stack<int> st(6000));
}

TEST(Stack, can_create_stack_with_negative_lenght)
{
	ASSERT_ANY_THROW(Stack<int> st(-5));
}

TEST(Stack, can_not_delete_if_stack_is_empty)
{
	Stack<int> st;
	ASSERT_ANY_THROW(st.pop());
}

TEST_F(TestStacks, copied_stack_is_equal_to_source_one)
{
	Stack<int> st(st1);
	EXPECT_EQ(9, st.pop());
	//EXPECT_EQ(st1, st);
}

TEST_F(TestStacks, can_get_quantity)
{
	EXPECT_EQ(10, st1.getSize());
}

TEST_F(TestStacks, can_push_element_and_view_top)
{
	st1.push(0);
	EXPECT_EQ(11, st1.getTop());
	EXPECT_EQ(0, st1.view());
}

TEST_F(TestStacks, can_pop_element)
{
	int s = st1.pop();
	EXPECT_EQ(9, s);
	EXPECT_EQ(9, st1.getTop());
}

TEST_F(TestStacks, can_check_emptiness)
{
	EXPECT_EQ(false, st1.isempty());
}

TEST_F(TestStacks, can_clean_steck)
{
	st1.clear();
	EXPECT_EQ(true, st1.isempty());
}
