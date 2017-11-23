// объ€вление и реализаци€ шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удалени€)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыдел€тьс€ пам€ть

//#ifndef ___STACK_H___
//#define ___STACK_H___

#include <iostream>

using namespace std;

const int MAX_STACK_SIZE = 1000;

//Ўаблон стека
template <class ValType>
class Stack
{
protected:
	ValType *pStack;  // указатель на стек
	int Size;  // максимальное количество элементов в стеке
	int top;  // номер текущего элемента стека
public:
	Stack(int s = 10);  //коструктор, по умолчанию размер стека 10
	Stack(const Stack &st); // конструктор копировани€
	~Stack();  // деструктор

	void push(const ValType &a);  //  вставка элемента
	ValType pop();  // извлечение элемента
	ValType view() { return pStack[top - 1]; };  // просмотр верхнего элемента
	bool isempty() { return top == 0; };  // проверка на пустоту
	int getTop() { return top; }  // получение кол-ва элементов
	int getSize() { return Size; } //доступ к размеру
	void clear() { top = 0; } // очистка стека
};/*-------------------------------------------------------------------------*/

// конструктор
template <class ValType>
Stack<ValType>::Stack(int s)
{
	if ((s >= 0) && (s <= MAX_STACK_SIZE))
	{
		Size = s;
		top = 0;
		pStack = new ValType[Size];
	}
	else
		throw "SizeError";
}/*-------------------------------------------------------------------------*/

// конструктор копировани€
template <class ValType>
Stack<ValType>::Stack(const Stack &st)
{
	Size = st.Size;
	top = st.top;
	pStack = new ValType[Size];
	for (int i = 0; i < top; i++)
		pStack[i] = st.pStack[i];
}/*-------------------------------------------------------------------------*/

// деструктор
template <class ValType>
Stack<ValType>::~Stack()
{
	delete[] pStack;
}/*-------------------------------------------------------------------------*/

// вставка элемента(с перевыделением пам€ти)
template <class ValType>
void Stack<ValType>::push(const ValType &a)
{
	if (top < Size)
	{
		top++;
		pStack[top - 1] = a;
	}
	else
	{
		if ((Size + (Size + 2) / 2) <= MAX_STACK_SIZE)
		{
			Size = Size + (Size + 2) / 2;
			ValType* Temp = new ValType[Size];
			for (int i = 0; i < top; i++)
				Temp[i] = pStack[i];
			delete[] pStack;
			pStack = Temp;
			top++;
			pStack[top - 1] = a;
		}
		else
			throw "SizeError";
	}
}/*-------------------------------------------------------------------------*/

 // извлечение элемента
template <class ValType>
ValType Stack<ValType>::pop()
{
	if (top != 0)
	{
		top--;
		return pStack[top];
	}
	else
		throw "SizeError";
}/*-------------------------------------------------------------------------*/
 

 



