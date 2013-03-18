/*
 *  CPP_basic - TODO
 *  Change Log:
 *  Copyleft(R) by jasonleakey
 *  <jasonleakey@gmail.com>
 *  <QQ:174481438>
 *  --------------------------------------------------------------------
 *  CPP_basic is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  CPP_basic is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with CPP_basic; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 *  --------------------------------------------------------------------
 */

#ifndef STACK_H_
#define STACK_H_

class Stack
{
		int max;
		int sp;
		float *stk;
public:
//		constructor and destructor
		Stack(int size);
		virtual ~Stack();
//		methods
		bool clear_stack();
		float top() const;
		bool is_stack_empty() const;
		int length() const;
		bool is_stack_full() const;
		bool push(float a);
		float pop();
		void traverse();
};

#endif /* STACK_H_ */
