/*! 
  \class Worker
  \brief Worker class (singleton) constains server engine.
  \version 1.0
  \file Worker.h
  \dir ../worker
  \package Worker
  \date 2009-03
*/

#ifndef __SRCC_WORKER_CLASS__
#define __SRCC_WORKER_CLASS__

#include "../lib/Errors.h"
#include "../lib/Socket.h"
#include <stdlib.h>
#include <stdio.h>

class Worker
{
  
  public:
    /*!
      Singleton.
      \public
      @param[out] theInstance The class object.
    */
    static Worker* getInstance() 
    { 
      static Worker theInstance;

      return &theInstance;
    }

    /*!
      Run worker.
      \public
      @param[out] static Worker theInstance The memory area to copy to.
      @param[in] server_name Server IP address (ex: 127.0.0.1).
      @param[in] port The port number (ex: 80).
    */
    void run(char* server_name,char* port);
    
  private:
    /*!
      Private consructor.
      \private
      \see getInstance()
    */
    Worker();
};

#endif

