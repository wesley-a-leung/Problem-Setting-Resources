#include <bits/stdc++.h>

namespace Validator {
  bool _hasLast = false;
  char _last;

  char _peekChar() {
    _last = _hasLast ? _last : getchar();
    _hasLast = true;
    return _last;
  }

  char _getChar() {
    char ret = _peekChar();
    _hasLast = false;
    return ret;
  }

  bool _isEOF(char c) {
    return c == std::char_traits<char>::eof();
  }

  long long readInt(long long minValid = std::numeric_limits<long long>::min(), long long maxValid = std::numeric_limits<long long>::max()) {
    std::string token = "";
    while (isdigit(_peekChar()) || _peekChar() == '-') token.push_back(_getChar());
    long long ret = std::stoll(token);
    assert(minValid <= ret && ret <= maxValid);
    return ret;
  }

  long double readFloat(long double minValid = std::numeric_limits<long double>::lowest(), long double maxValid = std::numeric_limits<long double>::max()) {
    std::string token = "";
    while (isdigit(_peekChar()) || _peekChar() == '-' || _peekChar() == '.') token.push_back(_getChar());
    long double ret = std::stold(token);
    assert(minValid <= ret && ret <= maxValid);
    return ret;
  }

  std::string readString(const std::regex &rgx) {
    std::string ret = "";
    while (!isspace(_peekChar())) {
      assert(!_isEOF(_peekChar())); 
      ret.push_back(_getChar());
    }
    assert(std::regex_match(ret, rgx));
    return ret;
  }

  std::string readString() {
    std::string ret = "";
    while (!isspace(_peekChar())) {
      assert(!_isEOF(_peekChar())); 
      ret.push_back(_getChar());
    }
    return ret;
  }

  char readChar(const std::regex &rgx) {
    assert(!_isEOF(_peekChar())); 
    char ret = _getChar();
    assert(std::regex_match(std::string(1, ret), rgx));
    return ret;
  }

  char readChar() {
    assert(!_isEOF(_peekChar())); 
    return _getChar();
  }

  std::string readLine(const std::regex &rgx) {
    std::string ret = "";
    while (_peekChar() != '\n') {
      assert(!_isEOF(_peekChar())); 
      ret.push_back(_getChar());
    }
    assert(std::regex_match(ret, rgx));
    return ret;
  }

  std::string readLine() {
    std::string ret = "";
    while (_peekChar() != '\n') {
      assert(!_isEOF(_peekChar())); 
      ret.push_back(_getChar());
    }
    return ret;
  }

  void readSpace() {
    assert(_getChar() == ' ');
  }

  void readNewLine() {
    assert(_getChar() == '\n');
  }

  void readEOF() {
    assert(_isEOF(_getChar())); 
  }
}

using namespace Validator;

int main() {
  readString();
  readEOF();
  return 0;
}
