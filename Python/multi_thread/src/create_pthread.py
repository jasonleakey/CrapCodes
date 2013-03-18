#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :  create_pthread.py
#  Establishment date:  2009-2-21
#  Author            :  jasonleakey
#  Module Function   :  invoke 
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

import thread #Module thread is deprecated,and use threading better
import time

def thread_fn(data):
    '''This function will be executed by thread'''
    print 'thread function output:%s' % data
    print 'thread will exit in 2s'
    time.sleep(2)
    print 'thread exit...'
    #the following statement is not a must
    exit()

def main():
    try:
        #create a new thread and the thread will execute thread_fn
        #in the 2nd arg ('hello world',) the comma is needed!
        thrd = thread.start_new_thread(thread_fn, ('hello world',))
    except ValueError, e:
        print 'create thread Error:%s' % e
        return 1
    else:
        print 'Main thread sleepays for 5s'
        time.sleep(5)
        print 'Main thread exit...'

if __name__ == '__main__':
    main()