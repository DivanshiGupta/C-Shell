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
int parse_pipes(char *t)
{
	char **strpiped = (char **)malloc(40 * sizeof(char *));
	int cnt = 0;
    char* token1 =strtok(t,"|");
    while (token1 != NULL)
    {
        strpiped[cnt] = (char *)malloc(400 * sizeof(char));
        strcpy(strpiped[cnt],token1);
        token1 = strtok(NULL,"|");
        cnt++;
    }
    cnt-- ;// count stores the number of pipes // strpiped stores tokenised input
    int pipefd1[2];
    int pipefd2[2];
    for(int i=0;i<cnt+1;i++)
    {
    	if(i%2 == 0)
    	{
    		if (pipe(pipefd1) < 0) 
            {   
            	printf("Error :Pipe\n");
                return 0;
            }
        }
        else
        {
        	if (pipe(pipefd2) < 0) 
            {   
            	printf("Error : Pipe\n");
                return 0;
            }
        }
		// char **parts1 = (char **)malloc(40 * sizeof(char *));
		// int j = parse_input(strpiped[i] , parts1);

	    pid_t p2 = fork();

	    if(p2 < 0)
	    {
	        printf("Error : Fork\n");
	        return 0;
	    }
	    if(p2 == 0)
	    {
	        if(i % 2 == 0)
	        {
	            if (i != 0)
	            {
	                dup2(pipefd2[0], STDIN_FILENO);
	            }
	            if (i != cnt)
	            {
	                dup2(pipefd1[1], STDOUT_FILENO);
	            }
	        }
	        else
	        {
	            dup2(pipefd1[0], STDIN_FILENO);
	            if(i != cnt) 
	            {
	                dup2(pipefd2[1], STDOUT_FILENO);
	            }
	        }  
	        if(check_redirection(strpiped[i]) == 2)  
	        {
	        	char **parts1 = (char **)malloc(40 * sizeof(char *));
				int j = parse_input(strpiped[i] , parts1);
	    		// printf("nu\n");
	        	if (execvp(parts1[0], parts1) < 0)
	        	{
	         	   	printf("\nCould not execute command 2..");
	        	}
	        }
            exit(0);
	           
	    } 
	    else 
	    {
	        if (i % 2 == 0)
	        {
	            if (i != 0)
	            {
	                close(pipefd2[0]);
	            }
	            if (i != cnt)
	            {
	                close(pipefd1[1]);
	            }
	        }
	        else 
	        {
	            close(pipefd1[0]);
	            if (i != cnt)
	            {
	                close(pipefd2[1]);
	            }
	        }
	        wait(NULL);
	    }
	}
}