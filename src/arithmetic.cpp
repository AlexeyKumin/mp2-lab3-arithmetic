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
	switch (allOperators.find(c))
	{
	case 0:
	{
		type = OPEN_BRACKET;
		break;
	}
	case 5:
	{
		type = CLOSE_BRACKET;
		break;
	}
	}
	if ((val > 0) && (val < 5))
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

int Term::PR()
{
	int k;
	if ((val > 0) && (val < 2))
		k = 1;
	else
		k = 2;
	return k;
}

Term& Term::operator=(const Term &t)
{
	val = t.val;
	type = t.type;
	return *this;
}

Arithmetic::Arithmetic(const string& str)
{
	terms = new Term[str.length()];
	inputStr = str;
	nTerms = 0;
	polishTerms = terms;
	nPolishTerms = 0;
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
	polishTerms = new Term[nTerms];
	Term a;
	Stack<Term> st;
	int k = 0;
	for (int i = 0; i < nTerms; i++)
	{
		switch (terms[i].type)
		{
		case VALUE:
		{
			polishTerms[nPolishTerms] = terms[i];
			nPolishTerms++;
			break;
		}
		case OPEN_BRACKET:
		{
			st.push(terms[i]);
			k = st.getTop();
			break;
		}
		case OPERATOR:
		{
			if (st.isempty())
				st.push(terms[i]);
			else if (st.view().PR() < terms[i].PR())
				st.push(terms[i]);
			else if (st.view().PR() == terms[i].PR())
				{
					polishTerms[nPolishTerms] = terms[i];
					nPolishTerms++;
				}
				else
				{
					for (int j = k + 1; j < st.getTop(); j++)
					{
						polishTerms[nPolishTerms] = st.pop();
						nPolishTerms++;
					}
					a = st.pop();
					k = 0;
				}
			break;
		}
		case CLOSE_BRACKET:
		{
			for (int j = k + 1; j < st.getTop(); j++)
			{
				polishTerms[nPolishTerms] = st.pop();
				nPolishTerms++;
			}
			a = st.pop();
			k = 0;
			break;
		}
		}
	}
}

double Arithmetic::Calculate()
{
	Stack<double> st;
	while (st.getTop() != 1)
	{
		int i = 0;
		if (polishTerms[i].type == VALUE)
			st.push(polishTerms[i].val);
		else
		{
			double a = st.pop(), b = st.pop();
			switch (polishTerms[i].PR())
			{
			case 1:
				st.push(b + a);
				break;
			case 2:
				st.push(b - a);
				break;
			case 3:
				st.push(b * a);
				break;
			case 4:
				st.push(b / a);
				break;
			}
		}
		return st.pop();
	}
}

double Arithmetic::Result()
{
	DivideToTerms();
	Check();
	ConvertToPolish();
	return Calculate();
}