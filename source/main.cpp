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
  s.Box();
  s.EnableBorder();
  s.mvPrint(5, 0, "HELLO");
  s.Move(1, 1);
  ss.Fill(' ');
  ss.Box();
  ss.EnableBorder();
  // ss.Box('+', tui::UTF_VERTICAL_DOUBLE_DASH,
  // tui::UTF_HORIZONTAL_DOUBLE_DASH);
  tui::SetTimeout(1);
  tui::Print(L"Hello World");
  s.Show();
  tui::Refresh();
  time_t t = time(NULL);
  double fps = 0;
  while (true) {
    s.Print(L"%i", rand());
    ss.Show();
    s.Show();
    tui::Refresh();
    fps++;
    unsigned int ch = tui::getch();
    if (ch == tui::KEY_Q) {
      break;
    } else if (ch != tui::KEY_ERR) {
      ss.Print(ch);
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
