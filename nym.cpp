#include <iostream>

#include <editline/readline.h>
#include <editline/history.h>


int main(){
  std::cout<<"nym 0.0.01a"<<std::endl;

  while(1){
    char* buffer = readline("nyn> ");
    add_history(buffer);
    std::cout<<buffer<<std::endl;
  }
  return 0;
}
