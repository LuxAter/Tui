#include "tui.hpp"

#include <iostream>

int main(int argc, const char* argv[]) {
  tui::InitTui();
  std::cout << "Hello World!";
  int a;
  std::cin >> a;
  tui::TermTui();
  /* code */
  return 0;
}
