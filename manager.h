#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <iostream>
#include <string>
#include <cstring>

#include <pthread.h>
#include <mqueue.h>

#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <sys/socket.h>

#include "consts.h"
#include "file_watch.h"

using namespace std;



const char ALPHA[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int ALPHASIZE = sizeof(ALPHA) - 1;
char buffer[EVENT_BUF_LEN];
pthread_t network, fileWatch, fileIO, DBManager;

char* toNetworkFile;
char* toFileWatchFile;
char* toFileIOFile;
char* toDBManagerFile;

char* fromNetworkFile;
char* fromFileWatchFile;
char* fromFileIOFile;
char* fromDBManagerFile;

mqd_t toFileWatch;
mqd_t fromFileWatch;
// networkSocket;
//sockaddr_un fileIOSocket;
//sockaddr_un DBManagerSocket;

//enum ResponseType {eWatchReponse, eIOResponse, eNetworkResponse};
//enum CommandType {eWatchCommand, eIOCommand, eNetworkCommand};

void printErrno(int err);
bool sendTo(mqd_t queue, void* msg, size_t size);

int main(int, char**);
void initQueues();
void initThreads();
char* generateFilename(int length);
bool fileExists(char* filename);
void printfLine(const char* fmt, ...);

//Thread functions
void* fileIOThread(void *);
void* networkThread(void *);
