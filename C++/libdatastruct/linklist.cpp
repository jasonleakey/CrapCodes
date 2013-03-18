// =====================================================================================
// 
//       Filename:  linklist.cpp
// 
//    Description:  the implementation of linked list
// 
//        Version:  1.0
//        Created:  08/31/2011 03:05:27 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  jasonleakey (uKi), jasonleakey@gmail.com
//        Company:  HIT
//        licence:  GPLv2
// 
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
// 
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//  MA 02110-1301, USA.
// =====================================================================================

template<class T>
ListNode<T>::ListNode():link(NULL)
{
}

template<class T>
ListNode<T>::ListNode(const T& item):data(item),link(NULL)
{
}

template<class T>
void ListNode<T>::InsertAfter(ListNode<T>* p)
{
    p->link = link;
    link = p;
}

//template<class T>
//ListNode<T>* ListNode<T>::CreateNode(const T& item, ListNode<T>* next = NULL)
//{
//    ListNode<T>* newnode = new ListNode<T>(item);
//    return newnode;
//}

template<class T>
ListNode<T>* ListNode<T>::RemoveAfter()
{
    ListNode<T>* tempptr = link;
    if (NULL == link)
    {
        return NULL;
    }
    link = tempptr->link;
    return tempptr;
}


template<class T>
List<T>::List(const T* values, int size)
{
    last = first = new ListNode<T> ();
    for (int i = size - 1; i >= 0; i--)
    {
        insert(values[i], 1);
    }
}


template<class T>
void List<T>::clear()
{
    ListNode<T>* q;
    while (first->link != NULL)
    {
        q = first->link;
        first->link = q->link;
        delete q;
    }
    last = first;
}

template<class T>
int List<T>::getlength() const
{
    int len = 0;
    ListNode<T>* q = first->link;
    while (NULL != q)
    {
        len++;
        q = q->link;
    }
    return len;
}

template<class T>
ListNode<T>* List<T>::find(const T& value)
{
    ListNode<T>* q = first->link;
    while (NULL != q && !(q->data == value))
    {
        q = q->link;
    }
    return q;
}

template<class T>
ListNode<T>* List<T>::find(int index)
{
    if (index < 0)
    {
        return NULL;
    }
//    PRINT(index);
    if (0 == index)
    {
        return first;
    }
    ListNode<T>* q = first->link;
    int j = 1;
    while (NULL != q && j < index)
    {
        q = q->link;
        j++;
    }
    return q;
}


template<class T>
bool List<T>::insert(const T& value, int index)
{
    ListNode<T>* q = find(index - 1);
    if (NULL == q)
    {
        return false;
    }
    ListNode<T>* newnode = new ListNode<T>(value);//CreateNode(value, q->link);
    newnode->link = q->link;
    if (last == q)
    {
        last = newnode;
    }
    q->link = newnode;
    return true;
}


template<class T>
T List<T>::remove(int index)
{
    ListNode<T>* q = find(index - 1);
    if (NULL == q || NULL == q->link)
    {
        return NULL;
    }
    ListNode<T>* p = q->link;
    q->link = p->link;
    if (NULL == q->link)
    {
        last = q;
    }
    T dat = p->data;
    delete p;
    p = NULL;
    return dat;
}


template <class T>
T List<T>::remove (ListNode<T>* p)
{
    ListNode<T>* q = first;
    for (; q != NULL && q->link != p; q = q->link)
    {
        NULL;
    }
    if (last == p)
    {
        last = q;
    }
    q->link = p->link;
    T dat = p->data;
    delete p;
    p = NULL;
    return dat;
}		// -----  end of method List<T>::remove  -----

template<class T>
const T* List<T>::get(int index) 
{
    ListNode<T>* q = find(index);
    if (NULL == q || first == q)
    {
        return NULL;
    }
    return &(q->data);
}


template <class T>
void List<T>::reverse ()
{
    if (getlength() > 1)
    {
        ListNode<T>* p = first->link->link;
        last = first->link;
        last->link = NULL;
        while (NULL != p)
        {
            ListNode<T>* q = p->link;
            p->link = first->link;
            first->link = p;
            p = q;
        }
    }
}		// -----  end of method List<T>::reverse  -----

template <class T>
void List<T>::traverse ()
{
    int len = getlength();
    for (int i = 0; i < len; i++)
    {
        cout << "No. " << i + 1 << ":\t" << *get(i + 1) << endl;
    }
}		// -----  end of method List<T>::traverse  -----

