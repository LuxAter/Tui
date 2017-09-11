#include "tui.hpp"

#include <iostream>

int main(int argc, const char* argv[]) {
  tui::InitTui();
  tui::Raw();
  tui::NoEcho();
  unsigned int ch = tui::getch();
  std::cout << ch << "<<\n";
  tui::Echo();
  tui::NoRaw();
  tui::TermTui();
  /* code */
  return 0;
}
