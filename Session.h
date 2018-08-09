#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <cstring>
#include <regex>
#include <map>
#include <typeinfo>
#include <algorithm>

#include <editline/readline.h>
#include <editline/history.h>

#include "cfg.h"
#include "PoolAllocator.h"


class Session{
private:
  std::string m_buffer;
  std::vector<lco::SYMBOL> m_formEntries;
  std::deque<std::string> m_splittedBuffer;

  mem::PoolAllocator<mem::lNumVector> m_lVecAllocator;
  mem::PoolAllocator<mem::dNumVector> m_dVecAllocator;
  std::map<std::string, mem::NumVector*> m_varMap;

  std::deque<mem::lNumVector*> m_lNumDq;
  std::deque<mem::dNumVector*> m_dNumDq;
  std::deque<std::string> m_lNames;
  std::deque<std::string> m_dNames;

public:
  Session() {m_formEntries.reserve(cfg::MAX_NUM_LINE_SYMBOLS);};
  ~Session(){
    for(auto& i : m_lNumDq){
      m_lVecAllocator.deallocate(i);
    }
    for(auto& i : m_dNumDq){
      m_dVecAllocator.deallocate(i);
    }
  }; // end deconstructor

  mem::ERROR_CODE main_loop(){
    std::vector<erc::ERROR> exitStatus(cfg::NUM_CHECKS, erc::noError);
    while(std::all_of(exitStatus.begin(), exitStatus.end(), [](erc::ERROR e){return e == erc::noError ? true : false;})){
      std::cout<<"nym> ";
      std::getline(std::cin, m_buffer);
      m_splittedBuffer = split_no_delim(m_buffer, cfg::LINE_DELIMETER);
      exitStatus[0] = comprehend_line();
      exitStatus[1] = interpret();
    }
    return mem::noError;
  } // end main_loop()

  erc::ERROR interpret(){
    erc::ERROR e = erc::noError;
    switch (m_formEntries[0]) {
      case lco::exitP :
        e = erc::userQuit;
        break;
      case lco::set :
        e = interpret_set();
        break;
      case lco::variable :
        e = display_variable();
        break;
    }
    return e;
  } // end interpret()

  erc::ERROR display_variable(){
    auto position = m_varMap.find(m_splittedBuffer[0]);
    if(position == m_varMap.end()){
      std::cout<<"variable not yet set"<<std::endl;
      return erc::unknownVariable;
    } else {
      mem::lNumVector* pos = dynamic_cast<mem::lNumVector*>(position->second);
      for(size_t i = 0; i < 10; ++i){
        std::cout<<(*pos)[i]<<" ";
      }
      std::cout<<std::endl;
    }
    return erc::noError;
  } // end display_variable()

  erc::ERROR interpret_set(){
    if(m_formEntries[1] != lco::variable){
      return erc::invalidVariable;
    }
    if(m_varMap.find(m_splittedBuffer[1]) == m_varMap.end()){
      m_lNumDq.push_back(m_lVecAllocator.allocate());
      mem::lNumVector* justAdded = m_lNumDq.back();
      justAdded->set_all(std::stoi(m_splittedBuffer[2], nullptr, 10));
      m_varMap.insert(std::pair<std::string, mem::NumVector*>(m_splittedBuffer[1], justAdded));
      return erc::noError;
    } else {
      std::cout<<"overwriteVariableAttempt"<<std::endl;
      return erc::overwriteVariableAttempt;
    }
  } // end interpret_set()

  erc::ERROR user_quit(){
    return m_formEntries[0] == lco::exitP ? erc::userQuit : erc::noError;
  } // end user_quit()

  void debug_printing(const std::deque<std::string>& splitted){
    for(auto & element : splitted){
      std::cout<<element<<std::endl;
    }
    for(size_t i = 0; i < 10; i++){
      std::cout<<m_formEntries[i]<<std::endl;
    }
  } // end debug_printing()

  lco::SYMBOL comprehend_element(const std::string& element){
    for(auto const& val : lco::SYMBOL_CONVERSIONS_MAP){
      if(std::regex_match(element, val.second)){
        return val.first;
      }
    }
    return lco::unknown;
  } // end comprehend_element

  erc::ERROR comprehend_line(){
    for(auto it = m_splittedBuffer.begin(); it != m_splittedBuffer.end(); ++it){
      auto i = std::distance(m_splittedBuffer.begin(), it);
      if(i >= cfg::MAX_NUM_LINE_SYMBOLS){
        return erc::tooLong;
      }
      m_formEntries[i] = comprehend_element(*it);
    }
    return erc::noError;
  } // end comprehend_line

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
