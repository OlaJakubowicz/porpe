/*!
  \brief Implementation of Worker class interface (methods)
  \version 1.0
  \file Worker.cpp
  \dir ../worker
  \package Worker
  \date 2009-03
*/

#include "Worker.h"
#include "../lib/File.h"
#include "../lib/Protocol.h"
#include <string>
#include <iostream>
#include <stdlib.h>

#define DEBUG_SOURCE "myfile.cpp_____precel_____#include <iostream>\nint main(int argc, char* argv[]){std::cout << \"test...\"; return 0;}\n"

#define INPUT_FILE "output.cpp"
#define OUTPUT_FILE "output.o"
#define ERRORS_FILE "errors.sr"
#define INF_FILE "inf.sr"

#define DATA_SEPARATOR "_____precel_____"

#define SELF_DEBUG 0

Worker::Worker()
{
  //assign basic things
}

/*!
  \class Worker
  Run worker.
  \public
  @param[in] server_name Server IP address (ex: 127.0.0.1).
  @param[in] port The port number (ex: 80).
*/
void Worker::run(char* server_name, char* port)
{
  // Create new socket class instance.
  Socket *socket = new Socket();
  
  // Connect to the server.
  socket->connect_(server_name, port);
  
  std::string hello = WORKER_HELLO;
  
  // "Introduce yourself to the server".
  socket->send_(hello);

  std::string data_result = "";
  std::string data_errors = "";
  std::string data_inf = "";
  std::string data_to_send = "";
  std::string data_filename = "";
  
  std::string data_recive = "";

  std::string compile_result = "";
  char ch;
  int pos1, pos2;

  while(true)
  {
    data_result = "";
    data_recive = "";
    data_errors = "";
    data_filename = "";
    data_inf = "";
    pos1 = 0;
    pos2 = 0;

    if (!SELF_DEBUG)
    {
	std::cout << "Czekam na dane...\n";

        try
        {
          data_recive = socket->recive_();
        }
        catch(char *str)
        {
           PANIC(-1, str);
        }
        catch(...)
        {
           PANIC(-1, "Exception..");
        }
    }
    else
    {
         data_recive = DEBUG_SOURCE;
    }

    pos1 = data_recive.find(DATA_SEPARATOR);
    pos2 = data_recive.find(DATA_SEPARATOR, pos1+1,16);
    data_filename = data_recive.substr(0, pos1);
    data_recive = data_recive.substr(pos1+16, pos2-25);
    
    // Write data from client to the file.
    File::write(INPUT_FILE, data_recive);

    /*
    FILE* fp = fopen(INPUT_FILE, "w");
    fprintf(fp,"%s",data_recive.c_str() );
    fclose(fp);
    */

    // Get g++ compiler version.
    std::cout << "Zbieram dane o kompilatorze...\n";
    system("g++ -v 2>inf.sr");
    
    //std::string result;
    //char tmp[1024];
    //FILE *term = popen("g++4 -c -o output.o output.cpp", "r");
    
    //while((fgets(tmp, 1024, term)) != 0)
    //{
    //     result += std::string(tmp);
    //     tmp[0] = '\0';
    //}

    // Compling...
    std::cout << "Kompiluje dane...\n";
    system("./bash_create_output");
    //system("python ./x.rb");
    system("g++ -c -o output.o output.cpp 2> errors.sr");
    //execl("/bin/sh","./bash_compile","bash_compile", NULL);
    
    // Get results from files using File namespace.
    std::cout << "Odczytuje dane...\n";

    data_result = File::read_bin(OUTPUT_FILE);
    data_errors = File::read(ERRORS_FILE);
    data_inf = File::read(INF_FILE);

       
    /*
    fp = fopen(OUTPUT_FILE, "r");
    do 
    {
      ch = fgetc(fp);
      data_result += ch ;
    }while(ch != EOF);
    fclose(fp);

    fp = fopen(ERRORS_FILE, "r");
    do 
    {
      ch = fgetc(fp);
      data_errors += ch ;
    }while(ch != EOF);
    fclose(fp);

    fp = fopen(INF_FILE, "r");
    do 
    {
      ch = fgetc(fp);
      data_inf += ch ;
    }while(ch != EOF);
    fclose(fp); */

    // Collect datas.
    data_to_send = data_filename;
    data_to_send += DATA_SEPARATOR;
    data_to_send += data_inf;
    data_to_send += DATA_SEPARATOR;
    data_to_send += data_errors;
    data_to_send += DATA_SEPARATOR;
    data_to_send += data_result;
    data_to_send += DATA_SEPARATOR;

    //std::cout << "\n\n\n\n" << data_result << "\n\n\n\n";

    if (!SELF_DEBUG)
    {
	std::cout << "Wysylam dane...\n";
        socket->send_(data_to_send);
	std::cout << "Dane wysłano.\n\n";
    }

    // Remove tmp files.
    system("rm -f ./output.cpp ./output.o ./errors.sr ./inf.sr");

    if (SELF_DEBUG)
    {
       //std::cout << data_to_send;
       std::cout << data_recive;
       break;
    }
  }
}

