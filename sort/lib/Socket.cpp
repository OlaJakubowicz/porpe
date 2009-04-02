#include "Socket.h"

void *get_in_addr(struct sockaddr *sa) 
{ 
    if (sa->sa_family == AF_INET) { 
        return &(((struct sockaddr_in*)sa)->sin_addr); 
    } 
    return &(((struct sockaddr_in6*)sa)->sin6_addr); 
}

Socket::Socket(){

}

int Socket::bind_and_listen(char* port){

  this->port = port ;
  
  struct sigaction sa; 
  int yes=1; 
  char s[INET6_ADDRSTRLEN]; 

  memset(&hints, 0, sizeof hints); 
  hints.ai_family = AF_UNSPEC; 
  hints.ai_socktype = SOCK_STREAM; 
  hints.ai_flags = AI_PASSIVE; // use my IP 
  if ((rv = getaddrinfo(NULL, this->port, &hints, &servinfo)) != 0) { 
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv)); 
      return 1; 
  } 
   // loop through all the results and bind to the first we can 
    for(p = servinfo; p != NULL; p = p->ai_next) { 
        if ((sockfd = socket(p->ai_family, p->ai_socktype, 
                p->ai_protocol)) == -1) { 
            perror("server: socket\n"); 
            continue; 
        } 
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, 
                sizeof(int)) == -1) { 
            perror("setsockopt\n"); 
            exit(1); 
        } 
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) { 
            close(sockfd); 
            perror("server: bind'n"); 
            continue; 
        } 
        break; 
    } 
    if (p == NULL)  { 
        fprintf(stderr, "server: failed to bind\n"); 
        return 2; 
    } 

    freeaddrinfo(servinfo); // all done with this structure 
    if (listen(sockfd, BACKLOG) == -1) { 
        perror("listen\n"); 
        exit(1); 
    }
    
    

}

//returns socket or -1 if client is making lulz out of us
int Socket::accept_and_pick(){
  
  printf("server: waiting for connections...\n"); 

        sin_size = sizeof their_addr; 
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size); 
        if (new_fd == -1) { 
            perror("accept"); 
        } 
  
        return new_fd;
}

//client methods

int Socket::connect_(char* address, char* port){
   this->port = port;
   char s[INET6_ADDRSTRLEN];  
   memset(&hints, 0, sizeof hints); 
   hints.ai_family = AF_UNSPEC; 
   hints.ai_socktype = SOCK_STREAM; 
   if ((rv = getaddrinfo(address, this->port, &hints, &servinfo)) != 0) { 
       fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv)); 
       return 1; 
   } 
    // loop through all the results and connect to the first we can 
    for(p = servinfo; p != NULL; p = p->ai_next) { 
        if ((sockfd = socket(p->ai_family, p->ai_socktype, 
                p->ai_protocol)) == -1) { 
            perror("client: socket\n"); 
            continue; 
        } 
        if (::connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) { 
            close(sockfd); 
            perror("client: connect\n"); 
            continue; 
        } 
        break; 
    } 
    if (p == NULL) { 
        fprintf(stderr, "client: failed to connect\n"); 
        return 2; 
    }
  
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), 
            s, sizeof s); 
    printf("client: connecting to %s\n", s); 
    freeaddrinfo(servinfo); // all done with this structure
  
  return 0 ;
}

int Socket::send_(std::string& msg){
  printf(">%s<\n",msg.c_str());
  
  MsgSize* msg_size = new MsgSize;
  msg_size->size = msg.size();
  // i will first send size of msg
  
#ifdef DEBUG 
  printf(">Length %d \n",msg_size->size);
#endif
  
  if(::send(sockfd,(char*)msg_size,sizeof(MsgSize), 0) == -1){
    FEAR("send failed\n");
  }
  
  if (::send(sockfd, msg.c_str() , msg.size() , 0) == -1) {
    FEAR("send failed\n");
    return -1;
  }
  return 0;
}


//repair it man
std::string& Socket::recive_(){
  std::string* msg = new std::string("");
  
  char lenbuff[10];
  
  MsgSize* size = NULL ;
  
  if ((numbytes = ::recv(sockfd, lenbuff, sizeof(MsgSize), 0)) == -1) { 
          FEAR("recv failed\n");
  }
  
  
  size = (MsgSize*)lenbuff;
  
  if ((numbytes = ::recv(sockfd, buf, size->size, 0)) == -1) { 
          FEAR("recv failed\n");
  }
  printf(">%s<\n",buf);
  buf[numbytes] = '\0';
  *msg = buf ;
  return *msg;
}
//empty line (warning: no newline at end of file)

