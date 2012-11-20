#include "file_watch.h"

//Return true on success, false on failure
bool addWatch(int fd, string dir, Watch * watch){
    int wd = inotify_add_watch(fd, dir.c_str(), IN_ATTRIB | IN_CREATE | IN_DELETE);
    //cout << wd << endl;
    //printf("%p\n", watch);
    //cout << "wd" << watch->wd << endl;
    watch->wd = wd;
    watch->path = dir;
    watch->file = false;
    return (watch->wd > 0);
}

void* fileWatchThread(void *arg){
    int main_notify;
    WatchCommand * task_ptr = (WatchCommand*) malloc(sizeof(WatchCommand));
    int msg_size;
    if((main_notify = inotify_init()) != -1){
        cout << "inotify started successfully" << endl;
    }else{
        cout << "inotify could not be started, errno: " << errno << endl;
        return NULL;
    }
    msg_size = mq_receive(watchCommandQueue, (char *)task_ptr, sizeof(WatchCommand), NULL);
    if (msg_size != sizeof(WatchCommand)){
        cout << "Error: size recived: " << msg_size << " size expected: " << sizeof(WatchCommand) << endl;
    }
    cout << "dir: " << task_ptr->dir << endl;
    return NULL;
}
