// qwcdll.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "qwcdll.h"


// Пример экспортированной переменной
QWCDLL_API int nqwcdll=0;

// Пример экспортированной функции.
QWCDLL_API int fnqwcdll(void)
{
	return 42;
}

// Конструктор для экспортированного класса.
// см. определение класса в qwcdll.h
Cqwcdll::Cqwcdll()
{
	return;
}
