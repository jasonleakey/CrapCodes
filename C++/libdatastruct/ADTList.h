// =====================================================================================
// 
//       Filename:  ADTList.h
// 
//    Description:  Abstract Data type of list
// 
//        Version:  1.0
//        Created:  08/08/2011 11:33:27 PM
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

#ifndef  ADTLIST_H_
#define  ADTLIST_H_


template <class T> class ADTList;
// =====================================================================================
//        Class:  ListNode
//  Description:  virtual node declaration
// =====================================================================================

template < class T >
class ListNode
{
    public:
        // ====================  LIFECYCLE     =======================================
        ListNode ();                           // constructor
        virtual ~ListNode ();                          // destructor
    private:
        // ====================  DATA MEMBERS  =======================================
        T data;
        ListNode<T>* link;
        friend class ADTList<T>;
}; // -----  end of template class ListNode  -----


// =====================================================================================
//        Class:  ADTList
//  Description:  linear list ADT
// =====================================================================================

template < class T >
class ADTList
{
    public:
        // ====================  LIFECYCLE     =======================================
        ADTList ();                           // constructor
        ADTList (const ADTList &other); // copy constructor
        virtual ~ADTList ();                          // destructor

        // ====================  ACCESSORS     =======================================
        virtual T& get_elem(const int idx) const;
        virtual T& set_elem(const int idx) const;
        virtual bool isempty();
        virtual ListNode& find(const T& val) const;
        virtual T& prior_elem(const T& curVal) const;
        virtual T& next_elem(const T& curVal) const;
        virtual void traverse(void (*visit)());
        virtual int getlength();

        // ====================  OPERATORS     =======================================
        virtual bool ins_elem(const T& val, int idx);
        virtual bool delete_elem(int idx);
        virtual void clear();

        virtual ADTList& operator = (const ADTList &other); // assignment operator
}; // -----  end of template class ADTList  -----

#endif   // ----- #ifndef ADTLIST_H_ -----
