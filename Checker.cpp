#include <cassert>
#include <fstream>
#include <iostream>
#include <istream>
#include <limits>
#include <memory>
#include <regex>
#include <string>

struct Reader {
private:
  std::unique_ptr<std::ifstream> streamPtr;
  std::istream &stream;
  int exitCode;
  std::string errorMessage;

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

public:
  Reader(std::istream &stream, const int exitCode, const std::string &errorMessage = "")
      : stream(stream), exitCode(exitCode) {}
  
  Reader(std::string fileName, const int exitCode, const std::string &errorMessage = "")
      : streamPtr(std::make_unique<std::ifstream>(fileName)), stream(*streamPtr), exitCode(exitCode) {}

  void setExitCode(int exitCode) {
    this->exitCode = exitCode;
  }

  void setErrorMessage(const std::string &errorMessage) {
    this->errorMessage = errorMessage;
  }

  long long readInt(long long minValid = std::numeric_limits<long long>::min(), long long maxValid = std::numeric_limits<long long>::max()) {
    long long ret;
    require(stream >> ret && minValid <= ret && ret <= maxValid);
    return ret;
  }

  long double readFloat(long double minValid = std::numeric_limits<long double>::lowest(), long double maxValid = std::numeric_limits<long double>::max()) {
    long double ret;
    require(stream >> ret && minValid <= ret && ret <= maxValid);
    return ret;
  }

  std::string readString(std::regex rgx = std::regex("\\S+")) {
    std::string ret;
    require(stream >> ret && std::regex_match(ret, rgx));
    return ret;
  }

  char readChar(std::regex rgx = std::regex("\\S")) {
    char ret;
    require(stream >> ret && std::regex_match(std::string(1, ret), rgx));
    return ret;
  }

  std::string readLine(std::regex rgx = std::regex(".+")) {
    std::string ret;
    require(std::getline(stream, ret) && std::regex_match(ret, rgx));
    return ret;
  }

  void skipws() {
    stream >> std::ws;
  }

  void readEOF() {
    char c;
    require(!(stream >> c));
  }
};

int main(int argc, char* argv[]) {
  assert(argc == 4);
  Reader input(argv[1], 3), actualOutput(argv[2], 1), expectedOutput(argv[3], 3);
  return 0;
}
