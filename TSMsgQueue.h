/**
 *
 *  File: TSMsgQueue.h
 *
 *
 *  Description: A vector<string> Queue that is threadsafe.
 *
 *  Author(s): Sean Farner
 *
 *  Version: $Id:$
 */

#include <pthread.h>
#include <string>
#include <vector>
using namespace std;

class CTSMsgQueue{

	public:
	  CTSMsgQueue();
	  ~CTSMsgQueue();
	
	  int push_back(string &msg);
	  int pop_front(string &msg);

	  void clear();
	  int size();

        private:
	  vector<string> queue;
	  pthread_mutex_t lock;
};
