// =====================================================================================
// 
//       Filename:  quene.h
// 
//    Description:  linked queue
// 
//        Version:  1.0
//        Created:  08/30/2011 05:07:33 PM
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


#ifndef  QUENE_H_
#define  QUENE_H_



#include	<iostream>
#include	<exception>
#include	<cstdlib>
using namespace std;

template < class T > class Queue;
// =====================================================================================
//        Class:  QueueNode
//  Description:  The queue node class declaration
// =====================================================================================

template < class T >
class QueueNode
{
    public:
        // ====================  LIFECYCLE     =======================================
        QueueNode();                            // constructor
        QueueNode(const T& val, QueueNode<T>* next = NULL) : data(val), link(next)
        {
         // constructor
        }

        // ====================  ACCESSORS     =======================================

        // ====================  MUTATORS      =======================================

        // ====================  OPERATORS     =======================================


    private:
        // ====================  DATA MEMBERS  =======================================
        T data;
        QueueNode<T>* link;
    friend class Queue<T>;

}; // -----  end of template class QueueNode  -----


// =====================================================================================
//        Class:  Queue
//  Description:  The link-based Queue declaration
// =====================================================================================

template < class T >
class Queue
{
    public:
        // ====================  LIFECYCLE     =======================================
        Queue() : head(NULL), tail(NULL) {}     // constructor
        Queue(const T* vals, int size);                   // constructor
        ~Queue()                                // destructor
        {
            clear();
        }

        // ====================  ACCESSORS     =======================================
        const T& get_front() const;
        bool isempty() const
        {
            return (head == NULL || tail == NULL);
        }

        // ====================  MUTATORS      =======================================

        // ====================  OPERATORS     =======================================
        void enqueue(const T& val);             // insert item to the queue 
        T dequeue();                            // remove and return the head node in the queue
        void clear();                           // clear the entire queue

    private:
        // ====================  DATA MEMBERS  =======================================
        QueueNode<T>* head;
        QueueNode<T>* tail;

}; // -----  end of template class Queue  -----

#include	"queue.cpp" // include definition
#endif   // ----- #ifndef QUENE_H_ -----
