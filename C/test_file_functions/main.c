/*
 * 		文件名称:	main.c
 * 		创建时间:	2009-1-16
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

#ifndef PATH_MAX
#define PATH_MAX 65535
#endif

#ifndef MAX_BUF_SIZE
#define MAX_BUF_SIZE 200
#endif

//Function use: 输出当前目录
int test_getcwd(void)
{
	char chCurWorkDir[255];		//用来存放路径

	if (NULL == getcwd(chCurWorkDir, 255))
	{
		perror("无法获得当前目录!\n");
		return 1;
	}
	printf("当前目录:%s\n", chCurWorkDir);
	return 0;
}

//Function use: 获得系统目录最大长度
int test_pathconf(void)
{
	long nDirLength;
	char* pchCurWorkDir;

	if (-1 == (nDirLength = pathconf(".", _PC_LINK_MAX)))
	{
		perror("无法获得当前目录长度!\n");
		return 1;
	}
	printf("当前目录最大长度为%ld\n", nDirLength);

	if (NULL == (pchCurWorkDir = (char*)malloc(nDirLength + 1)))
	{
		perror("内存不足!\n");
		exit(EXIT_FAILURE);
	}
	pchCurWorkDir[nDirLength] = '\0';
	if (NULL == (getcwd(pchCurWorkDir, nDirLength)))
	{
		perror("无法获得当前目录!\n");
		return 1;
	}
	printf("当前目录:%s\n", pchCurWorkDir);
	return 0;
}

//Function use: 改变当前工作目录
int test_chdir_fchdir(void)
{
	char chDir[PATH_MAX];
	printf("更改当前目录:");
	fgets(chDir, PATH_MAX, stdin);
	if ('\0' != chDir[0])
	{
		printf("当前目录未改变!\n");
	}
	else if (-1 == chdir(chDir))
	{
		perror("无法更改目录!\n");
		return 1;
	}
	else
	{
		test_getcwd();
		printf("更改目录成功!\n");
	}
	return 0;
}

//Function use: 创建和删除目录
int test_mkdir_rmdir(void)
{
	char chDir[PATH_MAX] = {'\0'};
	printf("请输入创建的目录名:");
	fgets(chDir, PATH_MAX, stdin);
	if ('\0' != chDir[0])
	{
		printf("未创建目录!\n");
	}
	else if (-1 == mkdir(chDir, 0777))
	{
		perror("创建目录错误!\n");
		return 1;
	}
	else
	{
		printf("创建目录成功!\n");
	}

	memset(chDir, '\0', PATH_MAX);

	printf("请输入要删除的目录名:");
	fgets(chDir, PATH_MAX, stdin);
	if ('\0' != chDir[0])
	{
		printf("未删除任何目录!\n");
	}
	else if (-1 == (rmdir(chDir)))
	{
		perror("无法删除目录\n");
		return 1;
	}
	else
	{
		printf("删除目录成功!\n");
	}
	return 0;
}

//Function use: 测试文件打开,读取,关闭三个文件I/O函数
int test_open_read_close()
{
	int nFd;	//文件描述符,整型数,而非FILE*文件指针
	char ch;

	if (-1 == (nFd = open("/home/jasonleakey/open.txt", O_RDONLY)))
	{
		perror("无法打开文件!\n");
		return 1;
	}

	while (0 != read(nFd, &ch, 1))
	{
		printf("读取字母:%c\n", ch);
	}
	close(nFd);
	return 0;
}

//Function use: 获得文件信息
int test_stat_fstat_lstat()
{
	//测试stat
	struct stat file_stat;
	if (-1 == (stat("/home/jasonleakey/stat", &file_stat)))
	{
		perror("无法获得文件信息!\n");
	}
	else
	{
		printf("stat文件的信息如下:\n");
		printf("inode值 = %ld\n", file_stat.st_ino);
		printf("文件访问权限 = %o\n", file_stat.st_mode);
		printf("所有者ID = %d, 组ID = %d\n", file_stat.st_uid, file_stat.st_gid);
		printf("最后访问时间:%15s", ctime(&file_stat.st_atime));
		printf("最后修改时间:%15s", ctime(&file_stat.st_mtime));
		printf("最后一次文件属性修改时间:%15s", ctime(&file_stat.st_ctime));
		if (S_ISREG(file_stat.st_mode))
		{
			printf("通过宏S_ISREG判断,stat是普通文件!\n");
		}
		if (file_stat.st_mode & S_IFREG)
		{
			printf("通过与S_IFREG的位运算后判断,stat是普通文件!\n");
		}
		if (S_ISCHR(file_stat.st_mode))
		{
			printf("stat是字符设备!\n");
		}
		if (S_ISBLK(file_stat.st_mode))
		{
			printf("stat是块设备!\n");
		}
		if (S_ISFIFO(file_stat.st_mode))
		{
			printf("stat是命名管道文件!\n");
		}
		if (S_ISDIR(file_stat.st_mode))
		{
			printf("通过宏S_ISDIR判断,stat是目录!\n");
		}
		if (file_stat.st_mode & S_IFDIR)
		{
			printf("通过与S_IFDIR的位运算后判断,stat是目录!\n");
		}
	}
	//测试fstat
	int nFd;	//文件描述符
	nFd = open("/home/jasonleakey/fstat", O_RDONLY);
	fstat(nFd, &file_stat);
	printf("fstat文件的信息如下:\n");
	printf("inode值 = %ld\n", file_stat.st_ino);
	printf("文件访问权限 = %o\n", file_stat.st_mode);
	printf("所有者ID = %d, 组ID = %d\n", file_stat.st_uid, file_stat.st_gid);
	printf("最后访问时间:%15s", ctime(&file_stat.st_atime));
	printf("最后修改时间:%15s", ctime(&file_stat.st_mtime));
	printf("最后一次文件属性修改时间:%15s\n", ctime(&file_stat.st_ctime));
	close(nFd);

	lstat("/home/jasonleakey/lstat", &file_stat);
	printf("通过lstat函数调用,lstat文件的信息如下:\n");
	printf("inode值 = %ld\n", file_stat.st_ino);
	printf("文件访问权限 = %o\n", file_stat.st_mode);
	printf("所有者ID = %d, 组ID = %d\n", file_stat.st_uid, file_stat.st_gid);
	printf("最后访问时间:%15s", ctime(&file_stat.st_atime));
	printf("最后修改时间:%15s", ctime(&file_stat.st_mtime));
	printf("最后一次文件属性修改时间:%15s\n", ctime(&file_stat.st_ctime));

	stat("/home/jasonleakey/lstat", &file_stat);
	printf("通过stat函数调用,lstat文件的信息如下:\n");
	printf("inode值 = %ld\n", file_stat.st_ino);
	printf("文件访问权限 = %o\n", file_stat.st_mode);
	printf("所有者ID = %d, 组ID = %d\n", file_stat.st_uid, file_stat.st_gid);
	printf("最后访问时间:%15s", ctime(&file_stat.st_atime));
	printf("最后修改时间:%15s", ctime(&file_stat.st_mtime));
	printf("最后一次文件属性修改时间:%15s\n", ctime(&file_stat.st_ctime));

	return 0;
}

//Function use: 更改文件访问权限
int test_chmod_fchmod(void)
{
	if (-1 == chmod("/home/jasonleakey/open.txt", 0755))
	{
		perror("无法更改文件访问权限!\n");
		return 1;
	}
	printf("更改open.txt文件属性为0755成功\n");
	return 0;
}

//Function use: 更改文件所有者
int test_chown_fchown_lchown(void)
{
	if (-1 == chown("/home/jasonleakey/chown", 0, 0))
	{
		perror("没有权限更改文件所有者!\n");
		return 1;
	}
	printf("chown文件所有者已更改为root:root\n");
	return 0;
}

//Function use: 设置新文件建立时的权限遮罩
int test_umask(void)
{
	int nFileDesA;
	int nFileDesB;

	//创建名为test的文件,权限为777
	if (-1 == (nFileDesA = open("/home/jasonleakey/test", O_CREAT | O_RDONLY, 0777)))
	{
		perror("无法创建文件!\n");
		return 1;
	}
	close(nFileDesA);

	struct stat file_stat;

	if (-1 == stat("/home/jasonleakey/test", &file_stat))
	{
		perror("无法获得文件信息!\n");
		return 1;
	}
	printf("修改umask前,test文件访问权限:%o\n", file_stat.st_mode);

	umask(066);

	if (-1 == (nFileDesB = open("/home/jasonleakey/test2", O_CREAT | O_RDONLY, 0777)))
	{
		perror("无法创建文件!\n");
		return 1;
	}
	close(nFileDesB);

	if (-1 == stat("/home/jasonleakey/test2", &file_stat))
	{
		perror("无法获得文件信息!\n");
		return 1;
	}
	printf("修改umask后,test2文件访问权限:%o\n", file_stat.st_mode);

	umask(002);
	return 0;
}

//Function use: 建立硬链接和符号链接,以及撤销这两种链接
int test_link_symlink_unlink(void)
{
	if (-1 == link("/home/jasonleakey/TEST_LINK", "/home/jasonleakey/link_file"))
	{
		perror("无法创建硬链接!\n");
	}
	else
	{
		printf("创建硬链接成功,链接文件名为link_file.\n");
	}
	if (-1 == symlink("/home/jasonleakey/TEST_LINK", "/home/jasonleakey/symlink_file"))
	{
		perror("无法创建符号链接!\n");
		return 1;
	}
	else
	{
		printf("创建符号链接成功,链接文件名为symlink_file.\n");
	}
	return 0;
}

//Function use: 用open函数建立文件和creat建立文件
int test_open_close_creat(void)
{
	int nFd;	//文件描述符

	umask(0133);
	if (-1 == (nFd = open("/home/jasonleakey/open_cre", O_CREAT, 0777)))
	{
		perror("无法用open创建文件!\n");
		return 1;
	}
	printf("用open函数创建open_cre文件成功!\n");
	if (-1 == close(nFd))
	{
		perror("关闭文件失败!\n");
		return 1;
	}

	if (-1 == (nFd = creat("/home/jasonleakey/cre", 0777)))
	{
		perror("无法用creat创建文件!\n");
		return 1;
	}
	printf("用creat函数创建cre文件成功!\n	");
	if (-1 == close(nFd))
	{
		perror("关闭文件失败!\n");
		return 1;
	}

	return 0;
}

//Function use: 用read和write函数实现文件复制功能
int test_write(void)
{
	int nFdFrom;	//复制的源文件
	int nFdTo;		//复制的目标文件
	int nLength;	//一次读取的字符数
	char chBuf[MAX_BUF_SIZE];	//缓冲区

	if (-1 == (nFdFrom =  open("/home/jasonleakey/open.txt", O_RDONLY)))
	{
		perror("无法打开open.txt!\n");
		return 1;
	}

	if (-1 == (nFdTo =  open("/home/jasonleakey/write.txt", O_RDWR | O_CREAT, 0777)))
	{
		perror("无法创建目标文件!\n");
		return 1;
	}
	while (0 < (nLength = read(nFdFrom, chBuf, MAX_BUF_SIZE)))
	{
		if (-1 == (write(nFdTo, chBuf, nLength)))
		{
			perror("无法写入文件!\n");
			close(nFdFrom);
			close(nFdTo);
			return 1;
		}
	}

	printf("\n成功将open.txt内容复制到write.txt中!\n");
	close(nFdFrom);
	close(nFdTo);

	return 0;
}

//Function use: 利用lseek函数实现对指定文件内容的搜索功能
int test_lseek(void)
{
	int nLen;		//用于保存输入要查询的字符串长度
	int nFd;		//文件描述符
	long nOffSet = 0;	//偏移量
	char chSubStr[MAX_BUF_SIZE];	//用于保存查询的字符串
	char chBuffer[MAX_BUF_SIZE];	//用于保存读出的文件内容
	int nCount = 0;		//用于统计查找到了几次相同字符

	printf("请输入要查找的字符串:");
	scanf("%s", chSubStr);
	if (0 >= (nLen = strlen(chSubStr)))
	{
		perror("查找的字符串不能为空!\n");
		return 1;
	}

	if (-1 == (nFd = open("/home/jasonleakey/lseek.txt", O_RDONLY)))
	{
		perror("无法打开文件!\n");
		return 1;
	}

	//不断读取lseek.txt并与匹配串比较,直到文件尾
	while (nLen == read(nFd, chBuffer, nLen))
	{
		chBuffer[nLen] = '\0';
		if (0 == strcasecmp(chBuffer, chSubStr))
		{
			nCount++;		//如果读出的字符串与匹配串相同,则记录
		}

		//将文件读写指针移直下一个字符
		++nOffSet;
		if (-1 == lseek(nFd, nOffSet, SEEK_SET))
		{
			perror("无法移动文件读写指针!\n");
			close(nFd);
			return 1;
		}
	}

	if (0 < nCount)
	{
		printf("已在lseek.txt中找到%d处%s!\n", nCount, chSubStr);
	}
	else
	{
		printf("未找到字符串!\n");
	}
	close(nFd);
	return 0;
}

//Function use: 用dup函数实现输入输出的重定向
int test_dup_dup2(void)
{
	int nFd;	//文件描述符
	int nStdoutBak;		//备份标准输出
	char chFileName[MAX_BUF_SIZE];	//文件名

	printf("请输入替代输出的文件名:\n");
	scanf("%s", chFileName);
	//将当前目录改成/home/jasonleakey/
	if (-1 == chdir("/home/jasonleakey/"))
	{
		perror("无法改变当前目录!\n");
		return 1;
	}
	//创建名为chFileName的文件
	if (-1 == (nFd = open(chFileName, O_CREAT | O_RDWR, 0644)))
	{
		perror("无法创建文件!\n");
		return 1;
	}
#if 0
	close(STDOUT_FILENO);	//关闭标准输出

	//将打开的文件描述符重定向到标准输出
	if (-1 == dup(nFd))
	{
		perror("无法重定向到标准输出!\n");
		close(nFd);
		return 1;
	}
#endif
	if (-1 == dup2(STDOUT_FILENO, nStdoutBak))
	{
		perror("无法备份标准输出!\n");
		close(nFd);
		return 1;
	}

	//以上dup函数可以换成dup2函数实现
	if (-1 == dup2(nFd, STDOUT_FILENO))
	{
		perror("无法重定向到标准输出!\n");
		close(nFd);
		return 1;
	}

	printf("因标准输出已关闭,重定向到此文件!\n");

	close(nFd);
	if (-1 == dup2(nStdoutBak, STDOUT_FILENO))
	{
		perror("无法打开标准输出!\n");
		return 1;
	}
	return 0;
}

//Function use: 利用ttyname函数判断某个文件描述符是否是终端设备
int test_ttyname(void)
{
	char* chTtyOutName = NULL;
	char* chTtyInName = NULL;
	char* chTtyErrName = NULL;

	if (NULL == (chTtyInName = ttyname(STDIN_FILENO)))
	{
		perror("无法获得标准输入的ttyname名!\n");
		return 1;
	}
	if (NULL == (chTtyOutName = ttyname(STDOUT_FILENO)))
	{
		perror("无法获得标准输出的ttyname名!\n");
		return 1;
	}
	if (NULL == (chTtyErrName = ttyname(STDERR_FILENO)))
	{
		perror("无法获得标准输出错误的ttyname名!\n");
		return 1;
	}

	printf("STDIN_FILENO tty name is %s\n", chTtyInName);
	printf("STDOUT_FILENO tty name is %s\n", chTtyOutName);
	printf("STDERR_FILENO tty name is %s\n", chTtyErrName);

	return 0;
}

int main(int argc, char **argv)
{
	test_getcwd();
	test_pathconf();
	test_chdir_fchdir();
	test_mkdir_rmdir();
	test_open_read_close();
	test_stat_fstat_lstat();
	test_chmod_fchmod();
	test_chown_fchown_lchown();
	test_umask();
	test_link_symlink_unlink();
	test_open_close_creat();
	test_write();
	test_lseek();
	test_dup_dup2();
	test_ttyname();
	return 0;
}
