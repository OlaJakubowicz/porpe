#include "../lib/File.h"
#include <assert.h>


int main(int argc,char* argv[]){
  char* fn1 = "TestingFileString";
  std::string stringtext = "string data test";

    // write string test

    File::write(fn1,stringtext);

  char* fn2 = "TestingFileChar";
  char* chartext = "char data test"; 

    // write char test

    File::write(fn2,chartext);
  
  char* fn3 = "test";
  std::string data = "";
  data =  File::read(fn3);
  
    //write repayable data
    
    printf(data.c_str());

  return 0;
}
