// объявление функций и классов для вычисления арифметических выражений

#pragma once

#include <string>
#include "stack.h"

using namespace std;

enum TermTypes { OPEN_BRACKET, CLOSE_BRACKET, OPERATOR, VALUE, VARIABLE, UNKNOWN };

const string allOperators = "(+-*/)";

struct Term
{
	TermTypes type; // Поле - тип лексемы
	double val; // Поле - значение лексемы

	Term(); // пустой конструктор, создает лексему типа UNKNOWN
	Term(const char c); // конструктор, принимает символ, определяет тип и значение этого сивола
	Term(const string& str); // конструктор, принимает строку, создает лексему число
	Term(const Term &t); // конструктор копирования
	Term& operator=(const Term &t);// перегрузка =
	~Term() { }; // деструктор
	int PR(); // выводит приоритет лексемы
	void inputVar(istream& in); // функция, позволяющая вводить значение лексемы VARIABLE
	double GetVal() { return val; } // возвращает поле val
};

class Arithmetic
{
	string inputStr; // поле - преобразованная строка

	Term* terms; // поле - указатель на массив лексем
	int nTerms; // число лексем во входной строке

	Term* polishTerms; // польская запись в виде массива лексем
	int nPolishTerms; // число термов в польской записи

public:
	string StringConversion(const string& str); // принимает строку, преобразует ее удаляя пробелы и ставя 0 перед унарным минусом

	Arithmetic(const string& str); // конструктор, принимает строку, преоразует ее, заполняет поля, создает массивы
	~Arithmetic() { delete[] terms; delete[] polishTerms; } // деструктор

	void DivideToTerms(); // обрабатывает поле inputStr, заполняет массив Terms лексемами
	void ReplacementVar(istream& in); // преобразует лесемы типа VARIABLE из массива Terms в тип VALUE и задает их значения
	void ConvertToPolish(); // обрабатывает массив Terms, заполняя массив polishTerms лексемами т.е. создает обратную польскую запись
	double Calculate(); // обрабатывает массив polishTerms, вычисляя изначальное арифметическое выражение, выводит его результат

	int CheckPoints(const string& str); // проверяет кол-во и правильность их расположения, чтобы правильно переводить строку в действительное число 
	int CheckBrackets(); // проверяет в массиве Terms соответствие скобок и их кол-во, выводит на экран ошибки
	int CheckLetters(); // проверка на неопределенные символы в строке, обрабатывает массив Terms, выводит на экран ошибки
	int CheckOperators(); // проверка на корректное расположение символов в строке, обрабатывает массив Terms, выводит на экран ошибки

	double GetValTerms(const int i) { return terms[i].val; } // выводит значение i-той лексемы массива Terms
	double GetValPolishTerms(const int i) { return polishTerms[i].val; } //выводит значение i-той лексемы массива polishTerms
};


