#include "input/input.hpp"

#include <stdio.h>
#include <sys/ioctl.h>
#include <time.h>
#include <iostream>

#include "input/keys.hpp"

namespace tui {
  int timeout_ = -1;
}  // namespace tui

unsigned int tui::getch() {
  unsigned int key_code = 0;
  if (kbhit() == true) {
    int key = std::cin.get();
    if (key == '\033') {
      std::cin.get();
      key = std::cin.get();
      key_code = GetEscapeKey(key);
    } else {
      key_code = key;
    }
  }
  return key_code;
}

bool tui::kbhit(int timeout_ms) {
  static const int STDIN = 0;
  int bytesWaiting;
  if (timeout_ms < 0) {
    bool wait = true;
    while (wait == true) {
      ioctl(STDIN, FIONREAD, &bytesWaiting);
      wait = !bytesWaiting;
    }
    return true;
  } else {
    clock_t start = clock(),
            end = start + (timeout_ms * CLOCKS_PER_SEC / 10000);
    bool wait = true;
    while (start < end && wait == true) {
      start = clock();
      ioctl(STDIN, FIONREAD, &bytesWaiting);
      wait = !bytesWaiting;
    }
    if (wait == false) {
      return true;
    } else {
      return false;
    }
  }
}

unsigned int tui::GetEscapeKey(char key) {
  unsigned int key_code = 0;
  switch (key) {
    case 'A':
      key_code = KEY_UP;
      break;
    case 'B':
      key_code = KEY_DOWN;
      break;
    case 'C':
      key_code = KEY_RIGHT;
      break;
    case 'D':
      key_code = KEY_LEFT;
      break;
    case 51:
      key_code = KEY_DELETE;
      break;
    default:
      std::cout << "Unknown key code: " << (int)key << std::endl;
  }
  return key_code;
}

void tui::SetTimeout(int timeout) { timeout_ = timeout; }
