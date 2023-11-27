#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <string.h>

#define BUFFSIZE 128


int main(){
    
    char input[BUFFSIZE];
    //char *a[BUFFSIZE];
    int i, status;

    write(STDOUT_FILENO, "Bienvenue dans le Shell ENSEA.\n", 30);
    write(STDOUT_FILENO, "\nPour quitter, tapez 'exit'.\n", 28);
    

    while (1)
    {
        write(STDOUT_FILENO, "\nenseash % ", 11);
        ssize_t inputsRead = read(STDIN_FILENO, input, BUFFSIZE);
        char *commande;
        commande = malloc(inputsRead-1);
        commande  = strncpy(commande,input,inputsRead-1);
        

        if (strcmp(commande, "exit") == 0) {
            write(STDOUT_FILENO, "\nBye Bye!\n", 10);
            break; 
        }

        pid_t pid = fork();
        if(pid == 0){ 
            
            execlp(commande,commande,(char *)NULL);
        }
        else{
        wait(&status);
        //execl("/bin/ls","ls","-l",(char *)NULL);
        }   
    }
    
    
}