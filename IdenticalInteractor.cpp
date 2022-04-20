#include "Input.h"

int main(int argc, char* argv[]) {
  assert(argc == 3);
  Input::Validator judgeInput(argv[1]);
  Input::Validator judgeOutput(argv[2]);
  Input::IdenticalReader userOutput(std::cin);
  return ExitCode::AC;
}
