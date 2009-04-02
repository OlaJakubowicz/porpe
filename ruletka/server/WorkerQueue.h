/*
* Document-class:  WorkerQueue and ServerWorker
*
* Queue for Workers and Worker Wrapper
* file: WorkerQueue.cpp
* author: JO
*/


/*! 
  \brief Thread safe workers queue implementation
  \version 1.0
  \file WorkerQueue.cpp
  \package Server
  \date 2009-03
  \todo Bremove comments, refactor units of work
*/

#ifndef __SRCC_WQUE_CLASS__
#define __SRCC_WQUE_CLASS__

#include <string>
#include <list>
#include <boost/thread/mutex.hpp>

class WorkerQueue;

class ServerWorker {
  int sockfd;
 
	   
 
  public:
	  int numb; 
    ServerWorker(int sockfd);
    int getWorkerAss();
    void die();
	void add();
	int getNumb();
};

class WorkerQueue{

  // atributes
  std::vector<ServerWorker* > workers_list;
  boost::mutex mutex;
  
  public:
    WorkerQueue(); 
	int size();
    void push(ServerWorker* worker);
    ServerWorker* pop();
	ServerWorker* popServerWorkerAt(int id);
	void sort(int numb);
	int ServerWorkerAt(int id);
  // private consructor
  private:
  
};

#endif


