/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ckelsey
 *
 * Created on February 16, 2023, 6:03 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
 * 
 */
int main(int argc, char** argv) {
    char *str = NULL, **tkns = NULL;
    size_t count = 0;
    int str_len, tkn_cnt = 0;

    if ((str_len = getline(&str, &count, stdin)) < 0) {
        printf("Error\n");
        return (EXIT_FAILURE);
    }
    str[str_len - 1] = 0;

    tkns = malloc(sizeof (char*)*count);

    int pipe_fd[2];

    if (pipe(pipe_fd) < 0) {
        printf("Pipe failed\n");
        return (EXIT_FAILURE);
    }

    tkns[tkn_cnt] = strtok(str, " ");
    while (tkns[tkn_cnt] != NULL) {
        if (strcmp(tkns[tkn_cnt], "|") == 0) {
            int pid = fork();
            if (pid < 0) {
                printf("Fork failed\n");
                return (EXIT_FAILURE);
            } else if (pid > 0) {
                tkns[tkn_cnt] = NULL;
                if (dup2(pipe_fd[1], STDOUT_FILENO) < 0) {
                    printf("Dup failed 1\n");
                    return (EXIT_FAILURE);
                }
                close(pipe_fd[0]);
                execvp(tkns[0], tkns);
            } else {
                tkn_cnt = -1;
            }
        }
        tkns[++tkn_cnt] = strtok(NULL, " ");
    }

    if (dup2(pipe_fd[0], STDIN_FILENO) < 0) {
        printf("Dup failed 2\n");
        return (EXIT_FAILURE);
    }
    close(pipe_fd[1]);
    execvp(tkns[0], tkns);

    free(tkns);
    free(str);

    return (EXIT_SUCCESS);
}

