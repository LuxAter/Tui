#include "input/input.hpp"

#include <cstdio>
#include <iostream>

#include "input/keys.hpp"

unsigned int tui::getch() {
  unsigned int key_code = 0;
  int key = std::cin.get();
  // char key = std::getchar();
  if (key == '\033') {
    std::cin.get();
    key = std::cin.get();
    key_code = GetEscapeKey(key);
  } else {
    key_code = key;
  }
  return key_code;
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
  }
  return key_code;
}
