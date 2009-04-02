/*
* Document-class:  Server
*
* Implementation of Server class interface (methods)
* file: Server.cpp
* author: JO
*/

/*! 
  \brief Server implemenetation
  \version 1.0
  \file Server.cpp
  \package Server
  \date 2009-03
  \todo Bremove comments, refactor units of work
*/

#include "Server.h"

#define MAXDATASIZE 512*512

/*
 Unit of work by JO
*/
std::string recive_data(int sockfd);
int send_data(int sockfd,std::string& msg);

struct UnitOfWork{
      int worker_sock;
      std::string data;
      std::string stash;
      UnitOfWork(int worker_sock, std::string data ){
        this->data = data;
        this->worker_sock = worker_sock;
      }
      std::string getStashedData(){ return this->stash; }
      void operator()()
      {
        printf( "I'm alive ! Spawned for doing job! \n" );
        //send to worker
        printf("@@@ %s \n",data.c_str() );
        send_data(this->worker_sock,this->data);
        std::string out;
        //recive from worker
        out = recive_data(this->worker_sock);
        printf("!!!! %s \n",out.c_str() );
        //stash
        this->stash = out ;
      }
};




std::string recive_data(int sockfd){
  char lenbuff[10];

  MsgSize* size = NULL ;

  if ((recv(sockfd, lenbuff, sizeof(MsgSize), 0)) == -1) { 
          FEAR("recv failed\n");
  }
  

  //talk with new guy
  char buf[MAXDATASIZE]; 
  int numbytes = 0 ;
  if ((numbytes = recv(sockfd, buf, ((MsgSize*)lenbuff)->size , 0) ) == -1){
    FEAR("Noob have failed\n");
  }
  buf[numbytes] = '\0';
  std::string strbuf = buf;
  return strbuf;
}

int send_data(int sockfd,std::string& msg){
  
    printf(">%s<\n",msg.c_str());

    MsgSize* msg_size = new MsgSize;
    msg_size->size = msg.size();
    // i will first send size of msg

    printf(">>>>>> %d",msg_size->size);

    if(::send(sockfd,(char*)msg_size,sizeof(MsgSize), 0) == -1){
      FEAR("send failed\n");
    }

    if (::send(sockfd, msg.c_str() , msg.size() , 0) == -1) {
      FEAR("send failed\n");
      return -1;
    }
  
}

struct UnitOfClientWork{
  WorkerQueue* queue;
  int client;
  UnitOfClientWork(WorkerQueue* queue, int client)
  {
    this->client = client;
    this->queue = queue;
  }
  void operator()()
  {
    std::string file_count = recive_data(this->client);
    int count = atoi( file_count.c_str() );
	queue=queue->sort(compare_size);
    ServerWorker* server_worker = queue->pop();
    int worker = server_worker->getWorkerAss();
    
    printf("Worker id = %d  \n", worker);
    
    for(int i=0; i<count; i++ ){
       std::string input = recive_data(client);
       send_data(worker,input);
       std::string output = recive_data(worker);
       send_data(client, output );
     }
     
     queue->push(server_worker);
  }
};

Server::Server(){
  
  //assign basic things

}

void Server::run(char* port_number){
  this->port = port_number;
  printf("Running on port: %s \n", this->port );
  
  Socket* socket = new Socket();
  socket->bind_and_listen(port);
  printf("Nasluchuje\n");
  
  
  WorkerQueue queue; 
  
  while(true)
  {
    int client ;
    int worker ;
      
    int noob_sockfd = socket->accept_and_pick();
    
    printf("Nowy uzytkownik\n");

    // who are you ?
    std::string who = recive_data(noob_sockfd);
    
    if( who == std::string(WORKER_HELLO) )
    {
      worker = noob_sockfd ;
      queue.push( new ServerWorker(noob_sockfd) );
      printf("Zarejestrowalem nowego workera\n");
      //dodac do kolejki
    }
    else if( who == std::string(CLIENT_HELLO) ){
      client = noob_sockfd ;
      printf("Nowy klient\n");
      
      
      UnitOfClientWork unit(&queue,client);
      boost::thread thrd(unit);
      
      thrd.join();    
     
      
    }else{
      printf("Nie znam\n");
    }    
  }
  
  
  delete socket;
  
  
}
