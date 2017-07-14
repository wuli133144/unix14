#include"../inc/err.h"


#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>
#include<errno.h>

/*@err.c handler err@*/

void err_e(int val,const char *fmt,...){
    va_list ap;
    va_start(ap,fmt);
    if(fmt!=NULL){
         vfprintf(stderr,fmt,ap);
         fprintf(stderr,":");
    }

    va_end(ap);
    fprintf(stderr,"%s\n",strerror(errno));
    exit(val);//exit
}

void warn_e(int val,const char *fmt,..){
       va_list ap;
    va_start(ap,fmt);
    if(fmt!=NULL){
         vfprintf(stderr,fmt,ap);
         fprintf(stderr,":");
    }

    va_end(ap);
    fprintf(stderr,"%s\n",strerror(errno)); 
}

void err_w(int val,const char *fmt,...){
    va_list ap;
    va_start(ap,fmt);
    if(fmt!=NULL){
         vfprintf(stderr,fmt,ap);   
    }
    
    va_end(ap);
    fprintf(stderr,"\n");
    exit(val);//exit
}

void warn_w(int val,const char *fmt,...){
      va_list ap;
    va_start(ap,fmt);
    if(fmt!=NULL){
         vfprintf(stderr,fmt,ap);
       
    }
    va_end(ap);
    fprintf(stderr,"\n");
   
}

/*@err.c handler err@*/
