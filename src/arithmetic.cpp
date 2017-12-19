// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"
#include <iostream>
using namespace std;

Term::Term()
{
	type = UNKNOWN;
	val = 0;
}

Term::Term(const char c)
{
	if (isalpha(c))
	{
		type = VARIABLE;
		val = c;
	}
	else
	{
		val = allOperators.find(c);
		switch (allOperators.find(c))
		{
		case 0:
			type = OPEN_BRACKET;
			break;
		case 5:
			type = CLOSE_BRACKET;
			break;
		}
		if ((val >= 0) && (val <= 5))
		{
			if ((val > 0) && (val < 5))
				type = OPERATOR;
		}
		else
			type = UNKNOWN;
	}
}

Term::Term(const string& str)
{
	val = stod(str);
	type = VALUE;
}

Term::Term(const Term &t)
{
	val = t.val;
	type = t.type;
}

int Term::PR()
{
	int k;
	if (val == 0)
		k = 0;
	else
	{
		if ((val > 0) && (val <= 2))
			k = 1;
		else
			k = 2;
	}
	return k;
}

Term& Term::operator=(const Term &t)
{
	val = t.val;
	type = t.type;
	return *this;
}

void Term::inputVar()
{
	char c = (char)val;
	cout << "Input VARIABLE " << c << " : ";
	cin >> val;
}

string Arithmetic::StringConversion(const string& str)
{
	string temp = str;
	for (int i = 0; i < temp.length(); i++)
		if (temp[i] == ' ')
			temp.erase(i, 1);
	if (temp != "")
	{
		if (temp[0] == '-')
			temp = "0" + temp;
		for (int i = 0; i < temp.length() - 1; i++)
		{
			if ((temp[i] == '(') && (temp[i + 1] == '-'))
				temp.insert(i + 1, "0");
		}
	}
	return temp;
}

Arithmetic::Arithmetic(const string& str)
{
	string temp;
	temp = StringConversion(str);
	terms = new Term[temp.length()];
	polishTerms = new Term[temp.length()];
	inputStr = temp;
	nTerms = 0;
	nPolishTerms = 0;
}

void Arithmetic::DivideToTerms()
{
	int L = inputStr.length();
	for (int i = 0; i < L; i++)
	{
		char c = inputStr[i];
		if ((allOperators.find(c) != string::npos) || (isalpha(c))) // если символ нашли в строке allOperators
		{
			Term t(c);
			terms[nTerms] = t;
			nTerms++;
		}
		else
			if (isdigit(c)) // это цифра, начиная с нее будет число.
			{
				string v;
				int j = i;
				while ((j < L) && (isdigit(inputStr[j]) || (inputStr[j] == '.')))
					j++;
				v = inputStr.substr(i, j - i);
				if (CheckPoints(v))
				{
					Term t(v);
					terms[nTerms] = t;
					nTerms++;
				}
				else
				{
					terms[nTerms].type = UNKNOWN;
					nTerms++;
				}
				i = j - 1;
			}
			else
			{
				terms[nTerms].type = UNKNOWN;
				nTerms++;
			}
	}
}

void Arithmetic::ReplacementVar()
{
	for (int i = 0; i < nTerms; i++)
	{
		if (terms[i].type == VARIABLE)
		{
			char c = (char)terms[i].val;
			terms[i].inputVar();
			terms[i].type = VALUE;
			for (int j = i + 1; j < nTerms; j++)
			{
				if ((terms[j].type == VARIABLE) && (c == (char)terms[j].val))
					terms[j] = terms[i];
			}
		}
	}
}

void Arithmetic::ConvertToPolish()
{
	Stack<Term> st;
	Stack<int> k;
	k.push(0);
	for (int i = 0; i < nTerms; i++)
	{
		int l = st.getTop();
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
			k.push(st.getTop());
			break;
		}
		case OPERATOR:
		{
			if (st.isempty() || (st.view().PR() < terms[i].PR()))
				st.push(terms[i]);
			else
			{
				polishTerms[nPolishTerms] = st.pop();
				nPolishTerms++;
				st.push(terms[i]);
			}
			break;
		}
		case CLOSE_BRACKET:
		{
			for (int j = k.view(); j < l; j++)
			{
				polishTerms[nPolishTerms] = st.pop();
				nPolishTerms++;
			}
			st.pop();
			k.pop();
			break;
		}
		}
	}
	if (!st.isempty())
	{
		while (!st.isempty())
		{
			polishTerms[nPolishTerms] = st.pop();
			nPolishTerms++;
		}
	}
}

