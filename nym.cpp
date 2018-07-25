#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <regex>

#include <editline/readline.h>
#include <editline/history.h>


std::deque<std::string> split_no_delim(std::string &stringToBeSplitted, std::string delimeter)
{
  std::deque<std::string> splittedString;
  int startIndex = 0;
  int  endIndex = 0;
  while( (endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size() )
  {
    std::string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);
    if(!val.empty())
    {
      splittedString.push_back(val);
    }
    startIndex = endIndex + delimeter.size();
  }
  if(startIndex < stringToBeSplitted.size())
  {
    std::string val = stringToBeSplitted.substr(startIndex);
    splittedString.push_back(val);
  }
  return splittedString;
}

enum LINE_MODE {math, set};

LINE_MODE get_line_mode(std::string s){
  if(std::regex_search(s, std::regex("^[0-9]")))
  {
    return math;
  }
  else
  {
    return set;
  }
}

int evaluate_maths(std::deque<std::string> d){
  int r = 0;
  for(auto & element : d){
    r += std::stoi(element, nullptr);
  }
  return r;
}


int main(){
  std::cout<<"nym 0.0.02b"<<std::endl;
  std::string buffer;
  std::string delimeter = " ";
  LINE_MODE lineMode;
  while(true){
    std::cout<<"nym> ";
    std::getline(std::cin, buffer);
    std::deque<std::string> splitted = split_no_delim(buffer, delimeter);
    lineMode = get_line_mode(splitted.front());
    std::cout<<"the mode is: "<<lineMode<<std::endl;
    if(lineMode == math){
      std::cout<<evaluate_maths(splitted)<<std::endl;
    }
    for(auto & element : splitted){
      std::cout<<element<<std::endl;
    }
  }
  return 0;
}
