// объявление функций и классов для вычисления арифметических выражений

#pragma once

#include <string>
#include "stack.h"

using namespace std;

enum TermTypes {OPEN_BRACKET, CLOSE_BRACKET, OPERATOR, VALUE, VARIABLE, UNKNOWN} ;

const string allOperators = "(+-*/)";

struct Term
{
	TermTypes type;
	double val;

	Term();
	Term(const char c);
	Term(const string& str);
	Term(const Term &t);// конструктор копирования
	Term& operator=(const Term &t);// перегрузка =
	~Term() { };
	int PR(); // выводит приоритет оперции 
	void inputVar();
	double GetVal() { return val; }
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
// [1] type = VALUE, val = 34.0;
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

	void Check(); 
	//void DivideToTerms(); // обходим входнуюю строку и разбиваем ее на массив terms, здесь же определяем их кол-во.
	void ConvertToPolish(); // вход - массив terms, nTerms; выход - массив polishTerms, nPolishTerms
	double Calculate(); // вычисление по польской записи. Вход - массив polishTerms, nPolishTerms, выход - double ответ

public:
	Arithmetic(const string& str);
	~Arithmetic() { delete[] terms; delete[] polishTerms;}
	double Result();
	void DivideToTerms();
	double GetValTerms(const int i) { return terms[i].val; }
};


