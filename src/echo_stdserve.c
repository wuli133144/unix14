
#include"../inc/sock.h"



#define BUFSIZE   

void err_handler(char *msg){

}


int main(int argc,char **argv){
  
  int listenfd,clientfd;
  char msg[BUFSIZE];
  memset(msg,0,sieof(BUFSIZE));
  int str_len,i;

  struct sockaddr_in listensock,clientsock;

  socklen_t client_len;
  FILE*readfd=NULL;
  FILE*writefd=NULL;
  if(argc!=2){
      unix_error("argc is not ");
  }

  //socket 
  listenfd=Socket(AF_INET,SOCK_STREAM,0);
  //BIND
   memset(&listensock,0,sieof(struct sockaddr_in));
   listensock.sin_family=AF_INET;
   litensock.sin_addr.s_addr=htonl(INADDR_ANY);
   listensock.sin_port=htons(atoi(argv[1]));

   Bind(listenfd,(struct sockaddr *)&listensock,sizeof(struct sockaddr));
   
   Listen(listenfd,10);
   
   client_len=sizeof(clientsock);
   for(i=0;i<5;i++){
    
    clientfd=Accept(listenfd,(struct sockaddr*)&clientsock,&client_len);
    if(clientfd<0){
        unix_error("connnect failed!");
    }

    readfd=fdopen(clientfd,"r");
    writefd=fdopen(clientfd,"w");
    
    while(!feof(readfd)){
        fgets(msg,BUFSIZE,readfd);
        fputs(msg,writefd);
        fflush(writefd);
    }
    
    close(readfd);
    close(writefd);
   }
   close(listenfd);
    return 0;
}
