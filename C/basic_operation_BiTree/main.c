/*
 * main.c
 *
 *  Created on: 2008-11-18
 *      Author: jasonleakey
 */

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "BiTree.h"

#define CLEAR_STDIN while(getchar() != '\n'){;}
#define PRINT_MAIN_MENU printf("1. 构造一棵二叉树\n"\
	"2. 求二叉树的高度\n"\
	"3. 判断树是否为空\n"\
	"4. 打印根结点的值\n"\
	"5. 打印所要求结点的值\n"\
	"6. 给所要求结点赋新值\n"\
	"7. 求双亲结点的值\n"\
	"8. 按给定值寻找结点,并打印结点地址\n"\
	"9. 按给定值寻找结点,打印出其左孩子结点的值\n"\
	"10.按给定值寻找结点,打印出其右孩子结点的值\n"\
	"11.按给定值寻找结点,打印出其左兄弟结点的值\n"\
	"12.按给定值寻找结点,打印出其右兄弟结点的值\n"\
	"13.在所要求结点的子树插入结点\n"\
	"14.删除所要求结点的子树\n"\
	"15.递归法先序遍历二叉树\n"\
	"16.递归法中序遍历二叉树\n"\
	"17.InOrderTraverse1_nonrecursive\n"\
	"18.InOrderTraverse2_nonrecursive\n"\
	"19.递归法后序遍历二叉树\n"\
	"20.层序遍历二叉树\n"\
	"21.PreOrderUnrec1\n"\
	"22.PreOrderUnrec2\n"\
	"23.PreOrderUnrec3\n"\
	"24.InOrderUnrec\n"\
	"0.退出程序\n"\
	"请输入序号: ")	//以上对每行加以" "号,可避免输出空白

