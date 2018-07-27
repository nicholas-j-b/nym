

namespace cfg{
  const size_t CONTENT_SIZE = 256;
  const size_t NUM_CONTENT_IN_POOL = 16;
  const std::string LINE_DELIMETER = " ";
};

namespace lco{
  //enum LINE_MODE {math, set, non};
  enum SYMBOL {
    set, plus, minus, multiply, divide, variable, unknown
  };
  // const std::deque<std::regex> SYMBOL_CONVERSIONS = {
  //   std::regex("set"),
  //   std::regex("\\+"),
  //   std::regex("-"),
  //   std::regex("\\*"),
  //   std::regex("/")
  // };

  const std::map<SYMBOL, std::regex> SYMBOL_CONVERSIONS_MAP {
    { set, std::regex("set") },
    { plus, std::regex("\\+") },
    { minus, std::regex("-") },
    { multiply, std::regex("\\*") },
    { divide, std::regex("/")}
  };


  struct COMPREHENSION_FORM{
    bool s;
    bool p;
  };
};
