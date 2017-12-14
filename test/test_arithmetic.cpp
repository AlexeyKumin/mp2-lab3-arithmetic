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
		EXPECT_EQ(5, t1.GetValTerms(2));

}

TEST(Arithmetic, CanCalcDiv)
{
//	Arithmetic t1("2/5");
	Arithmetic t1("1+1");

	t1.DivideToTerms();
	t1.ConvertToPolish();
	double x = t1.Calculate();
//	EXPECT_EQ(2.0 / 5.0, x);
	EXPECT_EQ(2.0, x);

}