#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Establishment date:  2009-2-27
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
#  text_transmit_UDP_server.py: transmit text-based information by UDP mode

from socket import *
import time

(
    HOST,
    PORT,
    BUFSIZE
) = ('127.0.0.1', 17911, 4096)
(ADDR) = ((HOST, PORT))

def main():
    #create a socket with mode UDP
    sock = socket(AF_INET, SOCK_DGRAM)
    #bind the IP address and port
    sock.bind(ADDR)
    
    while True:
        try:
            print 'wait...'
            (data, client_info) = sock.recvfrom(BUFSIZE)
            current_time = time.ctime()
            print '[%s]client(%s:%s) say:%s'\
                % (current_time, client_info[0], client_info[1], data)
            sock.sendto('server receive ' + data + ' at [%s]'\
                        % current_time, client_info)
        except KeyboardInterrupt:
            print 'Server is terminated!'
            sock.close()
            return 1
    sock.close()

if __name__ == '__main__':
    main()