#include "tui.hpp"

#include <time.h>
#include <iostream>

#include <math.h>
#include <bitset>

#include <sys/ioctl.h>
#include <time.h>
#include <iostream>

int main(int argc, const char* argv[]) {
  tui::InitTui();
  tui::Raw();
  tui::NoEcho();
  tui::NoCursor();
  tui::EnabledMouse();
  tui::Window canv = tui::stdscr.CreateWindow();
  canv.Refresh();
  tui::Refresh();
  char ch = tui::GetCh(-1);
  tui::DisableMouse();
  tui::Cursor();
  tui::Echo();
  tui::NoRaw();
  tui::TermTui();
  std::cout << ch << "\"\n";
  // std::cout << ev.type << ">>" << ev.x << "," << ev.y << "<<\n";
  return 0;
}
