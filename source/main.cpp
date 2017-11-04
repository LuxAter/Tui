#include "tui.hpp"

#include <iostream>

int main(int argc, const char* argv[]) {
  tui::ColorPair a{{255, 255, 0}, {0, 255, 255}};
  tui::InitTui();
  tui::Raw();
  tui::NoEcho();
  tui::NoCursor();
  // tui::SetColor(255, 0, 255);
  tui::SetColor(a);
  // tui::SetBackground(tui::BLUE);
  tui::BufferWrite(5, 40, "Hello");
  tui::SetColor(tui::RED);
  tui::BufferWrite(0, 0, "0");
  tui::BufferWrite(1, 1, "A");
  tui::SetColor(87);
  tui::SetBackground(tui::DEFAULT);
  tui::BufferWrite(2, 2, "B");
  tui::BufferWrite(3, 3, "C");
  tui::BufferRefresh();
  // tui::BufferClear();
  // tui::BufferRefresh();
  // std::cout << "Enter: \n";
  // tui::SetTimeout(5000);
  unsigned int ch = tui::getch();
  // std::cout << ch << "<<\n";
  tui::Cursor();
  tui::Echo();
  tui::NoRaw();
  tui::TermTui();
  /* code */
  return 0;
}
