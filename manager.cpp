#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/inotify.h>
#include <errno.h>
#include <unistd.h>
#include "TSMsgQueue.cpp"


#define EVENT_SIZE  (sizeof(struct inotify_event))
#define EVENT_BUF_LEN     (32 * ( EVENT_SIZE + 16))


using namespace std;

int main();
char buffer[EVENT_BUF_LEN];
pthread_t network, fileWatch, fileIO;
enum WatchTask {eWatch, eUnwatch};
enum WatchResponse {eOkay, eError};

struct watch{
    int wd;
    string path;
    bool file;
};


int main(){
    //CREATE
    //networkThread
    //fileWatchThread
    //fileIOThread
    int main_notify;
    watch root;
    if((main_notify = inotify_init()) != -1){
        cout << "inotify started successfully" << endl;
    }else{
        cout << "inotify could not be started, errno: " << errno << endl;
        return 1;
    }
    root.wd = inotify_add_watch(main_notify, "/tmp/watch/", IN_ATTRIB | IN_CREATE | IN_DELETE);
    root.path = "/tmp/watch/";
    root.file = false;
    
    if (root.wd > 0){
        cout << "Watch created" << endl;
    }else{
        cout << "Watch cannot be created, errno: " << errno << endl;
    }
    inotify_event *ev;
    while(true){
        int err = read(main_notify, &buffer, sizeof(buffer));
        if (err < 0){
            cout << "err" << endl;
            switch(errno){
            case EAGAIN:
                cout << "eagain" << endl;
                break;
            case EBADF:
                cout << "ebadf" << endl;
                break;
            case EFAULT:
                cout << "efault" << endl;
                break;
            case EINTR:
                cout << "eintr" << endl;
                break;
            case EINVAL:
                cout << "einval" << endl;
                break;
            case EIO:
                cout << "eio" << endl;
                break;
            case EISDIR:
                cout << "eisdir" << endl;
                break;
            }
            break;
        }
        ev = (struct inotify_event*) &buffer[0];
        if (ev->wd == root.wd){
            cout << "Root watch" << endl;
        }else{
            cout << "watch: " << ev->wd << endl;
        }
        switch(ev->mask & (IN_CREATE | IN_DELETE | IN_MODIFY)){
            case IN_CREATE:
                cout << "File created, filename: " << ev->name << endl;
                break;
            case IN_DELETE:
                cout << "File deleted, filename: " << ev->name << endl;
                break;
            case IN_MODIFY:
                cout << "File modified, filename: " << ev->name << endl;
                break;
        }
    }
    return 0;
}


void *networkThread(void *arg){
    //TODO
}
void *fileWatchThread(void *arg){
    //TODO
}
void *fileIOThread(void *arg){
    //TODO
}
