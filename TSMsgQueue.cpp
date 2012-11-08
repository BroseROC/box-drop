#include "TSMsgQueue.h"

CTSMsgQueue::CTSMsgQueue()
{
	lock = PTHREAD_MUTEX_INITIALIZER;
	queue = vector<string>();
	queue.reserve(100000000);
}


CTSMsgQueue::~CTSMsgQueue()
{
	

}
int CTSMsgQueue::push_back( string &msg)
{
	pthread_mutex_lock(&lock);
	queue.push_back(msg);
	pthread_mutex_unlock(&lock);
	return 1;

}

int CTSMsgQueue::pop_front( string &msg)
{
	string tempString;
	pthread_mutex_lock(&lock);
	msg =queue.front();
	queue.erase(queue.begin());
	pthread_mutex_unlock(&lock);
	return 1;
}

void CTSMsgQueue::clear()
{
	pthread_mutex_lock(&lock);
	queue.clear();
	pthread_mutex_unlock(&lock);

}

int CTSMsgQueue::size(){
	pthread_mutex_lock(&lock);
	int returnSize = (int)queue.size();
	pthread_mutex_unlock(&lock);
	return returnSize;

}
