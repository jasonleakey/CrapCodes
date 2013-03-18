#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Aug 25, 2009
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
#  custom_signal.py:  create a custom signal and send it to the callback function

import gobject

### regular Method

#class Sender(gobject.GObject):
#    def __init__(self):
#        self.__gobject_init__()
#
#gobject.type_register(Sender)
#gobject.signal_new('uKi_signal', Sender, gobject.SIGNAL_RUN_FIRST, \
#                   gobject.TYPE_NONE, ())


### the recommended Method

class Sender(gobject.GObject):
    __gsignals__ = {
        'uKi_signal': (gobject.SIGNAL_RUN_FIRST, gobject.TYPE_NONE, ()),
    }
    
    def __init__(self):
        self.__gobject_init__()
        
class Receiver(gobject.GObject):
    def __init__(self, sender):
        self.__gobject_init__()
        sender.connect('uKi_signal', self.cb_uKi)
        
        
    def cb_uKi(self, sender):
            print 'signal uKi received from %s' % sender
            
def user_cb_uKi(object):
    print 'signal uKi handled in function first'

def them_cb_uKi(object):
    print 'signal uKi handled again'
    
def go_cb_uKi(object):
    print 'signal uKi handled finally'
    
if __name__ == '__main__':
    send = Sender()
    receive = Receiver(send) # default handler
    
    send.connect('uKi_signal', user_cb_uKi)
    send.connect('uKi_signal', them_cb_uKi)
    send.connect('uKi_signal', go_cb_uKi)
    send.emit('uKi_signal')