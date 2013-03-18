/*
 *  CPP_practice - TODO
 *
 *  Copyleft(R) by jasonleakey
 *  <jasonleakey@gmail.com>
 *  <QQ:174481438>
 *  --------------------------------------------------------------------
 *  CPP_practice is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  CPP_practice is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with CPP_practice; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 *  --------------------------------------------------------------------
 */

#ifndef QUIRY_H_
#define QUIRY_H_

#include <string>
#include <iostream>

namespace cplusplus_primer
{
	class Query
	{
		Query(const std::string&);
		std::ostream& display(std::ostream&) const;
	};
	class Query_base
	{
		;
	};
}

namespace cplusplus_primer
{
	// the first nested namespace
	// Nested namespaces are useful when a library provider
	// needs to prevent names in each part of a library
	//from colliding with names in other parts of the library.
	namespace QueryLib
	{
		class Query
		{

		};
		Query operator&(const Query&, const Query&);
	}
	// second nested namespace
	class Bookstore
	{
		class Item_base
		{

		};
		class Bulk_item : public Item_base
		{

		};
	};
}

namespace
{
	int i = 0;
}



#endif /* QUIRY_H_ */
