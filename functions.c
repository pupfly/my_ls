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

#include "/home/pupf/MyCode/code_of_ls/declarations.h"

int g_leave_len=80;//一行剩余长度

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
  
  printf(" ");
  psd=getpwuid(buffer.st_uid);
  grp=getgrgid(buffer.st_gid);
  printf("%4d  ",buffer.st_nlink);
  printf("%-8s",psd->pw_name);
  printf("%-8s",grp->gr_name);
  printf("%6d",buffer.st_size);
  strcpy(b_time,ctime(&buffer.st_mtime));
  b_time[strlen(b_time) - 1] = '\0';
  printf(" %s",b_time);
}

void get_all_name(int flag , char *path)//获取一个目录下的所有文件
{
  DIR *dir;
  struct dirent *ptr;
  int count = 0;
  int i,j;
  char filename[64];
  
  if (( dir = opendir(path)) == NULL)
  {
    perror("opendir");
    exit(1);
  }
  while((ptr = readdir(dir)) != NULL)
  {
    if (MAX_NAME_LEN < strlen(ptr->d_name))
    {
      MAX_NAME_LEN = strlen(ptr->d_name);
    }
    count++;
  }
  if (count > 256)
  {
    printf("Too many files under %s\n",path);
    exit(0);
  }
  closedir(dir);
  if (( dir = opendir(path)) == NULL)
  {
    perror("opendir");
    exit(1);
  }
  for (i = 0; i < count;i++)
  {
   if (( ptr = readdir(dir)) == NULL)
    {
      perror("opendir");
      exit(1);
    }
    strcpy(filename, path);
    strcat(filename,ptr->d_name);
    add_to_stud(&head ,filename);
  }
   sort_stud(&head);
   struct filenames *p;
   p = &head;
   while((p=p->next) != NULL)
   {
     show_with_param(flag ,p->name);
   }
  if (flag == 0 ||flag == 1)
  {
    printf("\n");
  }
   closedir(dir);
}

void out_a_filename(char *name,int *leave_len)//显示一个文件名
{
  int i,length;
  if (*leave_len < MAX_NAME_LEN)
  {
    printf("\n");
    *leave_len= MAXROWLEN;
  }
  length = strlen(name);
  length = MAX_NAME_LEN-length;
  printf("%-s",name);
  for (i = 0;i < length;i++)
  {
    printf(" ");
  }
  printf("  ");
  *leave_len -= (MAX_NAME_LEN + 2);
}

void show_with_param(int flag ,char *path)//带解析参数的显示函数
{
  int i,j;
  struct stat buf;
  char name[100];
  
  //获取文件或目录名字
  for (i = 0,j = 0;i < strlen(path);i++)
  {
    if (path[i] == '/')//出现次级目录,将J归0
    {
      j = 0;
      continue;
    }
    name[j++] = path[i];
  }
  name[j] = '\0';
  if ((lstat(path,&buf)) == -1)
  {
    perror("lstat");
    exit(1);
  }
  switch (flag)
  {
    case NONE:
      if (name[0] != '.')
      {
	out_a_filename(name,&g_leave_len);
      }
      break;
    case A:
      out_a_filename(name,&g_leave_len);
      break;
    case L:
      if (name[0] != '.')
      {
	out_all(buf);
	printf(" %-s\n",name);
      }
      break;
    case AL:
      out_all(buf);
      printf(" %-s\n",name);
      break;
    case R:
    {}
    break;
  }
}
void add_to_stud(struct filenames *head , char *name)//链表插入函数
{
  	struct filenames *s1,*s2;
	s1 = head;
	s2=(struct filenames *)malloc(sizeof(struct filenames));
	strcpy(s2->name,name);
	s2->next = s1->next;
	s1->next = s2;
	return;
}
void sort_stud(struct filenames *head)//链表排序函数,避免结构体复制,增加效率
{
  	struct filenames *p1,*min_node,*p2,*p3,*before_min,*temp,*temp2;//利用选择排序的思想进行排序
	for(p1 = head;p1->next->next != NULL;p1 = p1->next)
	{
		min_node = p1->next;
		before_min = p1;
		for(p2 = min_node->next,p3 = min_node;p2->next != NULL;p2 = p2->next , p3 = p3->next)
		{
			if(strcmp(p2->name,min_node->name) < 0)
			{
			  min_node = p2;
			  before_min = p3;
			}
		}
		if(min_node != p1->next)
		{
			temp = p1->next;
			p1->next = min_node;
			before_min->next = min_node->next;
			min_node->next = temp;
		}
	}
	//此时名为".."的隐藏文件排在最后,下面将它放在第二的位置,(原因尚未找到)
	temp2 = head;
	while(temp2 = temp2->next)
	{
	  if (temp2->next == NULL)
	  {
	    break;
	  }
	}
	temp = head->next->next->next;
	head->next->next = temp2;
	temp2->next = temp;
	temp = head;
	int i = 0;
	while ((temp = temp->next) != NULL)
	{
	  if (temp->next == temp2)
	    i++;
	  if (i == 2)
	  {
	    temp->next = NULL;
	    break;
	  }
	}
}