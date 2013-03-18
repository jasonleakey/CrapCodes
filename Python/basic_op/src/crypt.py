#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Date:  Nov 15, 2009
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
#  crypt.py: encrypt and decrypt password

from __future__ import with_statement
import base64
import os
import os.path


class Pwd():
    def __init__(self, file = '/home/jasonleakey/GeekDocument/.psw'):
        try:
            self.doc = open(file, 'r+')
        except IOError, e:
            print 'IOError: %s' % e
            exit(1)

    def __del__(self):
        self.doc.close()

    def encrypt(self):
        codedStr = []
        for line in self.doc:
            codedStr.append(base64.b64encode(line.rstrip()) + '\n')
        self.doc.seek(0, os.SEEK_SET)
        self.doc.truncate()
        self.doc.writelines(codedStr)

    def decrypt(self):
        dcodedStr = []
        for line in self.doc:
            dcodedStr.append(base64.b64decode(line.rstrip()) + '\n')
        self.doc.seek(0, os.SEEK_SET)
        self.doc.truncate()
        self.doc.writelines(dcodedStr)

if __name__ == '__main__':
    pwd = Pwd()
    sel = raw_input('encrypt or decrypt(1/2)?')
    if sel == '1':
	    pwd.encrypt()
    elif sel == '2':
	    pwd.decrypt()
    else:
        print 'invalid input'



