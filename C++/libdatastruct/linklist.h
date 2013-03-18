/*
 *
 *  NAME: The declaration for link list
 *  DATE: Sun 03 Jul 2011 11:22:54 AM CST
 *
 *  Copyleft(R) by jasonleakey
 *  <jasonleakey@gmail.com>
 *
 *  GPLv2 licence
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


#ifndef HUAWEI_LIST_H_
#define HUAWEI_LIST_H_

#include    <stdlib.h>
#include	<iostream>
using namespace std;

template<class T> class List;

template<class T>
class ListNode {
    friend class List<T>;
private:
    T data;
    ListNode<T>* link;
public:
    ListNode();
    ListNode(const T& item);
    ListNode<T>* NextNode() { return link; }
    void InsertAfter(ListNode<T>* p);
//    ListNode<T>* CreateNode(const T& item, ListNode<T>* next);
    ListNode<T>* RemoveAfter();
};

template<class T>
class List {
    ListNode<T>* first;
    ListNode<T>* last;
public:
    List() {last = first = new ListNode<T>; }
    List(const T*, int);
    ~List() {
        clear();
        delete first;
        first = last = NULL;
    }
    void clear();
    int getlength() const;
    bool insert(const T&, int);
    T remove(int);
    T remove(ListNode<T>*);
    ListNode<T>* find(const T&);
    ListNode<T>* find(int);
    const T* get(int index);
    void traverse();
    void reverse();
};

#include	"linklist.cpp" // include the implementation
#endif // HUAWEI_LIST_H_
