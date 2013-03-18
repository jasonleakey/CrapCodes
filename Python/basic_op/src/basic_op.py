#!/usr/bin/python
# -*- coding: utf-8 -*-

#  File name         :	basic_op.py
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



print '******************'
print "    猜数字游戏"
print '******************'
nGuessNum = 23
bGuessed = False

while not bGuessed:
    nGes = int(raw_input('请输入一个整数:'))
    if nGes == nGuessNum:
        print '猜对了!'
        bGuessed = True
    elif nGes > nGuessNum:
        print '偏大!'
    else:
        print '偏小!'
else:
    print '循环结束!'
print '程序结束!\n'

print '***************************'
print '   测试默认参数值'
print '***************************'
def say(message, time = 1):
    print message * time
say('Hello')
say('World', 5)
print '\n'

print '***************************'
print '   测试关键参数'
print '***************************'
def key_prt(a, b = 5, c = 10):
    print 'a =', a, '\tb =', b, '\tc =', c
key_prt(3, 8)
key_prt(6, c = 32)
key_prt(a = 9, c = 22)

print '***************************'
print ' 测试文档字符串(DocStrings)'
print '***************************'
def print_max(a, b):
	'''此函数用于打印两者最大值,传递的两数必须是整形数'''
	a = int(a)	#如果是非整形且可以转化成整形,将其转化
	b = int(b)
	
	if a >= b:
		print 'Max =', a
	else:
		print 'Max =', b

print_max(2, 4)
#print print_max.__doc__ #两者作用相同
#print help(print_max)

print '***************************'
print '   测试模块的装入'
print '***************************'
import sys	#导入sys.py模块

print 'The Command Line arguments is'
for i in sys.argv:
	print i

print '\n\nPYTHON_PATH is', sys.path, '\n'


print '***************************'
print '   测试模块的__name__作用'
print '***************************'

if __name__ == '__main__':
	print '此模块由用户单独运行'
else:
	print '此模块被其他模块导入'
print '\n'

print '***************************'
print '   测试导入其他模块'
print '***************************'
import submodule
from submodule import sayhi, version	#一般避免这样使用,应使用import
sayhi()
print submodule.__file__	#子模块的成员变量,即绝对路径
print submodule.__name__	#导入子模块的话,子模块的__name__为模块名
print 'Version is', version, '\n'

print '***************************'
print '   测试dir函数的作用'
print '***************************'
#dir函数来列出模块定义的标识符。标识符有函数、类和变量。
print dir(sys)
print dir()
a = 4
a		#无效表达式,没有任何效果,如果是交互式终端,则会输出a的值
print dir() #定义了a后,此dir()的结果将比下一个dir()多一个a
del a
print dir()

print '***************************'
print '   列表的使用-购物单'
print '***************************'
#定义购物单-列表, 用方括号
shoplist = ['apple', 'banana', 'pear', 'orange']

print '购物单里有', len(shoplist), '样物品\n它们分别是',
for item in shoplist:
	print item, 		#注意item后的逗号,可使item输出在同一行,逗号本身不输出

shoplist.append('water melon')
print '更新后的购物单:', shoplist

shoplist.sort()
print '经排列后的购物单:', shoplist

print '第一件要买的物品是:', shoplist[0]
oldItem = shoplist[0]
del shoplist[0]
print '已经买了', oldItem
print '现在购物单如下:', shoplist


print '***************************'
print '   元组的使用方法'
print '***************************'
#定义三元组, 用圆括号
zoo = ('monkey', 'donkey', 'lion')

print '动物园里有', len(zoo), '种动物'
print '它们分别是',
for animal in zoo:
	print animal,
print '\n'

#定义另一个三元组,且包含上个三元组,类似广义表
new_zoo = ('tiger', 'deer', zoo)
print '新式动物园里有', len(new_zoo), '种动物'
print '它们分别是', new_zoo
print '其中原来的动物园里动物有', new_zoo[2]
print '原来动物园里最后一种动物是', new_zoo[2][2]

print '***************************'
print '   元组的应用-输出的定制'
print '***************************'
age = 22
name = 'jasonleakey'
print '%s\'s age is %d' % (name, age)
print 'why is %s playing with Python?' % name

