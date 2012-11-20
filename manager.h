#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/inotify.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>


#include "file_watch.h"

#define EVENT_SIZE  (sizeof(struct inotify_event))
#define EVENT_BUF_LEN     (32 * ( EVENT_SIZE + 16))

#define SOCKET_FILENAME_PREFIX "/tmp/"
#define SOCKET_FILENAME_SIZE 10
#define SOCKET_FILENAME_TOTAL_SIZE sizeof(SOCKET_FILENAME_PREFIX) + SOCKET_FILENAME_SIZE

using namespace std;

char * generateFilename(int length);
const char ALPHA[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
const int ALPHASIZE = sizeof(ALPHA) - 1;
char buffer[EVENT_BUF_LEN];
pthread_t network, fileWatch, fileIO, DBManager;
char[SOCKET_FILENAME_TOTAL_SIZE] networkSocket;
char[SOCKET_FILENAME_TOTAL_SIZE] fileWatchSocket;
char[SOCKET_FILENAME_TOTAL_SIZE] fileIOSocket;
char[SOCKET_FILENAME_TOTAL_SIZE] DBManagerSocket;
enum WatchTask {eWatch, eUnwatch};
enum WatchResponse {eOkay, eError};
enum TaskType {eWatchTask, eIOTask, eNetworkTask};
//enum ResponseType {eWatchReponse, eIOResponse, eNetworkResponse};
//enum CommandType {eWatchCommand, eIOCommand, eNetworkCommand};

struct Watch{
    int wd;
    string path;
    bool file;
};

struct WatchCommand{
    WatchTask task;
    string dir;
};

mqd_t watchCommandQueue;
mqd_t watchResponseQueue;

int main(int,char**);
bool initQueues();
void* fileIOThread(void *);
void* networkThread(void *);
