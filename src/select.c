
#include"../inc/epoll_inc.h"

#include<unistd.h>
#include<stdio.h>

#define BUFSIZE  1024

/*main start*/
int main(int argc,char **argv){
  
   fd_set readset;
   fd_set temps;
   int result,str_len;
   char buf[BUFSIZE];
   struct timeval tmval;
   FD_ZERO(&readset);
   FD_SET(STDIN_FILENO,&readset);//
   
    while(1){
  
      temps=readset;
    //  tmval.tv_sec=5;
     // tmval.tv_usec=0;
    Select(1,&readset,NULL,NULL,&tmval);

            if(FD_ISSET(STDIN_FILENO,&readset)){
                int read_cnt=read(STDIN_FILENO,buf,BUFSIZE);
                if(read_cnt==0){//eof
                        break;
                }else if(read_cnt<0){
                    errno=EINTR;//中断
                    break;
                }else{
                    fputs(buf,stdout);
                    fflush(stdout);
                }

            }

    }



 return 0;
}

/*main end*/