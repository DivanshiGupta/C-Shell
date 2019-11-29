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
int execute_input(char **str,int len,int bg)
{
	if(bg ==1)
	{
		execArgs(str,1);
		return 0;
	}
	if(len ==1)
	{	//PWD
		char a[] ="pwd";
		if(strcmp(str[0],a) == 0)
		{
			int pATH_MAX = 100000;
			char buff[pATH_MAX];
			if (getcwd(buff, pATH_MAX) != NULL)
			{
				printf("%s\n",buff);
			}
			return 0;
		}	
	}
	//ECHO
	char a1[]="echo";
	if(strcmp(str[0],a1) == 0)
	{
		for(int i=1;i<len;i++)
		{
			printf("%s ",str[i]);
		}
		printf("\n");
		return 0;		
	}
	//SETENV
	char b[] ="setenv";
	if(strcmp(b,str[0]) == 0)
	{
		char *s = *environ;
		for(int i=1;s;i++)
		{
			if(str_comp(s,str[1],strlen(str[1])) == 0)
			{
				char d[strlen(str[2])];
				strcpy(d,str[2]);
				int y =strlen(d);
				y-=2;
				char e[y+1];
				for(int j=0;j<y;j++)
				{
					e[j] = d[j+1];
				}
				e[y] = '\0';
				int a = strlen(str[1]) +  strlen(e) + 1;
				char c[a+1];
				strcpy(c,str[1]);
				strcat(c,"=");
				strcat(c,e);
				 strcpy(*(environ + i-1) , c);
				break;
			}
			s = *(environ+i);
		}
		return 0;
	}	
	//UNSETENV
	char b11[]="unsetenv";
	if(strcmp(b11,str[0]) == 0)
	{
		char *s = *environ;
		for(int i=1;s;i++)
		{
			if(str_comp(s,str[1],strlen(str[1])) == 0)
			{
				 char c[]="";
				 strcpy(*(environ + i-1) , c);
				break;
			}
			s = *(environ+i);
		}
		return 0;
	}	

	//JOBS
	char a11[]="jobs";
	if(strcmp(str[0],a11) == 0 && len==1)
	{
		for(int i=0;i<count;i++)
		{
				char a2[]="/proc/";
				char a3[]="/stat";
				int pp = bg2[i];
				char a4[100];
				sprintf(a4,"%d",pp);
				strcat(a2,a4);
				strcat(a2,a3);

				int fd = open(a2,O_RDONLY);
			if(fd != -1)
			{
				// printf("%d\n",fd);
				char b[1000];

				int l11 =read(fd,&b,1000);
				
				char **parts1 = (char **)malloc(40 * sizeof(char *));
			    	
			    for (int i = 0; i < 50; i++)
			        parts1[i] = (char *)malloc(400 * sizeof(char));

			    int i1 = parse_input(b,parts1);
	  
				// printf("%s\n",parts1[2]);

				printf("[%d] ",i+1);

				// printf("%s\n",parts1[2]);
			    char a6[]="R";
			    char a7[]="S";
			    char a8[]="D";
			    char a9[]="T";
			    char a10[]="t";
			    char a11[]="Z";

			    
			    if(strcmp(parts1[2] , a6) ==0)
			    {
			    	printf("Running ");
			    }
			   	else if(strcmp(parts1[2],a9) == 0 || strcmp(parts1[2],a10) == 0)
			    {
			    	printf("Stopped ");
			    }
			    else if(strcmp(parts1[2],a7) == 0 || strcmp(parts1[2],a8) == 0)
			    {
			    	printf("Sleeping ");
			    }
			    else if(strcmp(parts1[2],a11) == 0)
			    {
			    	printf("Defunct/Zombie ");
			    }

				// fgets(buf,32,fd);
				// pid_t p = bg2[i];
				// printf("[%d] ",i+1);
				// char *rr = /proc/p/status;
				// printf("%s\n",rr);
				// if(bg1[i] == -1)
				// {
				// 	printf("Stopped ");
				// 	// printf("%s\n ",proc/);
				// }
				// else
				// 	printf("Running ");
			    printf("%s",parts1[1]);
				// printf("%s/ [",names[i]);
				printf(" [%d]\n",bg2[i]);
			}

		}
		return 0;
	}
	//kjob
	char a12[] = "kjob";
	if(strcmp(str[0],a12)== 0)
	{
		if(len < 3)
		{
			printf("Error :more arguments required\n");
			return 0;
		}
		int sig,p;
		sscanf(str[1],"%d",&p);
		int pi = bg2[p-1];
		sscanf(str[2],"%d",&sig);
		 kill(pi,sig);
		 return 0;
	}	
	//OVERKILL
	char a13[]="overkill";
	if(strcmp(str[0], a13)==0)
	{
		if(len > 1)
		{
			printf("Error : Incorrect arguments\n");
		}
		for(int i=0;i<count;i++)
		{
			if(bg1[i] != -1)
			{
				kill(bg2[i],9);
			}
		}
		return 0;
	}
	//QUIT
	char a6[]="quit";
	if(strcmp(str[0],a6) == 0)
	{
		exit(0);
	}
	//FG
	char a7[]="fg";	
	if(strcmp(str[0] , a7) == 0)
	{   
		pid_t p11 = getpid();		

		if(len > 2)
		{			
			printf("Error : Wrong number of arguments\n");		
		}
		if(len == 1)
		{
			printf("Error : pass arguments\n");
		}
		int x1;
		sscanf(str[1],"%d",&x1);
		if(x1 <= count)
		{
			pid_t pidnumber;
	   		 pidnumber = bg2[x1 - 1];
	   		 // printf("%d\n",pidnumber);
		    signal(SIGTTOU, SIG_IGN);
		    signal(SIGTTIN, SIG_IGN);
		    tcsetpgrp(0, getpgid(pidnumber));
		    kill(pidnumber, SIGCONT);
		    waitpid(pidnumber, NULL, WUNTRACED);
		    // signal(SIGTTOU, SIG_IGN);
		    tcsetpgrp(0, p11);
		    signal(SIGTTOU, SIG_DFL);
    		signal(SIGTTIN, SIG_DFL);


		}
		else
		{
			printf("Error : Non existent job number\n");
		}
		return 0;

	}
		// return 0;

	
	//BG
	char a8[]="bg";
	if(strcmp(str[0],a8) ==0)
	{
		if(len == 1)
		{
			printf("Error : Give job number as argument\n");
		}	
		else if(len == 2)
		{
			int x1;
			sscanf(str[1],"%d",&x1);
			if(x1 <= count)
			{
				pid_t pidd = bg2[x1-1];
				 kill(pidd, SIGTTIN);
    			kill(pidd, SIGCONT);
			}
			else
			{
				printf("Error : Non existent job number\n");
			}
		}
		else
		{
			printf("Error : Less arguments required\n");
		}
		return 0;

	}
	//CRONJOB
	char a9[]="cronjob";
	if(strcmp(str[0],a9) == 0)
	{
		if(len!=7)
		{
			printf("Error : Give 6 arguments");
			return 0;
		}
		int x1,x2,x4,x3;
		sscanf(str[6],"%d",&x2);
		sscanf(str[4],"%d",&x1);
		 x4 = x2/x1;
		 
		 pid_t pid = fork();

	    if (pid == 0) 
	    {
	        setpgid(0, 0);
	        close(STDERR_FILENO);
	        sleep(x1);
	        while(x4--) {
	 
				char **parts1 = (char **)malloc(40 * sizeof(char *));
         		 parts1[0] = (char *)malloc(400 * sizeof(char));
         		 strcpy(parts1[0] , str[2]);
	            pid_t p = fork();
	            if (p == -1)
	            {
	                printf("Error : Fork\n");
	            }
	            if (p == 0) 
	            {
	                if (execvp(parts1[0], parts1) == -1)
	                {
	                    printf("Error : execvp\n");
	                }
	                exit(0);
	            }    
	            sleep(x1);
	        }
	    }
	    return 0;
	}
	//CD
	int r1 =cd_command(str,len);
	if(r1){return 0;}
	int r2=ls_command(str,len);
	if(r2){return 0;}
	 int r3=pinfo_pid(str,len);
	if(r3){return 0;}
	
	execArgs(str,bg);
}
