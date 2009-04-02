/*! 
  \brief Worker class (singleton) constains server engine.
  \version 1.0
  \file main.cpp
  \dir ../worker
  \package Worker
  \date 2009-03
  \todo Better line command parsing - DONE
*/

#include "Worker.h"

#include <string>
#include <iostream>
#include <tclap/CmdLine.h>

using namespace TCLAP;
using namespace std;

/*!
Main().
@param[out] 0.
@param[in] argc.
@param[in] argv[].
*/
int main(int argc, char* argv[])
{
	// Set description for <cmd_line> -- version.
	TCLAP::CmdLine cmd("Worker Area..", ' ', "worker 1.0");

  	// Set required args.
	TCLAP::ValueArg<std::string> serverArg("s", "server", "Server address", true, "homer", "string");
	TCLAP::ValueArg<std::string> portArg("p", "port", "Port number", true, "homer", "string");

 	// Add args.
	cmd.add(serverArg);
	cmd.add(portArg);

	cmd.parse(argc, argv);

	// Get the value parsed by each arg.
	std::string server = serverArg.getValue();
	std::string port = portArg.getValue();

	// Convert string to char.
	char *server_ch = new char[server.length()+1];    
	char *port_ch = new char[port.length()+1];

	strcpy(server_ch, server.c_str());
	strcpy(port_ch, port.c_str());
	//std::cout << "server " << server << "port " << port << std::endl;

	// Start worker.
	Worker::getInstance()->run(server_ch, port_ch);

        // Free memory.
        delete server_ch;
        delete port_ch;
  
	return 0;
}

