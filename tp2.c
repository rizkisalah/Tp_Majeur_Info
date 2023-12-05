#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>



#define BUFFSIZE 128 
/*
struct timespec {
    //start_time, 
    time_t tv_sec;
    long tv_nsec;
};
*/
long long temps_exec( struct timespec start, struct timespec end){
    return (end.tv_nsec - start.tv_nsec)/100000000;
} 
int main() {
    
    char input[BUFFSIZE];
    int i, status;
    
    write(STDOUT_FILENO, "Bienvenue dans le Shell ENSEA.\n", 30);
    write(STDOUT_FILENO, "\nPour quitter, tapez 'exit'.\n", 28);
        
    while (1) {
        write(STDOUT_FILENO, "\nenseash % ", 11);
        ssize_t inputsRead = read(STDIN_FILENO, input, BUFFSIZE);
        char *commande;
        commande = malloc(inputsRead-1);
        commande = strncpy(commande, input, inputsRead-1);
        
        if (strcmp(commande, "exit") == 0) {
            write(STDOUT_FILENO, "Bye Bye!\n", 10);
            break; 
        }

        
        pid_t pid = fork();
        if (pid == 0) { 
            struct timespec start_time, end_time;
            clock_gettime(CLOCK_REALTIME, &start_time);
            pid_t ppid = getpid();
            printf("PID | %d\n",ppid);
            //sleep(10);
            execlp(commande, commande, (char *)NULL);
        }
        else {
            waitpid(pid, &status, 0);
            char *cmd = malloc(40);
            //clock_gettime(CLOCK_MONOTONIC, &end_time);
            
            if (WIFEXITED(status)) {
                /*
                    //write(STDOUT_FILENO, "[exit:", 6);
                    sprintf(cmd,"[exit: %d",WEXITSTATUS(status));
                    write(STDOUT_FILENO,cmd,10); 
                    write(STDOUT_FILENO, "] % ", 4);
                */
               struct timespec start_time, end_time;
               clock_gettime(CLOCK_REALTIME, &end_time);
               sprintf(cmd, "[exit:%d|%lldms] %% ", WEXITSTATUS(status), temps_exec(start_time,end_time));
               write(STDOUT_FILENO, cmd, strlen(cmd));
                
            } else if (WIFSIGNALED(status)) {
                /*
                    //write(STDOUT_FILENO, "[sign:", 6);
                    sprintf(cmd,"[sign: %d", WTERMSIG(status));
                    write(STDOUT_FILENO, cmd, 10);
                    write(STDOUT_FILENO, "] % ", 4);
                */  
                struct timespec start_time, end_time;
                clock_gettime(CLOCK_REALTIME, &end_time);
                sprintf(cmd, "[sign:%d|%lldms] %% ", WTERMSIG(status), temps_exec); 
                write(STDOUT_FILENO, cmd, strlen(cmd)); 
                
            }
        }   
    }
    return 0;
}
