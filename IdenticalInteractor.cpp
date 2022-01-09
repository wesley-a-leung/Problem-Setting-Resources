#include <cassert>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <limits>
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>

struct IdenticalReader {
private:
  std::unique_ptr<std::ifstream> streamPtr;
  std::istream &stream;
  int exitCode;
  std::string errorMessage;
  bool hasLast;
  char last;

  void require(const bool expr) const {
    if (!expr) {
      if (exitCode == 3) assert(false);
      else {
        if (!errorMessage.empty()) {
          std::cerr << errorMessage << std::endl;
          std::cout << errorMessage << std::endl;
        }
        exit(exitCode);
      }
    }
  }

  char peekChar() {
    if (!hasLast) stream.get(last); 
    hasLast = true;
    return last;
  }

  char getChar() {
    char ret = peekChar();
    hasLast = false;
    return ret;
  }

public:
  IdenticalReader(std::istream &stream, const int exitCode, const std::string &errorMessage = "")
      : stream(stream), exitCode(exitCode), errorMessage(errorMessage), hasLast(false) {}
  
  IdenticalReader(std::string fileName, const int exitCode, const std::string &errorMessage = "")
      : streamPtr(std::make_unique<std::ifstream>(fileName)), stream(*streamPtr), exitCode(exitCode), errorMessage(errorMessage), hasLast(false) {}

  void setExitCode(int exitCode) {
    this->exitCode = exitCode;
  }

  void setErrorMessage(const std::string &errorMessage) {
    this->errorMessage = errorMessage;
  }

  long long readInt(long long minValid = std::numeric_limits<long long>::min(), long long maxValid = std::numeric_limits<long long>::max()) {
    std::string token = "";
    while (isdigit(peekChar()) || peekChar() == '-') token.push_back(getChar());
    long long ret;
    try {
      ret = std::stoll(token);
    } catch (std::invalid_argument &) {
      require(false);
    }
    require(minValid <= ret && ret <= maxValid);
    return ret;
  }

  long double readFloat(long double minValid = std::numeric_limits<long double>::lowest(), long double maxValid = std::numeric_limits<long double>::max()) {
    std::string token = "";
    while (isdigit(peekChar()) || peekChar() == '-' || peekChar() == '.') token.push_back(getChar());
    long double ret;
    try {
      ret = std::stold(token);
    } catch (std::invalid_argument &) {
      require(false);
    }
    require(minValid <= ret && ret <= maxValid);
    return ret;
  }

  std::string readString(std::regex rgx = std::regex("\\S+")) {
    std::string ret = "";
    while (!isspace(peekChar())) ret.push_back(getChar());
    require(std::regex_match(ret, rgx));
    return ret;
  }

  char readChar(std::regex rgx = std::regex("\\S")) {
    char ret = getChar();
    require(std::regex_match(std::string(1, ret), rgx));
    return ret;
  }

  std::string readLine(std::regex rgx = std::regex(".+")) {
    std::string ret = "";
    while (peekChar() != '\n') ret.push_back(getChar());
    require(std::regex_match(ret, rgx));
    return ret;
  }

  void readSpace() {
    require(getChar() == ' ');
  }

  void readNewLine() {
    require(getChar() == '\n');
  }

  void readEOF() {
    require(getChar() == std::char_traits<char>::eof());
  }
};

int main(int argc, char* argv[]) {
  assert(argc == 3);
  IdenticalReader judgeInput(argv[1], 3), judgeOutput(argv[2], 3), userOutput(std::cin, 1);
  return 0;
}