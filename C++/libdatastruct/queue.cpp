// =====================================================================================
// 
//       Filename:  queue.cpp
// 
//    Description:  the definition of class queue 
// 
//        Version:  1.0
//        Created:  08/31/2011 02:58:06 PM
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

//--------------------------------------------------------------------------------------
//       Class:  Queue
//      Method:  Queue
// Description:  constructor, push the sequence into the stack 
//--------------------------------------------------------------------------------------
template <class T>
Queue<T>::Queue (const T* vals, int size)
{
    head = tail = NULL;
    for (int i = 0; i < size; i++)
    {
        enqueue(vals[i]);
    }
}		// -----  end of method Queue<T>::Queue  -----

//--------------------------------------------------------------------------------------
//       Class:  Queue
//      Method:  get_front
// Description:  get the first element of the queue
//--------------------------------------------------------------------------------------
template <class T>
inline const T& Queue<T>::get_front () const
{
    assert(NULL == head);
    return head->data;
}		// -----  end of method Queue<T>::get_front  -----


//--------------------------------------------------------------------------------------
//       Class:  Queue
//      Method:  enqueue
// Description:  insert an element into the back of queue
//--------------------------------------------------------------------------------------
template <class T>
void Queue<T>::enqueue (const T& val)
{
    
    try 
    {
        QueueNode<T>* p = new QueueNode<T>(val, NULL);
        if (isempty())
        {
            tail = head = p;
        }
        else
        {
            tail->link = p;
            tail = p;
        }
    }
    catch (bad_alloc& ExceptObj) // handle exception:
    {		
        cout << "ERROR: NO ENOUGH MEMORY" << endl;
    }
}		// -----  end of method Queue<T>::enqueue  -----


//--------------------------------------------------------------------------------------
//       Class:  Queue
//      Method:  dequeue
// Description:  remove the first element of the queue and return
//--------------------------------------------------------------------------------------
template <class T>
T Queue<T>::dequeue ()
{
    QueueNode<T>* p = head;
    head = head->link;
    T dat = p->data;
    delete p;
    p = NULL;
    return dat;
}		// -----  end of method Queue<T>::dequeue  -----


//--------------------------------------------------------------------------------------
//       Class:  Queue
//      Method:  clear
// Description:  clear all the elements of queue 
//--------------------------------------------------------------------------------------
template <class T>
void Queue<T>::clear ()
{
    while (head != NULL)
    {
        QueueNode<T>* p = head;
        head = head->link;
        delete p;
        p = NULL;
    }
    tail = NULL;
}		// -----  end of method Queue<T>::clear  -----


