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
int parse_input(char *t1,char **parts)
{ 
    int i = 0;
    char* token1 =strtok(t1," \t");
    while (token1 != NULL)
    {
         parts[i] = (char *)malloc(400 * sizeof(char));
        strcpy(parts[i],token1);
        token1 = strtok(NULL," \t");
        i++;
    }
    return i;
}   
