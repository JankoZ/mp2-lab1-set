// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"
#pragma warning( disable : 4717)

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp), MaxPower(mp) 
{
    return;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField), MaxPower(s.MaxPower) 
{
    return;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf), MaxPower(bf.GetLength()) 
{
    return;
}

TSet::operator TBitField()
{
    TBitField tempField = (TBitField)*this;

    return tempField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem < 0 || Elem >= MaxPower) throw 0;

    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower) throw 0;
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower) throw 0;
    BitField.ClrBit(Elem);
}

#pragma region set-theoretic operations
TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this != &s)
    {
        MaxPower = s.GetMaxPower();
        BitField = s.BitField;
    }

    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return (BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower) return 1;
    else if (BitField != s.BitField) return 1;

    return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    int length = MaxPower;
    if (s.MaxPower > MaxPower) length = s.MaxPower;

    TSet temp(length);
    temp.BitField = BitField | s.BitField;

    return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if ((Elem < 0) || (Elem >= MaxPower)) throw 0;
    BitField.SetBit(Elem);

    return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if ((Elem < 0) || (Elem >= MaxPower)) throw 0;
    BitField.ClrBit(Elem);

    return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    int length = MaxPower;
    if (s.MaxPower > MaxPower) length = s.MaxPower;

    TSet temp(length);
    temp = BitField & s.BitField;

    return temp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet temp(*this);
    temp.BitField = ~temp.BitField;

    return temp;
}
#pragma endregion

#pragma region I/O overload
istream &operator>>(istream &istr, TSet &s) // ввод
{
    char c;
    int i;

    do
    {
        istr >> c;
    } while (c != '{');
    do
    {
        istr >> i;
        s.InsElem(i);
        istr >> c;
    } while (c != '}');

    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    ostr << '{';
    for (int i = 0; i < s.GetMaxPower(); i++)
    {
        if (s.IsMember(i))
            ostr << i;
        ostr << ',';
    }
    ostr << '}';

    return ostr;
}
#pragma endregion