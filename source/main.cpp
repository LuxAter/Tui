#include "tui.hpp"

#include <time.h>
#include <iostream>

int main(int argc, const char* argv[]) {
  // std::string unicode = "\u251C";
  // std::cout << unicode << ":\n";
  // for (int i = 0; i < unicode.size(); i++) {
  // std::cout << "  " << unicode[i] << ">" << static_cast<int>(unicode[i])
  // << "\n";
  // }
  tui::ColorPair a{{255, 0, 255}, {156, 156, 0}};
  tui::InitTui();
  tui::Raw();
  tui::NoEcho();
  tui::NoCursor();
  tui::Window s = tui::CreateWindow(5, 5, 40, 40);
  tui::Window ss = s.CreateWindow(5, 5, 20, 20);
  // ss.Print("Hello WOrld");
  ss.Fill(' ');
  ss.Box();
  tui::SetTimeout(1);
  tui::stdscr.Print("Hello\u251bWorld");
  s.Show();
  tui::Refresh();
  time_t t = time(NULL);
  double fps = 0;
  while (true) {
    s.Print("%i", rand());
    ss.Show();
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
