/*! 
  \class Client
  \brief Client class (singleton) constains server engine.
  \version 1.0
  \file Client.h
  \dir ../client
  \package Client
  \date 2009-03
  \todo: alter interface for file choosing / adding / selecting
*/

#ifndef __SRCC_CLIENT_CLASS__
#define __SRCC_CLIENT_CLASS__

#include "../lib/Errors.h"
#include "../lib/Socket.h"
#include "../lib/Protocol.h"

#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

class Client
{

  public:
    /*!
      Singleton.
      \public
      @param[out] theInstance The class object.
    */
    static Client* getInstance() 
    { 
	static Client theInstance; 

	return &theInstance; 
    }

    /*!
      Run client.
      \public
      @param[out] static Worker theInstance The memory area to copy to.
      @param[in] server_name Server IP address (ex: 127.0.0.1).
      @param[in] port The port number (ex: 80)
      @param[in] files Files to compile (ex: main.cpp).
    */
    void run(char* server, char* port, vector<string> files);
    
  private:
    /*!
      Private consructor.
      \private
      \see getInstance()
    */
    Client();
};

#endif

