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
void signal_handler(int sig_num) {

    pid_t process = forsig;
    if (process > 0) {
        kill(process, sig_num);
        printf("\n");
        fflush(stdout);
    } else {
        printf("\n");
        print_dirname(size);
        fflush(stdout);
    }
}
// void ctrlz(int sig_num) {

//     pid_t process = forsig;
//     if (process > 0) {
//         kill(process, sig_num);

//         bg1[count] = process;        
//             bg2[count] = process;        
            
//             for(int w = 0;w<strlen(abcd);w++)
//              {
//                 if(abcd[w] == ' ')
//                     break;
//                  names[count][w] = abcd[w];
//              }
//             count+=1;




//         printf("\n");
//         fflush(stdout);
//     } else {
//         printf("\n");
//         print_dirname(size);
//         fflush(stdout);
//     }
// }