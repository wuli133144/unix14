

#include"../inc/common.h"

#include<syslog.h>

/*create daemon proc*/

void daemon_my(const char *cmd){
     int i,fd0,fd1,fd2;
     pid_t pid;
     struct rlimit rlim;
     struct sigaction sa;

     umask(0);
     if(getrlimit(RLIMIT_NOFILE,&rlim)<0){
         err_dump("getrlimit");
     }
     pid=Fork();
     if(pid){
            exit(0);//kill parent
     }

     Setsid();//create session

     sa.sa_handler=SIG_IGN;
     sigemptyset(&sa.sa_mask);
     sa.sa_flags=0;
     if(sigaction(SIGHUP,&sa,NULL)<0){
         err_dump("error signal");
     }
     pid=Fork();
     if(pid){
         exit(0);//kill parent
     }

     if((chdir("/"))<0){
         err_dump("chdir");
     }

     if(rlim.rlim_max==RLIM_INFINITY){
         rlim.rlim_max=1024;
     }
     for(i=0;i<rlim.rlim_max;i++){
         close(i);
     }

     fd0=Open("/dev/null",O_RDONLY|O_WRONLY,0666);
     fd1=dup(0);
     fd2=dup(0);
     openlog(cmd,LOG_CONS,LOG_DAEMON);
     if(fd0!=0||fd1!=1||fd2!=2){
         syslog(LOG_ERR,"Unexpected file description%d %d %d",fd0,fd1,fd2);
         exit(0);
     }

}

/*create daemon proc end*/

int main(){
    

    //  struct rlimit lim;
    
    //  lim.rlim_max=12345;
    //  lim.rlim_cur=123;
    //  Setrlimit(RLIMIT_NOFILE,&lim);

    //  Getrlimit(RLIMIT_NOFILE,&lim);
     
    // printf("hard limit%d\n soft limit %d\n",lim.rlim_cur,lim.rlim_max);
     
     //daemon_my("/bin/date");

    return 0;

}