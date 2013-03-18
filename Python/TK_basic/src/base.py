#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  File name         :	base.py
#  Establishment date:  2009-1-24
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

import pygtk
pygtk.require('2.0')
import gtk

class Base:
	def destroy(self, widget, data = None):
		'''
		destory信号的回调函数
		@param widget:
		@param data:
		'''
		print 'destroy occured'
		gtk.main_quit()

	def hello(self, widget, data):
		'''
		clicked信号的回调函数
		@param widget:
		@param data:
		'''
		print 'hello ' + data + ' this is a button clicked() test!'

	def delete_event(self, widget, event, data = None):
		'''
		如果delete_event返回假,则会触发destroy信号,从而关闭窗口
		如果返回真,则不会关闭窗口,这个特性在当我们在关闭窗口需要确认时很有用
		@param widget:
		@param event:
		@param data:
		'''
		print 'delete event occured'
		return False

	def __init__(self):
		self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
		#设置delete_event信号由delete_event函数处理
		self.window.connect('delete_event', self.delete_event)
		#设置delete信号触发delete函数
		hander_destroy = self.window.connect('destroy', self.destroy)
		print 'hander_destroy is %s' % hander_destroy
		self.window.set_title('PyGTK test')
		self.window.set_default_size(200, 200)
		self.window.set_border_width(100)
		#控制窗口出现的位置
		self.window.set_position(gtk.WIN_POS_CENTER)
		
		
		#生成按钮实例
		self.button1 = gtk.Button()
		self.button2 = gtk.Button()
		self.button1.set_label('label1')
		self.button2.set_label('label2')
		#设置按钮的clicked信号触发hello函数，并传递‘pyGTK’字符串参数给hello函数
		handler2 = self.button1.connect("clicked", self.hello, "pyGTK")
		print "handler2 is:%d" % handler2
		#设置按钮的clicked信号触发self.window对象的gtk.Widget.destroy方法
		self.button1.connect_object("clicked", gtk.Widget.destroy, self.window)
		#使用object.disconnect(id)方法取消handler2的功能
		#self.button.disconnect(handler2)
		#设置一个不可见的横向的栏位self.box1
		self.box1 = gtk.HBox(False, 0)
		#把box1放到窗口中
		self.window.add(self.box1)
		#把button1部件放到box1中
		self.box1.pack_start(self.button1, True, True, 0)
		self.button1.show()
		#把button2部件放到button1部件之后
		self.box1.pack_start(self.button2, True, True, 0)
		self.button2.show()
		self.box1.show()
		self.window.show()
	def main(self):
		gtk.main()

print __name__
if __name__ == '__main__':
	base = Base()
	base.main()
