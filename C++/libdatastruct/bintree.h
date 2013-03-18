// =====================================================================================
// 
//       Filename:  bintree.h
// 
//    Description:  the declaration of binary tree
// 
//        Version:  1.0
//        Created:  08/31/2011 03:13:17 PM
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


#ifndef  BINTREE_H_
#define  BINTREE_H_


#include	<iostream>
#include	<cstdlib>
using namespace std;
template < class T > class BinTree;

typedef enum {
    LEFT,
    RIGHT,
} Direct;				// ----------  end of enum Direct  ----------

// =====================================================================================
//        Class:  BinTreeNode
//  Description:  the node class in binary tree
// =====================================================================================

template < class T >
class BinTreeNode
{
    public:
        // ====================  LIFECYCLE     =======================================
        BinTreeNode(const T& val = NULL, BinTreeNode<T>* lptr = NULL,
         BinTreeNode<T>* rptr = NULL) : data(val), lchild(lptr), rchild(rptr)
        {
        } // constructor
        BinTreeNode(const BinTreeNode<T>& other);// copy constructor

        // ====================  ACCESSORS     =======================================
        T get_data() const { return data; }
        void set_data(const T& val) { data = val; }
        BinTreeNode<T>* get_lchild() const { return lchild; }
        void set_lchild(BinTreeNode<T>* ptr) { lchild = ptr; }
        BinTreeNode<T>* get_rchild() const { return rchild; }
        void set_rchild(BinTreeNode<T>* ptr) { rchild = ptr; }

        // ====================  MUTATORS      =======================================

        // ====================  OPERATORS     =======================================
        BinTreeNode<T>& operator = (const BinTreeNode<T>& other); // assignment operator


    private:
        // ====================  DATA MEMBERS  =======================================
        T data;
        BinTreeNode<T>* lchild;
        BinTreeNode<T>* rchild;
    friend class BinTree<T>;
}; // -----  end of template class BinTreeNode  -----


// =====================================================================================
//        Class:  BinTree
//  Description:  The class declaration for binary tree
// =====================================================================================

template < class T >
class BinTree
{
    public:
        // ====================  LIFECYCLE     =======================================
        BinTree() : root(NULL) {}                           // constructor
        BinTree (const BinTree &other); // copy constructor
        ~BinTree() // destructor
        {
            destroy(root);
        }

        // ====================  ACCESSORS     =======================================
        bool isempty() const
        {
            return (NULL == root);
        }
        BinTreeNode<T>* get_root() const
        {
            return root;
        }
        const BinTreeNode<T>* parent(const BinTreeNode<T>* current) const
        {
            return (NULL == root || current == root ? NULL : parent(root, current));
        }
        int depth() const; // get the max depth of binary tree

        // ====================  MUTATORS      =======================================
        BinTreeNode<T>* get_leftsibling(const BinTreeNode<T>* current);
        BinTreeNode<T>* get_rightsibling(const BinTreeNode<T>* current);

        // ====================  OPERATORS     =======================================
        bool insertchild(const BinTreeNode<T>* current, Direct d, const BinTree<T>* other);
        bool deletechild(const BinTreeNode<T>* current, Direct d); 
        void preorder_traverse() 
        {
            preorder_traverse(root);
            cout << endl;
        }
        void inorder_traverse()
        {
            inorder_traverse(root);
            cout << endl;
        }
        void postorder_traverse()
        {
            postorder_traverse(root);
            cout << endl;
        }
//        non-recursive method of preorder traversal 
        void preorder_traverse_nore();
        void preorder_traverse_nore2();
        void preorder_traverse_nore3();
        void inorder_traverse_nore();
        void inorder_traverse_nore2();
        void postorder_traverse_nore();
        void levelorder_traverse();

        BinTree& operator = (const BinTree& other); // assignment operator

        friend ostream& operator << (ostream& os, const BinTree<T>& obj)
        {
            os << "先序输出二叉树:" << endl;
            obj.printout(obj.root);   
            return os;
        } // -----  end of function operator <<  -----
        friend istream& operator >> (istream& is, BinTree<T>& obj)
        {

            cout << "先序构造二叉树" << endl;
            obj.create_bintree(is, obj.root);
            return is;
        }		// -----  end of function operator >>  -----

    private:
        // ====================  DATA MEMBERS  =======================================
        BinTreeNode<T>* root;

        // ====================  PRIVATE OPERATORS ==============
        const BinTreeNode<T>* parent(const BinTreeNode<T>* start, const BinTreeNode<T>* current) const;
        void destroy(BinTreeNode<T>* current); 
        void preorder_traverse(const BinTreeNode<T>* current);
        void inorder_traverse(const BinTreeNode<T>* current);
        void postorder_traverse(const BinTreeNode<T>* current);
        void create_bintree(istream& is, BinTreeNode<T>*& subtree);
        void printout(const BinTreeNode<T>* current) const;

}; // -----  end of template class BinTree  -----


#include	"bintree.cpp" // include the implementation
#endif   // ----- #ifndef BINTREE_H_ -----
