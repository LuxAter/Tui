#include "tui.hpp"

#include <time.h>
#include <iostream>

#include <math.h>
#include <bitset>

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
  // tui::ColorPair a{{255, 0, 255}, {156, 156, 0}};
  tui::InitTui();
  tui::Raw();
  tui::NoEcho();
  tui::NoCursor();
  tui::Canvas canv = tui::stdscr.CreateCanvas(0, 0, 50, 50);
  canv.DisableScroll();
  // canv.Fill('#');
  canv.Box();
  canv.EnableBorder();
  canv.SetPixel(tui::BRAILLE);
  canv.SetOrigin(0.5, 0.5);
  canv.DrawPoint(0, 0);
  canv.SetColor(tui::RED);
  canv.Refresh();
  tui::Refresh();
  // canv.DrawPoint(1, 1);
  // canv.SetPixel(tui::BRAIL);
  for (int i = canv.MinX(); i < canv.MaxX(); i++) {
    // std::cout << "   " << i << "\n";
    // canv.DrawPoint(i, i);
    canv.DrawPoint(i, 0.001 * pow(i, 3));
    canv.Refresh();
    tui::Refresh();
    // canv.DrawPoint(i, 5 * sin(i / 5.0));
  }
  canv.Refresh();
  tui::Refresh();
  tui::getch();
  tui::Cursor();
  tui::Echo();
  tui::NoRaw();
  tui::TermTui();
  return 0;
}
