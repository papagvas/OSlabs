#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
//#include <fcntl.h>
#include <setjmp.h>
//#define die(e) do { fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE); } while (0);


int interruptions_counter = 0;
sigjmp_buf bf;

void termination_handler (int signum) {
    if (interruptions_counter < 11) {
      printf("%s\n","Ctrl + c" );
      interruptions_counter = interruptions_counter + 1;
      siglongjmp(bf, 1);
    }
    else {
        exit(0);
    }
}


void main() {
    struct sigaction mySigint;
    mySigint.sa_handler = termination_handler;
    mySigint.sa_flags = 0;
    sigprocmask(0,NULL,&mySigint.sa_mask);
    sigaction(SIGINT,&mySigint,NULL);
    sigsetjmp(bf,1);
    char filename[100];
    char regex[100];
    int pipes[2];
    sigsetjmp(bf,1);
    pipe(pipes); //need to add error handling
    char foo[4096];
    sigsetjmp(bf,1);
    printf("%s\n","Enter the filename");
    scanf("%s", &filename[0]); //need to add error handling
    sigsetjmp(bf,1);
    printf("%s\n","Enter the regex");
    scanf("%s",&regex); //need to add error handling
    if (fork() == 0) {
        sigsetjmp(bf,1);
        dup2(pipes[1], STDOUT_FILENO); //need to add error handling
  	    close(pipes[0]);
        close(pipes[1]);
        execl("/bin/grep/","grep",regex,filename,(char *) NULL);
    }
    else {
        sigsetjmp(bf,1);
        close(pipes[1]);
        int nbytes = read(pipes[0],foo,sizeof(foo));
        execl("./b.exe","b.exe",foo,(char *) NULL);
        wait(NULL);
    }
}
