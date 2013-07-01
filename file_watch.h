#ifndef _FILE_WATCH_H
#define _FILE_WATCH_H

#include <string>
#include <cstring>
#include <iostream>

#include <pthread.h>

#include <unistd.h>
#include <stdarg.h>
#include <vector>
#include <sys/stat.h>

#include <mqueue.h>
#include <sys/inotify.h>
#include <sys/epoll.h>
#include "consts.h"

using namespace std;


class FileWatch{
    
    public:
        enum WatchTask {WT_Watch, WT_Unwatch, WT_Exit};
        enum WatchResponse {WR_Okay, WR_Error};
        struct WatchCommand{
            WatchTask task;
            char * dir;
        };
        struct Watch{
            int wd;
            const char* path;
            bool isDir;
        };

        FileWatch(char* toFileWatchFile, char* fromFileWatchFile);
        bool addWatch(int fd, char* dir, Watch * watch);
        void startThread(pthread_t*);
    private:
        void* fileWatchThread(void *);
        const static int init_watch_array_size = 1000;
        int pollfd;
        vector<Watch*> watches;
        size_t msg_size;
        int main_notify;
        mqd_t toFileWatch;
        mqd_t fromFileWatch;

        Status DoCommand(WatchCommand * command);
        WatchCommand * receiveCommand();
    protected:
        void printfLine(const char* fmt, ...);
};


#endif
