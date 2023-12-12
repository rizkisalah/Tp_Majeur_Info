#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>


int main(int argc, char* argv[]){
  char * serveur=argv[1];
  //char * fichier=argv[2];
  int sfd;
  struct addrinfo serv;
  struct addrinfo *result;
  memset(&serv, 0, sizeof serv);
  int stt = getaddrinfo(serveur,"1069",&serv,&result);
  
  serv.ai_family = AF_UNSPEC; 
  serv.ai_socktype=SOCK_DGRAM;
  serv.ai_flags= AI_PASSIVE;
  serv.ai_protocol=0;
  serv.ai_canonname=NULL;
  serv.ai_addr=NULL;
  serv.ai_next=NULL;

  
  if (stt != 0){
    fprintf (stderr, "getadrrinfo: %s\n",gai_strerror(stt));
    exit(EXIT_FAILURE);
  }
  else{
    fprintf (stderr, "getadarinfo: rigth\n" );
  }
  
  
  if (result ==  NULL){
    fprintf(stderr, "we can not login\n");
    exit(EXIT_FAILURE);
  }
  else{
    fprintf(stderr, "connected successfully\n");
  }

  sfd = socket (result->ai_family, result-> ai_socktype, result->ai_protocol);
  if (sfd==-1){
    fprintf(stderr, "erreur creation socket\n");
  }}
