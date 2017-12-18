// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"


string t[18] = { " ", "+", "25+-5", "*25+5", "25+5*", "25 + 5/", "(", ")", "(25+5", "25+5)", "25(5+5)", "(25+5)5", "25.5.5", "25..5", "a.5+5", "(2+3)(5+6)", "(25+5+)", "(+25+5)" };
string tt[3] = { "25+5+10-(3*2-1)", "-5", "(-5)" };
string ttt[5] = { "6+4", "13-3", "5*2", "50/5", "-5+15" };


class ParArithmetic : public ::testing::TestWithParam<string>
{
protected:
	string s;
public:
	ParArithmetic() { s = GetParam(); }
	~ParArithmetic() {}
};
class ParArithmetic2 : public ParArithmetic
{
protected:
	string s2;
public:
	ParArithmetic2() { s2 = GetParam(); }
	~ParArithmetic2() {}
};
class ParArithmetic3 : public ParArithmetic2
{
protected:
	string s3;
public:
	ParArithmetic3() { s3 = GetParam(); }
	~ParArithmetic3() {}
};

TEST_P(ParArithmetic, isIncorrect1)
{
	Arithmetic A(s);
	A.DivideToTerms();
	EXPECT_EQ(false, A.CheckBrackets() && A.CheckLetters() && A.CheckOperators());
}

INSTANTIATE_TEST_CASE_P(INSTANTIATE1, ParArithmetic, ::testing::ValuesIn(t));

//TEST_P(ParArithmetic2, isIncorrect2)
//{
//	Arithmetic A(s2);
//	A.DivideToTerms();
//	EXPECT_EQ(true, A.CheckBrackets() && A.CheckLetters() && A.CheckOperators());
//}
//INSTANTIATE_TEST_CASE_P(i2, ParArithmetic2, ::testing::ValuesIn(tt));


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

TEST(Arithmetic, StringCoversion)
{
	//string a = "3*5+(-2.0)/4.5*(- 5-a)";
	//string b = "3*5+(0-2.0)/4.5*(0- 5-a)";
	string a = " - ( -(5 * 1 - 1 / 2))";
	string b = "0- (0-(5 * 1 - 1 / 2))";

	Arithmetic t1("1+1");
	string c = t1.StringConversion(a);
	EXPECT_EQ(b, c);
}

TEST(Arithmetic, DivideToTerms)
{
	Arithmetic t1(" - ( -(5 * 1 - 1 / 2))");
	t1.DivideToTerms();
	//ASSERT_NO_THROW(t1.DivideToTerms());
	EXPECT_EQ(0, t1.GetValTerms(0));
	EXPECT_EQ(2, t1.GetValTerms(1));
	EXPECT_EQ(0, t1.GetValTerms(2));
	EXPECT_EQ(0, t1.GetValTerms(3));
	EXPECT_EQ(2, t1.GetValTerms(4));
	EXPECT_EQ(0, t1.GetValTerms(5));
	EXPECT_EQ(5, t1.GetValTerms(6));
	EXPECT_EQ(3, t1.GetValTerms(7));
	EXPECT_EQ(1, t1.GetValTerms(8));
	EXPECT_EQ(2, t1.GetValTerms(9));
	EXPECT_EQ(1, t1.GetValTerms(10));
	EXPECT_EQ(4, t1.GetValTerms(11));
	EXPECT_EQ(2, t1.GetValTerms(12));
}

TEST(Arithmetic, DivideToTerms1)
{
	Arithmetic t1("-3/5");
	t1.DivideToTerms();
	//ASSERT_NO_THROW(t1.DivideToTerms());
	EXPECT_EQ(0, t1.GetValTerms(0));
	EXPECT_EQ(2, t1.GetValTerms(1));
	EXPECT_EQ(3, t1.GetValTerms(2));
	EXPECT_EQ(4, t1.GetValTerms(3));
	//EXPECT_EQ(2, t1.GetValTerms(4));
	//EXPECT_EQ(3, t1.GetValTerms(5));

}


