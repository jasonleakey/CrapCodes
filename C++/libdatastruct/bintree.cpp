// =====================================================================================
// 
//       Filename:  bintree.cpp
// 
//    Description:  The implementation of binary tree
// 
//        Version:  1.0
//        Created:  08/31/2011 03:20:10 PM
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


#include	"stack.h"
#include	"queue.h"
#include	<iostream>
using namespace std;

//--------------------------------------------------------------------------------------
//       Class:  BinTreeNode
//      Method:  BinTreeNode
// Description:  copy constructor
//--------------------------------------------------------------------------------------
template <class T>
BinTreeNode<T>::BinTreeNode (const BinTreeNode<T>& other)
{
    data = other.data;
    lchild = other.lchild;
    rchild = other.rchild;
}		// -----  end of method BinTreeNode<T>::BinTreeNode  -----


//--------------------------------------------------------------------------------------
//       Class:  BinTreeNode
//      Method:  operator =
// Description:  assignment operator
//--------------------------------------------------------------------------------------
template <class T>
BinTreeNode<T>& BinTreeNode<T>::operator = (const BinTreeNode<T>& other)
{
    data = other.data;
    lchild = other.lchild;
    rchild = other.rchild;
    return *this;
}		// -----  end of method BinTreeNode<T>::operator =  -----


template <class T>
int BinTree<T>::depth () const
{
    if (NULL == root)
    {
        return 0;
    }
    else
    {
        int lchildepth = 0;
        int rchildepth = 0;
        if (NULL != root->get_lchild())
        {
            // compute the depth of left child
            lchildepth = depth(root->lchild);
        }
        if (NULL != root->get_rchild())
        {
            // compute the depth of right child
            rchildepth = depth(root->get_rchild());
        }
        // return the deeper one plus 1
        return (lchildepth > rchildepth) ? (lchildepth + 1) \
            : (rchildepth + 1); 
    }
}		// -----  end of method BinTree<T>::depth  -----


template <class T>
const BinTreeNode<T>* BinTree<T>::parent (const BinTreeNode<T>* start, \
        const BinTreeNode<T>* current) const 
{
    if (NULL == start)
    {
        return NULL;
    }
    else if (start->get_lchild() == current || start->get_rchild() == current)
    {
        return start;
    }
    else 
    {
        BinTreeNode<T>* p = NULL;
        if (NULL != (p = parent(start->get_lchild(), current)))
        {
            return p;
        }
        else
        {
            return parent(start->get_rchild(), current);
        }
    }
}		// -----  end of method BinTree<T>::parent  -----


template <class T>
BinTreeNode<T>* BinTree<T>::get_leftsibling (const BinTreeNode<T>* current) 
{
    assert(NULL != current);
    if (NULL != root)
    {
        BinTreeNode<T>* p = parent(current);
        if (NULL != p 
            && NULL != p->get_lchild()
            && NULL != p->get_rchild()
            && p->get_rchild()->get_data() == current->get_data())
        {
            return p->get_lchild();
        }
    }
    return NULL;
}		// -----  end of method BinTree<T>::get_leftsibling  -----


template <class T>
BinTreeNode<T>* BinTree<T>::get_rightsibling (const BinTreeNode<T>* current)
{
    assert(NULL != current);
    if (NULL != root)
    {
        BinTreeNode<T>* p = parent(current);
        if (NULL != p 
            && NULL != p->get_lchild()
            && NULL != p->get_rchild()
            && p->get_lchild().get_data() == current->get_data())
        {
            return p->get_rchild();
        }
    }
    return ;
}		// -----  end of method BinTree<T>::get_rightsibling  -----


template <class T>
bool BinTree<T>::insertchild (const BinTreeNode<T>* current, Direct d, const BinTree<T>* other)
{
    assert(NULL != current);
    if (d == LEFT)
    {
        if (NULL != current->get_lchild())
        {
            other->get_rchild() = current->get_lchild();
        }
        current->get_lchild() = other;
        return true;
    }
    if (d == RIGHT)
    {
        if (NULL != current->get_rchild())
        {
            other->get_lchild() = current->get_rchild();
        }
        current->get_rchild() = other;
        return true;
    }
    return false;
}		// -----  end of method BinTree<T>::insertchild  -----


template <class T>
bool BinTree<T>::deletechild (const BinTreeNode<T>* current, Direct d)
{
    assert(current != NULL);
    if (LEFT == d && NULL != current->get_lchild())
    {
        destroy(current->get_lchild());
        return true;
    }
    if (RIGHT == d && NULL != current->get_rchild())
    {
        destroy(current->get_rchild());
        return true;
    }
    return false;
}		// -----  end of method BinTree<T>::deletechild  -----


template <class T>
void BinTree<T>::preorder_traverse (const BinTreeNode<T>* current)
{
    if (NULL != current)
    {
        cout << current->get_data() << '\t'; 
        preorder_traverse(current->lchild);
        preorder_traverse(current->rchild);
    }
}		// -----  end of method BinTree<T>::preorder_traverse  -----


template <class T>
void BinTree<T>::inorder_traverse (const BinTreeNode<T>* current)
{
    if (NULL != current)
    {
        inorder_traverse(current->lchild);
        cout << current->get_data() << '\t';
        inorder_traverse(current->rchild);
    }
}		// -----  end of method BinTree<T>::inorder_traverse  -----


