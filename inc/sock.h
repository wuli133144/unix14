#include"../inc/unix_error.h"

#include<sys/socket.h>
#include<stdarg.h>
#include<stddef.h>
#include<signal.h>
#include<sys/types.h>
#include<netdb.h>

#include<arpa/inet.h>

 
#define LISTEN_NUM  100

/*@socket start@*/
int Socket(int domain,int type,int protocol){
    int rval;
    if((rval=socket(AF_INET,SOCK_STREAM,0))<0){
        unix_error("socket");
    }
    return rval;
}

/*@socket end@*/


/*@connect start@*/

int Connnect(int clientfd, struct sockaddr *addr,int len){
    int rval;
    if((rval=connect(clientfd,addr,len))<0){
        unix_error("connect");
    }
    return rval;
}
/*@connect end@*/


/*@ bind start@*/
int Bind(int sockfd,const struct sockaddr*addr,socklen_t len){
     int rval;
     if((rval=bind(sockfd,addr,len))<0){
         unix_error("bind");
     }
     return rval;
}
/*@bind end@*/

/*@listen start@*/
int Listen(int listenfd,int num){
    int rval;
    if((rval=listen(listenfd,num))<0){
        unix_error("listen");
    }
    return rval;
}
/*@listen end@*/

/*accept start*/
int Accept(int listenfd,struct sockaddr *addr,socklen_t *len){
    int rval;
    if((rval=accept(listenfd,addr,len))<0){
          unix_error("accept");
    }
    return rval;
}
/*accept end*/

/*@getaddrinfo handler@*/
int Getaddrinfo(const char *hostname,\
const char *service,                 \
const struct addrinfo *hints,        \
struct addrinfo**info)
{      
       int rval;
       if((rval=getaddrinfo(hostname,service,hints,info))<0){
           unix_error("getaddrinfo");
       }
     return rval;
}
/*@getaddrinfo handler@*/


/*@getnameinfo @*/
int Getnameinfo(const struct sockaddr *restrict sa, socklen_t salen, \
       char *restrict node, socklen_t nodelen, char *restrict service, \
       socklen_t servicelen, int flags){
            int rval;
            if((rval=getnameinfo(sa,salen,node,nodelen,service,servicelen,flags))<0){
                unix_error("getnameinfo");
            }
            return rval;
       }
/*@getnameinfo end@*/

/*@freeaddrinfo@*/
void Freeaddrinfo(struct addrinfo *p){
      freeaddrinfo(p);
}
/*@freeaddrinfo@*/

/*Setsockopt start*/
int Setsockopt(int sock, int level, int optname, const void *optval, socklen_t optlen){
    int rval;
    if((rval=setsockopt(sock,level,optname,optval,optlen))<0){
        unix_error("setsockopt");
    }
    return rval;
}
/*Setsockopt*/

/*@open_clientfd start@*/
int open_clientfd(const char *hostname,char* port){
   
      int clientfd;
      struct addrinfo hints,*listp,*p;
      memset(&hints,0,sizeof(struct addrinfo));
      //hints.ai_family=AF_INET;
      hints.ai_socktype=SOCK_STREAM;
      hints.ai_flags=AI_NUMERICSERV;
      hints.ai_flags|=AI_ADDRCONFIG;
      Getaddrinfo(hostname,port,&hints,&listp);

      for(p=listp;p;p=p->ai_next){

          if((clientfd=socket(p->ai_family,p->ai_socktype,p->ai_protocol))<0){
              continue;
          }
          if((connect(clientfd,p->ai_addr,p->ai_addrlen))!=-1){
                    break;//success
          }
          close(clientfd);//failed
      }
      Freeaddrinfo(listp);
      if(p==NULL){
          return -1;//failed
      }
     return clientfd;

}
/*open_clientfd end*/

/*open_listenfd start*/
int open_listenfd(char *port){
      
  struct addrinfo hints,*listp,*p;
  int listenfd,optval;
  memset(&hints,0,sizeof(struct addrinfo));
   
   hints.ai_socktype=SOCK_STREAM;
   hints.ai_flags=AI_NUMERICSERV;
   hints.ai_flags=AI_PASSIVE|AI_ADDRCONFIG;
   
   Getaddrinfo(NULL,port,&hints,&listp);

   for(p=listp;p;p=p->ai_next){
          if(listenfd=(socket(p->ai_family,p->ai_socktype,p->ai_protocol))<0){
              continue;
          }
          Setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(const void *)&optval,sizeof(int));
          if((bind(listenfd,p->ai_addr,p->ai_addrlen))==0){
              break;
          }
          close(listenfd);
   }
    
    Freeaddrinfo(listp);
    if(p==NULL){return -1;}
    if(listen(listenfd,LISTEN_NUM)<0){
           close(listenfd);
           return -1;
    }
   return listenfd;

}
/*open_listenfd end*/

typedef void (*sighandler_t)(int);
/*@signal handler@*/
sighandler_t Signal(int signum,sighandler_t hander){
    
    struct sigaction newaction,oldaction;

    newaction.sa_handler=hander;
    sigemptyset(&newaction.sa_mask);
    newaction.sa_flags=SA_RESTART;

    if(sigaction(signum,&newaction,&oldaction)<0){
        unix_error("sigaction");
    }
    return (oldaction.sa_handler);
}
/*@signla hander end@*/


/*sigprocmask*/
int Sigprocmask(int how,const sigset_t *set,sigset_t *oset){
      int rval;
      if((rval=sigprocmask(how,set,oset))<0){
          unix_error("sigprocmask");
      }
      return rval;
}
/*@sigprocmsk@*/

/*@memory operation@*/

/*@Malloc operation start@*/

void *Malloc(size_t length){
   
   void *ptr=NULL;
   if((ptr=malloc(length))==NULL){
       unix_error("malloc error");
   }
    return ptr;
}

/*@Malloc operation end@*/

/*@Realloc  memory@*/
 
 void * Realloc(void *base,size_t sz){
     void *ptr=NULL;
     if((ptr=realloc(base,sz))==NULL){
         unix_error("realloc error");
     }
     return ptr;
 }
/*@Realloc memory@*/
/*@calloc @*/
void *Calloc(unsigned int n,ssize_t length){
    void *rptr=NULL;
    if((rptr=calloc(n,length))==NULL){
        unix_error("calloc error");
    }
    return rptr;
}
/*@calloc end@*/