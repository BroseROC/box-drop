#include "manager.h"

int main(int argc, char ** argv){
    //TODO: CREATE
    //networkThread
    //fileWatchThread
    //fileIOThread
    bool status;
    char * dir;
    if (argc != 2){
        cout << "No arguments!" << endl;
        return 1;
    }
    dir = argv[1];
    cout << "Using directory: " << dir << endl;
        
    //Watch * root;
    //root = (Watch *) malloc(sizeof(Watch));
    /*Watch root;
    status = addWatch(main_notify, (string)dir, &root);
    if (status){
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
    }*/
    cout << initQueues() << endl;
    WatchCommand temp;
    temp.dir = "/tmp/watch";
    temp.task = eWatch;
    mq_send(watchCommandQueue, (const char *)&temp, sizeof(temp), 0);
    void* a;
    a = fileWatchThread(NULL);
    return 0;
}

bool initSockets(){
    //string 
    return false;
}

string generateFilename(int length){
    string filename = "";
    for (int i = 0; i < length; i++){
        filename.append(ALPHA[rand() % sizeof(ALPHA)]);
    }
    return filename;
}

void* fileIOThread(void *arg){
    //TODO
}

void* networkThread(void *arg){
    //TODO
}
