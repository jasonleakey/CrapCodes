/*
 *  CPP_Algorithms - TODO
 *
 *  Copyleft(R) by jasonleakey
 *  <jasonleakey@gmail.com>
 *  <QQ:174481438>
 *  --------------------------------------------------------------------
 *  CPP_Algorithms is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  CPP_Algorithms is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with CPP_Algorithms; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 *  --------------------------------------------------------------------
 */

#ifndef CDATALIST_H_
#define CDATALIST_H_

#include <iostream>
using namespace std;

template<class Keytype, class Infotype>
struct CElement
{
	Keytype key;
	Infotype otherdata;
	CElement<Keytype, Infotype>& operator=(CElement<Keytype, Infotype>& x)
	{
		key = x.key;
		otherdata = x.otherdata;
		return *this;
	}
	bool operator==(const CElement<Keytype, Infotype>& x)
	{
		return key == x.key;
	}
	bool operator<=(const CElement<Keytype, Infotype>& x)
	{
		return key <= x.key;
	}
	bool operator>=(const CElement<Keytype, Infotype>& x)
	{
		return key >= x.key;
	}
	bool operator>(const CElement<Keytype, Infotype>& x)
	{
		return key > x.key;
	}
	bool operator<(const CElement<Keytype, Infotype>& x)
	{
		return key < x.key;
	}
};

template<class Keytype, class Infotype>
class CDataList
{
	CElement<Keytype, Infotype>* Vector;
	int m_maxSize;
	int m_curSize;
	enum
	{
		DEFAULTSIZE = 100
	};
public:
	CDataList(int maxSz = DEFAULTSIZE) :
		m_maxSize(maxSz), m_curSize(0)
	{
		Vector = new CElement<Keytype, Infotype> [m_maxSize];
	}
	~CDataList()
	{
		delete[] Vector;
	}
	void swap(CElement<Keytype, Infotype>& x, CElement<Keytype, Infotype>& y)
	{
		CElement<Keytype, Infotype> temp = x;
		x = y;
		y = temp;
	}
	int length()
	{
		return m_curSize;
	}
	CElement<Keytype, Infotype>& operator[](int i)
	{
		return Vector[i];
	}

	void append(CElement<Keytype, Infotype> elem);
	void output();
	int Partition(int low, int high);
};

template<class Keytype, class Infotype>
void CDataList<Keytype, Infotype>::append(CElement<Keytype, Infotype> elem)
{
	Vector[m_curSize++] = elem;
}

template<class Keytype, class Infotype>
void CDataList<Keytype, Infotype>::output()
{
	for (int i = 0; i < m_curSize; i++)
	{
		cout << "key: " << Vector[i].key << "\totherdata: " << Vector[i].otherdata <<endl;
	}
}

template<class Keytype, class Infotype>
int CDataList<Keytype, Infotype>::Partition(int low, int high)
{
	CElement<Keytype, Infotype> pivot = Vector[low];
	while (low < high)
	{
		while (low < high && Vector[high] >= pivot)
		{
			--high;
		}
		Vector[low] = Vector[high];
		while (low < high && Vector[low] <= pivot)
		{
			++low;
		}
		Vector[high] = Vector[low];
	}
	Vector[low] = pivot;
	return low;
}

#endif /* CDATALIST_H_ */
