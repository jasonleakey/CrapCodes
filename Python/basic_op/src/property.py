#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Aug 24, 2009
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
#  property.py: how to use property()

class C(object):
    def __init__(self, data):
        self._x = data
    
#    @property
#    def x(self):
#        '''look at x!'''
#        return self._x
    def __pro
    
    @property
    def x(): #@NoSelf
        doc = """look at there""" #@UnusedVariable
       
        def fget(self):
            return self._x
           
        def fset(self, value):
            self._x = value
           
        def fdel(self):
            del self._x
           
        return locals()
       
#    x = property(**x())
#    def x(self, newValue):
#        self._x = newValue
#    
#    @x.deleter
#    def x(self):
#        del self._x
        
    #x = property(getx, setx, delx, 'look at x!')
        
if __name__ == '__main__':
    log = C(0.9)
    print log.x
    log.x = 6
    print log.x
    print log.__doc__
    del log.x
    