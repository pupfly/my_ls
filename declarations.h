// =====================================================================================
// 
//       Filename:  declarations.h
//
//    Description:  Declarations of functions and structs used in my own "ls"
//
//        Version:  1.0
//        Created:  2014年07月16日 17时45分12秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  pupengfei, 
//        Company:  
// 
// =====================================================================================

//headfiles

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/limits.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>

//definations of constant variables

#define NONE 0   //无参数
#define A 1      //参数-a
#define L 2      //参数-l
#define AL 3     //参数-al,参数-la视为前者
#define R 4	 //参数-R
#define MAXROWLEN 80

struct filenames
{
  char name[100];
  struct filenames *next;
}head;

int MAX_NAME_LEN;//最长名字长度

//declarations of functions

void out_all(struct stat buf);//显示一个文件的所有信息

void get_all_name(int flag , char *path);//获取一个目录下的所有文件,存入链表等待操作

void out_a_filename(char *name,int *leave_len);//显示一个文件名

void show_with_param(int flag ,char *path);//带解析参数的显示函数

void add_to_stud(struct filenames *head , char *name);//链表插入函数

void sort_stud(struct filenames *head);//链表排序函数



