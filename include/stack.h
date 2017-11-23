// ���������� � ���������� ���������� �����
// ���� ������������ ��������: 
// - ������� ��������, 
// - ���������� ��������, 
// - �������� �������� �������� (��� ��������)
// - �������� �� �������, 
// - ��������� ���������� ��������� � �����
// - ������� �����
// ��� ������� � ������ ���� ������ �������������� ������

//#ifndef ___STACK_H___
//#define ___STACK_H___

#include <iostream>

using namespace std;

const int MAX_STACK_SIZE = 1000;

//������ �����
template <class ValType>
class Stack
{
protected:
	ValType *pStack;  // ��������� �� ����
	int Size;  // ������������ ���������� ��������� � �����
	int top;  // ����� �������� �������� �����
public:
	Stack(int s = 10);  //����������, �� ��������� ������ ����� 10
	Stack(const Stack &st); // ����������� �����������
	~Stack();  // ����������

	void push(const ValType &a);  //  ������� ��������
	ValType pop();  // ���������� ��������
	ValType view() { return pStack[top - 1]; };  // �������� �������� ��������
	bool isempty() { return top == 0; };  // �������� �� �������
	int getTop() { return top; }  // ��������� ���-�� ���������
	int getSize() { return Size; } //������ � �������
	void clear() { top = 0; } // ������� �����
};/*-------------------------------------------------------------------------*/

// �����������
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

// ����������� �����������
template <class ValType>
Stack<ValType>::Stack(const Stack &st)
{
	Size = st.Size;
	top = st.top;
	pStack = new ValType[Size];
	for (int i = 0; i < top; i++)
		pStack[i] = st.pStack[i];
}/*-------------------------------------------------------------------------*/

// ����������
template <class ValType>
Stack<ValType>::~Stack()
{
	delete[] pStack;
}/*-------------------------------------------------------------------------*/

// ������� ��������(� �������������� ������)
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

 // ���������� ��������
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
 

 



