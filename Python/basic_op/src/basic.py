#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	basic.py
#  Establishment date:  2009-2-17
#  Author            :	jasonleakey
#  Module Function   :  test basic operation
#  Copyright (R) 2009jasonleakey
#  <jasonleakey2005@gmail.com>
#  <QQ:174481438>
#  --------------------------------------------------------------------
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.

import types
import struct

def test_enumerate():
	foo = 'abc'
	for i, ch in enumerate(foo):
		print ch, '(%d)' % i
		
def test_swap():
	#swap a with b
	(a, b) = (1, 2)
	(a, b) = (b, a)
	print 'a=%d,b=%d' % (a, b)
	
def test_del():
	#test del
	a = 'abc'
	b = a
	del a
	print b
	
def test_type():
	#the return of type() is also a object
	a = 'string'
	print 'Type a:%s' % str(type(a))
	print 'Type type:%s' % type(type(a))
	
def compare():
	#cmp() is similar to strcmp() in C, but more powerful
	(a, b) = (-4, 12)
	print 'a > b:%s' % cmp(a, b)
	print 'a < b:%s' % cmp(b, a)
	#same as (3 < 4) and (4 < 8)
	print '3 < 4 < 8 = %s' % (3 < 4 < 8)
	
def same_object():
	a = ['gogo', 23, '-28']
	b = a
	c = ['gogo', 23, '-28']
	print 'a=', str(a), '\nb=', str(b), '\nc=' + str(c)
	print '(a is b):%s' % (a is b)
	print '(a is not b):%s' % (a is not b)
	print '(a is c):%s' % (a is c)
	print '(a is not c):%s' % (a is not c)
	#type(65) is identical to types.IntTypes
	print 'type(69) is types.IntTypes:%s' % (type(69) is types.IntType)
	
def execute_str():
	#eval() to execute a string-type statement
	print eval(repr('gogo'))
	
def test_isinstance():
	num = [-69, 9999999999999L, 98.6, -5.2+1.9j, 'xxx']
	for i in num:
		if isinstance(i, (int, long, float, complex)):
			#HOW-TO use type().__name__
			print "%s's type:" % i, type(i).__name__
		else:
			print 'Not a number at all!'

def use_struct():
	buffer = struct.pack('ihb', 1, 2 ,3)
	print repr(buffer)
	print struct.unpack('ihb', buffer)

def test_finally():
	try:
		raise
	except TypeError, e:
		print 'TypeError Occured:%s' % e
		return 1
	finally:
		#although the 'return' is put in 'except'
		#the 'finally' block is also executed
		print 'In finally'

if __name__ == '__main__':
	test_enumerate()
	print
	test_swap()
	print
	test_del()
	print
	test_type()
	print
	compare()
	print
	same_object()
	print
	execute_str()
	print
	test_isinstance()
	print
	use_struct()
	print
	test_finally()