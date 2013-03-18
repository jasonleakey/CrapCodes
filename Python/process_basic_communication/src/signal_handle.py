#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :  signal_handle.py
#  Establishment date:  2009-2-19
#  Author            :  jasonleakey
#  Module Function   :  capture and handle or ignore signals 
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

import signal
import sys

def handler(signum, frame):
    '''handler function of signal'''
    print 'Got the %d signal...' % signum

def main():
    #ignore signal SIGINT
    signal.signal(signal.SIGINT, signal.SIG_IGN)
    #link signal SIG_USR1 with handler
    signal.signal(signal.SIGUSR1, handler)
    
    signal.pause()
    
if __name__ == '__main__':
    main()