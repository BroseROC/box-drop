#ifndef _FILE_WATCH_H
#define _FILE_WATCH_H

#include <string.h>

struct Watch;

class FileWatch{
    
    public:
        FileWatch(char *);
        void* fileWatchThread(void *);
        bool addWatch(int, string, Watch *);
};

#endif
