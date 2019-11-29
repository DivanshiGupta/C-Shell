#include <sys/utsname.h>
#include <unistd.h>
#include <string.h>
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<fcntl.h> 
#include <dirent.h>
#include<sys/types.h> 
#include<sys/wait.h>
#include<grp.h>
#include<pwd.h>
#include <sys/stat.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdio.h>
#include <stdint.h>
int str_comp(char *str,char *a,int len)
{
	int f=0;
	for(int i=0;i<len;i++)
	{
		if(str[i]!=a[i])
		{
			f=1;
			break;
		}		
	}
	if(f==0)
	{
		return 0;
	}

	return 1;
}