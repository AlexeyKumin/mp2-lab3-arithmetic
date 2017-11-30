// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"
Term::Term()
{
	type = UNKNOWN;
	val = 0;
}

Term::Term(const char c)
{   
	val = allOperators.find(c);
	switch (c)
	{
	case '(':
	{
		type = OPEN_BRACKET;
		val = 0;
		break;
	}
	case ')':
	{
		type = CLOSE_BRACKET;
		val = 0;
		break;
	}
	}
	if (val > 0)
		type = OPERATOR;
}

Term::Term(const string& str, TermTypes myType)
{
	val = stod(str);
	type = myType;
}

Term::Term(const Term &t)
{
	val = t.val;
	type = t.type;
}

Term& Term::operator=(const Term &t)
{
	val = t.val;
	type = t.type;
}

Arithmetic::Arithmetic(const string& str)
{
	terms = new Term[str.length()];
	inputStr = str;
	nTerms = 0;
}

void Arithmetic::DivideToTerms()
{
	for (int i = 0; i < inputStr.length(); i++)
	{
		char c = inputStr[i];
		if (allOperators.find(c) != string::npos) // если символ нашли в строке allOperators
		{
			terms[nTerms] = Term(c); // здесь определили тип внутри конструктора
			nTerms++;
		}
		else if (isdigit(c)) // это цифра, начиная с нее будет число.
		{
			string v;
			int j = i;
			while (j < inputStr.length() && (inputStr[j] == isdigit(c) || inputStr[j] == '.'))
				j++;
			v = inputStr.substr(i, j - i);
			terms[nTerms] = Term(v, VALUE); // здесь определили тип внутри конструктора
			nTerms++;
			i = j - 1;
		}
		else if (c != ' ')
			break;
	}
}

int Arithmetic::Check()
{
	DivideToTerms();
	return nTerms;
}