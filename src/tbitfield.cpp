// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0)
	{
		throw "Out of data";
	}
	BitLen = len;
	MemLen = (len+31)>>5;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
	{
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
	{
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
}

TBitField::~TBitField() //деструктор 
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n >= 0) && (n < BitLen))
	{
		return n >> 5;
	}

	if ((n < 0) || (n >= BitLen))
	{
		throw "Out of data";
	}
	
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n & 31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{ 
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n >= 0) && (n < BitLen))
	{
		pMem[GetMemIndex(n)] |= GetMemMask(n);
 	}
	if ((n < 0) || (n >= BitLen))
	{
		throw "Out of data";
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >= 0) && (n < BitLen))
	{
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	}
	if ((n < 0) || (n >= BitLen))
	{
		throw "Out of data";
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= 0) && (n < BitLen))
	{
		return (pMem[GetMemIndex(n)] & GetMemMask(n));
	}
	
	if ((n < 0) || (n >= BitLen))
	{
		throw "Out of data";
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	if (pMem != NULL)
	{
		delete[]pMem;
	}
	pMem = new TELEM[MemLen]; 
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
	for (int i = 0; i < MemLen; i++)
	{
		if (pMem[i] != bf.pMem[i])
			return 0;
	}
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen)
		return 0;
	for (int i = 0; i < MemLen; i++)
	{
		if (pMem[i] == bf.pMem[i])
			return 0;
	}
	return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	unsigned int dl = BitLen;
	if (dl < bf.BitLen)
	{
		dl = BitLen;
	}
	TBitField tmp(dl);
	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		tmp.pMem[i] |= bf.pMem[i];
	}
	return tmp;
	}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	unsigned int dl = BitLen;
	if (dl < bf.BitLen)
	{
		dl = BitLen;
	}
	TBitField tmp(dl);
	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		tmp.pMem[i] &= bf.pMem[i];
	}
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	unsigned int dl = BitLen;
	TBitField tmp(dl);
	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = ~pMem[i];
	}
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int ch,i=0;
	do
	{
		istr >> ch;
	} while (ch = ' ');
	while (1)
	{
		if (ch == '0')
		{
			bf.ClrBit(i++);
		}
		if (ch == '1')
		{
			bf.SetBit(i++);
		}
		if ((ch != '0') && (ch != '1'))
		{
			break;
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (bf.GetBit(i))
		{
			ostr << "1";
		}
		else
		{
			ostr << "0";
		}
	}
	return ostr;
}
