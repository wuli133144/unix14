#include <time.h> 
#include <stdio.h> 
 
static int get_current_date(char* buf,int size){  
 
    time_t now;  
    struct tm *timenow;  
    time(&now);  
    timenow = localtime(&now);  
 
    return strftime(buf,size,"%Y-%m-%d",timenow);  
 
}  
static int get_current_time(char* buf,int  size){  
 
    time_t now;  
    struct tm *timenow;  
    time(&now);  
    timenow = localtime(&now);  
    return strftime(buf,size,"%Y-%m-%d %H:%M:%S",timenow);  
 
}  