print '***************************'
print '   字典的使用'
print '***************************'
#ab is short for 'a'ddress'b'ook
#其实函数的参数表本身就是一字典
ab = {	'Bob' : 'bob@gmail.com',
		'lele': 'lele@sohu.com',
		'Chen':	'chenzh@sina.com',
		'Yao' : 'yaoyuan@163.com'
	 }
print "lele's address is", ab['lele']
print "Chen's address is %s" % ab['Chen']

#加记录-一组"键"和"值"
ab['Jason'] = 'jasonleakey@sohu.com'
#删除一组记录
del ab['lele']
print "There are %d contacts in the addbook" % len(ab)
print "They are"
for (name, address) in ab.items():
	print "Contact %s at %s" % (name, address)

if 'Yao' in ab: #等价于 if ab.has_key('Yao')
	print "Yao's address is %s" % ab['Yao']


print '***************************'
print '   序列的含义'
print '***************************'
#序列的两个特殊术语:索引操作符和切片操作符
#索引操作符(Index)让我们可以从序列中抓取一个特定项目
#切片操作符(Slice)让我们能够获取序列的一个切片，即一部分序列。
surName = ['wang', 'lee', 'huang', 'zhong']
#索引在列表中的使用
print 'item 0 is %s' % surName[0]
print 'item 1 is %s' % surName[1]
print 'item 2 is %s' % surName[2]
print 'item 3 is %s' % surName[3]
print 'item -1 is %s' % surName[ - 1]
print 'item -2 is %s' % surName[ - 2]
#索引在字符串中的使用
chStr = 'UbuntuLinux'
print 'letter 1 is %c' % chStr[1]

#在列表中使用分片
print 'item 1 to 3 is %s' % surName[1 : 3]
print 'item 2 to end is', surName[2 :]
print 'item 1 to -1 is', surName[1 : -1]
print 'item start to end is', surName[:]

#在字符串使用分片
print 'substr 1 to 3 is', chStr[1 : 3]
print 'substr 2 to end is %s' % chStr[2 :]
print 'substr 5 to -2 is', chStr[5 : -2]
print 'substr start to end is', chStr[:]
print 'substr 4 to 8 is', chStr.__getslice__(4, 8)

print '***************************'
print '   参考的含义'
print '***************************'
#参考的两复杂变量指向同一块内存
oldArr = ['chen', 'zhu', 'yang', 'fang', 'huang']
newArr = oldArr    #newArr只是oldArr的一个别名,两者指向同一个列表
#所以两者打印结果应是一致的
del oldArr[0]
print 'reference, List oldArr is', oldArr
print 'reference, List newArr is', newArr
#使用分片复制变量内容
newArr = oldArr[:]
del oldArr[0]
print 'copy, List oldArr is', oldArr
print 'copy, List newArr is', newArr

print '***************************'
print '   字符串的方法的应用'
print '***************************'
testStr = 'Linux for Human beings'
if testStr.__contains__('hum'):
	print "testStr contains 'hum'"
print '__len__()', testStr.__len__()	#求字符串长度,不含'\0'
print testStr.__str__() #???
print "zfill():", testStr.zfill(30)	#字符前填补'0'字符使用字数满足30
print 'upper():', testStr.upper()
print "titlecase():", testStr.title()	#将每个单词首字母大写
print "swapcase():", testStr.swapcase()	#将大小母调换
print "strip():", testStr.strip('Lisnugao ')	#从首尾开始依次寻找并删除形参内的字符
if testStr.startswith("Lin"):
	print "testStr is start with 'Lin'"	#判断字符串是否以某字符串开头
if 'o' in testStr:
	print "testStr contains 'o'"
#合并两个字符串,将sepstr加入到testStr元素之间
sepstr = '_*_'
print "join():", sepstr.join(testStr)
srchName = ['google', 'baidu', 'yahoo', 'sogou']
print "join():", sepstr.join(srchName)

####等等

print '***************************'
print '   类的基本使用'
print '***************************'
class Personnel:
	def __init__(self, name = 'Jasonleakey'): #类似于C++中的构造函数
		self.name = name	#创建一个新域name
	def __del__(self):
		'''析构函数'''
		print 'I am dead'
	def sayHi(self):	#成员函数,self指向类本身
		print 'how are you?'
		print 'My name is', self.name
