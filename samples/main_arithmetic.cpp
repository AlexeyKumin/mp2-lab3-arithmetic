// реализация пользовательского приложения
#include "arithmetic.h"
#include <iostream>
using namespace std;

void main()
{
	string input;
	int p = 1;
	while (p)
	{
		cout << "Enter the expression" << endl;
		cin >> input;
		Arithmetic A(input);
		A.DivideToTerms();
		if (A.CheckBrackets() && A.CheckLetters() && A.CheckOperators())
				{
					double x;
					A.ReplacementVar();
					A.ConvertToPolish();
					x = A.Calculate();
					cout << " = " << x << endl;
					cout << endl;
				}
		cout << "Enter 1 to calculate again" << endl;
		cout << "Enter 0 to exit" << endl;
		cin >> p;
		cout << endl;	
	}
	cout << "END" << endl;
}
