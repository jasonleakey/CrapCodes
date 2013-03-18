#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	>>.py
#  Establishment date:  2009-2-17
#  Author            :	jasonleakey
#  Module Function   :  test '>>' to redirect
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

import sys

#redirect output to stderr
print >> sys.stderr, 'This is stderr'

try:
	#append
	fd = open('./redirect.log', 'a')
except IOError, e:
	print 'IOError:%s' % e
else:
	print >> fd, 'Error Occured!'
	fd.close()
