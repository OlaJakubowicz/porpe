/*
* Document-class:  Server
*
* Server class (singleton) constains server engine
* file: Server.h
* author: JO
*/


#ifndef __SRCC_SERVER_CLASS__
/*! 
  \brief Server class (singleton)
  \version 1.0
  \file Server.h
  \package Server
  \date 2009-03
  \todo nothing,its fucking perfect, well we could remove stupid comments
*/

#define __SRCC_SERVER_CLASS__

#include "../lib/Errors.h"
#include "../lib/Socket.h"
#include "../lib/Protocol.h"
#include <string>
#include <stdlib.h>
#include <list>
#include "WorkerQueue.h"

#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <boost/thread/xtime.hpp>

class Server{

  // atributes
  char* port;
  
  // singleton method
  public:
    static Server* getInstance() { static Server theInstance; return &theInstance; }
    void run(char* port_number);
    
  // private consructor
  private:
    Server();
  
};


#endif