p = Personnel() #定义p为Person类的对象,此处参数为空,即使用默认参数值
p.sayHi()
del p

print '***************************'
print '   类的变量和对象的变量'
print '***************************'
class Person():
	'''代表人类'''
	population = 0	#现有人数
	def __init__(self, name):
		'''人出生,构造基本信息'''
		self.name = name
		print '(Initializing %s)' % self.name
		
		#当人出生时,人数增加
		Person.population += 1
	def __del__(self):
		'''人死亡,析构基本信息'''
		print '%s says bye' % self.name
		Person.population -= 1
		if Person.population == 0:
			print 'I am the last one'
		else:
			print 'There are still %d people left' % Person.population
			
	def sayHi(self):
		'''打招呼'''
		print 'Hi, My name is %s', self.name
	
	def howmany(self):
		'''输出现有人数'''
		if Person.population == 0:
			print 'There is no people'
		elif Person.population == 1:
			print 'There is only one people left'
		else:
			print 'There are %d individuals left' % Person.population

chenzh = Person('chenzh')
chenzh.sayHi()
chenzh.howmany()

zhongYQ = Person('zhongYQ')
zhongYQ.sayHi()
zhongYQ.howmany()

chenzh.sayHi()
chenzh.howmany()
del chenzh
del zhongYQ

print '***************************'
print '   继承(超类和子类)'
print '***************************'
#Teacher类和Student类继承SchoolMember类
class SchoolMember():
	'''represent any school member'''
	def __init__(self, name, age):
		self.name = name
		self.age = age
		print '(Initialized school member:%s)' % self.name
	def tell(self):
		'''tell my details'''
		print 'My name:%s, My age:%s' % (self.name, self.age)

class Teacher(SchoolMember):	#继承的使用方法,即超类作为一个元组跟在定义类之后
	'''represent a teacher'''
	def __init__(self, name, age, Salary):
		SchoolMember.__init__(self, name, age)
		self.salary = Salary
		print '(Initialized Teacher:%s)' % self.name
	def tell(self):
		'''tell teachers' details'''
		SchoolMember.tell(self)
		print 'My Salary is', self.salary

class Student(SchoolMember):
	'''represent a student'''
	def __init__(self, name, age, Marks):
		SchoolMember.__init__(self, name, age)
		self.marks = Marks
		print '(Initialized Student:%s)' % self.name
	def tell(self):
		'''tell students' details'''
		SchoolMember.tell(self)
		print 'My Marks is', self.marks

pys = Teacher('panyongsuo', 38, 4000)
hyt = Student('Huang Ye Tian', 21, 89)

print	#打印一个空行

members = [pys, hyt]
for memb in members:
	memb.tell()


print '***************************'
print '   测试文件类的使用'
print '***************************'
poem = '''\
Programming is fun
When the work is done
if you wanna make your work also fun
		use Python!
'''
#往open_poem.txt写入poem字符串
f = file('/home/jasonleakey/open_poem.txt', 'w') #定义f为为file类
f.write(poem)	#写入字符串
f.close()	#关闭文件

f = file('/home/jasonleakey/open_poem.txt')	#如果未指定模式,默认为'r',即只读
while True:
	line = f.readline()	#读取一行字符
	if len(line) == 0:	#如果只读到一个换行符,则退出
		break
	print line,
f.close()

print '***************************'
print '   存储器模块的使用'
print '***************************'
import cPickle as pk	#存储器模块,import..as..pk是cPickle的别名,图方便
#import pickle as pk

shoplistfile = '/home/jasonleakey/shop.dat'

shoplist = ['apple', 'mango', 'carrot']

f = file(shoplistfile, 'w')
pk.dump(shoplist, f)	#dump the object to a file
f.close()

del shoplist	#remove the shoplist

f = file(shoplistfile)
storedlist = pk.load(f)	#read back from the file
print storedlist
f.close()


print '***************************'
print '   异常的捕获'
print '***************************'
import sys

try:
	s = raw_input('Enter something-->')
