#include "tui.hpp"

#include <iostream>
#include <time.h>

#include <bitset>
#include <math.h>

#include <iostream>
#include <sys/ioctl.h>
#include <time.h>

int main(int argc, const char* argv[])
{
  tui::InitTui();
  tui::Raw();
  tui::NoEcho();
  tui::NoCursor();
  // tui::Print("\u01f6");
  // tui::Refresh();
  // tui::GetCh();
  tui::EnabledMouse(tui::MOUSE_MOVEMENT);
  tui::Canvas canv = tui::stdscr.CreateCanvas();
  canv.Box();
  // canv.SetPixel(tui::TWO_BLOCK);
  canv.SetPixel(tui::BRAILLE);
  // canv.SetPixel(tui::QUARTER_BLOCK);
  // canv.SetPixel(tui::BLOCK);
  canv.EnableBorder();
  canv.Refresh();
  tui::Refresh();
  bool looping = true;
  while (looping == true) {
    tui::Event ev = tui::WaitEvent();
    if (ev.type == tui::KEYBOARD_EVENT) {
      if (ev.keyboard.key == tui::KEY_Q) {
        looping = false;
      } else if (ev.keyboard.key == tui::KEY_C) {
        canv.ClearCanvas();
      }
    } else if (ev.type == tui::MOUSE_EVENT) {
      if (ev.mouse.type == tui::MOUSE_BUTTON_DOWN || ev.mouse.type == tui::MOUSE_MOVE) {
        // if (ev.mouse.button == tui::MOUSE_BUTTON_LEFT) {
        canv.DrawPoint(0.5 * (ev.mouse.x - 2), ((canv.MaxY() - (1 * ev.mouse.y)) + 1));
        // }
      }
    }
    canv.Refresh();
    tui::Refresh();
  }
  tui::DisableMouse(tui::MOUSE_MOVEMENT);
  tui::Cursor();
  tui::Echo();
  tui::NoRaw();
  tui::TermTui();
  return 0;
}
