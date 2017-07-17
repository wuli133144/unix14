

#include"../inc/sock.h"

//file_client.c
#define BUFSIZE  1024

int main(int argc,char **argv){ 

            int sad;
            FILE *fp;
            char buf[BUFSIZE];
            int read_cnt;
            int i=0;
            struct sockaddr_in serve_addr;
            bzero(buf,sizeof(buf));

            fp=fopen("r.dat","wb");
            if(fp==NULL){
                unix_error("fopen error");
            }
            sad=Socket(AF_INET,SOCK_STREAM,0);
            memset(&serve_addr,0,sizeof(struct sockaddr_in));
            serve_addr.sin_family=AF_INET;
            serve_addr.sin_addr.s_addr=inet_addr("10.99.1.145");

            serve_addr.sin_port=htons(atoi("80"));
               
           for(;;){

             connect(sad,(struct sockaddr *)&serve_addr,sizeof(struct sockaddr));
             // sleep(1);
             close(sad);
             sad=Socket(AF_INET,SOCK_STREAM,0);
             memset(&serve_addr,0,sizeof(struct sockaddr_in));
             serve_addr.sin_family=AF_INET;
             serve_addr.sin_addr.s_addr=inet_addr("10.99.1.145");
            
           }

            while((read_cnt=read(sad,buf,BUFSIZE))!=0){
                 fwrite((void *)buf,1,read_cnt,fp);
                 puts(buf);
            }
             
            fclose(fp);
            close(sad);
            return 0;
}