
#include"../inc/sock.h"
#include<unistd.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>



#include<sys/types.h>
#include<sys/wait.h>

 pid_t Fork(){
     pid_t pid;
     if((pid=fork())<0){
         unix_error("fork error");
     }
     return pid;
 }

int Open( const char * fd,int flag,mode_t mode){
     int rval;
     if((rval=open(fd,flag,mode))==-1){
         unix_error("open failed!");
     }
     return rval;
}


#define MODE   S_IRUSR|S_IWUSR


int main(){
    pid_t pid;
    int fd;
    int i;

    pid=Fork();
    fd=Open("r.dat",O_RDWR,MODE); 
   
    if(pid){//father
     
    fprintf(stdout,"father pid=%d\n",getpid());
   
     close(fd);
     //write(fd,"jackwu father\n",100);
     //wait(&i);
     while(1);

    }else{//child
    #if 0
       int newfd=fd;
       fd=Open("file_client.c",O_RDONLY,MODE);
       write(newfd,"jackwu child\n",100);
    #endif
    #if 1
        
         fd=STDOUT_FILENO; 

    #endif
    fprintf(stdout,"child pid=%d\n",getpid());
     while(1);
       exit(0);
  };
  
    return 0;
}
