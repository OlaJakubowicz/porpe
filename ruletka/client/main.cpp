/*! 
  \brief Client area, main function.
  \version 1.0
  \file main.cpp
  \dir ../client
  \package Client
  \date 2009-03
  \todo getopt server address to run and provide it to start class
  \todo read files list from args or use some dir, maybe *.cpp file selection and push it to Client 
*/

#include "Client.h"
#include <string>
#include <iostream>
#include <vector>
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
	TCLAP::CmdLine cmd("Client Area..", ' ', "client 1.0");

  	// Set required args.
	TCLAP::ValueArg<std::string> serverArg("s", "server", "Server address", true, "homer", "string");
	TCLAP::ValueArg<std::string> portArg("p", "port", "Port number", true, "homer", "string");
	TCLAP::MultiArg<std::string> filesArg("f", "file", "Files to compile", false, "string");

 	// Add args.
	cmd.add(serverArg);
	cmd.add(portArg);
	cmd.add(filesArg);

	cmd.parse(argc, argv);

	// Get the value parsed by each arg.
	std::string server = serverArg.getValue();
	std::string port = portArg.getValue();
	vector<string> files = filesArg.getValue();

	// Convert string to char.
	char *server_ch = new char[server.length()+1];    
	char *port_ch = new char[port.length()+1];

	strcpy(server_ch, server.c_str());
	strcpy(port_ch, port.c_str());

	// Run client.
	Client::getInstance()->run(server_ch, port_ch, files);

        // Memory cleaning
	delete server_ch;
	delete port_ch;        
		
	return 0;
}
