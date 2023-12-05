//Bloc d'inclusions des bibliotheques 

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
/* Ce bloc comprend les bibliothèques essentielles au programme, telles que les bibliothèques standard d'entrées/sorties, de gestion des processus, de gestion du temps, etc.*/



//Définition de la taille du tampon
#define BUFFSIZE 128 
//Définit la taille du tampon utilisé pour stocker l'entrée de l'utilisateur.



/* Fonction qui calcul le temps d'exécution :
Cette fonction prend deux horodatages et retourne la différence en millisecondes entre eux.*/
long long temps_exec( struct timespec start, struct timespec end){
    return (end.tv_nsec - start.tv_nsec)/100000000;
} 



//Fonction principale (main)
int main() { 
    
    //Initialisation des variables et affichage d'un message de bienvenue:
    char input[BUFFSIZE];
    int i, status;
    
    write(STDOUT_FILENO, "Bienvenue dans le Shell ENSEA.\n", 30);
    write(STDOUT_FILENO, "\nPour quitter, tapez 'exit'.\n", 28);
    
    
    
    La boucle principale du programme qui continue jusqu'à ce que l'utilisateur tape "exit" :    
    while (1) {
    
    //Affiche le prompt, lit l'entrée utilisateur, alloue dynamiquement de la mémoire et copie l'entrée dans une variable:
    write(STDOUT_FILENO, "\nenseash % ", 11);
        ssize_t inputsRead = read(STDIN_FILENO, input, BUFFSIZE);
        char *commande;
        
        //la fonction malloc est utilisée pour allouer dynamiquement de la mémoire
        commande = malloc(inputsRead-1);
        commande = strncpy(commande, input, inputsRead-1);
        
        
        //Vérifie si l'utilisateur a saisi "exit" pour quitter le shell :
        if (strcmp(commande, "exit") == 0) {
            write(STDOUT_FILENO, "Bye Bye!\n", 10);
            break; 
        }

        //Le processus parent crée un processus enfant qui exécute la commande saisie : 
        pid_t pid = fork();
        if (pid == 0) { 
            // Code exécuté par le processus fils
            struct timespec start_time, end_time;
            clock_gettime(CLOCK_REALTIME, &start_time);
            pid_t ppid = getpid();
            printf("PID | %d\n",ppid);
            //sleep(10);
            execlp(commande, commande, (char *)NULL);
        }
        else {
            // Code exécuté par le processus parent
            
            
            //Le processus parent attend la fin du processus enfant.
            waitpid(pid, &status, 0);
            
            
            //la fonction malloc est utilisée pour allouer dynamiquement de la mémoire
            char *cmd = malloc(40);
            
            
            
        //Le code du parent gère les résultats de l'exécution du processus fils, affichant le statut de sortie ou le signal reçu.
            if (WIFEXITED(status)) {
                
               struct timespec start_time, end_time;
               clock_gettime(CLOCK_REALTIME, &end_time);
               sprintf(cmd, "[exit:%d|%lldms] %% ", WEXITSTATUS(status), temps_exec(start_time,end_time));
               write(STDOUT_FILENO, cmd, strlen(cmd));
                
            } else if (WIFSIGNALED(status)) {
                 
                struct timespec start_time, end_time;
                clock_gettime(CLOCK_REALTIME, &end_time);
                sprintf(cmd, "[sign:%d|%lldms] %% ", WTERMSIG(status), temps_exec); 
                write(STDOUT_FILENO, cmd, strlen(cmd)); 
                
            }
        }   
    }
    return 0;
}
