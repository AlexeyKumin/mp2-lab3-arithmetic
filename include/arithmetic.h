// объявление функций и классов для вычисления арифметических выражений

#pragma once

#include <string>

using namespace std;

enum TermTypes {OPEN_BRACKET, CLOSE_BRACKET, OPERATOR, VALUE, UNKNOWN} ;

const string allOperators = "+-*/()";

struct Term
{
	TermTypes type;
	string symbol; // можно без него
	double val;

	Term();
	Term(const string& str);
	Term(char c);
	Term(const string& str, TermTypes myType);
	Term(char c, TermTypes myType);
	// конструктор копирования
	// перегрузка =
};

// конвертация в double функция stod(): http://www.cplusplus.com/reference/string/stod/


// "(34-5)" ==>  массив из 5 Term 
// если храним поле symbol
// [0] type = OPEN_BRACKET, symbol = "(", val = 0.0;
// [1] type = VALUE, symbol = "34", val = 34.0;
// [2] type = OPERATOR, symbol = "-", val = 0.0;
// [3] type = VALUE, symbol = "5", val = 5.0;
// [2] type = CLOSE_BRACKET, symbol = ")", val = 0.0;

// если НЕ храним поле symbol
// [0] type = OPEN_BRACKET, val = 0.0;
// [1] type = VALUE, symbol = "34", val = 34.0;
// [2] type = OPERATOR, val = 1.0 (это позиция '-' в строке allOperators);
// [3] type = VALUE, val = 5.0;
// [2] type = CLOSE_BRACKET, val = 0.0;


// для этой строки: polishTerms = {"34", "5", "-"}

//Term t = Term("(");
//Term t2 = Term("34");

class Arithmetic
{
	string inputStr;
	Term* terms;
	int nTerms; // число термов во входной строке

	Term* polishTerms; // польская запись в виде массива термов
	int nPolishTerms; // число термов в польской записи


	void DivideToTerms(); // обходим входнуюю строку и разбиваем ее на массив terms, здесь же определяем их кол-во.
	void ConvertToPolish(); // вход - массив terms, nTerms; выход - массив polishTerms, nPolishTerms
	double Calculate(); // вычисление по польской записи. Вход - массив polishTerms, nPolishTerms, выход - double ответ

public:
	Arithmetic(const string& str)
	{
		terms = new Term[str.length()];
		inputStr = str;
		nTerms = 0;
	}
	int Check(); //возвращает позицию, в которой ошибка
};


void Arithmetic::DivideToTerms()
{
	for (int i = 0; i < inputStr.length(); i++)
	{
		char c = inputStr[i];

		// способ 1
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
			{
				j++;
			}
			v = inputStr.substr(i, j - i);
			terms[nTerms] = Term(v, VALUE); // здесь определили тип внутри конструктора
			nTerms++;

			i = j - 1;
		}
		// способ 2
		//switch (c)
		//{
		//case '(': 
		//	{
		//		terms[nTerms] = Term('(', OPEN_BRACKET); // здесь тип определили снаружи конструктора
		//		nTerms++;
		//	}
		//case ')': {}
		//case '+': {}
		//}
	}
}