#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
        }

    }
    return 0;
}