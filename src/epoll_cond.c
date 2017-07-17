#include"../inc/epoll_inc.h"

#include"../inc/common.h"

#include"../inc/sock.h"


#define BUFSIZE  1024

#define EPOLL_SIZE  100


// /*malloc start*/
// void *Malloc(size_t length){
   
//    void *ptr=NULL;
//    if((ptr=malloc(length))==NULL){
//        UNIX_error("malloc error");
//    }
//     return ptr;
// }

// /*malloc end*/



int main(int argc,char **argv){

      int epfd;
      int i;
      struct epoll_event *pevent;
      struct epoll_event event;
      char buf[BUFSIZE];


     /*socket area*/
  int listenfd,clientfd;
  char msg[BUFSIZE];
  memset(msg,0,sizeof(BUFSIZE));
  int str_len;

  struct sockaddr_in listensock,clientsock;

  socklen_t client_len;
  int read_cnt;
  //FILE*fp=NULL;
  //fp=fopen("file_serve.c","rb");
  if(argc!=2){
      UNIX_error("argc is not ");
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
   
  // clientfd=Accept(listenfd,(struct sockaddr*)&clientsock,&client_len);
    /*@socket area@*/
    
   bzero(buf,BUFSIZE);

   //init event struct
   event.data.fd=listenfd;
   event.events=EPOLLIN;
   
   pevent=(struct  epoll_event *)Malloc(BUFSIZE*sizeof(struct epoll_event));

   int epfd=Epoll_create(BUFSIZE);

    Epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&event);

   while(1){
      
       int event_cnt=Epoll_wait(epfd,pevent,BUFSIZE,-1);
        for(i=0;i<event_cnt;i++){
            
            if(pevent[i].data.fd==listenfd){
                       
                       clientfd=Accept(listenfd,(struct sockaddr *)&clientsock,(socklen_t *)&client_len);
                       
                       event.events=EPOLLIN;
                       event.data.fd=clientfd;
                       Epoll_ctl(epfd,EPOLL_CTL_ADD,clientfd,&event);

                       printf("connect fd=%d\n",clientfd);
                       int read_cnt=0;
                    //    while((read_cnt=read(clientfd,buf,BUFSIZE))!=0){
                    //         if(read_cnt<0){//error eintr
                    //            errno=EINTR;
                    //            break;
                    //         }else{
                    //             write(clientfd,buf,BUFSIZE);
                    //         }
                    //    }

                
            }else if(pevent[i].data.fd==clientfd){
                       int read_cnt=0;
                        while((read_cnt=read(clientfd.data.fd,buf,BUFSIZE))!=0){
                             if(read_cnt<0){//error eintr
                                errno=EINTR;
                                break;
                             }else{
                                 write(clientfd.data.fd,buf,BUFSIZE);
                             }
                        }
            }
             
        }
       
   }
 




      




















    return 0;
}