TEST(Arithmetic, ConvertToPolish)
{
	Arithmetic t1("-(-(5 * 1 - 1 / 2))");
	//Arithmetic t1("1+1");

	t1.DivideToTerms();
	t1.ConvertToPolish();
	EXPECT_EQ(0, t1.GetValPolishTerms(0));
	EXPECT_EQ(0, t1.GetValPolishTerms(1));
	EXPECT_EQ(5, t1.GetValPolishTerms(2));
	EXPECT_EQ(1, t1.GetValPolishTerms(3));
	EXPECT_EQ(3, t1.GetValPolishTerms(4));
	EXPECT_EQ(1, t1.GetValPolishTerms(5)); 
	EXPECT_EQ(2, t1.GetValPolishTerms(6));
	EXPECT_EQ(4, t1.GetValPolishTerms(7));
	EXPECT_EQ(2, t1.GetValPolishTerms(8));
	EXPECT_EQ(2, t1.GetValPolishTerms(9));
	EXPECT_EQ(2, t1.GetValPolishTerms(10));
}


TEST(Arithmetic, CanCalcDiv1)
{
	Arithmetic t1("-1 + (-3*5)");

	t1.DivideToTerms();
	t1.ConvertToPolish();
	double x = t1.Calculate();
	EXPECT_EQ(-1 + (-3 * 5), x);
}

TEST(Arithmetic, CanCalcDiv)
{
	Arithmetic t1("-(-(5*1-1/2))");

	t1.DivideToTerms();
	t1.ConvertToPolish();
	double x = t1.Calculate();
	EXPECT_EQ(-(-(5 * 1 - 0.5)), x);
}

TEST(Arithmetic, inputVar)
{
	Arithmetic t1("(a + (-a))");
	t1.DivideToTerms();
	t1.ReplacementVar();
	t1.ConvertToPolish();
	double x = t1.Calculate();
	EXPECT_EQ( 0, x);
}

TEST(Arithmetic, Result)
{
	Arithmetic t1("3*5+(-2.0)/4.5*(-5-a)");
	t1.DivideToTerms();
	t1.ReplacementVar();
	t1.ConvertToPolish();
	double x = t1.Calculate();
	EXPECT_EQ(3 * 5 + (-2.0) / 4.5*(-5 - 1), x);
}

TEST(Arithmetic, CheckBrackets)
{
	Arithmetic t1("(1 + 3)+(-1))");
	bool k; 
	t1.DivideToTerms();
	k = t1.CheckBrackets();
	EXPECT_EQ(false, k);
}

TEST(Arithmetic, CheckLatters)
{
	Arithmetic t1("(1.2.)+(.12)+(1.2.4) + ! +90");
	//Arithmetic t1("(90)+(-2)");
	bool k;
	t1.DivideToTerms();
	k = t1.CheckLetters();
	EXPECT_EQ(false, k);
}

TEST(Arithmetic, CheckOperators)
{
	//Arithmetic t1("(1.2.)+(.12)+(1.2.4) + ! +90");
	Arithmetic t1("(90)(35* 6 -+)+(2)");
	bool k;
	t1.DivideToTerms();
	k = t1.CheckOperators();
	EXPECT_EQ(false, k);
}

TEST(Arithmetic, CheckOperators1)
{
	//Arithmetic t1("(1.2.)+(.12)+(1.2.4) + ! +90");
	Arithmetic t1("aa-+ ()a-");
	bool k;
	t1.DivideToTerms();
	k = t1.CheckOperators();
	EXPECT_EQ(false, k);
}

TEST(Arithmetic, CheckOperators2)
{
	//Arithmetic t1("(1.2.)+(.12)+(1.2.4) + ! +90");
	Arithmetic t1("1/ ( -3)");
	bool k;
	t1.DivideToTerms();
	k = t1.CheckOperators();
	EXPECT_EQ(true, k);
}

