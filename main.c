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

extern char **environ;

int size;
char abcd[1000];
int  bg1[1000];
int bg2[1000];
char tilda[100];
int count =0;
char names[100][100];
int forsig =0;

#include"parse_input.h"
#include"bg_exit.h"
#include"start_init.h"
#include"print_dirname.h"
#include"get_input.h"
#include"str_comp.h"
#include"exec.h"
#include"cd.h"
#include"ls.h"
#include"pinfo_pid.h"
#include"execute_input.h"
#include"check_redirection1.h"
#include"parse_pipes.h"
#include"signal_handler.h"
#include"ctrlz.h"
int main()
{
	int co=0;
	start_init();
	signal(SIGINT, signal_handler);
	signal(SIGTSTP, ctrlz);

	while(1)
	{

		forsig =0;
         bg_exit();
		
		if(co ==0)
		{
			int pATH_MAX = 100000;
			char buff[pATH_MAX];
			getcwd(buff,pATH_MAX);
			 size = strlen(buff);
			 for(int i=0;i<size;i++)
			 {
			 	tilda[i] = buff[i];
			 }
		}
		co =1;
		int l1 = print_dirname(size);
		if(l1 == 1) 
			return 0;
		char *t = get_input();


			strcpy(abcd,t);
			if(t[0] != 10)
			{
				int f=0;
				t[strlen(t) -1] ='\0';

				for(int i=0;i<strlen(t);i++)
				{
					if(t[i] == '|')
						f=1;
				}
				if(f==1)
				{
					parse_pipes(t);
				}
				else
				{
					int yy =check_redirection(t);
					if(yy == 2)
					{
						// printf("1\n");
						char **parts = (char **)malloc(40 * sizeof(char *));

						int i = parse_input(t,parts);
						int bg =0;
					 	char a3[]="&";
					 	if(strcmp(parts[i-1],a3) ==0  )
					 	{
					 		bg =1;
					 		parts[i-1] ='\0';
					 	}
					    execute_input(parts,i,bg);  
					   
					}
				}
			}
		
	}
	return 0;
}