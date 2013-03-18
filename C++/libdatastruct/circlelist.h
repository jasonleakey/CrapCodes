// =====================================================================================
// 
//       Filename:  circlelist.h
// 
//    Description:  circular linked list
// 
//        Version:  1.0
//        Created:  08/07/2011 10:15:22 PM
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


#ifndef  CIRCLELIST_H_
#define  CIRCLELIST_H_


template < class T > class CircleList;
// =====================================================================================
//        Class:  CircleListNode
//  Description:  the declaration for the node of circular linked list 
// =====================================================================================
template < class T >
class CircleListNode 
{
    public:
        // ====================  LIFECYCLE     =======================================
        CircleListNode (); // constructor
        CircleListNode (const T& val, CircleListNode<T>* next = NULL);                           // constructor
        ~CircleListNode ();                          // destructor

    private:
        T data;
        CircleListNode<T>* link;
    friend class CircleList<T>;
}; // -----  end of template class CircleListNode  -----

// =====================================================================================
//        Class:  CircleList
//  Description:  circular linked list
// =====================================================================================

template < class T >
class CircleList
{
    public:
        // ====================  LIFECYCLE     =======================================
        CircleList ();                           // constructor
        CircleList (const T* vals, int size);  // constructor
        ~CircleList ();                          // destructor

        // ====================  ACCESSORS     =======================================
        bool isempty()
        {
            return header->link == header;
        }
        CircleListNode<T>* find(const T& val) const;
        T& getdata() const;
        void curr2head()
        {
            curr = header;
        }
        bool prior();
        bool next();
        void traverse(void (*visit)(const T&));
        int length();

        // ====================  OPERATORS     =======================================
        bool insertbefore(const T& val);
        bool insertafter(const T& val);
        bool remove();
        void clear();
        bool josephus(int round, int count, void (*visit)(const T&));

        CircleList<T>& operator = (const CircleList<T>& other); // assignment operator

    protected:
        // ====================  DATA MEMBERS  =======================================

    private:
        CircleListNode<T>* header;
        CircleListNode<T>* curr;
}; // -----  end of template class CircleList  -----


#include	"circlelist.cpp" // include definition
#endif   // ----- #ifndef CIRCLELIST_H_ -----

