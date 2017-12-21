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
  tui::EnabledMouse(tui::MOUSE_MOVEMENT);
  tui::Canvas canv = tui::stdscr.CreateCanvas();
  canv.Box();
  canv.SetPixel(tui::TWO_BLOCK);
  canv.EnableBorder();
  canv.Refresh();
  tui::Refresh();
  bool looping = true;
  while (looping == true) {
    tui::Event ev = tui::WaitEvent();
    if (ev.type == tui::KEYBOARD_EVENT) {
      if (ev.keyboard.key == tui::KEY_Q) {
        looping = false;
      }else if(ev.keyboard.key == tui::KEY_C){
        canv.ClearCanvas();
      }
    } else if (ev.type == tui::MOUSE_EVENT) {
      if (ev.mouse.type == tui::MOUSE_BUTTON_DOWN ||
          ev.mouse.type == tui::MOUSE_MOVE) {
        // if (ev.mouse.button == tui::MOUSE_BUTTON_LEFT) {
          canv.DrawPoint(0.5*(ev.mouse.x - 2), ((canv.MaxY() - (1*ev.mouse.y)) + 1));
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
