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
  bool emptyBuffer, hitEOF;

  void getNextLine() {
    emptyBuffer = false;
    lineStream = std::stringstream();
    std::stringstream ss;
    std::string line, token;
    bool hasToken = false;
    while (!hitEOF && !hasToken) {
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

  StandardReader(std::istream &stream, const int exitCode, const std::string &errorMessage = "")
      : stream(stream), exitCode(exitCode), errorMessage(errorMessage), emptyBuffer(true), hitEOF(false) {}
  
  StandardReader(std::string fileName, const int exitCode, const std::string &errorMessage = "")
      : streamPtr(std::make_unique<std::ifstream>(fileName)), stream(*streamPtr), exitCode(exitCode), errorMessage(errorMessage), emptyBuffer(true), hitEOF(false) {}

  void setExitCode(int exitCode) {
    this->exitCode = exitCode;
  }

  void setErrorMessage(const std::string &errorMessage) {
    this->errorMessage = errorMessage;
  }

  long long readInt(long long minValid = std::numeric_limits<long long>::min(), long long maxValid = std::numeric_limits<long long>::max()) {
    if (emptyBuffer) getNextLine();
    long long ret;
    require(lineStream >> ret && minValid <= ret && ret <= maxValid);
    return ret;
  }

  long double readFloat(long double minValid = std::numeric_limits<long double>::lowest(), long double maxValid = std::numeric_limits<long double>::max()) {
    if (emptyBuffer) getNextLine();
    long double ret;
    require(lineStream >> ret && minValid <= ret && ret <= maxValid);
    return ret;
  }

  std::string readString(std::regex rgx) {
    if (emptyBuffer) getNextLine();
    std::string ret;
    require(lineStream >> ret && std::regex_match(ret, rgx));
    return ret;
  }

  std::string readString() {
    if (emptyBuffer) getNextLine();
    std::string ret;
    require(bool(lineStream >> ret));
    return ret;
  }

  char readChar(std::regex rgx = std::regex("\\S")) {
    if (emptyBuffer) getNextLine();
    char ret;
    require(lineStream >> ret && std::regex_match(std::string(1, ret), rgx));
    return ret;
  }

  char readChar() {
    if (emptyBuffer) getNextLine();
    char ret;
    require((lineStream >> ret));
    return ret;
  }

  std::string readLine(std::regex rgx) {
    if (emptyBuffer) getNextLine();
    std::string ret;
    require(std::getline(lineStream, ret) && std::regex_match(ret, rgx));
    return ret;
  }

  std::string readLine() {
    if (emptyBuffer) getNextLine();
    std::string ret;
    require(bool(std::getline(lineStream, ret)));
    return ret;
  }

  void readNewLine() {
    char c;
    require(!(lineStream >> c));
    lineStream = std::stringstream();
    emptyBuffer = true;
  }

  void readEOF() {
    char c;
    require(!(lineStream >> c));
    getNextLine();
    require(hitEOF);
  }
};

int main(int argc, char* argv[]) {
  assert(argc == 4);
  StandardReader judgeInput(argv[1], 3), userOutput(argv[2], 1), judgeOutput(argv[3], 3);
  return 0;
}
