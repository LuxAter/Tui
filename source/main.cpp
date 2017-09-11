#include "tui.hpp"

#include <iostream>

int main(int argc, const char* argv[]) {
  /* code */
  printf("%i", tui::HasColor());
  tui::Raw();
  tui::NoEcho();
  std::cout << "Enter a string: ";
  std::string str;
  std::cin >> str;
  tui::Echo();
  tui::NoCursor();
  std::cout << "Enter a new string: ";
  std::cin >> str;
  tui::Cursor();
  tui::NoRaw();
  return 0;
}
