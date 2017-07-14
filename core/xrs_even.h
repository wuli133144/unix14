

#ifndef   ___EVENT__H
#define   ___EVENT__H



#define  XRS_READ_EVENT         0x1 
#define  XRS_WRITE_EVENT        0x4
#define  XRS_TIMEOUT_EVENT      0x8

typedef  struct  xrs_event_st{
  
  TAILQ_ENTRY (xrs_event_st)    read_set;
  TAILQ_ENTRY (xrs_event_st)    write_set;
  TAILQ_ENTRY (xrs_event_st)    timeout_set;
   
  int event_fd;//事件发生对应文件描述符
  void *(*call_back_op)(void *arg);//select回调函数
  void *arg;//参数设置
  char buffer[MAXLINE];//extension
  int  xrs_flag;// w r timeout

  struct timeval tm_val;
  
}xrs_event;


void even_init(void );//初始化对应事件队列
void even_dispatch_select(void);//事件分发

void  



#endif
