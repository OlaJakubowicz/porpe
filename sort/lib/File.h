/*!
  \brief File Utils. File operations wrapper
  \version 1.0
  \file File.h
  \dir ../lib
  \package Lib
  \date 2009-03
*/

#ifndef __FILE_UTILS_H__
#define __FILE_UTILS_H__

#define APPEND_EXTRA_BYTES 45

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

namespace File 
{
 
  /*!
    Write to the file.
    \public
    @param[in] filename Name of the file.
    @param[in] data (string) Datas to write.
  */
  void write(char* filename, std::string& data)
  {
    FILE* fp = fopen(filename, "w");
    fprintf(fp, "%s", data.c_str());
  }

  /*!
    Write to the file.
    \public
    @param[in] filename Name of the file.
    @param[in] data (char) Datas to write.
  */  
  void write(char* filename, char* data)
  {
    FILE* fp = fopen(filename, "w");
    fprintf(fp, "%s", data);
  }
  
  /*!
    Reads data from file.
    \public
    @see write()
    @param[out] data Data from file.
    @param[in] filename Name of the file.
  */
  std::string read(char* filename)
  {
    FILE* fp = fopen(filename, "r");
    if(fp!=NULL){
      
      char ch;
      std::string data = "";

      do {
        ch = fgetc(fp);
        data += ch ;
      }while(ch != EOF);

      return data; 
     }else{return "";}
  // FIX: no empty strings, exception or some sort of error code.
  }


  /*!
    Reads data from binary file.
    \public
    @see read()
    @param[out] data Data from binary file.
    @param[in] filename Name of the binary file.
  */
  std::string read_bin(char* filename)
  {
    int size;
    char * memblock;

    ifstream file;
    file.open(filename, ios::binary);
    if (file.is_open())
    {
      std::string output = "";
//      size = file.tellg();
      int i = 0;

	file.seekg (0, ios::end);
  	size = file.tellg();
	file.seekg (0, ios::beg);

       memblock = new char [size];

      file.read(memblock, size);
      file.close();
      std::string my_output = "";
      for(i; i<size; i++)
      {
        output += memblock[i] + APPEND_EXTRA_BYTES;
        my_output += memblock[i];
      }


      delete[] memblock;
    
      return output;
    }
    else{
       return "";
    }
    // FIX: no empty strings, exception or some sort of error code.
  }

  /*!
    Writes data from binary file.
    \public
    @see read()
    @param[in] filename Name of the binary file, data Sting of data.
  */

  void write_bin(char* filename,std::string& data)
  {
    ofstream file(filename, ios::binary);
    

    char *ch_data = new char[data.length()+1];    strcpy(ch_data, data.c_str());

    std::string output = "";
    int i = 0;
    for(i; i<data.length(); i++)
    {
      output += ch_data[i]  - APPEND_EXTRA_BYTES;
    }
   
    file << output;
    file.close();
  }
}

#endif

