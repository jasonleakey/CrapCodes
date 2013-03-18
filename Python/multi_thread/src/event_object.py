#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Establishment date:  2009-2-26
#  Author            :  jasonleakey
#  Copyright (R) 2009   jasonleakey
#  <jasonleakey2005@gmail.com> <QQ:174481438>
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
#  event_object.py: test event object functions

import threading

class Mythread(threading.Thread):
    def __init__(self, event, threadname):
        self.event = event
        threading.Thread.__init__(self, name = threadname)
    
    def run(self):
        #determine if the internal flag is true
        #similar to condition determinant condition variable
        if self.event.isSet():
            #then clear it,that is,set it False
            #similar to do unlock in condition variable
            self.event.clear()
            #similar to  do wait in condition variable
            self.event.wait()
            print self.getName()
        else:
            print self.getName()
            #similar to  lock in condition variable
            self.event.set()
            
def main():
    #create a event
    event = threading.Event()
    #set its internal flag to True 
    event.set()
    
    thread_list = []
    
    for i in range(10):
        thread = Mythread(event, str(i))
        thread_list.append(thread)
        
    for thread in thread_list:
        thread.start()
        
    for thread in thread_list:
        thread.join()
        
if __name__ == '__main__':
    main()