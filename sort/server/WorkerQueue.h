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
  int numb;
  public:
    ServerWorker(int sockfd);
    int getWorkerAss();
    void die();
	void add();
};

class WorkerQueue{

  // atributes
  std::list<ServerWorker* > workers_list;
  boost::mutex mutex;
  
  public:
    WorkerQueue();
    void push(ServerWorker* worker);
    ServerWorker* pop();
	void sort(int numb);
  // private consructor
  private:
  
};

#endif


