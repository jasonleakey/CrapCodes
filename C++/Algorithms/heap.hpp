/*
 *  CPP_practice - TODO
 *  
 *  Feb 10, 2010
 *  Copyleft(R) by jasonleakey
 *  <jasonleakey@gmail.com>
 *  <QQ:174481438>
 *  --------------------------------------------------------------------
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 *  --------------------------------------------------------------------
 */

#ifndef HEAP_HPP_
#define HEAP_HPP_

template<class Keytype, class Infotype>
struct CElement;



template<class Keytype, class Infotype>
class CMaxHeap
{
    
	CElement<Keytype, Infotype>* heap; // the array to store element
	int m_curSize; // the size of current elements
	int m_maxHeapSize; // the max size of elements allowed
	enum
	{
		DEFAULTSIZE = 100
	};
public:
	CMaxHeap(int sz = DEFAULTSIZE);
	CMaxHeap(CElement<Keytype, Infotype> arr[], int n);
	~CMaxHeap()
	{
		delete[] heap;
	}
	int insert(const CElement<Keytype, Infotype>& x);
	int remove(CElement<Keytype, Infotype>& x);
	void sift_down(int start, int m); // sift the heap in top-down order
	void sift_up(int start); // sift the heap in bottom-up order
	void swap(const int i, const int j) // swap the element in heap
	{
		CElement<Keytype, Infotype> tmp = heap[i];
		heap[i] = heap[j];
		heap[j] = tmp;
	}
	bool isEmpty() const
	{
		return 0 == m_curSize;
	}
	bool isFull() const
	{
		return m_curSize == m_maxHeapSize;
	}
	int length() const
	{
		return m_curSize;
	}
	int capacity() const
	{
		return m_maxHeapSize;
	}
	CElement<Keytype, Infotype>& operator [](int idx)
	{
		return heap[idx];
	}
	template<class K, class I>
	friend ostream& operator <<(ostream& os, CMaxHeap<K, I>& hp);
};

template<class Keytype, class Infotype>
CMaxHeap<Keytype, Infotype>::CMaxHeap(int sz)
{
	heap = NULL;
}

template<class Keytype, class Infotype>
CMaxHeap<Keytype, Infotype>::CMaxHeap(CElement<Keytype, Infotype> arr[], int n)
	: m_curSize(n), m_maxHeapSize(DEFAULTSIZE)
{
	heap = NULL;
	if (NULL == (heap = new CElement<Keytype, Infotype>[n + 1]))
	{
		cerr << "no enough memory.." << endl;
		exit(0);
	}
	for (int i = 1; i <= n; i++)
	{
		heap[i] = arr[i - 1];
	}
}

template<class Keytype, class Infotype>
void CMaxHeap<Keytype, Infotype>::sift_down(const int start, const int m)
{
	int i = start;
	CElement<Keytype, Infotype> temp = heap[start];
	for (int j = 2 * i; j <= m; j *= 2)
	{
		if (j < m && heap[j] < heap[j + 1])
		{
			++j;
		}
		if (temp >= heap[j])
		{
			break;
		}
		heap[i] = heap[j];
		i = j;
	}
	heap[i] = temp;
}

template<class Keytype, class Infotype>
ostream& operator <<(ostream& os, CMaxHeap<Keytype, Infotype>& hp)
{
	for (int i = 1; i <= hp.length(); i++)
	{
		os << i << "." << hp[i].key << ' ' << hp[i].otherdata << endl;
//		os << "ok!" << endl;
	}
	return os;
}

#endif /* HEAP_HPP_ */
