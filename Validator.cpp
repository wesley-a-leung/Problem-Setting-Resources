#include "Input.h"

int main(int argc, char* argv[]) {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  Input::Validator in(std::cin);
  in.readEOF();
  return 0;
}
