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
int ls_command(char **str ,int len)
{
	char a5[] ="ls";
	if(strcmp(a5,str[0]) != 0)
	{
		return 0;
	}
	int codee=0;
	if(len ==1)
	{
		codee =1;
	}
	else
	{
		char a1[] ="-a";
		char a2[] ="-l";
		char a3[]= "-al";
		char a4[] ="-la";
		if(strcmp(a1,str[1]) ==0)
			codee =2;
		else if(strcmp(str[1],a2) ==0)
			codee=3;
		else if(strcmp(str[1],a3) ==0 || strcmp(str[1],a4)==0)
			codee=4;

	}
	DIR* dr;
	struct dirent *de;
	
	if(codee == 0 || len == 3)
	{
		if(codee==0)
		{	
			dr =opendir(str[1]);
			codee = 1;
		}
		else
			dr= opendir(str[2]);			
	}
	else
		dr = opendir(".");

	while((de= readdir(dr)) !=NULL)
	{
		char *b = ".";
		// printf("%s\n",de->d_name);
		
		while(de->d_name[0] == *b && (codee ==1 || codee ==3))
		{
			//printf("12");
			de =readdir(dr);
			if(de == NULL)
			{
				if(codee==1)
					printf("\n");
				return 1;
			}
		}
		 // printf("%s\n",de->d_name);
		struct stat info;
		stat(de->d_name,&info) ;
		
		if(codee == 3 || codee ==4)
		{
			printf( (S_ISDIR(info.st_mode)) ? "d" : "-");
			printf( (info.st_mode & S_IRUSR) ? "r" : "-");
			printf( (info.st_mode & S_IWUSR) ? "w" : "-");
		    printf( (info.st_mode & S_IXUSR) ? "x" : "-");
		    printf( (info.st_mode & S_IRGRP) ? "r" : "-");
		    printf( (info.st_mode & S_IWGRP) ? "w" : "-");
		    printf( (info.st_mode & S_IXGRP) ? "x" : "-");
		    printf( (info.st_mode & S_IROTH) ? "r" : "-");
		    printf( (info.st_mode & S_IWOTH) ? "w" : "-");
		    printf( (info.st_mode & S_IXOTH) ? "x" : "-");
			printf(" ");
					
			printf("%ld ",info.st_nlink);
				
			printf("%s ",(getpwuid(info.st_uid)->pw_name));				
    		printf("%s ", (getgrgid(info.st_gid)->gr_name));
					
    		printf("%ld ",info.st_size);					

			char * ct = ctime(&info.st_mtime);
			char **cts = (char **)malloc(40 * sizeof(char *));    	
	    	for (int i = 0; i < 5; i++)
	        	cts[i] = (char *)malloc(400 * sizeof(char));
	        int i1 = parse_input(ct,cts);
	        for(int i=1;i<i1-1;i++)
	        {
	        	if(i == i1 -2)
	        	{
	        		for(int j=0;j<5;j++)
	        		{
	        			printf("%c",cts[i][j]);
	        		}
	        		printf(" ");
	        	}
	     		else
	       			printf("%s ",cts[i]);
	        }	
	    }
	    if(codee == 3 || codee ==4)
			printf("%s\n ",de->d_name);								    
        else
        	printf("%s ",de->d_name);		
	}
	if(codee == 1 || codee ==2)
	{
		printf("\n");
	}
	return 1;

}