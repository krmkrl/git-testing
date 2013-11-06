#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    if (argc < 2) {
        printf("Usage: exec_wrapper <full/path/to/program>\n");
        return 0;
    }

    pid_t pid;
    int status;
    
    //copy arguments, excluding the first
    char* exec_args[argc - 1];
    int i;
    for (i=0; i < (argc - 1); i++) {
        exec_args[i] = argv[i+1];
    }
    exec_args[i] = NULL;

    //fork child process
    pid = fork();
    if (pid == -1) {
        printf("Error forking process\n");
        return 1;
    } else if (pid == 0) {
        //child
        execv(exec_args[0], exec_args);
        printf("Error, problem with execv\n");
        return 1;
    } else {
        //parent
        wait(&status);
        printf("Child exit with status: %d\n", status);
    }

    return 0;
}
