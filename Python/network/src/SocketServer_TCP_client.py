#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Establishment date:  2009-2-28
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
#  SocketServer_TCP_client: create a client version 2

from socket import *

(
    HOST, 
    PORT,
    BUFSIZE
) = ('127.0.0.1', 21999, 4096)

def main():
    while True:
        sock = socket(AF_INET, SOCK_STREAM)
        try:
            sock.connect((HOST, PORT))
        except errno, e:
            print 'connect server Error:%s' % e
            sock.close()
            return 1
        try:
            data = raw_input('>>')
        except KeyboardInterrupt:
            print 'Client is terminated!'
            return 1
        else:
            if not data:
                print 'No data is input!'
                break
            sock.send('%s\r\n' % data)
            recv_data = sock.recv(BUFSIZE)
            if not recv_data:
                print 'No data is received!'
                break
            print recv_data.strip()
        finally:
            sock.close()
        
if __name__ == '__main__':
    main()