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
int cd_command(char **str,int len)
{
	char a3[]="cd";
	if(strcmp(a3,str[0]) !=0)
	{
		return 0;
	}
	if(len ==1)
	{
		//CD (FOR HOME)
		char* username = getenv("USER");
		
		char home[] = "/home/";
		char y[100000];
		for(int i=0;i<6;i++)
		{
			y[i] = home[i];
		}
		for(int i=6;i<(6+strlen(username));i++)
		{
			y[i]=username[i-6];
		}
		chdir(y);
		return 1;
	}
	//CD PATHNAME
	else  
	{
		char a4[]="~";
		if(strcmp(a4,str[1]) ==0)
		{
			chdir(tilda);
		}
		else
			chdir(str[1]);
		return 1;		
	}
	return 0;
}