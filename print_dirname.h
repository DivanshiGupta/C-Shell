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
#define RED   "\x1B[31m"
#define RESET "\x1B[0m"
#define GRN   "\x1B[32m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
int print_dirname(int size)
{
	// 	The getenv() function searches the environment list to find the environment variable name,
	//  and returns a pointer to the corresponding value string.
	
	char* username = getenv("USER"); 
	printf(GRN"%s@" RESET,username);

	char hostname[300];
	gethostname(hostname,300);
	// Determines the path name of the working directory and stores it in buffer.
	int pATH_MAX = 100000;
	char buff[pATH_MAX];

	if (getcwd(buff,pATH_MAX) != NULL) 
	{	
			if(strlen(buff) >= size)
			{
				printf(GRN"%s:~" RESET,hostname);
				
				for(int i=size;i<strlen(buff);i++)
				{
					printf(GRN"%c"RESET,buff[i]);
				}

			}
			else
			{
				printf(GRN"%s:~" RESET,hostname);
			
				for(int i=0;i < strlen(buff);i++)
		       	{
		       		printf(GRN"%c" RESET,buff[i]);
		       	}

		    }
	    
       	printf(GRN"-> "RESET);
   	}
    else 
    {
       perror("getcwd() error");
       return 1;
   	}
   	return 0;
}