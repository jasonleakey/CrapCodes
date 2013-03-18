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
#include <fstream>
#include <sstream>
#include <string>
#include "sales_item.h"
#include "query.h"
#include <vector>
#include <map>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <bitset>
#include <stdexcept>
#include <limits>
#include <list>
#include <deque>
#include <canberra.h>



using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using cplusplus_primer::Sales_item;
using std::bitset;
using std::ifstream;
using std::runtime_error;
using std::istream;
using std::numeric_limits;
using std::flush;
using std::ends;
using std::ofstream;
using std::istringstream;
using std::ostringstream;
using std::list;
using std::deque;

namespace A
{
	int bi = 37;
	int bj = 15;
	int bk = 18;
}
int bj = 99;

namespace B
{
	int i;
	int j;
	extern int h;
	class C1
	{
		int i;
		int k;
	public:
		C1() : i(0), k(0) {}
		int f1()
		{
			return k;
		}
		int f2()
		{
			return h; // error: h is not defined
		}
		int f3();
	};
	int h = 1;
}

int B::C1::f3()
{
	return h; // ok.
}

string g_s1("go away");

inline string bool2str(bool expr)
{
	return expr ? "TRUE" : "FALSE";
}

template<class T>
void swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

void print(vector<int>::const_iterator begin,
           vector<int>::const_iterator end)
{
	while (begin != end)
	{
		cout << *begin++;
		if (begin != end)
		{
			cout << " ";
		}
	}
	cout << endl;
}

// return a non-const reference which is a lvalue.
// pay attention to the Default Argument
/* const */ char& get_val(string& str, string::size_type idx = 0)
{
	return str[idx];
}

void manage_io(void)
{
	int ival;
	while (cin >> ival, !cin.eof())
	{
		if (cin.bad()) // input stream is corrupted; bail out
		{
			cout << "IOIOIOIOIO!!!!!!!!!" << endl;
			throw runtime_error("IO stream corrupted");
		}
		if (cin.fail()) // bad input
		{
			cerr << "bad data, try again!";
			cin.clear(/* istream::failbit */); // clear the failbit state and reset the stream.
			cin.ignore(numeric_limits<int>::max(), '\n'); // clear input stream until '\n'
			continue;
		}
	}
}

ifstream& open_file(ifstream& in, const string& filename)
{
	in.close(); // in case it was already open
	in.clear(); // any existing errors
	in.open(filename.c_str(), ifstream::in | ofstream::out);
	if (in)
	{
		return in;
	}
	else
	{
		cerr << "no such file!" << endl;
//		throw runtime_error("cann't open file");
	}
}

void sstream_translate(void)
{
	string word;
	string line;
	while (getline(cin, line))
	{
		istringstream strstream(line);
		int cnt = 0;
		while (strstream >> word)
		{
			++cnt;
			cout << cnt << ". " << word << endl;
		}
	}
}

int sstream_transform_str2int(const string& str)
{
	int result = 0;
	istringstream instr(str);
	instr >> result;
	return result;
}

string sstream_transform_int2str(int integer)
{
	string result;
	ostringstream outstr;
	outstr << integer;
	return outstr.str();
}

