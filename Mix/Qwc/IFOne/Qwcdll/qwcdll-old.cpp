// qwcdll.cpp: ���������� ���������������� ������� ��� ���������� DLL.
//

#include "stdafx.h"
#include "qwcdll.h"


// ������ ���������������� ����������
QWCDLL_API int nqwcdll=0;

// ������ ���������������� �������.
QWCDLL_API int fnqwcdll(void)
{
	return 42;
}

// ����������� ��� ����������������� ������.
// ��. ����������� ������ � qwcdll.h
Cqwcdll::Cqwcdll()
{
	return;
}
