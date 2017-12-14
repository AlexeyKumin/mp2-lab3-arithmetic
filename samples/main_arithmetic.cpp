// реализация пользовательского приложения
#include "arithmetic.h"
#include <iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");

	string input;
	cout << "Введите выражение" << endl;
	cin >> input;
	Arithmetic A(input);
	A.DivideToTerms();
	//if ()
	//cout << A.Result() << endl;
}
