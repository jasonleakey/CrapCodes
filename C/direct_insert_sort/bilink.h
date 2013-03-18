/*
 * bilink.h
 *
 *  Created on: 2008-10-27
 *      Author: jasonleakey
 */

#ifndef BILINK_H_
#define BILINK_H_

#define OK 1
#define ERROR -1

typedef unsigned char Elemtype;
typedef int Status;

typedef struct BiNode {
	Elemtype data;
	struct BiNode *pre, *next;
}BiNode, *BiLink;

extern Status direct_insert_sort(BiLink *pL);

#endif /* BILINK_H_ */
