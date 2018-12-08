// smart_ptr.cpp : Defines the entry point for the console application.
//

/*
��� ������ ����� �������. 
��� ����� ������� ����� ��������� �� ������ ������ std::string.
�� ������ ����� ������ �� ������������� NULL -
��� ������� ��� ������� �� ������ �������������� 
������ ���� ������ ������.

��������� ��� ������ ��������.

std::string s1 = "Hello, world!";

StringPointer sp1(&s1);
StringPointer sp2(NULL);

std::cout << sp1->length() << std::endl;
std::cout << *sp1 << std::endl;
std::cout << sp2->length() << std::endl;
std::cout << *sp2 << std::endl;

N.B. ��� ��� ��� ��������� ��� ������������ ������� ����� 
�������������� ������ ���� ������ ������, �� �������� 
������������ �� ������������ ������ � �����������. 
������� �� ��������� ������������ ������ � �������,
��� ��� ��� �������� �� ���� ������� :)
*/

#include "stdafx.h"
#include <string>
#include <iostream>

class StringPointer {
public:
	std::string* operator->() { 
		return m_pString;
	};
	operator std::string*() {
		return m_pString;
	}
	StringPointer(std::string *Pointer) {
		m_pString = Pointer;
	}
	~StringPointer() {
		if (m_pString->empty())
		{
			delete m_pString;
		}
	}
private:
	std::string* m_pString;

};

int main()
{
	std::string s1 = "Hello, world!";

	StringPointer sp1(&s1);
	StringPointer sp2(NULL);

	std::cout << sp1->length() << std::endl;
	std::cout << *sp1 << std::endl;
	std::cout << sp2->length() << std::endl;
	std::cout << *sp2 << std::endl;

    return 0;
}

