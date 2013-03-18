// =====================================================================================
// 
//       Filename:  stack.h
// 
//    Description:  Stack 
// 
//        Version:  1.0
//        Created:  08/29/2011 06:19:10 PM
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


#ifndef  STACK_H_
#define  STACK_H_

#include	<iostream>
#include	<exception>
using namespace std;
template < class T > class Stack;


// =====================================================================================
//        Class:  StackNode
//  Description:  The Node declaration of Stack 
// =====================================================================================

template < class T >
class StackNode
{
    public:
        // ====================  LIFECYCLE     =======================================
        StackNode();                             // constructor
        StackNode(const T& val, StackNode<T>* next = NULL);  // constructor
        ~StackNode();

    private:
        // ====================  DATA MEMBERS  =======================================
        T data;
        StackNode<T>* link;

    friend class Stack<T>;
}; // -----  end of template class StackNode  -----


// =====================================================================================
//        Class:  Stack
//  Description:  The declaration of Stack class
// =====================================================================================

template < class T >
class Stack
{
    public:
        // ====================  LIFECYCLE     =======================================
        Stack() : top(NULL) {}                  // constructor
        Stack (const Stack &other);             // copy constructor
        ~Stack()
        {
            clear();
        }// destructor

        // ====================  ACCESSORS     =======================================

        // ====================  MUTATORS      =======================================

        // ====================  OPERATORS     =======================================
        bool push(const T& val);
        const T& pop();
        const T& getTop() const;
        void clear();
        int isempty() const
        {
            return (top == NULL);
        }

    private:
        // ====================  DATA MEMBERS  =======================================
        StackNode<T>* top;

}; // -----  end of template class Stack  -----

#include	"stack.cpp" // include implementation
#endif   // ----- #ifndef STACK_H_ -----