template <class T>
void BinTree<T>::postorder_traverse (const BinTreeNode<T>* current)
{
    if (NULL != current)
    {
        postorder_traverse(current->lchild);
        postorder_traverse(current->rchild);
        cout << current->get_data() << '\t';
    }
}		// -----  end of method BinTree<T>::postorder_traverse  -----


//template <class T>
//BinTree& BinTree<T>::operator = (const BinTree& other)
//{
//    return ;         
//}		// -----  end of method BinTree<T>::operator =  -----



template <class T>
void BinTree<T>::preorder_traverse_nore ()
{
    Stack<BinTreeNode<T>*> s;
    BinTreeNode<T>* p = root;
    while (NULL != p || !s.isempty())
    {
        while (NULL != p)
        {
            cout << p->get_data() << '\t';
            if (NULL != p->get_rchild())
            {
                s.push(p->get_rchild());
            }
            p = p->get_lchild();
        }
        if (!s.isempty())
        {
            p = s.pop();
        }
    }
    cout << endl;
}		// -----  end of method BinTree<T>::preorder_traverse_nore  -----


template <class T>
void BinTree<T>::preorder_traverse_nore2 ()
{
    Stack<BinTreeNode<T>*> s;
    BinTreeNode<T>* p = root;
    while (NULL != p || !s.isempty())
    {
        if (NULL != p)
        {
            cout << p->get_data() << '\t';
            s.push(p);
            p = p->get_lchild();
        }
        else
        {
            do
            {
                p = s.pop();
            } while (!s.isempty() && NULL == p->get_rchild());
            p = p->get_rchild();
        }
    }
    cout << endl;
}		// -----  end of method BinTree<T>::preorder_traverse_nore  -----


template <class T>
void BinTree<T>::preorder_traverse_nore3 ()
{
    Stack<BinTreeNode<T>*> s;
    BinTreeNode<T>* p = root;
    while (NULL != p || !s.isempty())
    {
        while (NULL != p)
        {
            cout << p->get_data() << '\t';
            s.push(p);
            p = p->get_lchild();
        }
        if (!s.isempty())
        {
            p = s.pop();
            p = p->rchild;
        }
    }
    cout << endl;
}		// -----  end of method BinTree<T>::preorder_traverse_nore3  -----

template <class T>
void BinTree<T>::inorder_traverse_nore ()
{
    Stack<BinTreeNode<T>*> s;
    BinTreeNode<T>* p = root;
    while (NULL != p || !s.isempty())
    {
        if (NULL != p)
        {
            s.push(p);
            p = p->get_lchild();
        }
        else
        {
            p = s.pop();
            cout << p->get_data() << '\t';
            p = p->get_rchild();
        }
    }
    cout << endl;
}		// -----  end of method BinTree<T>::inorder_traverse_nore  -----


template <class T>
void BinTree<T>::inorder_traverse_nore2 ()
{
    Stack<BinTreeNode<T>*> s;
    BinTreeNode<T>* p = root;
    s.push(p);
    while (!s.isempty())
    {
        while (NULL != (p = s.getTop()))
        {
            s.push(p->get_lchild());
        }
        //-----------------
        //  pop up the void pointer
        //-----------------
        s.pop();
        if (!s.isempty())
        {
            p = s.pop();
            cout << p->get_data() << '\t';
            s.push(p->get_rchild());
        }
    }
    cout << endl;
}		// -----  end of method BinTree<T>::inorder_traverse_nore2  -----


template <class T>
void BinTree<T>::levelorder_traverse ()
{
    Queue<BinTreeNode<T>*> Q;
    BinTreeNode<T>* p = root;
    if (NULL != p)
    {
        Q.enqueue(p);
    }
    while (!Q.isempty())
    {
        p = Q.dequeue();
        cout << p->get_data() << '\t';
        if (NULL != p->get_lchild())
        {
            Q.enqueue(p->get_lchild());
        }
        if (NULL != p->get_rchild())
        {
            Q.enqueue(p->get_rchild());
        }
    }
    cout << endl;
}		// -----  end of method BinTree<T>::levelorder_traverse  -----

template <class T>
void BinTree<T>::destroy (BinTreeNode<T>* current)
{
    if (NULL != current)
    {
        destroy(current->get_lchild());
        destroy(current->get_rchild());
        destroy(current);
    }
}		// -----  end of method BinTree<T>::destroy  -----

template <class T>
void BinTree<T>::create_bintree (istream& is, BinTreeNode<T>*& subtree)
{
    T item;
    if (is >> item)
    {
        if ("#" != item)
        {
            try 
            {
                subtree = new BinTreeNode<T>(item);
                create_bintree(is, subtree->lchild);
                create_bintree(is, subtree->rchild);
            }
            catch (const bad_alloc& ExceptObj) // handle exception:
            {		
                cout << "ERROR: NO ENOUGH MEMORY" << ExceptObj.what() << endl;
            }
        }
        else
        {
            subtree = NULL;
        }
    }
    return ;
}		// -----  end of method BinTree<T>::create_bintree  -----

template <class T>
void BinTree<T>::printout (const BinTreeNode<T>* current) const
{
    if (NULL != current)
    {
        cout << current->get_data();
        if (NULL != current->get_lchild() 
            || NULL != current->get_rchild())
        {
            cout << "(";
            printout(current->get_lchild());
            if (current->get_rchild())
            {
                cout << ",";
            }
            printout(current->get_rchild());
            cout << ")";
        }
    }
}		// -----  end of method BinTree<T>::printout  -----
