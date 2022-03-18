#include "Input.h"

int main(int argc, char* argv[]) {
  Input::Validator in(std::cin);
  in.readEOF();
  return 0;
}
