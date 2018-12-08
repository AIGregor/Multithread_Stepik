// smart_ptr.cpp : Defines the entry point for the console application.
//

/*
“ут задача очень проста€. 
¬ам нужно создать умный указатель на объект класса std::string.
ќн должен иметь защиту от разыменовани€ NULL -
при попытке это сделать он должен конструировать 
внутри себ€ пустую строку.

—ледующий код должен работать.

std::string s1 = "Hello, world!";

StringPointer sp1(&s1);
StringPointer sp2(NULL);

std::cout << sp1->length() << std::endl;
std::cout << *sp1 << std::endl;
std::cout << sp2->length() << std::endl;
std::cout << *sp2 << std::endl;

N.B. “ак как ваш указатель при определенных случа€х может 
конструировать внутри себ€ пустую строку, не забудьте 
позаботитьс€ об освобождении пам€ти в деструкторе. 
—истема не провер€ет корректность работы в пам€тью,
так что это остаетс€ на вашу совесть :)
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

