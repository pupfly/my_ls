// =====================================================================================
// 
//       Filename:  main.c
//
//    Description:  main function for my own "ls"
//
//        Version:  1.0
//        Created:  2014年07月16日 17时47分24秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  pupengfei, 
//        Company:  
// 
// =====================================================================================

#include </home/pupf/MyCode/code_of_ls/declarations.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "declarations.h"

int main(int argc, char *argv[])
{
  struct stat buf;
  if (lstat("declarations.h",&buf)==-1)
  {
   printf("du cuo le !");
   exit(0);
  }
  out_all(buf);
  return 0;
}

