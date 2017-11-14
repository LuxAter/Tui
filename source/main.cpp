#include "tui.hpp"

#include <time.h>
#include <iostream>

int main(int argc, const char* argv[]) {
  // std::vector<std::string> un = {"\u0000", "\u1000", "\u2000", "\u3000",
  // "\u4000", "\u5000", "\u6000", "\u7000",
  // "\u8000", "\u9000", "\uA000"};
  // for (int j = 0; j < un.size(); j++) {
  // std::string unicode = un[j];
  // std::cout << unicode << ":\n";
  // for (int i = 0; i < unicode.size(); i++) {
  // std::cout << "  " << unicode[i] << ">" << static_cast<int>(unicode[i])
  // << "\n";
  // }
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
  tui::Print(L"Hello World");
  s.Show();
  tui::Refresh();
  time_t t = time(NULL);
  double fps = 0;
  while (true) {
    // s.Print("%i", rand());
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
