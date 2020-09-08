#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()  {
    int pipe_descriptors[2];
    pipe(pipe_descriptors);

    if (fork() == 0)  {
        close(pipe_descriptors[0]);
        close(1);
        dup2(pipe_descriptors[1], 1);
        execl("/usr/bin/find", "find", "-ctime", "-7", "-ls", (char *) NULL); //запускаю шелл скрипт имя файла - дата создания - режим доступа
    }
    else  {
        wait(NULL);
        char buffer[1000];
        int nbytes = read(pipe_descriptors[0], buffer, sizeof(buffer));
        FILE* file;
        if ((file=fopen("info.txt", "w"))==NULL)  {
            fprintf(stderr, "Can't open file info.txt");
            exit(2);
        }
        else  {
            fprintf(file, "%s\n", buffer, nbytes);
            fclose(file);
        }
        FILE* fptr;
        fptr = fopen("info.txt", "r");
        if (fptr == NULL) {
          printf("Cannot open file \n");
          exit(0);
        }
        char  c = fgetc(fptr);
        while (c != EOF) {
          printf ("%c", c);
          c = fgetc(fptr);
        }
        fclose(fptr);
    }
}
