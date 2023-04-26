/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ckelsey
 *
 * Created on February 6, 2023, 8:45 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 * 
 */
int main(int argc, char** argv) {
    int ch, forkID;
    char command[101], *args[101];
    args[0] = command;
    
    do  {
        int i = 0, argCounter = 1, frst = -1;
       
        printf("Your command>");

        while ( (ch = getchar()) != EOF && ch != '\n') {
            if (ch == ' ') {
                if (frst < 0) {
                    frst = i;
                }
                command[i++] = 0;
                args[argCounter++] = command + i;
            } else {
                command[i++] = ch;
            }
        }
        
        if (i == 0) {
            printf("invalid input");
            return EXIT_FAILURE;
        }
        
        if (frst < 0) {
            frst = i;
        }
        
        command[i] = 0;
        args[argCounter] = NULL;
        forkID = fork();
        
        if (forkID < 0) {
            printf("error!");
            return EXIT_FAILURE;
        } else if (forkID == 0) {
            if (command[frst-1] == '&') {
                command[frst-1] = 0;
            }
            execvp(args[0],args);
        } else {
            if (command[frst-1] != '&') {
                wait(NULL);
            }
        }
    } while (ch != EOF);
    return (EXIT_SUCCESS);
}

