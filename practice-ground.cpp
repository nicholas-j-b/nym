#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split_no_delim(std::string &stringToBeSplitted, std::string delimeter)
{
  std::vector<std::string> splittedString;
  int startIndex = 0;
  int  endIndex = 0;
  while( (endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size() )
  {
    std::string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);
    if (!val.empty())
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

LINE_MODE someFunc(LINE_MODE l){
  return math;
}

int main(){
  LINE_MODE lineMode = set;
  lineMode = someFunc(lineMode);

  std::cout<<lineMode<<std::endl;


  // std::string myString = "   here   it      is, and that's a wrap!";
  // std::string myString2 = "3243  2 23432";
  // std::string delimeter = " ";
  // std::vector<std::string> splitted = split_no_delim(myString, delimeter);
  //
  // for (auto & element : splitted){
  //   std::cout<<element<<std::endl;
  // }
  return 0;
}
