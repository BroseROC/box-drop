#include "manager.h"


int main(int argc, char ** argv){
    //TODO: CREATE
    //networkThread
    //fileIOThread
    //DB thread
    initQueues();
    initThreads();
    FileWatch::WatchCommand temp;
    char command[64];
    char dir[64];
    while (true){
        cout << "Enter command: ";
        cin.getline(command, 64);
        cout << "Enter directory: ";
        cin.getline(dir, 64);
        if(strcmp("watch", command)){
            temp.task = FileWatch::WT_Watch;
        }else if(strcmp("unwatch", command)){
            temp.task = FileWatch::WT_Unwatch;
        }else if(strcmp("exit", command)){
            temp.task = FileWatch::WT_Exit;
        }
        temp.dir = (char*)malloc(sizeof(dir));
        strcpy(temp.dir, dir);
        printfLine("Sending command");
        sendTo(toFileWatch, (void*)&temp, sizeof(FileWatch::WatchCommand));
        if(temp.task == FileWatch::WT_Exit){
            printfLine("Waiting for fileWatch thread...");
            pthread_join(fileWatch, NULL);
            printfLine("fileWatch thread closed, exiting");
            break;
        }
    }
    return 0;
}


void initThreads(){
    FileWatch fwatch(toFileWatchFile, fromFileWatchFile);
    fwatch.startThread(&fileWatch);
}

void initQueues(){
    int err;
    int filenamesToCreate = 8;
    int nameLength = 7;
    size_t filenameSize = (sizeof(char) * nameLength) + 2;
    char* tempFilename = (char*)malloc(filenameSize);
    char* fileNames[filenamesToCreate];//[sizeof(filenameSize)];
    srand(time(NULL));
    for (int i = 0; i < filenamesToCreate; i++){
        fileNames[i] = (char*)malloc(sizeof(filenameSize));
        tempFilename = generateFilename(nameLength);
        /*while (fileExists(tempFilename)){
            tempFilename = generateFilename(nameLength);
        }*/
        snprintf(fileNames[i], nameLength, "/%s", tempFilename);
        printfLine("Using filename: %s", fileNames[i]);
    }
    toNetworkFile = fileNames[0];
    toFileWatchFile = fileNames[1];
    toFileIOFile = fileNames[2];
    toDBManagerFile = fileNames[3];
    fromNetworkFile = fileNames[4];
    fromFileWatchFile = fileNames[5];
    fromFileIOFile = fileNames[6];
    fromDBManagerFile = fileNames[7];

    int queueFlag = O_CREAT;
/*    mq_attr def_attr, toFileWatchAttr, fromFileWatchAttr;
    def_attr.mq_msgsize = 1024;
    def_attr.mq_flags = 0;
    def_attr.mq_maxmsg = 10;
    
    cout << "def_attr.mq_msgsize: " << def_attr.mq_msgsize << endl;*/

    //memcpy(&toFileWatchAttr, &def_attr, sizeof(def_attr));
    //memcpy(&fromFileWatchAttr, &def_attr, sizeof(def_attr));
    
    fromFileWatch = mq_open(fromFileWatchFile, O_RDONLY | queueFlag, QUEUE_MODE, NULL);
    if(fromFileWatch < 0){
        err = errno;
        printfLine("fromFileWatch could not be started, %s", strerror(err));
    }else{
        printfLine("fromFileWatch started");
    }
    toFileWatch = mq_open(toFileWatchFile, O_WRONLY | queueFlag, QUEUE_MODE, NULL);
    if(toFileWatch < 0){
        err = errno;
        printfLine("toFileWatch could not be started, %s", strerror(err));
    }else{
        printfLine("toFileWatch started");
    }
    mq_attr attr;
    mq_getattr(toFileWatch, &attr);
}

bool sendTo(mqd_t queue, void* msg, size_t size){
    return 0 == mq_send(queue, (char*)msg, size, 0);
}

char*  generateFilename(int length){
    char* filename = (char*)malloc((length * sizeof(char)) + 1);
    for (char* i = filename; i < filename + length; i++){
        *i = ALPHA[rand() % ALPHASIZE];
    }
    filename[length * sizeof(char)] = '\0';
    return filename;
}

inline bool fileExists(char* filename){
    return access(filename, F_OK) == 0;
}

void* fileIOThread(void *arg){
    //TODO
    return (void*)NULL;
}

void* networkThread(void *arg){
    //TODO
    return (void*)NULL;
}

void printfLine(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    printf("MG: [%s] ", timestamp());
    vprintf(fmt, args);
    printf("\n");
    va_end(args);
}


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