int main(int argc, char **argv)
{
	printf("*************************************************\n");
	printf("程序名称: 二叉树基本操作的演示\t作者:jasonleakey\n");
	printf("*************************************************\n");
	PRINT_MAIN_MENU;
	int selNum = 0; //选择菜单的号码
	char ch;
	int lrflag = 0;
	int btdepth;
	BiTree p = NULL;
	BiTree T = NULL;
	BiTree T_2 = NULL;
	while (scanf("%d", &selNum) == 1 && selNum != EOF)
	{
		switch (selNum)
		{
			case 0:
				printf("********谢谢使用**********再见**********\n");
				DestroyBiTree(&T);
				DestroyBiTree(&T_2);
				exit(EXIT_SUCCESS);
			case 1:
				InitBiTree(&T); //构造二叉树前先对其初始化为空树
				printf("按先序次序输入二叉树的结点的值:");
				CLEAR_STDIN;
				CreateBiTree(&T); //构造二叉树
				printf("构造二叉树完成!\n");
				break;
			case 2:
				btdepth = BiTreeDepth(T); //调用BiTreeDepth计算树高
				printf("二叉树高为:%d\n", btdepth);
				break;
			case 3:
				if (!BITREEEMPTY(T))
				{
					printf("二叉树不空!\n");
				}
				else
				{
					printf("二叉树为空!\n");
				}
				break;
			case 4:
				printf("根结点的值为:%c\n", ROOT(T));
				break;
			case 5:
				printf("请输入欲查找的值:");
				CLEAR_STDIN
				;
				scanf("%c", &ch);
				p = Point(T, ch);
				printf("找到此结点,地址为%p,结点值为%c\n", Point(T, ch), p->data);
				break;
			case 6:
				printf("请输入欲修改结点的值:");
				CLEAR_STDIN
				;
				scanf("%c", &ch);
				p = Point(T, ch);
				printf("请输入修改值:");
				CLEAR_STDIN
				;
				scanf("%c", &ch);
				ASSIGN(p, ch);
				printf("修改成功!\n");
				break;
			case 7:
				printf("请输入需要查找的值:");
				CLEAR_STDIN
				;
				scanf("%c", &ch);
				printf("双亲结点值为:%c", Parent(T, ch));
				printf("\n");
				break;
			case 8:
				printf("请输入需要查找的值:");
				CLEAR_STDIN
				;
				scanf("%c", &ch);
				printf("该结点的指针:%p", Point(T, ch));
				printf("\n");
				break;
			case 9:
				printf("请输入需要查找的值:");
				CLEAR_STDIN
				;
				scanf("%c", &ch);
				printf("该结点的左孩子值:%c\n", LeftChild(T, ch));
				printf("\n");
				break;
			case 10:
				printf("请输入需要查找的值:");
				CLEAR_STDIN
				;
				scanf("%c", &ch);
				printf("该结点的右孩子值:%c\n", RightChild(T, ch));
				break;
			case 11:
				printf("请输入需要查找的值:");
				CLEAR_STDIN
				;
				scanf("%c", &ch);
				printf("该结点的左兄弟值:%c\n", LeftSibling(T, ch));
				break;
			case 12:
				printf("请输入需要查找的值:");
				CLEAR_STDIN
				;
				scanf("%c", &ch);
				printf("该结点的右兄弟值:%c\n", RightSibling(T, ch));
				break;
			case 13:
				//构造要插入的树T_2
				InitBiTree(&T_2);
				printf("创建另一棵树.\n");
				printf("按先序次序输入二叉树的结点的值:");
				CLEAR_STDIN
				;
				CreateBiTree(&T_2);
				printf("构造完成!\n");


				//插入到T树中p指向的结点
				printf("输入你要插入的结点的值:");
				CLEAR_STDIN
				;
				scanf("%c", &ch);
				p = Point(T, ch);
				printf("插入其左子树或右子树?(0左1右):");
				CLEAR_STDIN
				;
				scanf("%d", &lrflag);
				InsertChild(p, lrflag, T_2);
				printf("插入子树完成!\n");
				printf("先序遍历结果:");
				PreOrderTraverse(T, visitT);
				printf("\n");
				break;
			case 14:
				//删除p结点左子树或右子树
				printf("输入你要删除的树的双亲结点的值:");
				CLEAR_STDIN
				;
				scanf("%c", &ch);
				p = Point(T, ch);
				printf("删除其左子树还是右子树?(0左1右):");
				CLEAR_STDIN
				;
				scanf("%d", &lrflag);
				DeleteChild(p, lrflag);
				printf("删除完成!\n");
				printf("先序遍历结果:");
				PreOrderTraverse(T, visitT);
				printf("\n");
				break;
			case 15:
				printf("以下是递归法先序遍历二叉树:\n");
				PreOrderTraverse(T, visitT);
				printf("遍历完成!\n");
				break;
			case 16:
				printf("以下是递归法中序遍历二叉树:\n");
				InOrderTraverse(T, visitT);
				printf("遍历完成!\n");
				break;
			case 17:
				printf("以下是第一个非递归法中序遍历二叉树:\n");
				InOrderTraverse1_nonrecursive(T, visitT);
				printf("遍历完成!\n");
				break;
			case 18:
				printf("以下是第二个非递归法中序遍历二叉树:\n");
				InOrderTraverse2_nonrecursive(T, visitT);
				printf("遍历完成!\n");
				break;
			case 19:
				printf("以下是递归法后序遍历二叉树:\n");
				PostOrderTraverse(T, visitT);
				printf("遍历完成!\n");
				break;
			case 20:
				printf("以下是层序遍历二叉树:\n");
				LevelOrderTraverse(T, visitT);
				printf("遍历完成!\n");
				break;
			case 21:
				printf("Following is PreOrderUnrec1\n");
				PreOrderUnrec1(T, visitT);
				printf("traversal Completed!\n");
				break;
			case 22:
				printf("Following is PreOrderUnrec2\n");
				PreOrderUnrec2(T, visitT);
				printf("traversal Completed!\n");
				break;
			case 23:
				printf("Following is PreOrderUnrec3\n");
				PreOrderUnrec3(T, visitT);
				printf("traversal Completed!\n");
				break;
			default:
				printf("输入有误!\n请重新输入: ");
		}
		CLEAR_STDIN;
		printf("按回车键回主菜单:");
		CLEAR_STDIN;
		PRINT_MAIN_MENU;
	}
	DestroyBiTree(&T_2);
	DestroyBiTree(&T);
	printf("********谢谢使用**********再见**********\n");
	return EXIT_SUCCESS;
}
