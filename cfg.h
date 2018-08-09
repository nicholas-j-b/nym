

namespace cfg{
  const size_t CONTENT_SIZE = 240;
  const size_t NUM_CONTENT_IN_POOL = 16;
  const std::string LINE_DELIMETER = " ";
  const size_t MAX_NUM_LINE_SYMBOLS = 64;
  const size_t NUM_CHECKS = 2;
};

namespace lco{
  //enum LINE_MODE {math, set, non};
  enum SYMBOL {
    notGiven, exitP, set, plus, minus, multiply, divide, equal, variable, unknown, tooLong
  };

  const std::map<SYMBOL, std::regex> SYMBOL_CONVERSIONS_MAP {
    { exitP, std::regex("exit")},
    { set, std::regex("set") },
    { plus, std::regex("\\+") },
    { minus, std::regex("-") },
    { multiply, std::regex("\\*") },
    { divide, std::regex("/") },
    { equal, std::regex("=")},
    { variable, std::regex("^[a-z][0-9a-zA-Z_]+") } // variable must be last???
  };


  // struct COMPREHENSION_FORM{
  //   bool s;
  //   bool p;
  //   bool TOOLONG;
  // };
};

namespace erc{
  enum ERROR {
    noError, userQuit, invalidVariable, overwriteVariableAttempt, unknownVariable,
    tooLong
  };
}
