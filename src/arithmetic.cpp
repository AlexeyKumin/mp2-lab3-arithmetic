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
			terms[nTerms] = Term(v, VALUE); // здесь определили тип снаружи конструктора
			nTerms++;
			i = j - 1;
		}
		else if (c != ' ')
			throw "DontDivideToTerms";
	}
}
  
void Arithmetic::Check()
{
	DivideToTerms();
	int k,p;
	for (int i = 0; i < nTerms; i++)
	{
		if (terms[i].type == OPEN_BRACKET) k++;
		if (terms[i].type == CLOSE_BRACKET) p++;
	}
	if (((terms[0].type == VALUE) || (terms[0].type == OPEN_BRACKET)) && ((terms[nTerms - 1].type == VALUE) || (terms[nTerms - 1].type == CLOSE_BRACKET))&&(p = k))
	{
		for (int i = 0; i < (nTerms - 1); i++)
			switch (terms[i].type)
		{
			case VALUE: 
				if ((terms[i + 1].type != CLOSE_BRACKET) || (terms[i + 1].type != OPERATOR))
					throw "StringError";
			case OPERATOR:
				if ((terms[i + 1].type != VALUE) || (terms[i + 1].type != CLOSE_BRACKET))
					throw "StringError";
			case OPEN_BRACKET:
				if ((terms[i + 1].type != VALUE) || (terms[i + 1].type != CLOSE_BRACKET))
					throw "StringError";
			case CLOSE_BRACKET:
				if ((terms[i + 1].type != CLOSE_BRACKET) || (terms[i + 1].type != OPERATOR))
					throw "StringError";
		}
	}	
	else 
		throw "StringError";
}

void Arithmetic::ConvertToPolish()
{

}