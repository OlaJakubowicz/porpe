/*!
  \brief Implementation of Client class interface (methods)
  \version 1.0
  \file Client.cpp
  \dir ../client
  \package Client
  \date 2009-03
*/
#include "Client.h"
#include "../lib/File.h"

#define DATA_SEPARATOR "_____precel_____"
#define SEPARATOR_LENGTH 16
#define BUFFER_SIZE 10

Client::Client(){
  //assign basic things
}


/*!
  \class Client
  Run client.
  \public
  @param[in] server_name Server IP address (ex: 127.0.0.1).
  @param[in] port The port number (ex: 80).
  @param[in] files Files to compile (ex: main.cpp).
*/

void Client::run(char* server_name, char* port, vector<string> files){
  
  // create new socket class instance  

  Socket* socket = new Socket();

  // conenction to server
 
  socket->connect_(server_name, port);

  // "Introduce yourself to the server".
  
  std::string hello = CLIENT_HELLO ;
  socket->send_( hello );
  
  // "Sending number of files to server;
  
  char buffer[BUFFER_SIZE];
  sprintf(buffer,"%u",files.size());
  std::string files_number = buffer; 
  socket->send_( files_number );
  
   int f_n = files.size();
  
  //sending files to server - "for" loop   

  for(int i=0;i<f_n;i++){
    
  // preparation of sending data

    std::string filetocompile = files[i];
    std::string data_send = "";
    data_send += filetocompile;
    data_send += DATA_SEPARATOR;
    std::string file = files[i];
    std::string msg = File::read((char*)file.c_str());
    if(msg == ""){
     FEAR("File doesn`t exist");
     continue;
    }
    else{
     data_send += File::read((char*)file.c_str());
     data_send += DATA_SEPARATOR;
     socket->send_(data_send); 
    }
   
  }   
 
 // receiving data - "for" loop 

 for(int i=1;i<=f_n;i++){
  std::string data_recv = "";  
  data_recv = socket->recive_();

  // transform received data into file
  std::string f_name, compilator, errors, file_recv;
  int place1,place2,place3,place4;
  place1 = data_recv.find(DATA_SEPARATOR);
  place2 = data_recv.find(DATA_SEPARATOR,place1+1,SEPARATOR_LENGTH);
  place3 = data_recv.find(DATA_SEPARATOR,place2+1,SEPARATOR_LENGTH);
  place4 = data_recv.find(DATA_SEPARATOR,place3+1,SEPARATOR_LENGTH);
  f_name = data_recv.substr(0,place1-3);
  f_name += "o";
  compilator = data_recv.substr(place1+SEPARATOR_LENGTH,place2-place1-SEPARATOR_LENGTH);
  errors = data_recv.substr(place2+SEPARATOR_LENGTH,place3-place2-SEPARATOR_LENGTH);
  file_recv = data_recv.substr(place3+SEPARATOR_LENGTH,place4-place3-SEPARATOR_LENGTH);
  char* nametab = (char*)f_name.c_str();
  printf("Compilator: %s", compilator.c_str(), "\n");
  printf("Errors: %s", errors.c_str(), "\n");
  File::write_bin(nametab,file_recv);

 }
  
}
