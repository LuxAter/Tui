#include "tui.hpp"

#include <time.h>
#include <iostream>

#include <math.h>
#include <bitset>

int main(int argc, const char* argv[]) {
  tui::InitTui();
  tui::Raw();
  tui::NoEcho();
  tui::NoCursor();
  tui::stdscr.SetColor(255, 255, 10);
  tui::Canvas canv = tui::stdscr.CreateCanvas();
  canv.DisableScroll();
  canv.Box();
  canv.EnableBorder();
  canv.SetPixel(tui::BRAILLE);
  // tui::SetTimeout(100);
  // canv.SetPixel(tui::TWO_BLOCK);
  // canv.SetPixel(tui::HORIZONTAL_BLOCK);
  // canv.SetPixel(tui::SQUARE);
  canv.SetOrigin(0.5, 0.5);
  canv.SetColor(255, 17, 129);
  // canv.DrawRegularPolygon(0, 0, 20, 5);
  // canv.DrawPolygon(
  // {-25, 0, -10, -25, 0, -10, 10, -25, 25, 0, 10, 25, 0, 10, -10, 25});
  canv.SetColor(tui::YELLOW);
  canv.DrawFilledPolygon(
      {-25, 0, -10, -25, 0, -10, 10, -25, 25, 0, 10, 25, 0, 10, -10, 25});
  // canv.DrawFilledRegularPolygon(0, 0, 20, 20);
  // canv.DrawFilledCircle(0, 0, 20);
  // canv.DrawFilledPolygon({-25, -10, 0, 10, 25, 10, 0, -10},
  // {0, -25, -10, -25, 0, 25, 10, 25});
  // canv.DrawRegularPolygon(0, 0, 20, 100);
  canv.Refresh();
  tui::Refresh();
  tui::getch();
  tui::Cursor();
  tui::Echo();
  tui::NoRaw();
  tui::TermTui();
  return 0;
}
