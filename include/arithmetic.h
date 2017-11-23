// ���������� ������� � ������� ��� ���������� �������������� ���������

#pragma once

#include <string>

using namespace std;

enum TermTypes {OPEN_BRACKET, CLOSE_BRACKET, OPERATOR, VALUE, UNKNOWN} ;

const string allOperators = "+-*/()";

struct Term
{
	TermTypes type;
	string symbol; // ����� ��� ����
	double val;

	Term();
	Term(const string& str);
	Term(char c);
	Term(const string& str, TermTypes myType);
	Term(char c, TermTypes myType);
	// ����������� �����������
	// ���������� =
};

// ����������� � double ������� stod(): http://www.cplusplus.com/reference/string/stod/


// "(34-5)" ==>  ������ �� 5 Term 
// ���� ������ ���� symbol
// [0] type = OPEN_BRACKET, symbol = "(", val = 0.0;
// [1] type = VALUE, symbol = "34", val = 34.0;
// [2] type = OPERATOR, symbol = "-", val = 0.0;
// [3] type = VALUE, symbol = "5", val = 5.0;
// [2] type = CLOSE_BRACKET, symbol = ")", val = 0.0;

// ���� �� ������ ���� symbol
// [0] type = OPEN_BRACKET, val = 0.0;
// [1] type = VALUE, symbol = "34", val = 34.0;
// [2] type = OPERATOR, val = 1.0 (��� ������� '-' � ������ allOperators);
// [3] type = VALUE, val = 5.0;
// [2] type = CLOSE_BRACKET, val = 0.0;


// ��� ���� ������: polishTerms = {"34", "5", "-"}

//Term t = Term("(");
//Term t2 = Term("34");

class Arithmetic
{
	string inputStr;
	Term* terms;
	int nTerms; // ����� ������ �� ������� ������

	Term* polishTerms; // �������� ������ � ���� ������� ������
	int nPolishTerms; // ����� ������ � �������� ������


	void DivideToTerms(); // ������� �������� ������ � ��������� �� �� ������ terms, ����� �� ���������� �� ���-��.
	void ConvertToPolish(); // ���� - ������ terms, nTerms; ����� - ������ polishTerms, nPolishTerms
	double Calculate(); // ���������� �� �������� ������. ���� - ������ polishTerms, nPolishTerms, ����� - double �����

public:
	Arithmetic(const string& str)
	{
		terms = new Term[str.length()];
		inputStr = str;
		nTerms = 0;
	}
	int Check(); //���������� �������, � ������� ������
};


void Arithmetic::DivideToTerms()
{
	for (int i = 0; i < inputStr.length(); i++)
	{
		char c = inputStr[i];

		// ������ 1
		if (allOperators.find(c) != string::npos) // ���� ������ ����� � ������ allOperators
		{
      		terms[nTerms] = Term(c); // ����� ���������� ��� ������ ������������
			nTerms++;
		}
		else if (isdigit(c)) // ��� �����, ������� � ��� ����� �����.
		{
			string v;
			int j = i;
			while (j < inputStr.length() && (inputStr[j] == isdigit(c) || inputStr[j] == '.'))
			{
				j++;
			}
			v = inputStr.substr(i, j - i);
			terms[nTerms] = Term(v, VALUE); // ����� ���������� ��� ������ ������������
			nTerms++;

			i = j - 1;
		}
		// ������ 2
		//switch (c)
		//{
		//case '(': 
		//	{
		//		terms[nTerms] = Term('(', OPEN_BRACKET); // ����� ��� ���������� ������� ������������
		//		nTerms++;
		//	}
		//case ')': {}
		//case '+': {}
		//}
	}
}