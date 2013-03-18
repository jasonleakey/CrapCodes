/*
 *  CPP_DS_List - TODO
 *
 *  Copyleft(R) by jasonleakey
 *  <jasonleakey@gmail.com>
 *  <QQ:174481438>
 *  --------------------------------------------------------------------
 *  CPP_DS_List is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  CPP_DS_List is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with CPP_DS_List; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 *  --------------------------------------------------------------------
 */

#ifndef CSEQLIST_H_
#define CSEQLIST_H_

#include <iostream>
#include <cstdlib>
using namespace std;

template<class T>
class CSeqList
{
protected:
	T* m_data;
	int m_nMaxSize;
	int m_nLast;
	enum { DEFAULTSIZE = 100, INCREMENT = 10 };
	void resize(int newsize);
public:
	CSeqList(int sz = DEFAULTSIZE);
	CSeqList(CSeqList<T>& L);
	~CSeqList();

	int get_size() const
		{ return m_nMaxSize; }
	int get_length() const
		{ return m_nLast + 1;	}
	int search(const T& key) const;
	int locate(int index) const;
	T* get_data(int index) const
		{ return (index > 0 && index <= m_nLast + 1) ? &m_data[index - 1] : NULL; }

	void set_data(int index, const T& key);
	bool insert(int index, const T& key);
	bool remove(int index, T& key);
	bool is_empty() const
		{ return -1 == m_nLast ? true : false; }

	bool is_full() const
		{ return m_nMaxSize == m_nLast ? true : false; }

	void sort();
	void input();
	void output();

	CSeqList<T> operator=(CSeqList<T>& L);
};


/*
 * constructor and allocate space
 */
template<class T>
CSeqList<T>::CSeqList(int sz)
{
	// Auto-generated constructor stub
	if (sz > 0)
	{
		m_nMaxSize = sz;
		m_nLast = -1;
		if (NULL == (m_data = new T[m_nMaxSize]))
		{
			cerr << "No enough memory!" << endl;
			exit(1);
		}
	}
}

/*
 * destructor
 */
template<class T>
CSeqList<T>::~CSeqList()
{
	// Auto-generated destructor stub
	delete[] m_data;
}

/*
 * copy constructor
 */
template<class T>
CSeqList<T>::CSeqList(CSeqList<T>& L)
{
	m_nMaxSize = L.get_size();
	m_nLast = L.get_length() - 1;
	m_data = new T[m_nMaxSize];
	if (NULL == m_data)
	{
		cerr << "No enough momery!" << endl;
		exit(1);
	}

	for (int i = 0; i < m_nLast + 1; i++)
	{
		m_data[i - 1] = L.get_data(i);
	}
}

template<class T>
void CSeqList<T>::resize(int newsize)
{
	if (newsize <= 0)
	{
		cerr << "Invalid array size!" << endl;
		return;
	}
	if (newsize != m_nMaxSize)
	{
		// create new array
		T* newarray = new T[newsize];
		if (NULL == newarray)
		{
			cerr << "No enough memory!" << endl;
			exit(1);
		}

		// copy data
		for (int oldlength = m_nLast; oldlength >= 0; oldlength--)
		{
			newarray[oldlength] = m_data[oldlength];
		}
		// delete old array
		delete[] m_data;
		// copy head pointer and max size
		m_data = newarray;
		m_nMaxSize = newsize;
	}
}


template<class T>
int CSeqList<T>::search(const T & key) const
{
	for (int i = 0; i <= m_nLast; i++)
	{
		if (m_data[i] == key)
		{
			return i + 1;
		}
	}
	return 0;
}

template<class T>
int CSeqList<T>::locate(int index) const
{
	if (index > 0 && index <= m_nLast + 1)
	{
		return index;
	}
	return 0;
}

template<class T>
void CSeqList<T>::set_data(int index, const T & key)
{
	if (index > 0 && index <= m_nLast + 1)
	{
		m_data[index - 1] = key;
	}
}

template<class T>
bool CSeqList<T>::insert(int index, const T & key)
{
	if (index < 0 && index > m_nLast + 1)
	{
		return false;
	}
	if (m_nLast == m_nMaxSize - 1)
	{
		resize(m_nMaxSize + INCREMENT);
	}
	for (int j = m_nLast; j >= index; j--)
	{
		m_data[j + 1] = m_data[j];
	}
	m_data[index] = key;
	m_nLast++;
	return true;
}

template<class T>
bool CSeqList<T>::remove(int index, T & key)
{
	if (m_nLast == -1 || index < 1 || index > m_nLast + 1)
	{
		return false;
	}
	key = m_data[index - 1];
	for (int j = index; j <= m_nLast; j++)
	{
		m_data[j - 1] = m_data[j];
	}
	m_nLast--;
	return true;
}

template<class T>
void CSeqList<T>::input()
{
	cout << "Input List size:";
	std::cin >> m_nLast;
	cout << "Input " << m_nLast << " elements:" << endl;
	for (int i = 0; i < m_nLast; i++)
	{
		cin >> m_data[i];
	}
}

template<class T>
void CSeqList<T>::output()
{
	for (int i = 0; i < m_nLast; i++)
	{
		cout << "#" << i + 1 << ":" << m_data[i] << endl;
	}
}

template<class T>
CSeqList<T> CSeqList<T>::operator =(CSeqList<T> & L)
{
	m_nMaxSize = L.get_size();
	m_nLast = L.get_length() - 1;
	m_data = new T[m_nMaxSize];
	if (NULL == m_data)
	{
		cerr << "No enough momery!" << endl;
		exit(1);
	}

	for (int i = 0; i < m_nLast + 1; i++)
	{
		m_data[i - 1] = L.get_data(i);
	}
}

template<class T>
void CSeqList<T>::sort()
{

}




#endif /* CSEQLIST_H_ */
