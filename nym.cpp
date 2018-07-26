
#include "Session.h"

int main(){
  std::cout<<"nym 0.0.03c"<<std::endl;
  Session session;
  session.main_loop();
  return 0;
}












// class DataList {
// private:
//   union Content {
//     std::list<long> iNums
//   }
// public:
//
// }

// enum LINE_MODE {math, set, non};
// // enum DATA_MODE {iNums, dNums, cChar};
// union lContent {
//   long lNums[cfg::CONTENT_SIZE];
//   char cChar[cfg::CONTENT_SIZE * sizeof(long)];
// };
//
// class lNumVector {
// private:
//   lContent content;
// public:
//   lNumVector() {};
//   ~lNumVector() {};
//   lNumVector(const lNumVector& other) = delete;
//   lNumVector(const lNumVector&& other) = delete;
//   lNumVector& operator=(const lNumVector& other) = delete;
//   lNumVector& operator=(const lNumVector&& other) = delete;
//
//   long operator[](int i) const {return content.lNums[i];}
//   long& operator[](int i){if(i <= cfg::CONTENT_SIZE){return content.lNums[i];}}
//
//   void zeros(){
//     std::memset(content.lNums, 0, cfg::CONTENT_SIZE);
//   }
//
//   void set_all(int a){
//     for (size_t i = 0; i < cfg::CONTENT_SIZE; ++i){
//       content.lNums[i] = a;
//     }
//   }
// };
//
//
//
// std::deque<std::string> split_no_delim(std::string &stringToBeSplitted, std::string delimeter)
// {
//   std::deque<std::string> splittedString;
//   int startIndex = 0;
//   int  endIndex = 0;
//   while( (endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size() )
//   {
//     std::string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);
//     if(!val.empty())
//     {
//       splittedString.push_back(val);
//     }
//     startIndex = endIndex + delimeter.size();
//   }
//   if(startIndex < stringToBeSplitted.size())
//   {
//     std::string val = stringToBeSplitted.substr(startIndex);
//     splittedString.push_back(val);
//   }
//   return splittedString;
// }
//
//
// LINE_MODE get_line_mode(std::string s){
//   if(std::regex_search(s, std::regex("^[0-9]")))
//   {
//     return math;
//   }
//   else if (std::regex_match(s, std::regex("set")))
//   {
//     return set;
//   }
//   else
//   {
//     return non;
//   }
// }
//
// void evaluate_maths(std::deque<std::string> d){
//   int r = 0;
//   for(auto & element : d){
//     r += std::stoi(element, nullptr);
//   }
//   std::cout<<r<<std::endl;;
// }
// void evaluate_set(std::deque<std::string> d){
//
// }
