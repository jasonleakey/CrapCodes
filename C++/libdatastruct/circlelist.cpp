// =====================================================================================
// 
//       Filename:  circlelist.cpp
// 
//    Description:  the definition of cirular linked list
// 
//        Version:  1.0
//        Created:  08/31/2011 03:03:18 PM
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
CircleListNode<T>::CircleListNode () : link(NULL)
{
}		// -----  end of method CircleListNode<T>::CircleListNode  -----

//--------------------------------------------------------------------------------------
//       Class:  CircleListNode
//      Method:  CircleListNode
// Description:  constructor 
//--------------------------------------------------------------------------------------
template <class T>
CircleListNode<T>::CircleListNode (const T& val, CircleListNode<T>* next) : data(val), link(next)
{
}		// -----  end of method CircleListNode<T>::CircleListNode  -----



template <class T>
CircleListNode<T>::~CircleListNode ()
{
}		// -----  end of method CircleListNode<T>::~CircleListNode  -----

//--------------------------------------------------------------------------------------
//       Class:  CircleList
//      Method:  CircleList
// Description:  constructor
//--------------------------------------------------------------------------------------
template <class T>
CircleList<T>::CircleList ()
{
    header = new CircleListNode<T>;
    header->link = header;
    curr = header;
}		// -----  end of method CircleList<T>::CircleList  -----



template <class T>
CircleList<T>::CircleList (const T* vals, int size)
{
    header = new CircleListNode<T>;
    header->link = header;
    curr = header;
    for (int i = 0; i < size; i++)
    {
        insertafter(vals[i]);
        next();
    }
    curr2head();
}		// -----  end of method CircleList<T>::CircleList  -----

//--------------------------------------------------------------------------------------
//       Class:  CircleList
//      Method:  ~CircleList
// Description:  destructor
//--------------------------------------------------------------------------------------
template <class T>
CircleList<T>::~CircleList ()
{
    clear();
    delete header;
}		// -----  end of method CircleList<T>::~CircleList  -----
//--------------------------------------------------------------------------------------
//       Class:  CircleList
//      Method:  find
// Description:  find the node according to its data and return
// pointer.
//--------------------------------------------------------------------------------------
template <class T>
CircleListNode<T>* CircleList<T>::find (const T& val) const
{
    for (CircleListNode<T>* q = header->link; q != header; q =
            q->link)
    {
        if (q->data == val)
        {
            return q;
        }
    }
    return NULL;
}		// -----  end of method CircleList<T>::find  -----


//--------------------------------------------------------------------------------------
//       Class:  CircleList
//      Method:  getdata
// Description:  return the data of current node
//--------------------------------------------------------------------------------------
template <class T>
T& CircleList<T>::getdata () const
{
    return curr->data;
}		// -----  end of method CircleList<T>::getdata  -----


//--------------------------------------------------------------------------------------
//       Class:  CircleList
//      Method:  prior
// Description:  let current cursor point to its previous node
//--------------------------------------------------------------------------------------
template <class T>
bool CircleList<T>::prior ()
{
    if (isempty())
    {
        return false;
    }
    CircleListNode<T>* q = header;
    for (; q->link != curr; q = q->link)
    {
        NULL;
    }
    curr = q;
    return true;
}		// -----  end of method CircleList<T>::prior  -----

//--------------------------------------------------------------------------------------
//       Class:  CircleList
//      Method:  next
// Description:  let current cursor point to its next node
//--------------------------------------------------------------------------------------
template <class T>
bool CircleList<T>::next ()
{
    if (isempty())
    {
        return false;
    }
    curr = curr->link;
    return true;
}		// -----  end of method CircleList<T>::next  -----


//--------------------------------------------------------------------------------------
//       Class:  CircleList
//      Method:  traverse
// Description:  output the entire list using external callback
// function
//--------------------------------------------------------------------------------------
template <class T>
void CircleList<T>::traverse (void (*visit)(const T&))
{
    if (isempty())
    {
        return;
    }
    for (CircleListNode<T>* q = header->link; q != header; q = q->link)
    {
        visit(q->data);
    }
}		// -----  end of method CircleList<T>::traverse  -----


template <class T>
int CircleList<T>::length () 
{
    int len = 0;
    for (CircleListNode<T>* q = header->link; 
            q != header; q = q->link)
    {
        len++;
    }
    return len;
}		// -----  end of method CircleList<T>::length  -----

//--------------------------------------------------------------------------------------
//       Class:  CircleList
//      Method:  insertbefore
// Description:  insert a node before current node
//--------------------------------------------------------------------------------------
template <class T>
bool CircleList<T>::insertbefore (const T& val)
{
    if (isempty())
    {
        return false;
    }
    prior();
    CircleListNode<T>* q = new CircleListNode<T>(val, curr->link);
    curr->link = q;
    curr = curr->link->link;
    return true;
}		// -----  end of method CircleList<T>::insert  -----


//--------------------------------------------------------------------------------------
//       Class:  CircleList
//      Method:  insertafter
// Description:  insert a node after current node
//--------------------------------------------------------------------------------------
template <class T>
bool CircleList<T>::insertafter (const T& val)
{
    CircleListNode<T>* q = new CircleListNode<T>(val, curr->link);
    curr->link = q;
    return true;
}		// -----  end of method CircleList<T>::insertafter  -----


//--------------------------------------------------------------------------------------
//       Class:  CircleList
//      Method:  remove
// Description:  delete current node
//--------------------------------------------------------------------------------------
template <class T>
bool CircleList<T>::remove ()
{
    if (isempty())
    {
        return false;
    }
    else
    {
        CircleListNode<T>* q = curr;
        prior();
        curr->link = q->link;
        delete q;
        q = NULL;
        next();
    }
    return true;
}		// -----  end of method CircleList<T>::remove  -----

//--------------------------------------------------------------------------------------
//       Class:  CircleList
//      Method:  clear
// Description:  remove all the elements except the head node.
//--------------------------------------------------------------------------------------
template <class T>
void CircleList<T>::clear ()
{
    curr = header->link;
    while (!isempty())
    {
        CircleListNode<T>* q = curr;
        curr = curr->link;
        header->link = curr;
        delete q;
        q = NULL;
    }
}		// -----  end of method CircleList<T>::clear  -----


//--------------------------------------------------------------------------------------
//       Class:  CircleList
//      Method:  josephus
// Description:  Josephus problem
//--------------------------------------------------------------------------------------
template <class T>
bool CircleList<T>::josephus (int round, int count, void (*visit)(const T&))
{
    if (round >= length())
    {
        return false;
    }
    curr = header->link;
    for (int i = 0; i < round; i++)
    {
        for (int j = 0; j < count - 1;)
        {
            if (curr != header)
            {
                j++;
            }
            next();
        }
        visit(getdata());
        remove();
    }
    return true;
}		// -----  end of method CircleList<T>::josephus  -----


//--------------------------------------------------------------------------------------
//       Class:  CircleList
//      Method:  operator =
// Description:  assignment operator
//--------------------------------------------------------------------------------------
template <class T>
CircleList<T>& CircleList<T>::operator = (const CircleList<T>& other)
{
    clear();
    curr = header;
    CircleListNode<T>* q = other.header->link;
    for (; q != other.header; q = q->link, curr = curr->link)
    {
        insertafter(q->data);
    }
    curr2head();
   
    return *this;
}		// -----  end of function operator =  -----

