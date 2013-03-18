#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Aug 16, 2009
#  Author:  jasonleakey
#  Change log:
#  Copyleft(R) by jasonleakey
#  <jasonleakey@gmail.com>
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
#  --------------------------------------------------------------------
#  classPractice.py: learning how to define and use class

from time import *

class Myclass(): #new-style class
    def ok(self):
        print 'here is', self.__class__.__name__

class Goodboy(Myclass):
    def ok(self):
        #super(Goodboy, self).ok() #new-style class
        Myclass.ok(self)          #classic class 
        print 'there is Goodboy'

class RoundFloatManual(object):
    def __init__(self, var):
        assert isinstance(var, float), "Value must be float"
        self.value = round(var, 2)
    
#    def __repr__(self):
#        return str(self.value)
    
    def __str__(self):
        return '%.2f' % self.value
    
    __repr__ = __str__
    
class Time60():
    def __init__(self, hour = 0, min = 0):
        self.hour = hour
        self.min = min
    
    def __str__(self):
        return '%d:%d' % (self.hour, self.min)     
    
    def __add__(self, other):
        return self.__class__((self.hour + other.hour) % 24,\
                              (self.min + other.min) % 60)
    
    def __iadd_(self, other):
        self.hour += other.hour
        self.min += other.min
        return self
          
class AnyIter():
    def __init__(self, data, safe = False):
        self.iter = iter(data)
        self.bSafe = safe
        
    def __iter__(self):
        return self
    
    def next(self, howmany = 1):
        retval = []
        for eachItem in range(howmany):
            try:
                retval.append(self.iter.next())
            except StopIteration:
                if self.bSafe:
                    break
                else:
                    raise 
        return retval

class NumStr():
    def __init__(self, num = 0, str = ''):
        self.__num = num
        self.__str = str
    
    def __str__(self):
        return '[%d :: %s]' % (self.__num, self.__str)
    __repr__ = __str__
    
    def __add__(self, other):
        if isinstance(other, NumStr):
            return self.__class__(self.__num + other.__num,\
                                  self.__str + other.__str)
        else:
            raise TypeError, 'illegal argument'
    
    def __mul__(self, num):
        if isinstance(num, int):
            return self.__class__(self.__num * num, self.__str * num)
        else:
            raise TypeError, 'illegal argument'
        
    def __nonzero__(self):
        return self.__num != 0 or self.__str != ''
    
#    def __norm_cval(self, cmpres):
#        return cmp(cmpres, 0)
#    
    def __cmp__(self, other):
        return cmp(cmp(self.__num, other.__num) \
                   + cmp(self.__str, other.__str), 0)
        
class WrappedType():
    def __init__(self, data):
        self.__data = data
        
    def get(self):
        return self.__data
    
    def __repr__(self):
        return `self.__data`
    
    def __str__(self):
        return str(self.__data)
    
    def __getitem__(self, key):
        return self.__data[key]
    
    def __getattr__(self, attr):
        return getattr(self.__data, attr)
    
    
class TimeWrapMe():
    def __init__(self, data):
        self.__data = data
        self.__ctime = self.__mtime = self.__atime = time()
    
    def get(self):
        self.__atime = time()
        return self.__data
    
    def set(self, obj):
        self.__data = obj
        self.__mtime = self.__atime = time()
    
    def gettimeval(self, time_t):
        if not isinstance(time_t, str) or time_t[0] not in 'cma':
            raise TypeError, 'illegal time type,"c", "m", or "a" are needed'
        else:
            return getattr(self, '_%s__%stime' % (self.__class__.__name__, \
                                                 time_t[0]))
    
    def gettimestr(self, time_t):
        return ctime(self.gettimeval(time_t))
    
    def __repr__(self):
        self.__atime = time()
        return `self.__data`
    
    def __str__(self):
        self.__atime = time()
        return str(self.__data)
    
    def __getattr__(self, attr):
        self.__atime = time()
        return getattr(self.__data, attr)
    
class CapOpen():
    def __init__(self, filename, mode):
        self.file = open(filename, mode)
    
    def __str__(self):
        return str(self.file)
    __repr__ = __str__
    
    def write(self, data):
        self.file.write(data.upper())
        
    def __getattr__(self, attr):
        return getattr(self.file, attr)
        
if __name__ == '__main__':
#    mc = Myclass()
#    mc.ok()
#    md = Goodboy()
#    md.ok()

#    rfm = RoundFloatManual(3.695)
#    rfm
#    rfm = RoundFloatManual(42)
#    print rfm.__str__()

#    mytime1 = Time60(21, 17)
#    mytime2 = Time60(22, 33)
#    mytime3 = Time60(12, 59)
#    print mytime1, mytime2, mytime3
#    print 'sum =', mytime1 + mytime2 + mytime3
#    mytime1 += mytime2
#    print 'new_mytime1 =', mytime1 

#    a = AnyIter(range(1, 9), True)
#    it = iter(a)object
#    for i in range(1, 5):
#        print i, ':', it.next(i)
    
#    ns1 = NumStr(9, 'go ahead!')
#    ns2 = NumStr(3, 'hey, come on~')
#    print ns1, ns2
#    print ns1 + ns2
#    print ns2 * 3
#    print ns1 == ns2

#    wrappedComplex = WrappedType(3.2 + 9.4j)
#    print repr(wrappedComplex)
#    print wrappedComplex
#    print wrappedComplex.real
#    print wrappedComplex.imag
#    print wrappedComplex.conjugate()
#    print wrappedComplex.get()
#    wrappedList = WrappedType(['ben', 5.3, 91])
#    wrappedList.append('google')
#    wrappedList.append('toolbar')
#    wrappedList.append(5.3)
#    print repr(wrappedList)
#    print wrappedList
#    print wrappedList.index(91)
#    print wrappedList.count(5.3)
#    print wrappedList
#    print wrappedList[1:4]

#    timeWrappedObj = TimeWrapMe(392)
#    print 'ctime:', timeWrappedObj.gettimestr('c')
#    print 'mtime:', timeWrappedObj.gettimestr('m')
#    print 'atime:', timeWrappedObj.gettimestr('a')
#    print 'waiting 3.3s...'
#    sleep(3.3)
#    print timeWrappedObj
#    print 'ctime:', timeWrappedObj.gettimestr('c')
#    print 'mtime:', timeWrappedObj.gettimestr('m')
#    print 'atime:', timeWrappedObj.gettimestr('a')
#    print 'waiting 1s...'
#    sleep(1)
#    timeWrappedObj.set('time is up')
#    print 'mtime:', timeWrappedObj.gettimestr('m')
#    print 'waiting 2.3s...'
#    sleep(2.3)
#    timeWrappedObj
#    print 'ctime:', timeWrappedObj.gettimestr('c')
#    print 'mtime:', timeWrappedObj.gettimestr('m')
#    print 'atime:', timeWrappedObj.gettimestr('a')

    f = CapOpen('/home/jasonleakey/test.txt', 'a')
    f.write('how are you?\n')
    f.write('fine, and you\n')
    f.write("I'm OK.\n")
    f.close()
    print f