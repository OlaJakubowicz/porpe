/*
* Document-class:  WorkerQueue and ServerWorker
*
* Queue for Workers and Worker Wrapper
* file: WorkerQueue.cpp
* author: JO
*/

/*! 
  \brief Queue implementation
  \version 1.0
  \file WorkerQueue.cpp
  \package Server
  \date 2009-03
  \todo Bremove comments, refactor units of work
*/

#include "WorkerQueue.h"

WorkerQueue::WorkerQueue(){
  //initialize meh
}

void WorkerQueue::push(ServerWorker* worker){
  //mutex lock (scoped)
  boost::mutex::scoped_lock scoped_lock(mutex);
  worker->numb = numb+1;
  this->workers_list.push_back(worker);

}


ServerWorker* WorkerQueue::pop(){
  //mutex lock (scoped)
  boost::mutex::scoped_lock scoped_lock(mutex);
  ServerWorker* worker = this->workers_list.front();
  this->workers_list.pop_front();
  return worker;
}



bool compp(ServerWorker const& a, ServerWorker const& b)
{
    return a.numb.compare(b.numb)==-1;
}


void WorkerQueue::sort(int numb){
    this->workers_list.sort(compp);
	
}

ServerWorker::ServerWorker(int sockfd){
  this->sockfd = sockfd;
}

int ServerWorker::getWorkerAss(){
  return this->sockfd;
}

void ServerWorker::die(){
  close(this->sockfd);
}

void ServerWorker::add(){
    this->numb = numb+1;
}
