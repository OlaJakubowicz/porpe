#include <stdio.h>
#include <assert.h>

// code to test
int add(int a,int b){
  return a + b ; 
}


// test cases
void test_add(){
  assert( add(5,5) == 10 );
}

void test_lol(){
  assert(1==2);
}

void test_one(){
  assert(1==1);
}

//my test framework typedefs

typedef void (*Test)();

typedef struct {
  char* name ;
  Test foo;
}UnitTest;


//user adds this tests to test collection
UnitTest tests[] = {
      {"test_lol", test_lol },
      {"test_add", test_add },
      {"test should check if 1 is 1", test_one }
};

// framework test runner
int run_tests( ){ 
  int i = sizeof(tests) / sizeof(UnitTest) ;
  printf("Tests to run %i\n\n",i);
  while(i--){
    printf("Starting test: %s \n",tests[i].name );
    tests[i].foo();
    printf("Passed \n\n");
  }
}


int main(int argc, char* argv[]) {
   
    run_tests(); 
    return 0;
}