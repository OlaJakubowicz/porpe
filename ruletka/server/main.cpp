#include "Server.h"
#include "WorkerQueue.h"



// struct watek
// {
//     WorkerQueue* kolej;
//     watek(WorkerQueue* kolej) 
//     {
//       this->kolej = kolej;
//     }
//     void operator()()
//     {
//       ServerWorker* worker = kolej->pop();
//       printf(">>podjeta liczba to>> %d \n", worker->getWorkerAss() );
//     }
// 
// };


int main(int argc, char* argv[]){

   // getopt port to run and provide it to start class

  if(argc != 2)
  {
    PANIC(-1,"Hey man, to start server you ned to specify port. eg. server 5578\n");
  }

  Server::getInstance()->run(argv[1]);
  
  // // test
  //  WorkerQueue* queue = new WorkerQueue;
  // 
  //  
  //  for(int i=0;i<10;i++)
  //  {
  //    queue->push(new ServerWorker( i*i ) ); 
  //    printf("Dodaje %i\n",i);
  //  }
  // 
  //  boost::xtime xt;
  //  boost::xtime_get(&xt, boost::TIME_UTC);
  //  xt.sec += 5;
  //  boost::thread::sleep(xt);
  // 
  //  for(int i=0;i<5;i++)
  //  {
  //    watek w(queue);
  //    boost::thread thrd( w );
  //    thrd.join();
  //  }
  //  
  //  boost::xtime_get(&xt, boost::TIME_UTC);
  //  xt.sec += 5;
  //  boost::thread::sleep(xt);

  //
  
  // Socket* socket = new Socket();
  // socket->bind_and_listen("5578");
  // printf("%d\n",socket->accept_and_pick() );
  // std::string str = "LOL BRACIE" ;
  // socket->send_(  str  );
  
  return 0;
  
}



















