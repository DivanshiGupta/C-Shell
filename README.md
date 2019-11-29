# C-Shell
A linux shell written in C to implement all inbuilt shell commands and some additional user-defined commands. It has functionalities to run both background and foreground processes.Piping , redirection and signal handling are also implemented.
Error handling is done wherever necessary.

# COMMANDS
1. ```echo [arguments]``` Print arguments on the shell.
2. ```pwd ```Shows the current working directory path.
3. ```pinfo <pid>``` Prints details of the process with given pid.If no argument is provided it takes pid of current process by    default. Details include : PID, Process Status, Memory , Executable Path.
4. ```cd ```Changes the directory
   ```cd [argument]``` Changes the current directory to the directory mentioned in argument.
   ```Cd ..```Takes back to the previous directory.
   ```cd or cd ~``` Take to the home direcotry.
   ```cd /``` Takes to root directory.
5. ```ls ```Lists all contents of current directory.
   ```ls -a``` Lists all hidden files also.
   ```ls -l``` Long Listing of all files.
   ```ls -al``` Long Listing of all files including hidden files.
6. ```setenv [var] [val]``` Sets value of the environment variable 'var' to value 'val'.
   ```unsetenv [var]``` Unsets the value of environment variable 'var'.
7. ```jobs``` Prints all the jobs in order of their creation along with their Unique Id,current status, Name of the job, Pid.  8.```fg [job_id]``` Brings the Job with given job_id to the foregound process i.e brings stopped or sleeping process to           foreground.
```bg[job_id]``` Takes the job with given job_id to the background process.
9. ```Ctrl-Z```Changes status of currently running job to stop and takes it to the background.
   ```Ctrl-C``` Interrupts the running process.
10. ```Overkill``` Kills all jobs at once. 
    ```kjob [job_id] [Signal_number]``` Sends signal 'signal_number' to process with given job_id.
11. ```cronjob -c <command name> -t <time_interval> -p <total period of running> ```eg. cronjob -c ls -t 3 -p 6 This command       should execute ls command after every 3 seconds until 6 seconds are elapsed.
12. ```quit``` Exits the shell.
13. Handles multiple piping and redirection properly.
