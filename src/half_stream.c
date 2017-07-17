
#include"../inc/common.h"



#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
//test/dup/msg/fdopen/FILE
#define BUFSIZE  1024

int main(){
int fd;
char msg[BUFSIZE];
bzero(msg,BUFSIZE);

fd=Open("info",O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR);

FILE *readfp;
FILE *writefp;

readfp=fdopen(fd,"r");
writefp=fdopen(dup(fd),"w");
//writefp=fdopen(fd,"w");

//shutdown(fileno(writefp),SHUT_WR);
shutdown(fd,SHUT_RD);//

//close(fileno(writefp));

int i=0;
for(i=0;i<5;i++){

fputs("123",writefp);
fflush(writefp);
//fclose(readfp);
fgets(msg,BUFSIZE,readfp);
fputs(msg,stdout);
fflush(stdout);
memset(msg,0,sizeof(msg));

sleep(2);

}
return 0;

}