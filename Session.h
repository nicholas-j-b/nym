#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <cstring>
#include <regex>
#include <map>

#include <editline/readline.h>
#include <editline/history.h>

#include "cfg.h"
#include "PoolAllocator.h"


class Session{
private:
  std::string m_buffer;
  lco::SYMBOL m_formEntries[cfg::MAX_NUM_LINE_SYMBOLS] = { };
  //lco::LINE_MODE m_currentLineMode;
  mem::PoolAllocator<mem::lNumVector> m_lVecAllocator;
  mem::PoolAllocator<mem::dNumVector> m_dVecAllocator;
  std::deque<mem::lNumVector*> m_lNumDq;
  std::deque<mem::dNumVector*> m_dNumDq;
  std::deque<std::string> m_lNames;
  std::deque<std::string> m_dNames;
public:
  Session() {};
  ~Session(){
    for(auto& i : m_lNumDq){
      m_lVecAllocator.deallocate(i);
      std::cout<<"correctly destructed"<<std::endl;
    }
    for(auto& i : m_dNumDq){
      m_dVecAllocator.deallocate(i);
    }
  }; // end deconstructor

  mem::ERROR_CODE main_loop(){
    while(true){
      std::cout<<"nym> ";
      std::getline(std::cin, m_buffer);
      std::deque<std::string> splitted = split_no_delim(m_buffer, cfg::LINE_DELIMETER);
      // m_currentLineMode = get_line_mode(splitted.front());
      comprehend_line(splitted, m_formEntries);
      for(auto & element : splitted){
        std::cout<<element<<std::endl;
      }
      for(size_t i = 0; i < 10; i++){
        std::cout<<m_formEntries[i]<<std::endl;
      }
    }
    return mem::noError;
  } // end main_loop()

  lco::SYMBOL comprehend_element(const std::string& element){
    for(auto const& val : lco::SYMBOL_CONVERSIONS_MAP){
      if(std::regex_match(element, val.second)){
        return val.first;
      }
    }
    return lco::unknown;
  } // end comprehend_element

  void comprehend_line(std::deque<std::string>& lineElements, lco::SYMBOL* formEntries){
    for(auto it = lineElements.begin(); it != lineElements.end(); ++it){
      auto i = std::distance(lineElements.begin(), it);
      if(i >= cfg::MAX_NUM_LINE_SYMBOLS){
        formEntries[cfg::MAX_NUM_LINE_SYMBOLS] = lco::tooLong;
        break;
      }
      formEntries[i] = comprehend_element(*it);
    }
  } // end comprehend_line


  // void evaluate_maths(std::deque<std::string> d){
  //   int r = 0;
  //   for(auto & element : d){
  //     r += std::stoi(element, nullptr);
  //   }
  //   std::cout<<r<<std::endl;
  // }; // end evaluate_maths
  //
  // void evaluate_set(std::deque<std::string> d){
  //   if (std::regex_match(d[1], std::regex("l")))
  //   {
  //     m_lNames.push_back(d[2]);
  //     m_lNumDq.push_back(m_lVecAllocator.allocate());
  //     std::cout<<"l vec set!"<<std::endl;
  //     m_lNumDq[0]->print(5);
  //     m_lNumDq[0]->set_all(5);
  //     m_lNumDq[0]->print(5);
  //   }
  //   else if (std::regex_match(d[1], std::regex("d")))
  //   {
  //     m_dNames.push_back(d[2]);
  //   }
  // }; // end evaluate_set

  // mem::LINE_MODE get_line_mode(std::string s){
  //   if(std::regex_search(s, std::regex("^[0-9]")))
  //   {
  //     return mem::math;
  //   }
  //   else if (std::regex_match(s, std::regex("set")))
  //   {
  //     return mem::set;
  //   }
  //   else
  //   {
  //     return mem::non;
  //   }
  // }
  std::deque<std::string> split_no_delim(std::string& stringToBeSplitted, std::string delimeter){
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
  } // end split_no_delim


};
