#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 


#include "ls_command.h"

#define MAX_LINE 80
#define MAX_ARGS 10

int main(){
    char input[MAX_LINE];
    char *token;
    char *argv[MAX_ARGS];

    while(1){
        //prompt
        printf("myshell> ");

        //read commend
        fgets(input, MAX_LINE, stdin);
        //printf("%s\n", input);

        //tokenize input
        token = strtok(input, " \n\t");
        int i = 0;
        while(token != NULL) {
            argv[i++] = token;
            token = strtok(NULL, " \n\t");
        }

        argv[i] = NULL;

        if(argv[0]==NULL){
            continue;
        }
        
        if(strcmp(argv[0], "exit")==0){
            printf("Goodbye~\n");
            exit(0);
        } else if (strcmp(argv[0], "cd")==0){
            chdir(argv[1]);
        } else if(strcmp(argv[0], "pwd")==0){
            getcwd(input, MAX_LINE);
            printf("%s\n", input);
        } else if(strcmp(argv[0], "ls")==0){
            my_ls();
        } else if(strcmp(argv[0], "cat")==0){
            if (argv[1] == NULL) {
                printf("Usage: cat <filename>\n");
            } else {
                FILE *file = fopen(argv[1], "r");
                if (file == NULL) {
                    perror("cat");
                } else {
                    char line[MAX_LINE];
                    while (fgets(line, sizeof(line), file)) {
                        printf("%s", line);
                    }
                    fclose(file);
                }
            }
        } else {
            pid_t pid = fork();
            if (pid == 0) {
                // Child process
                execvp(argv[0], argv);
                perror("execvp");
                exit(1);
            } else if (pid > 0) {
                // Parent process
                wait(NULL);
            } else {
                perror("fork");
            }
        }
    
        

    }
    return 0;
}