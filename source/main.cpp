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
  tui::Canvas canv = tui::stdscr.CreateCanvas();
  // tui::SetTimeout(20);
  canv.DisableScroll();
  // canv.Fill('#');
  canv.Box();
  canv.EnableBorder();
  // canv.SetPixel(tui::QUARTER_BLOCK);
  canv.SetPixel(tui::BRAILLE);
  canv.SetOrigin(0.5, 0.5);
  canv.SetColor(255, 17, 129);
  for (int i = canv.MinX(); i < canv.MaxX(); i++) {
    // std::cout << "   " << i << "\n";
    // canv.DrawPoint(i, 0.01 * i);
    // canv.DrawPoint(i, i);
    // canv.DrawPoint(i, 0.001 * pow(i, 3));
    canv.Refresh();
    tui::Refresh();
    // canv.DrawPoint(i, 10 * tan(i / 50.0));
    // canv.SetColor(10 * tan(i / 50.0), 10 * tan(i / 50.0), 10 * tan(i /
    // 50.0));
    // canv.SetColor(i, i, 255);
    double freq = 20.0;
    double scale = 33.333;
    // canv.SetColor(tui::RED);
    // canv.DrawPoint(
    // i, scale * sin((i / 2.0) / freq) * sin((10.0 * i / 2.0) / freq));
    // canv.SetColor(tui::BLUE);
    // canv.DrawPoint(i, scale * sin((i / 2.0) / freq));
    // canv.SetColor(tui::GREEN);
    // canv.DrawPoint(i, -scale * sin((i / 2.0) / freq));
    // canv.DrawLine(
    // i, scale * sin((i / 2.0) / freq) * sin((10.0 * i / 2.0) / freq), i - 1,
    // scale * sin(((i - 1) / 2.0) / freq) *
    // sin((10.0 * (i - 1) / 2.0) / freq));
    // canv.SetColor(tui::BLUE);
    // canv.DrawLine(i, scale * sin((i / 2.0) / freq), i - 1,
    // scale * sin(((i - 1) / 2.0) / freq));
    // canv.SetColor(tui::GREEN);
    // canv.DrawLine(i, -scale * sin((i / 2.0) / freq), i - 1,
    // -scale * sin(((i - 1) / 2.0) / freq));
    canv.DrawLine(i, 10 * tan(i / 25.0), i - 1, 10 * tan((i - 1) / 25.0));
    // canv.DrawPoint(i, sqrt(pow(100, 2) - pow(i, 2)));
    // canv.DrawLine(i, sqrt(pow(100, 2) - pow(i, 2)), i - 1,
    // sqrt(pow(100, 2) - pow(i - 1, 2)));
    // canv.DrawPoint(i, 50 * (sin(i / 10.0) - sin(i / 20.0)));
  }
  canv.Refresh();
  tui::Refresh();
  canv.Refresh();
  tui::Refresh();
  while (tui::getch() == tui::KEY_ERR) {
  }
  tui::Cursor();
  tui::Echo();
  tui::NoRaw();
  tui::TermTui();
  return 0;
}
