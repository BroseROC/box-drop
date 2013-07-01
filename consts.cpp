#include "consts.h"

char* timestamp(){
    time_t ltime;
    struct tm *t;
    char* ret = (char*)malloc(sizeof(char) * 18);
    ltime = time(NULL);
    t = localtime(&ltime);
    strftime(ret, sizeof(char) * 18, "%d/%m/%y %H:%M:%S", t);
    return ret;
}
