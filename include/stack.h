// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

//#ifndef ___STACK_H___
//#define ___STACK_H___

#include <iostream>

using namespace std;

const int MAX_STACK_SIZE = 1000;

//Шаблон стека
template <class ValType>
class Stack
{
protected:
	ValType *pStack;  // поле - указатель на стек
	int Size;  // поле - максимальное количество элементов в стеке
	int top;  // поле - номер текущего элемента стека
public:
	Stack(int s = 10);  //коструктор, принимает размер создаваемого стека, по умолчанию размер стека 10
	Stack(const Stack &st); // конструктор копирования, принимает ссылку на стек, с которого создается копия
	~Stack();  // деструктор - освобождает память

	void push(const ValType &a);  //  вставка элемента типа ValType на вершину стека, принимает ссылку на элемент типа ValType
	ValType pop();  // извлечение элемента типа ValType с вершины стека, выводит элемент типа ValType
	ValType view() { return pStack[top - 1]; };  // просмотр элемента вершины стека, выводит элемент типа ValType
	bool isempty() { return top == 0; };  // проверка на пустоту стека, выводит элемент типа bool
	int getTop() { return top; }  // получение кол-ва элементов стека, выводит поле top
	int getSize() { return Size; } //доступ к полю размера стека, выводит поле Size 
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

// конструктор копирования
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

// вставка элемента(с перевыделением памяти)
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
 

 



