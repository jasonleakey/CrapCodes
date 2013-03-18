// =====================================================================================
// 
//       Filename:  stack.cpp
// 
//    Description:  the definition of class stack
// 
//        Version:  1.0
//        Created:  08/31/2011 03:01:12 PM
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

template <class T>
inline StackNode<T>::StackNode (const T& val, StackNode<T>* next) : 
    data(val), link(next)
{
}		// -----  end of method StackNode<T>::StackNode  -----

template <class T>
inline StackNode<T>::~StackNode ()
{
    link = NULL;
}		// -----  end of method StackNode<T>::~StackNode  -----

//--------------------------------------------------------------------------------------
//       Class:  Stack
//      Method:  Stack
// Description:  copy constructor
//--------------------------------------------------------------------------------------
template <class T>
Stack<T>::Stack (const Stack& other)
{
    try 
    {
        top = new StackNode<T>(other.top->data, top);
    }
    catch (const bad_alloc& ExceptObj) // handle exception:
    {		
        cout << "RUN OUT OF MEMORY!" << endl;
    }

    for (StackNode<T>* p = other.top->link, q = top;
            p != NULL; p = p->link)
    {
        try 
        {
            StackNode<T>* s = new StackNode<T>(p->data);
            q->link = s;
            q = s;
        }
        catch (const bad_alloc& ExceptObj) // handle exception:
        {		
            cout << "RUN OUT OF MEMORY!" << endl;
        }

    }
}		// -----  end of method Stack<T>::Stack  -----


//--------------------------------------------------------------------------------------
//       Class:  Stack
//      Method:  push
// Description:  push an element to the stack
//--------------------------------------------------------------------------------------
template <class T>
bool Stack<T>::push (const T& val)
{
    try
    {
        top = new StackNode<T>(val, top);
        return true;
    }
    catch (exception& e) // handle exception:
    {		
        cout << "RUN OUT OF MEMORY" << e.what() << endl;
        return false;
    }
}		// -----  end of method Stack<T>::push  -----


template <class T>
const T& Stack<T>::pop ()
{
    try 
    {
        if (isempty())
        {
            throw;
        }
        const T& dat = top->data;
        top = top->link;
        return dat;
    }
    catch (exception &e) // handle exception:
    {		
        cout << e.what() << endl;
    }
}		// -----  end of method Stack<T>::pop  -----


template <class T>
const T& Stack<T>::getTop () const
{
    
    try 
    {
        if (isempty())
        {
            throw;
        }
        return top->data;
    }
    catch (exception& e) // handle exception:
    {		
        cout << e.what() << endl;
    }
}		// -----  end of method Stack<T>::getTop  -----


template <class T>
void Stack<T>::clear ()
{
    while (NULL != top)
    {
        StackNode<T>* p = top;
        top = top->link;
        delete p;
        p = NULL;
    }
}		// -----  end of method Stack<T>::clear  -----

