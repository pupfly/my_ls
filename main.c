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
//         Author:  pupengfei
//        Company:  
// 
// =====================================================================================

#include "/home/pupf/MyCode/code_of_ls/declarations.h"

int main(int argc, char **argv)
{
  head.next = NULL;
 // get_all_name(1,"/usr/");
  int i,j,num,k;
  char path[PATH_MAX + 1];
  char param[32];
  int flag=NONE;
  struct stat buf;
  j = 0;
  num = 0;
 // printf("%d\n",argc);
  for (i = 1;i < argc;i++)
  {
    if (argv[i][0] == '-')
    {
      for (k =1;k < strlen(argv[i]);k++)
      {
	param[j++] = argv[i][k];
      }
      num++;//"-"的个数
      param[j] = '\0';
    }
  }
  //确定参数
  if (strcmp(param,"a") == 0)
  {
    flag = A;
  }
  else if (strcmp(param,"l") == 0)
  {
    flag = L;
  }
  else if (strcmp(param,"al") == 0 ||strcmp(param,"la") == 0)
  {
    flag = AL;
  }
  else if (strcmp(param,"R") == 0)
  {
    flag = R;
    if ((num + 1) == argc)
    {
      strcpy(path,"./");
      path[2] = '\0';
      print_all_name_for_R(flag,path);
      return 0;
    }
    for (i = 1;i < argc;i++)
    {
      if (argv[i][0] == '-')
      {
	continue;
      }
      else
      {
	strcpy(path,argv[i]);
	if (lstat(path,&buf) == -1)
	{
		  perror("lstat");
		  exit(1);
	}
	if (S_ISDIR(buf.st_mode))
	{
		  if (path[strlen(path)-1] != '/')
		  {
		    path[strlen(path)] = '/';
		    path[strlen(path) + 1] = '\0';
		  }
		  else
		  {
		    path[strlen(path) + 1] = '\0';
		  }
		  print_all_name_for_R(flag,path);
	}
	else
	{
		  show_with_param(flag,path,flag);
		  if (flag == 0)
		  {
		    printf("\n");
		  }
	}
      }
    }
    return;
  }
  else if(strlen(param) != 0)
  {
    printf("参数无效\n");
    exit(1);
  }
   if ((num + 1) == argc)
  {
    strcpy(path,"./");
    path[2] = '\0';
    get_all_name(flag,path);
    return 0;
  }
  for (i = 1;i < argc;i++)
  {
    if (argv[i][0] == '-')
    {
      continue;
    }
    else
    {
      strcpy(path,argv[i]);
      if (lstat(path,&buf) == -1)
      {
		perror("lstat");
		exit(1);
      }
      if (S_ISDIR(buf.st_mode))
      {
		if (path[strlen(path)-1] != '/')
		{
		  path[strlen(path)] = '/';
		  path[strlen(path) + 1] = '\0';
		}
		else
		{
		  path[strlen(path) + 1] = '\0';
		}
		get_all_name(flag,path);
      }
      else
      {
		show_with_param(flag,path,flag);
		if (flag == 0)
		{
		  printf("\n");
		}
      }
    }
  }
  destory_stud(&head);
  return 0;
}