int main(int argc, char **argv)
{
	int ival(1024); // direct initialization
	string titleA("C++ primer, 4th edition");
	string all_9(10, '9');
	string &all_line = all_9; // must be initialized
	cout << ival << ' ' << titleA << ' ' << all_line << endl;

	string s1("gay");
	// :: scope operator
	cout << "local:" << s1 << " global:" << ::g_s1 << endl;

	// literal constant
	cout << L"a wide string literal." << endl;
	cout << "a multi-line "
			"string literal "
			"using concatenation!" << endl;

	// section2.3 variables
	int value = 2;
	int pow = 10;
	int result = 1;
	for (int i = 0; i != pow; i++) // pay attention here '!='
	{
		result *= value;
	}
	cout << value
		<< " raised to the power of "
		<< pow << ": \t"
		<< result << endl;

	// namespace
	cplusplus_primer::Sales_item trans1;
	cplusplus_primer::Sales_item trans2;

	namespace Qlib = cplusplus_primer::QueryLib; // namespace alias
	Qlib::Query tq;

	using namespace A;
	++bi;
	++::bj; // global bj
	++A::bj;
	int bk = 92; // local bk hide A::bk
	++bk;

	// const reference
	const int val(1024);
	const int& reval = val;
	// int& reval = val;
	int xj = 10;
	const int& ri = 42;
	const int& go = xj + ri;
	// int& rj = 88; // error: initializer must be an object

	string s0; // empty string
	string s2(s0); // initialize s2 as a copy of s1
	string s3("value");
	string s4(3, 'c');
	cout << s4 << endl;

//	cout << "input two words:";
//	cin >> s2 >> s3;
//	cout << "words you input are: " << s2 << s3 << endl;

//	cout << "input a sentence:";
//	while (cin >> s2) // read until EOF(CTRL_D)
//	{
//		cout << s2 << ' ';
//	}
//	cout << endl;

//	getline(cin, s2);
//	cout << s2 << endl;

	s3 = "some days i make it through.";
	cout << "PROPERTY of string: " << s3 << endl;
	cout << "empty: " << (s3.empty() ? "TRUE" : "FALSE") << endl;
	cout << "size: " << s3.size() << endl;
	cout << "s3[10] = " << s3[10] << endl;
	for (string::size_type i = 0; i != s3.size(); i++)
	{
		cout << s3[i];
	}
	cout << endl;

	string big("big");
	string small("small");
	cout << "big" << (big > small ? ">" : "<=") << "small" << endl;

	string s10("hello");
	string s11("world");
	string s12 = s10 + ", ";
//	string s13 = "hello" + ", "; // the addition between two STRING literals is illegal
	string s14 = s10 + ", " + "world";
//	string s15 = "hello" + ", " + s11; // illegal

	vector<int> ivec4(10, -1);
	vector<string> ivec3(9, "hi");
	vector<string> itemlist;
	cout << "empty vector:" << (itemlist.empty() ? "TRUE" : "FALSE") << endl;
	cout << "size:" << itemlist.size() << endl;
	itemlist.push_back("go back");
	cout << "size:" << itemlist.size() << endl;
	cout << "ivec3 == itemlist: " << (ivec3 == itemlist) << endl;
	for (vector<string>::size_type i = 0; i != ivec3.size(); i++)
	{
		cout << i << ": " << ivec3[i] << endl;
	}
	for (vector<int>::size_type i = 0; i != 10; i++)
	{
		ivec4.push_back(i);
	}
	// use iterator to access element instead of subscript
	//
	// Note that the difference of const_iterator and const iterator
	// that is
	// 		an iterator that cannot write elements
	// 		vector<int>::const_iterator
	// 		an iterator whose value cannot change
	// 		const vector<int>::iterator
	//
	for (vector<int>::const_iterator iter = ivec4.begin();
			iter != ivec4.end(); ++iter)
	{
		cout << *iter << endl;
	}
	const vector<int>::iterator cIter = ivec4.begin();
	// ++cIter; // error!

	// iterator arithmetic
	// iter + n OR iter - n
	// iter2 - iter1 returns a difference_type like size_type
	vector<int>::difference_type dist = (ivec4.end() - 1) - (ivec4.begin() + 3);
	cout << "difference is " << dist << endl;
	// compute the middle element
	vector<int>::iterator mid = ivec4.begin() + ivec4.size() / 2;
	cout << "mid element is " << *mid << endl;

	// define a bitset containing 32 bits, all zeros
	bitset<32> bitvec32;
	string bitstr("01010010110001");
	bitset<16> bitvec16(bitstr); // 0001 0100 1011 0001
	bitset<8> bitvec8(bitstr, 5, 7); // 0010 1100
	cout << "bitset: " << bitvec16 << endl;
	cout << "any: " << bool2str(bitvec16.any()) << endl; // any bit on?
	cout << "none: " << bool2str(bitvec16.none()) << endl; // none bit on?
	cout << "count: " << bitvec16.count() << endl; // number of bits on
	cout << "size: " << bitvec16.size() << endl; // number of all bits
	cout << "b[3]=" << bitvec16[3] << endl; // access bit at the position given
	cout << "b.test(5)=" << bitvec16.test(5) << endl;
	cout << "b.flip(3): " << bitvec16.flip(3) << endl;
	cout << "b[3]=" << bitvec16[3] << endl;

	// use size_t instead of int when iterate
	size_t array_size = 7;

	// exception and handling
	try
	{
		ifstream fp("ok.exe");
		if (!fp)
		{
			throw runtime_error("could not open file: ok.exe");
		}
	}
	catch (runtime_error e)
	{
		cout << "exception expected!" << e.what() << endl;
	}

	int swapA = 5;
	int swapB = 8;
	cout << "before, A=" << swapA << ";B=" << swapB << endl;
	swap(swapA, swapB);
	cout << "after, A=" << swapA << "; B=" << swapB << endl;

	string s9("get out!");
	get_val(s9, 3) = '*';
	cout << "s9=" << s9 << endl;

//	manage_io();

	cout << "MANIPULATOR: flush" << flush; // flush the buffer; adds no data
	cout << "MANIPULATOR: ends" << ends; // insert a null and flush the buffer
	cout << "MANIPULATOR: endl" << endl; // insert a new line and flush the buffer

//	cout << "to be flushed!";
//	cin.tie(&cout); // ties cin to cout
//	int val9;
//	cin >> val9;

	string file("goaway.txt");
	ifstream input;
	open_file(input, file);
	input.close();

//	sstream_translate();
	cout << sstream_transform_int2str(2000) << endl;
	string huge("90000121");
	cout << sstream_transform_str2int(huge) << endl;

	vector<string> slst(12, "lost");
	list<string> slst2(12, "lose"); // copy initialization
	// i don't know why it should use iterator instead of const_iterator here
	vector<string>::iterator middle = slst.begin() + slst.size() / 2;
//  error! list does not support arithmetic addition and substraction.
//	list<string>::const_iterator lmid = slst2.begin() + slst2.size() / 2;
	deque<string> front(slst.begin(), middle); // excluding mid
	deque<string> back(middle, slst.end());
	vector<string> vctval(slst); // copy all element
	vector<string> vctval2(slst.begin(), slst.end()); // copy all element, too.
	char* words[] = {"one", "two", "three", "four", "five"};
	size_t words_size = sizeof(words) / sizeof(char*);
	list<string> words2(words, words + words_size);
	// additional operations on list
	slst2.push_front("first");
	slst2.insert(slst2.begin(), "spouse");
	slst2.insert(slst2.end(), 10, "Anna");
	slst2.insert()


	return 0;
}

