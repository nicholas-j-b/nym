#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string stringToBeSplitted, std::string delimeter)
{
  std::vector<std::string> splittedString;
  int startIndex = 0;
  int  endIndex = 0;
  while( (endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size() )
  {
    std::string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);
    splittedString.push_back(val);
    startIndex = endIndex + delimeter.size();
  }
  if(startIndex < stringToBeSplitted.size())
  {
    std::string val = stringToBeSplitted.substr(startIndex);
    splittedString.push_back(val);
  }
  return splittedString;
}

int main(){
  std::string myString = "here it is, and that's a wrap!";
  std::string delimeter = " ";
  std::vector<std::string> splitted = split(myString, delimeter);

  for (auto & element : splitted){
    std::cout<<element<<std::endl;
  }
  return 0;
}
