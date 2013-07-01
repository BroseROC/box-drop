#include "file_watch.h"

#define cout std::cout
#define endl std::endl

//Return true on success, false on failure
bool FileWatch::addWatch(int fd, char* dir, Watch * watch){
    printfLine("Adding watch to: %s", dir);
    int wd = inotify_add_watch(fd, dir, IN_ATTRIB | IN_CREATE | IN_DELETE);
    watch->wd = wd;
    watch->path = dir;
    struct stat stat_buf;
    stat(dir, &stat_buf);
    watch->isDir = S_ISDIR(stat_buf.st_mode);
    return (watch->wd > 0);
}


void FileWatch::startThread(pthread_t* thread){
    pthread_create(thread, NULL, &fileWatchThread, (void*)NULL);
}

void* FileWatch::fileWatchThread(void *arg){
    printfLine("In fileWatchThread");
    int s_error;
    fd_set toQueue;
    char mq_buf[msg_size];
    WatchCommand nextCommand;
    size_t size_recv;
    while(true){
        FD_ZERO(&toQueue);
        FD_SET(toFileWatch, &toQueue);
        printfLine("Entering select");
        s_error = select(toFileWatch + 1, &toQueue, NULL, NULL, NULL);
        if(s_error == -1){
            printfLine("Select error, exiting");
            break;
        }
        if(!FD_ISSET(toFileWatch, &toQueue)){
            printfLine("toFileWatch not set, exiting");
            break;
        }
        printfLine("Receiving command");
        size_recv = mq_receive(toFileWatch, &(mq_buf[0]), msg_size, NULL);
        cout << size_recv << endl;
        memcpy(&nextCommand, &mq_buf, sizeof(WatchCommand));
        switch(DoCommand(&nextCommand)){
            case S_OK:
                printfLine("Command completed sucessfully");
                break;
            case S_Error:
                printfLine("Error while executing command");
                break;
            case S_Exit:
                printfLine("Exiting thread");
                return NULL;
                break;
            default:
                printfLine("WTF default?!");
                break;
        }
    }
    return NULL;
}

Status FileWatch::DoCommand(WatchCommand* command){
    char* dir;
    if(command->task == NULL){
        printfLine("Error in DoCommand, command->task == NULL");
        return S_Error;
    }
    switch(command->task){
        case WT_Watch:
            {
            printfLine("Found WT_Watch");
            dir = command->dir;
            if(dir == NULL){
                printfLine("Error in DoCommand, command->dir == NULL");
            }
            Watch* tempWatch = (Watch*)malloc(sizeof(Watch));
            addWatch(main_notify, dir, tempWatch);
            watches.push_back(tempWatch);
            }
            return S_OK;
        case WT_Unwatch:
            printfLine("Found WT_Unwatch");
            return S_OK;
        case WT_Exit:
            printfLine("Found WT_Exit");
            return S_Exit;
        default:
            return S_Error;
    }
    return S_Error;
}

FileWatch::FileWatch(char* toFileWatchFile, char* fromFileWatchFile){
    int err;
    if((main_notify = inotify_init()) != -1){
        printfLine("inotify started successfully");
    }else{
        err = errno;
        printfLine("inotify could not be started, errno: %s", strerror(err));
        return;
    }
    fromFileWatch = mq_open(fromFileWatchFile, O_WRONLY, QUEUE_MODE, NULL);
    if (fromFileWatch < 0){
        err = errno;
        printfLine("fromFileWatch mqueue could not be started, %s", strerror(err));
        return;
    }else{
        printfLine("fromFileWatch mqueue stared sucessfully");
    }
    toFileWatch = mq_open(toFileWatchFile, O_RDONLY, QUEUE_MODE, NULL);
    if (toFileWatch < 0){
        err = errno;
        printfLine("toFileWatch mqueue could not be started, %s", strerror(err));
        return;
    }else{
        printfLine("toFileWatch mqueue stared sucessfully");
    }

    mq_attr attr;
    mq_getattr(toFileWatch, &attr);
    msg_size = attr.mq_msgsize;

    watches.resize(sizeof(Watch*) * 1000);
    pollfd = epoll_create(1000);
    if(pollfd < 0){
        printfLine("Could not create epoll interface, %s", strerror(errno));
    }else{
        printfLine("Created epoll interface");
    }
}

void FileWatch::printfLine(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    printf("FW: [%s] ", timestamp());
    vprintf(fmt, args);
    printf("\n");
    va_end(args);
}

#undef cout
#undef endl
