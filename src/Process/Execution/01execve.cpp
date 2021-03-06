/**
 * File             : 01execve.cpp
 * Date of creation : January 1 2013
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * The exec() call family replaces the child process (which is identical to the parents process when forked)
 * by a new one.
 * In this example, we will make our childProcess run the ls command using the execve() command.
 * execve() requires you to specify the file path and environment variable (PATH)
 *
 * Output :
 * --------------------------------------
 * Parent Process ID : <PID-Parent> .
 * Child Process ID : <PID-Child> .
 * ----------------- .
 * 
 * total xx
 * -rw-r--r-- 1 <user> <user> 2276 Jan  1 17:36 01execve.cpp
 * -rw-r--r-- 1 <user> <user> 1621 Dec 31 15:50 02execlp.cpp
 * -rw-r--r-- 1 <user> <user> 1621 Jan  1 17:03 03execvp.cpp
 * drwxr-xr-x 2 <user> <user> 4096 Jan  1 16:59 childProc 
 * --------------------------------------
 * 
 * References :
 * - http://www.die.net
 * - http://linux.die.net/man/2/execve
 *
 */

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *arg[])
{
    pid_t childPID;
    childPID = fork(); 

    if(childPID >= 0)
    {
        if(childPID == 0) // Code executed in the child process
        {
            printf("Child Process ID : %i .\n", getpid());
            printf("----------------- \n\n"); // Output formatting

            char *env[] = {NULL};
            char *args[3] = {NULL};
            args[0] = "ls"; // <from documentation> : By convention, the first of these strings should contain the filename associated with the file being executed.
            args[1] = "-l"; // Argument for ls
            args[2] = NULL; // Argument for ls; This line is optional since the array was initialised to NULL

            int execution = execve("/bin/ls", args, env); // int execve(const char *filename, char *const argv[], char *const envp[])
            
            if( execution < 0) // If the execution is a sucess, the exec() call won't return; If error, it will return -1
            {
                printf("Execution failed with error : %i .\n", errno);
                return 1;
            }
        }
        else // Code executed in the parent process
        {
            printf("Parent Process ID : %i .\n", getpid());
        }
    }
    else if(childPID < 0)
    {
        printf("Fork failed with error code : %i .\n", errno);
        return 1;
    }

    return 0;
}