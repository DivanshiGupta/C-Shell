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
int pinfo_pid(char **str,int len)
{
	char a1[]="pinfo";
	if(strcmp(a1,str[0]) != 0)
	{
		return 0;
	}

	char a2[]="/proc/";
	char a3[]="/stat";
	if(len ==1)
	{
		char a4[]="self";
		strcat(a2,a4);

	}
	else
		strcat(a2,str[1]);
	strcat(a2,a3);
    	
	int fd = open(a2,O_RDONLY);
	
	char b[1000];

	int l11 =read(fd,&b,1000);
	

	char **parts1 = (char **)malloc(40 * sizeof(char *));
    	
    for (int i = 0; i < 50; i++)
        parts1[i] = (char *)malloc(400 * sizeof(char));

    int i1 = parse_input(b,parts1);
  
    long long int arr[1000];
   	int  p=0;
   	
    printf("pid -- %s\n",parts1[0]);
    printf("Process Status -- %s\n",parts1[2]);
	printf("memory ​ -- %s\n",parts1[22]);
	printf("Executable Path --​ ​ %s\n",parts1[1]);

return 1;
}