#include "tset.h"

TSet::TSet(int mp) :MaxPower(mp), BitField(mp) {}

// конструктор копирования
TSet::TSet(const TSet &s) :
	MaxPower(s.MaxPower), BitField(s.MaxPower) {
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) :
	MaxPower(bf.GetLength()), BitField(bf) {
}

TSet::operator TBitField()
{
	return TBitField(this->BitField);
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;

	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	return TSet(BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TBitField temp = BitField;
	temp.SetBit(Elem);

	return TSet(temp);
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TBitField temp = BitField;
	temp.ClrBit(Elem);

	return TSet(temp);
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	return TSet(BitField & s.BitField);
}

TSet TSet::operator~(void) // дополнение
{
	return TSet(~BitField);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int temp;
	char ch;

	do
	{
		istr >> ch;
	} while (ch != '{');

	do
	{
		istr >> temp;
		s.InsElem(temp);

		do
		{
			istr >> ch;
		} while ((ch != ',' && ch != '}'));

	} while (ch != '}');

	return istr;

}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	int i, n;
	char ch = ' ';
	ostr << "{";
	n = s.GetMaxPower();
	for (int i = 0; i < n; i++)
	{
		if (s.IsMember(i))
		{
			ostr << ch << " " << i;
			ch = ',';
		}
	}
	ostr << "}";
	return ostr;
}
