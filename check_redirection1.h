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
int check_redirection(char *t)
{
	// printf("%s\n\n\n",t);
	int flag=0,flag1=0;
	for(int i =0;i<strlen(t);i++)
	{
		if(t[i] == '<' )
		{
			flag1=1;
		}
		else if(t[i] == '>')
		{
			flag=1;
		}
	}

	if(flag == 0 && flag1==0)
		return 2;

	if(flag ==1 && flag1==0)
	{
		int f=0;
		for(int i = strlen(t)-1;i>=0;i--)
		{
			if(t[i]=='>')
			{
				if(t[i-1] == '>')
				{
					f=1;
				}
				break;
			}
		}
		char **partsb = (char **)malloc(40 * sizeof(char *));

		int i=0;
	    char* token1 =strtok(t,">");
	    while (token1 != NULL)
	    {

	         partsb[i] = (char *)malloc(400 * sizeof(char));
	        strcpy(partsb[i],token1);
	    	i++;
	        token1 = strtok(NULL,">");
	    }

	    pid_t p1; 
	    p1 = fork(); 
	    if (p1 < 0) { 
	        printf("\nCould not fork"); 
	        return 0; 
	    } 
	  
	    if (p1 == 0)
	    {     
	    	char **partsa = (char **)malloc(40 * sizeof(char *));
	    	char **partsc = (char **)malloc(40 * sizeof(char *));

	        parse_input(partsb[0],partsa);
	        parse_input(partsb[i-1],partsc);
	    
	        int fd;
	        if(f==1)
	        	 fd = open(partsc[0],O_CREAT | O_WRONLY |O_APPEND,S_IRWXU|S_IRWXO|S_IRWXO);  
	        else	
	        	fd = open(partsc[0],O_CREAT | O_WRONLY |O_TRUNC,S_IRWXU|S_IRWXO|S_IRWXO);  
	        dup2(fd, STDOUT_FILENO); 

	        if (execvp(partsa[0], partsa)  < 0) { 
	            printf("\nCould not execute command 1.."); 
	             exit(0); 
	        }
	    } 
	}
	else if(flag ==0 && flag1==1)
	{
		char **partsb = (char **)malloc(40 * sizeof(char *));

		int i=0;
	    char* token1 =strtok(t,"<");
	    while (token1 != NULL)
	    {
	         partsb[i] = (char *)malloc(400 * sizeof(char));
	        strcpy(partsb[i],token1);
	        token1 = strtok(NULL,"<");
	        i++;
	    }
		
	    pid_t p1; 
	    p1 = fork(); 
	    if (p1 < 0) { 
	        printf("\nCould not fork"); 
	        return 0; 
	    } 
	  
	    if (p1 == 0) { 
	       char **partsa = (char **)malloc(40 * sizeof(char *));
	    	char **partsc = (char **)malloc(40 * sizeof(char *));

	        parse_input(partsb[0],partsa);
	        parse_input(partsb[i-1],partsc);
	    
	       
	        int fd = open(partsc[0], O_RDONLY);  
	        dup2(fd, STDIN_FILENO); 
	        
	        if (execvp(partsa[0], partsa) < 0) { 
	            printf("\nCould not execute command 1.."); 
	             exit(0); 
	        } 
	    } 
	}
	else if(flag ==1 && flag1==1)
	{
		int f=0;
		for(int i = strlen(t)-1;i>=0;i--)
		{
			if(t[i]=='>')
			{
				if(t[i-1] == '>')
				{
					f=1;
				}
				break;
			}
		}
		int c=0,c1=0;
		for(int i=strlen(t)-1;i>=0;i--)
		{
			if(t[i] == '<')
				c++;
			else if(t[i] =='>')
				break;
		}
		for(int i=strlen(t)-1;i>=0;i--)
		{
			if(t[i] == '>')
			{
				c1++;
				t[i]='<';
			}
			else if(t[i] =='<')
				break;
		}
		int i = 0;
		
		char **partsb = (char **)malloc(40 * sizeof(char *));

	    char* token1 =strtok(t,"<");
	    while (token1 != NULL)
	    {
	         partsb[i] = (char *)malloc(400 * sizeof(char));
	        strcpy(partsb[i],token1);
	        token1 = strtok(NULL,"<");
	        i++;
	    }

	    pid_t p1; 
	    p1 = fork(); 
	    if (p1 < 0) { 
	        printf("\nCould not fork"); 
	        return 0; 
	    } 
	  
	    if (p1 == 0) { 
	        char **partsa = (char **)malloc(40 * sizeof(char *));
	        char **partsc = (char **)malloc(40 * sizeof(char *));
	        char **partsd = (char **)malloc(40 * sizeof(char *));

	        parse_input(partsb[i-c1-1],partsa);
	        parse_input(partsb[i-c-1],partsc);
	        parse_input(partsb[0],partsd);
	 
	        int fd = open(partsa[0], O_RDONLY);  
	        dup2(fd, STDIN_FILENO); 

	        int fd1; 
	        if(f==1)
	        	fd1 =open(partsc[0],O_CREAT | O_WRONLY| O_APPEND,S_IRWXU|S_IRWXO|S_IRWXO);
	        else
	        	fd1 =open(partsc[0],O_CREAT | O_WRONLY| O_TRUNC,S_IRWXU|S_IRWXO|S_IRWXO);

	        dup2(fd1, STDOUT_FILENO);
	     	   
	        if (execvp(partsd[0], partsd) < 0) { 
	            printf("\nCould not execute command 1.."); 
	             exit(0); 
	        } 
	    } 
	}
		
}