double Arithmetic::Calculate()
{
	Stack<double> st;
	for (int i = 0; i < nPolishTerms; i++)
	{
		if (polishTerms[i].type == VALUE)
			st.push(polishTerms[i].val);
		else
		{
			double a = st.pop(), b = st.pop();
			switch ((int)polishTerms[i].val)
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
	}
	return st.pop();
}

int Arithmetic::CheckPoints(const string& str)
{
	int l = str.length(), k = 0;
	bool flag = true;

	for (int i = 0; i < l; i++)
		if (str[i] == '.')
			k++;

	if ((str[0] == '.') || (str[l] == '.') || (k > 1))
		flag = false;
	return flag;
}

int Arithmetic::CheckBrackets()
{	
	bool flag = true;
	if (inputStr == "")
	{
		cout << " VOID " << endl;
		flag = false;
	}
	else
	{
		int Brackets = 0, k = 0;

		
		for (int i = 0; i < nTerms && Brackets >= 0; i++)
		{
			if (terms[i].type == OPEN_BRACKET)
			{
				Brackets++;
				k = i;
			}
			if (terms[i].type == CLOSE_BRACKET)
			{
				Brackets--;
				k = i;
			}
		}
		if (Brackets != 0)
		{
			cout << "Brackets ERROR: " << k + 1 << endl;
			flag = false;
		}
	}
	return flag;
}

int Arithmetic::CheckLetters()
{
	bool flag = true;
	for (int i = 0; i < nTerms; i++)
		if (terms[i].type == UNKNOWN)
		{
			cout << "Unknown symbol: " << i + 1 << endl;
			flag = false;
		}

	return flag;
}

int Arithmetic::CheckOperators()
{
	bool flag = true;
	if (!((terms[0].type == OPEN_BRACKET) || (terms[0].type == VALUE) || (terms[0].type == VARIABLE) || (terms[0].val == 2)))
	{
		cout << "Mistake OPERATOR IN :" << 1 << endl;
		flag = false;
	}

	for (int i = 0; i < nTerms - 1; i++)
		{
			switch (terms[i].type)
			{
			case OPEN_BRACKET:
				if (!((terms[i + 1].type == OPEN_BRACKET) || (terms[i + 1].type == VALUE) || (terms[i + 1].type == VARIABLE) || (terms[i + 1].val == 2)))
				{
					cout << "Mistake OPERATOR IN :" << i + 1 << endl;
					flag = false;
				}
				break;
			case VALUE:
				if (!((terms[i + 1].type == OPERATOR) || (terms[i + 1].type == CLOSE_BRACKET)))
				{
					cout << "Mistake OPERATOR IN :" << i + 1 << endl;
					flag = false;
				}
				break;
			case VARIABLE:
				if (!((terms[i + 1].type == OPERATOR) || (terms[i + 1].type == CLOSE_BRACKET)))
				{
					cout << "Mistake OPERATOR IN :" << i + 1 << endl;
					flag = false;
				}
				break;
			case OPERATOR:
				if (!((terms[i + 1].type == VALUE) || (terms[i + 1].type == VARIABLE) || (terms[i + 1].type == OPEN_BRACKET)))
				{
					cout << "Mistake OPERATOR IN :" << i + 1 << endl;
					flag = false;
				}
				break;
			case CLOSE_BRACKET:
				if (!((terms[i + 1].type == OPERATOR) || (terms[i + 1].type == VARIABLE) || (terms[i + 1].type == CLOSE_BRACKET)))
				{
					cout << "Mistake OPERATOR IN :" << i + 1 << endl;
					flag = false;
				}
				break;
			}
		}

	if (!((terms[nTerms - 1].type == CLOSE_BRACKET) || (terms[nTerms - 1].type == VALUE) || (terms[nTerms - 1].type == VARIABLE)))
	{
		cout << "Mistake OPERATOR IN :" << nTerms << endl;
		flag = false;
	}
	return flag;

}