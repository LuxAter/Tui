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
  // tui::Print("\u01f6");
  // tui::Refresh();
  // tui::GetCh();
  // tui::EnabledMouse(tui::MOUSE_MOVEMENT);
  tui::Window win = tui::stdscr.CreateWindow();
  win.Box();
  // win.EnableBorder();
  win.Refresh();
  tui::Refresh();
  bool looping = true;
  while (looping == true) {
    tui::Event ev = tui::WaitEvent();
    if (ev.type == tui::KEYBOARD_EVENT) {
      if (ev.keyboard.key == tui::KEY_Q) {
        looping = false;
      } else if (ev.keyboard.key == tui::KEY_C) {
        win.Clear();
      } else if (ev.keyboard.key == tui::KEY_H) {
        win.Resize(win.GetWidth() - 5, win.GetHeight());
      } else if (ev.keyboard.key == tui::KEY_L) {
        win.Resize(win.GetWidth() + 5, win.GetHeight());
      } else if (ev.keyboard.key == tui::KEY_J) {
        win.Resize(win.GetWidth(), win.GetHeight() - 5);
      } else if (ev.keyboard.key == tui::KEY_K) {
        win.Resize(win.GetWidth(), win.GetHeight() + 5);
      }else if(ev.keyboard.key == tui::KEY_D){
        win.Position(win.GetX() + 5, win.GetY());
      }else if(ev.keyboard.key == tui::KEY_A){
        win.Position(win.GetX() - 5, win.GetY());
      }else if(ev.keyboard.key == tui::KEY_W){
        win.Position(win.GetX(), win.GetY() - 5);
      }else if(ev.keyboard.key == tui::KEY_S){
        win.Position(win.GetX(), win.GetY() + 5);
      }
    }
    win.Refresh();
    tui::Refresh();
  }
  tui::DisableMouse(tui::MOUSE_MOVEMENT);
  tui::Cursor();
  tui::Echo();
  tui::NoRaw();
  tui::TermTui();
  return 0;
}
