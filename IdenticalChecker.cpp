#include "Input.h"

int main(int argc, char* argv[]) {
  assert(argc == 4);
  Input::Validator judgeInput(argv[1]);
  Input::IdenticalReader userOutput(argv[2]);
  Input::Validator judgeOutput(argv[3]);
  return ExitCode::AC;
}
