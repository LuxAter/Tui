#include "tui.hpp"

#include <time.h>
#include <iostream>

int main(int argc, const char* argv[]) {
  // tui::ColorPair a{{255, 0, 255}, {0, 0, 0}};
  tui::InitTui();
  tui::Raw();
  tui::NoEcho();
  tui::NoCursor();
  tui::Window s = tui::CreateWindow();
  tui::SetTimeout(1);
  tui::stdscr.Print("Hello World");
  time_t t = time(NULL);
  double fps = 0;
  while (true) {
    for (int i = 0; i < 200; i++) {
      s.Print("%i", rand());
    }
    s.Show();
    tui::Refresh();
    fps++;
    unsigned int ch = tui::getch();
    if (ch == tui::KEY_Q) {
      break;
    }
  }
  t = time(NULL) - t;
  fps /= t;
  tui::Cursor();
  tui::Echo();
  tui::NoRaw();
  tui::TermTui();
  std::cout << fps << "\n";
  return 0;
}
