// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

TEST(Term, Term1)
{
	Term t1('(');
	EXPECT_EQ(0, t1.val);
}

TEST(Term, Term2)
{
	Term t1("2");
	EXPECT_EQ(2, t1.val);
}

TEST(Term, Term3)
{
	Term t1('/');
	EXPECT_EQ(2, t1.PR());
}

TEST(Arithmetic, DivideToTerms)
{
	Arithmetic t1("2/5");
	t1.DivideToTerms();
	//ASSERT_NO_THROW(t1.DivideToTerms());
		EXPECT_EQ(2,t1.GetValTerms(0));
		EXPECT_EQ(4, t1.GetValTerms(1));
}