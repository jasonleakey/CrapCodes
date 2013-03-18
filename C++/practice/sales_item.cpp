/*
 *  CPP_practice - TODO
 *  
 *  Copyleft(R) by jasonleakey
 *  <jasonleakey@gmail.com>
 *  <QQ:174481438>
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

#include <iostream>
#include "sales_item.h"

namespace cplusplus_primer
{
	// definition of Sales_item members and overloaded operators
	// members definition inside namespace
	std::istream& operator >>(std::istream& in, Sales_item& s)
	{
		//...
	}
}

// members definition outside namespace
// the definition should specify the namespace
cplusplus_primer::Sales_item cplusplus_primer::operator +(
		const Sales_item& lhs, const Sales_item& rhs)
{
	Sales_item ret(lhs);
	// ..
}
