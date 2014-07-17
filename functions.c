// =====================================================================================
// 
//       Filename:  functions.c
//
//    Description:  Definition of all functions used in my own "ls"
//
//        Version:  1.0
//        Created:  2014年07月16日 17时40分45秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  pupengfei, 
//        Company:  
// 
// =====================================================================================

#include </home/pupf/MyCode/code_of_ls/declarations.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

void out_all(struct stat buffer)//显示一个文件的所有信息
{
  char b_time[32];
  struct passwd *psd;//存储所属用户名2
  struct group *grp;//存储所属组名
  if (S_ISLNK(buffer.st_mode))
    printf("l");
  else if (S_ISREG(buffer.st_mode))
    printf("-");
  else if (S_ISDIR(buffer.st_mode))
    printf("d");
  else if (S_ISCHR(buffer.st_mode))
    printf("c");
  else if (S_ISBLK(buffer.st_mode))
    printf("b");
  else if (S_ISFIFO(buffer.st_mode))
    printf("f");
  else if (S_ISSOCK(buffer.st_mode))
    printf("s");
  if (buffer.st_mode & S_IRUSR)
    printf("r");
  else
    printf("-");
  if (buffer.st_mode & S_IWUSR)
    printf("w");
  else
    printf("-");
   if (buffer.st_mode & S_IXUSR)
    printf("x");
  else
    printf("-");
  if (buffer.st_mode & S_IRGRP)
    printf("r");
  else
    printf("-");
  if (buffer.st_mode & S_IWGRP)
    printf("w");
  else
    printf("-");
   if (buffer.st_mode & S_IXGRP)
    printf("x");
  else
    printf("-");
  if (buffer.st_mode & S_IROTH)
    printf("r");
  else
    printf("-");
  if (buffer.st_mode & S_IWOTH)
    printf("w");
  else
    printf("-");
   if (buffer.st_mode & S_IXOTH)
    printf("x");
  else
    printf("-");
  printf("    ");
  psd=getpwuid(buffer.st_uid);
  grp=getgrgid(buffer.st_gid);
  printf("%4d",buffer.st_nlink);
  printf("%-8s",psd->pw_name);
  printf("%-8s",grp->gr_name);
  printf("%6d",buffer.st_size);
  strcpy(b_time,ctime(&buffer.st_mtime));
  b_time[strlen(b_time)-1]='\0';
  printf("  %s",b_time);
}
