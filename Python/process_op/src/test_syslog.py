#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	test_syslog.py
#  Establishment date:  2009-2-14
#  Author            :	jasonleakey
#  Module Function   :  test how to log infomation into log_files.
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

import syslog
import sys

def main():
	'''test openlog,syslog,closelog'''
	
	syslog.openlog(sys.argv[0], syslog.LOG_CONS | syslog.LOG_PID, syslog.LOG_USER)
	
	for i in range(5):
		syslog.syslog(syslog.LOG_INFO, "%d. log here..." % i)
	
	syslog.closelog()

if __name__ == '__main__':
	main()