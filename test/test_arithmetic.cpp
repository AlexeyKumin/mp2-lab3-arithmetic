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

TEST(Arithmetic, StringCoversion)
{
	string a = " - ( -(5 * 1 - 1 / 2))";
	string b = "0-(0-(5*1-1/2))";

	Arithmetic t1("1+1");
	string c = t1.StringConversion(a);
	EXPECT_EQ(b, c);
}

TEST(Arithmetic, StringCoversion1)
{
	string a = "";
	string b = "";

	Arithmetic t1("1+1");
	string c = t1.StringConversion(a);
	EXPECT_EQ(b, c);
}

TEST(Arithmetic, DivideToTerms)
{
	Arithmetic t1(" - ( -(5 * 1 - 1 / 2))");
	t1.DivideToTerms();
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
	EXPECT_EQ(0, t1.GetValTerms(0));
	EXPECT_EQ(2, t1.GetValTerms(1));
	EXPECT_EQ(3, t1.GetValTerms(2));
	EXPECT_EQ(4, t1.GetValTerms(3));
}

TEST(Arithmetic, ConvertToPolish)
{
	Arithmetic t1("3+ 2");
	t1.DivideToTerms();
	t1.ConvertToPolish();
	EXPECT_EQ(3, t1.GetValPolishTerms(0));
	EXPECT_EQ(2, t1.GetValPolishTerms(1));
	EXPECT_EQ(1, t1.GetValPolishTerms(2));
}

TEST(Arithmetic, ConvertToPolish1)
{
	Arithmetic t1("-(-(5 * 1 - 1 / 2))");
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

TEST(Arithmetic, CanCalcDiv)
{
	Arithmetic t1("-1 + (-3*5)");
	t1.DivideToTerms();
	t1.ConvertToPolish();
	double x = t1.Calculate();
	EXPECT_EQ(-1 + (-3 * 5), x);
}

TEST(Arithmetic, CanCalcDiv1)
{
	Arithmetic t1("-(-(5*1-1/2))");
	t1.DivideToTerms();
	t1.ConvertToPolish();
	double x = t1.Calculate();
	EXPECT_EQ(-(-(5 * 1 - 0.5)), x);
}

TEST(Arithmetic, CanCalcDiv2)
{
	Arithmetic t1("3 + 2");
	t1.DivideToTerms();
	t1.ConvertToPolish();
	double x = t1.Calculate();
	EXPECT_EQ(5, x);
}

TEST(Arithmetic, inputVarCalcDiv3)
{
	Arithmetic t1("(a + (-a))");
	t1.DivideToTerms();
	t1.ReplacementVar();
	t1.ConvertToPolish();
	double x = t1.Calculate();
	EXPECT_EQ( 0, x);
}

TEST(Arithmetic, CanCalcDiv4)
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
	Arithmetic t1("(90)(35* 6 -+)+(2)");
	bool k;
	t1.DivideToTerms();
	k = t1.CheckOperators();
	EXPECT_EQ(false, k);
}

TEST(Arithmetic, CheckOperators1)
{
	Arithmetic t1("aa-+ ()a-");
	bool k;
	t1.DivideToTerms();
	k = t1.CheckOperators();
	EXPECT_EQ(false, k);
}

TEST(Arithmetic, CheckOperators2)
{
	Arithmetic t1("1/ ( -3)");
	bool k;
	t1.DivideToTerms();
	k = t1.CheckOperators();
	EXPECT_EQ(true, k);
}

TEST(Arithmetic, CheckOperators3)
{
	Arithmetic t1("(1.2.)+(.12)+(1.2.4) + ! +90");
	bool k;
	t1.DivideToTerms();
	k = t1.CheckOperators();
	EXPECT_EQ(false, k);
}

string false1[22] = { "" ," ", "+", "25+-5", "*25+5", "25+5*", "25 + 5/", "(", ")", "(25+5", "25+5)", "25(5+5)", "(25+5)5", "25.5.5", "25..5", "a.5+5", "(2+3)(5+6)", "(25+5+)", "(+25+5)", "25/5/5.0.", "+0", "25*()" };

string true1[5] = { "25+5+10-(3*2-1)", "-5", "(-5)", "-(-(-5*6.7/(6+2.5)))", "4.25*3.5" };

double dtrue1[5] = { 25 + 5 + 10 - (3 * 2 - 1), -5, (-5), -(-(-5 * 6.7 / (6 + 2.5))), 4.25 *3.5 };

TEST(Arithmetic, uncorrect_string)
{
	for (int i = 0; i < 22; i++)
	{
		Arithmetic A(false1[i]);
		A.DivideToTerms();
		EXPECT_EQ(false, A.CheckBrackets() && A.CheckLetters() && A.CheckOperators());
	}
}

TEST(Arithmetic, correct_string)
{
	for (int i = 0; i < 5; i++)
	{
		Arithmetic A(true1[i]);
		A.DivideToTerms();
		EXPECT_EQ(true, A.CheckBrackets() && A.CheckLetters() && A.CheckOperators());
	}
}

TEST(Arithmetic, correct_string_calc)
{
	for (int i = 0; i < 5; i++)
	{
		Arithmetic A(true1[i]);
		A.DivideToTerms();
		A.ConvertToPolish();
		EXPECT_EQ(dtrue1[i], A.Calculate());
	}
}


