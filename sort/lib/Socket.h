/*
* Document-class:  Socket
*
* Basic Socket class, to enhance coding
* file: Socket.h
* author: JO
*/

#ifndef __SOCKET_H_SRCC__
#define __SOCKET_H_SRCC__

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h> 
#include <arpa/inet.h> 
#include <sys/wait.h> 
#include <signal.h>
#include <string>
#include "Errors.h"

#define BACKLOG 10
#define MAXDATASIZE 512*512

#define MSG_LEN_SIZE 6


struct MsgSize{
  int size;
};

class Socket {
  
  char* port ;
  int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd 
  struct sockaddr_storage their_addr; // connector's address information 
  socklen_t sin_size;
  struct addrinfo hints, *servinfo, *p; 
  int rv; 
  int numbytes;  
  char buf[MAXDATASIZE];
public: 
  
  Socket();
  //server methods
  int bind_and_listen(char* port);
  int accept_and_pick();
  
  //client methods
  std::string& recive_();
  int send_(std::string& msg);
  int connect_(char* address, char* port);
};

#endif
//empty line (warning: no newline at end of file)

