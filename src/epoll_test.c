#include"../inc/epoll_inc.h"

#define BUFSIZE  1024

#define EPOLL_SIZE  100


/*malloc start*/
void *Malloc(size_t length){
   
   void *ptr=NULL;
   if((ptr=malloc(length))==NULL){
       UNIX_error("malloc error");
   }
    return ptr;
}

/*malloc end*/


int main(int argc,char **argv){
 
 struct epoll_event *pevent;
 struct epoll_event event;
 int epfd,even_cnt;
 int i=0;
 char buf[BUFSIZE];
 
 bzero(buf,BUFSIZE);



 epfd=Epoll_create(EPOLL_SIZE);
 
 pevent=Malloc(sizeof(struct epoll_event)*EPOLL_SIZE);

 event.events=EPOLLIN;
 event.data.fd=STDIN_FILENO;

  Epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);


  while(1){

    even_cnt=Epoll_wait(epfd,pevent,EPOLL_SIZE,-1);
    
    for(i=0;i<even_cnt;i++){
         
         if(pevent[i].data.fd==STDIN_FILENO){//stdard stdin
             int read_cnt;
             while((read_cnt=read(STDIN_FILENO,buf,BUFSIZE))!=0){
                    if(read_cnt==0){//eof
                        break;
                    }else if(read_cnt<0){
                        errno=EINTR;
                        break;
                    }else{
                        fputs(buf,stdout);
                        fflush(stdout);
                    }
             }
//////////////////////////////////////////////////////////////
          event.events=EPOLLOUT;
          event.data.fd=STDOUT_FILENO;
          Epoll_ctl(epfd,EPOLL_CTL_ADD,STDOUT_FILENO,&event);

         }else if(pevent[i].data.fd==STDOUT_FILENO){
               
                 int fd=open("epoll",O_RDWR|O_APPEND|O_CREAT,S_IRUSR|S_IWUSR);
                 if(fd<0){
                     goto err;
                 }
                 
                 dup2(STDOUT_FILENO,fd); 

         }

    }

  }
   err:
      UNIX_error("open error");
      
 close(epfd);
return 0;
}