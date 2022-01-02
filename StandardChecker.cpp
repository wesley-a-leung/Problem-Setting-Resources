#include <cassert>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <limits>
#include <memory>
#include <regex>
#include <string>

struct StandardReader {
private:
  std::unique_ptr<std::ifstream> streamPtr;
  std::istream &stream;
  int exitCode;
  std::string errorMessage;
  std::stringstream lineStream;
  bool hitEOF;

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

  void getNextLine() {
    lineStream = std::stringstream();
    std::stringstream ss;
    std::string line, token;
    bool hasToken = false;
    while (!hasToken) {
      if (!std::getline(stream, line)) {
        hitEOF = true;
        break;
      }
      ss << line;
      while (ss >> token) {
        if (hasToken) lineStream << ' ';
        hasToken = true;
        lineStream << token;
      }
    }
  }

public:
  StandardReader(std::istream &stream, const int exitCode, const std::string &errorMessage = "")
      : stream(stream), exitCode(exitCode), errorMessage(errorMessage), hitEOF(false) {
    getNextLine();
  }
  
  StandardReader(std::string fileName, const int exitCode, const std::string &errorMessage = "")
      : streamPtr(std::make_unique<std::ifstream>(fileName)), stream(*streamPtr), exitCode(exitCode), errorMessage(errorMessage), hitEOF(false) {
    getNextLine();
  }

  void setExitCode(int exitCode) {
    this->exitCode = exitCode;
  }

  void setErrorMessage(const std::string &errorMessage) {
    this->errorMessage = errorMessage;
  }

  long long readInt(long long minValid = std::numeric_limits<long long>::min(), long long maxValid = std::numeric_limits<long long>::max()) {
    long long ret;
    require(lineStream >> ret && minValid <= ret && ret <= maxValid);
    return ret;
  }

  long double readFloat(long double minValid = std::numeric_limits<long double>::lowest(), long double maxValid = std::numeric_limits<long double>::max()) {
    long double ret;
    require(lineStream >> ret && minValid <= ret && ret <= maxValid);
    return ret;
  }

  std::string readString(std::regex rgx = std::regex("\\S+")) {
    std::string ret;
    require(lineStream >> ret && std::regex_match(ret, rgx));
    return ret;
  }

  char readChar(std::regex rgx = std::regex("\\S")) {
    char ret;
    require(lineStream >> ret && std::regex_match(std::string(1, ret), rgx));
    return ret;
  }

  std::string readLine(std::regex rgx = std::regex(".+")) {
    std::string ret;
    require(std::getline(lineStream, ret) && std::regex_match(ret, rgx));
    return ret;
  }

  void readNewLine() {
    char c;
    require(!(lineStream >> c));
    getNextLine();
  }

  void readEOF() {
    char c;
    require(hitEOF && !(stream >> c));
  }
};

int main(int argc, char* argv[]) {
  assert(argc == 4);
  StandardReader input(argv[1], 3), actualOutput(argv[2], 1), expectedOutput(argv[3], 3);
  return 0;
}
