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
#define MAX_CHAR 80

//declarations of functions

void out_all(struct stat buf);//显示一个文件的所有信息

void out_filename(char *name);//显示一个文件名

void get_all_name(int flag , char *path);//显示一个目录下的所有文件





