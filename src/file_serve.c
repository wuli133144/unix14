
#include"../inc/sock.h"


#define BUFSIZE  1024


void err_handler(char *msg){

}


int main(int argc,char **argv){
  
  int listenfd,clientfd;
  char msg[BUFSIZE];
  memset(msg,0,sizeof(BUFSIZE));
  int str_len,i;

  struct sockaddr_in listensock,clientsock;

  socklen_t client_len;
  int read_cnt;
  FILE*fp=NULL;
   fp=fopen("file_serve.c","rb");
  if(argc!=2){
      unix_error("argc is not ");
  }

  //socket 
   listenfd=Socket(AF_INET,SOCK_STREAM,0);
  //BIND
   memset(&listensock,0,sizeof(struct sockaddr_in));
   listensock.sin_family=AF_INET;
   listensock.sin_addr.s_addr=htonl(INADDR_ANY);
   listensock.sin_port=htons(atoi(argv[1]));

   Bind(listenfd,(struct sockaddr *)&listensock,sizeof(struct sockaddr));
   
   Listen(listenfd,10);
   
   client_len=sizeof(clientsock);
   
   clientfd=Accept(listenfd,(struct sockaddr*)&clientsock,&client_len);

   while(1){
          read_cnt=fread((void *)msg,1,BUFSIZE,fp);
          if(read_cnt<BUFSIZE){
              write(clientfd,msg,read_cnt);
              break;
          }
          write(clientfd,msg,BUFSIZE);
   }
   shutdown(clientfd,SHUT_WR);
   read(clientfd,msg,BUFSIZE);
   printf("%s",msg);
   fclose(fp);
   close(clientfd);
   close(listenfd);
   return 0;

}