#!/usr/bin/python
# -*- coding: utf-8 -*-

#  File name         :	submodule.py
#  Establishment date:  2009-1-21
#  Author            :	jasonleakey
#  Copyright (R) 2009 jasonleakey 
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

print '程序从此运行!'

if __name__ == '__main__':
	print '此模块不能单独运行!'
else:
	def sayhi():
		print 'Hi, 子模块~'
	version = '0.1'