except EOFError:	#按下CTRL_D抛出的异常
	print '\nWhy did you do an EOF on me?'
	sys.exit()
except:		#未抛出异常
	print '\nSome Exception occured'
print 'Done'

print '***************************'
print '   自定义异常类'
print '***************************'
#ShortInputException继承自Exception类
class ShortInputException(Exception):
	'''用户自定义异常类,'''
	def __init__(self, length, atleast):
		Exception.__init__(self)
		self.length = length
		self.atleast = atleast

try:
	s = raw_input('Input something-->')
	if len(s) < 3:
		raise ShortInputException(len(s), 3)	#如果输入字数小于3,raise抛出异常
	#对于其他输入正常
except EOFError:
	print '\nWhy did you do an EOF on me?'
except ShortInputException, x:	#将(len(s), 3)传于x,类似函数调用
	print 'ShortInputException: your Input is length %d,'\
		'was expecting at least %d' % (x.length, x.atleast)
except:
	print 'No exception was raised!'

print '***************************'
print '   try..finally的使用方法'
print '***************************'
import time

try:
	f = file('/home/jasonleakey/open_poem.txt')
	while True:
		line = f.readline()
		if len(line) == 0:
			break
		time.sleep(0.2)
		print line,
#不管是否抛出异常,finally语句都会被执行
finally:
	f.close()
	print 'Cleaning up...Closed the file'

print '***************************'
print '   测试os模块的使用'
print '***************************'

import os

#os.name返回正在使用的平台
print os.name
#os.getcwd()返回当前目录
print os.getcwd()
#os.getenv和os.putenv分别用来读取和设置环境变量
#print os.getenv(key, default)
#os.listdir返回指定目录下所有目录和文件名
print 'file in home directory:', os.listdir('/home/jasonleakey/project')
#os.remove用来删除指定文件
#os.path.exists()检验路径是否存在
del_file_name = '/home/jasonleakey/dele.txt'
if os.path.exists(del_file_name):
	os.remove('/home/jasonleakey/dele.txt')
	print '%s has been deleted' % del_file_name
else:
	print 'No such file or directory:%s' % del_file_name
#os.system()用来运行shell命令
print 'ls -l result:\n', os.system('ls -l')
#os.linesep给出当前平台的行终止符
print '行终止符:', os.linesep
#os.path.split()返回一个路径的目录名和文件名
print '将/home/jasonleakey/open_poem.txt分成目录和文件名:'
print os.path.split('/home/jasonleakey/open_poem.txt')
#os.path.isdir()和os.path.isfile()分别检验是目录还是文件

print '***************************'
print '   列表综合'
print '***************************'
listone = [2, 3, 4]
listtwo = [2 * i for i in listone if i > 2]

print listtwo

print '***************************'
print '   函数中接收元组和列表'
print '***************************'
#在函数中接收元组,在函数获取可变参数时特别有用
#接收元组或字典,分别加*或**前缀
def powersum(power, *args):	#传入参数会作为一个元组存储于args变量中
	'''
	return the sum of all args raised to specified power.
	@param power:
	'''
	total = 0
	for i in args:
		total += pow(i, power)
	return total

print 'powersum(2, 3, 4)=%d' % powersum(2, 3, 4)
print 'powersum(2, 10)=%d' % powersum(2, 10)
print 'powersum(3, 2, 4, 3)=%d' % powersum(3, 2, 4, 3)

print '***************************'
print '   lambda关键字的理解'
print '***************************'

#等价于(lambda x: x**2)(8)
g = lambda x: x**2	#lambda类似内联函数,这是普通应用,g为函数对象
print '8**2 =', g(8)

def make_repeater(n):
	return lambda m: m*n	#返回一个函数类

twice = make_repeater(2)

print twice('word')
print twice(7)


print '***************************'
print '   exec和eval的使用'
print '***************************'
#exec执行字符串的语句
exec 'print "hello World"'
#eval计算字符串中的表达式
print '3 * 2 =', eval('3 * 2')

print '***************************'
print '   repr函数的使用方法'
print '***************************'
#repr用来取得对象的规范字符串表示
i = []
i.append('tool')
#以下两者作用相同
print 'i =', repr(i)
print 'i =', `i`

del i
