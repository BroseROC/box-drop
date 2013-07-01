#ifndef _CONSTS_H_
#define _CONSTS_H_

#include <string>

#define EVENT_SIZE  (sizeof(struct inotify_event))
#define EVENT_BUF_LEN     (32 * ( EVENT_SIZE + 16))

#define SOCKET_FILENAME_PREFIX "/tmp/"
#define SOCKET_FILENAME_SIZE 10
#define SOCKET_FILENAME_TOTAL_SIZE sizeof(SOCKET_FILENAME_PREFIX) + SOCKET_FILENAME_SIZE
#define QUEUE_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP

enum TaskType {TT_WatchTask, TT_IOTask, TT_NetworkTask};
enum Status {S_Exit, S_OK, S_Error};


char* timestamp();

#endif
