#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <cstring>
#include <regex>

#include <editline/readline.h>
#include <editline/history.h>

#include "cfg.h"
#include "PoolAllocator.h"

class LineComprehension{
private:
  comprehensionFormula;
public:
  comprehend;
}

class Session{
  friend class LineComprehension;
private:
  std::string m_buffer;
  std::string m_delimeter;
  mem::LINE_MODE m_currentLineMode;
  mem::PoolAllocator<mem::lNumVector> m_lVecAllocator;
  mem::PoolAllocator<mem::dNumVector> m_dVecAllocator;
  std::deque<mem::lNumVector*> m_lNumDq;
  std::deque<mem::dNumVector*> m_dNumDq;
  std::deque<std::string> m_lNames;
  std::deque<std::string> m_dNames;
public:
  Session() : m_delimeter(" ") {};
  ~Session(){
    for(auto& i : m_lNumDq){
      m_lVecAllocator.deallocate(i);
      std::cout<<"correctly destructed"<<std::endl;
    }
    for(auto& i : m_dNumDq){
      m_dVecAllocator.deallocate(i);
    }
  };
  mem::ERROR_CODE main_loop(){

    while(true){
      std::cout<<"nym> ";
      std::getline(std::cin, m_buffer);
      std::deque<std::string> splitted = split_no_delim(m_buffer, m_delimeter);
      m_currentLineMode = get_line_mode(splitted.front());
      switch(m_currentLineMode){
        case mem::math: evaluate_maths(splitted); break;
        case mem::set: evaluate_set(splitted); break;
      }
      // std::cout<<"the mode is: "<<lineMode<<std::endl;
      // if(lineMode == math){
      //   std::cout<<evaluate_maths(splitted)<<std::endl;
      // }
      for(auto & element : splitted){
        std::cout<<element<<std::endl;
      }
    }

  }
  void evaluate_maths(std::deque<std::string> d){
    int r = 0;
    for(auto & element : d){
      r += std::stoi(element, nullptr);
    }
    std::cout<<r<<std::endl;
  }
  void evaluate_set(std::deque<std::string> d){
    if (std::regex_match(d[1], std::regex("l")))
    {
      m_lNames.push_back(d[2]);
      m_lNumDq.push_back(m_lVecAllocator.allocate());
      std::cout<<"l vec set!"<<std::endl;
      m_lNumDq[0]->print(5);
      m_lNumDq[0]->set_all(5);
      m_lNumDq[0]->print(5);
    }
    else if (std::regex_match(d[1], std::regex("d")))
    {
      m_dNames.push_back(d[2]);
    }
  }
  mem::LINE_MODE get_line_mode(std::string s){
    if(std::regex_search(s, std::regex("^[0-9]")))
    {
      return mem::math;
    }
    else if (std::regex_match(s, std::regex("set")))
    {
      return mem::set;
    }
    else
    {
      return mem::non;
    }
  }

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

};
