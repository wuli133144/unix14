#ifndef  __ERR__H__
#define  __ERR__H__






/*@ start jckwu  error handle@*/
void err_e(int err,const char *fmt,...);
void warn_e(int err,const char *fmt,...);
void err_w(int err,const char *fmt);
void warn_w(int err,const char *fmt);
/*@ end jckwu  error handle@*/


#endif