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
            socklen_t len;
            bzero(buf,sizeof(buf));

            fp=fopen("r.dat","wb");
            if(fp==NULL){
                unix_error("fopen error");
            }
            sad=Socket(AF_INET,SOCK_STREAM,0);
            memset(&serve_addr,0,sizeof(struct sockaddr_in));
            serve_addr.sin_family=AF_INET;
            serve_addr.sin_addr.s_addr=inet_addr("local.com");
            serve_addr.sin_port=htons(atoi("80"));
            for(;;)
            
              connect(sad,(struct sockaddr *)&serve_addr,sizeof(struct sockaddr));

}