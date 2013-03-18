/*
 * 		文件名称:	SLinkList.h
 * 		创建时间:	2008-12-14
 * 		程序作者:	jasonleakey
 * 		当前版本:	1.0
 * 		Copyright 2008 jasonleakey
 * 		<jasonleakey@sohu.com>
 * 		<QQ:174481438>
 * 		--------------------------------------------------------------------
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */


#ifndef SLINKLIST_H_
#define SLINKLIST_H_

#define SIZE 100		//capacity of static linklist
typedef int KeyType;	//define key type as integer
typedef int InfoType;	//define other infomation as integer

typedef struct {
	KeyType key;		//key
	InfoType otherinfo;	//other info
} RedType;				//record type

typedef struct {
	RedType rc;			//record
	int next;			//the address of next record
} SLNode;				//static linklist node

typedef struct {
	SLNode r[SIZE];		//Unit 0 is considered as head node
	int length;			//total length
} SLinkList;			//Static linklist Type

typedef int Status;
#define OK 0
#define ERROR -1



#endif /* SLINKLIST_H_ */
