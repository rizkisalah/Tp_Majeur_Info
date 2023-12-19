#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>




int main(int argc, char* argv[]){
  char * serveur=argv[1];
  char * fichier=argv[2];
  int sfd;
  struct addrinfo serv;
  struct addrinfo *result;
  memset(&serv, 0, sizeof serv);
 
  
  serv.ai_family = AF_UNSPEC; 
  serv.ai_socktype=SOCK_DGRAM;
  serv.ai_flags= AI_PASSIVE;
  serv.ai_protocol=0;
  serv.ai_canonname=NULL;
  serv.ai_addr=NULL;
  serv.ai_next=NULL;
 
 int stt = getaddrinfo(serveur,"1069",&serv,&result);
  
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
  }
  
  char * mode = 'octet';
 
  int SIZE = 3+sizeof(fichier)+sizeof(mode)+1 ; 
  
  char * RRQ = malloc(SIZE);
 
  RRQ[0]=0; 
  RRQ[1] =1;
  strcpy (RRQ+2, fichier); 
  RRQ[2+strlen (fichier)] = 0; 
  strcpy (RRQ+3+strlen(fichier) , mode) ; 
  RRQ[3+strlen (fichier)+strlen (mode)] = 0; 
  int lenRRQ = 2+strlen (fichier)+strlen (mode)+1+1;
  
  int nSend=sendto (sfd, RRQ, lenRRQ,0, result->ai_addr,result->ai_addrlen);
  printf("number of bits send =%d\n", nSend);
  
  int block_size=512;
  char buf[512]={}; 
  ssize_t nRecv=recvfrom(sfd,buf,block_size ,0, result->ai_addr,&(result->ai_addrlen));
  
  char ACK[50]={}; ACK[0]=0; ACK[1]=4; 
  int lenACK=4; 
  int f =open(fichier, O_CREAT|O_WRONLY|O_TRUNC, 0x777); 
  ACK[2]=buf [2]; ACK[3]=buf[3];
  write(f,buf+4,block_size);
  nSend=sendto (sfd,ACK, lenACK, 0, result->ai_addr,result->ai_addrlen); 
  nRecv=recvfrom(sfd, buf,block_size+4,0,result->ai_addr,&(result->ai_addrlen));
  printf("nbr bits recv:%d \n°d d %d sd details: %x\n", (int)nRecv,buf[0],buf[1],buf[2],buf[3],buf[4]);
  }
