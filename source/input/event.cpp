#include "input/event.hpp"

#include <queue>

#include <sys/ioctl.h>
#include <time.h>
#include <iostream>

#include <stdio.h>
#include <stropts.h>
#include <unistd.h>
#include <string>

#include "input/event_class.hpp"

static std::queue<unsigned int> character_stack_;
static std::queue<tui::Event> event_queue_;

namespace tui {
  int timeout_ = -1;
}  // namespace tui

tui::Event tui::PopEvent() {
  tui::Event event;
  if (event_queue_.empty() == false) {
    event = event_queue_.front();
    event_queue_.pop();
  }
  return event;
}

tui::Event tui::GetEvent() {
  tui::Event event;
  PollEvents(0);
  return PopEvent();
}

tui::Event::MouseEvent tui::GetMouseEvent() {
  tui::Event event;
  PollEvents(0);
  while (event_queue_.empty() == false && event.type != MOUSE_EVENT) {
    tui::Event ev = PopEvent();
    if (ev.type == MOUSE_EVENT) {
      event = ev;
    }
  }
  return event.mouse;
}
tui::Event::KeyboardEvent tui::GetKeyboardEvent() {
  tui::Event event;
  PollEvents(0);
  while (event_queue_.empty() == false && event.type != KEYBOARD_EVENT) {
    tui::Event ev = PopEvent();
    if (ev.type == KEYBOARD_EVENT) {
      event = ev;
    }
  }
  return event.keyboard;
}

tui::Event tui::WaitEvent(int timeout) {
  if (event_queue_.empty() == false) {
    return PopEvent();
  } else {
    PollEvents(timeout);
    return PopEvent();
  }
}

tui::Event::MouseEvent tui::WaitMouseEvent(int timeout) {
  tui::Event event;
  if(event_queue_.empty() == false){
    tui::Event ev = PopEvent();
    while(ev.type != MOUSE_EVENT && event_queue_.empty() == false){
      ev = PopEvent();
    }
    if(ev.type == MOUSE_EVENT){
      event = ev;
      return event.mouse;
    }
  }
  if (timeout >= 0) {
    clock_t start = clock(), end = start + (timeout * CLOCKS_PER_SEC / 10000);
    while (event.type != MOUSE_EVENT && start < end) {
      PollEvents(timeout);
      while (event_queue_.empty() == false && event.type != MOUSE_EVENT) {
        tui::Event ev = PopEvent();
        if (ev.type == MOUSE_EVENT) {
          event = ev;
        }
      }
      start = clock();
    }
  } else {
    while (event.type != MOUSE_EVENT) {
      PollEvents(timeout);
      while (event_queue_.empty() == false && event.type != MOUSE_EVENT) {
        tui::Event ev = PopEvent();
        if (ev.type == MOUSE_EVENT) {
          event = ev;
        }
      }
    }
  }
  return event.mouse;
}
tui::Event::KeyboardEvent tui::WaitKeyboardEvent(int timeout) {
  tui::Event event;
  if(event_queue_.empty() == false){
    tui::Event ev = PopEvent();
    while(ev.type != KEYBOARD_EVENT && event_queue_.empty() == false){
      ev = PopEvent();
    }
    if(ev.type == KEYBOARD_EVENT){
      event = ev;
      return event.keyboard;
    }
  }
  if (timeout >= 0) {
    clock_t start = clock(), end = start + (timeout * CLOCKS_PER_SEC / 10000);
    while (event.type != KEYBOARD_EVENT && start < end) {
      PollEvents(timeout);
      while (event_queue_.empty() == false && event.type != KEYBOARD_EVENT) {
        tui::Event ev = PopEvent();
        if (ev.type == KEYBOARD_EVENT) {
          event = ev;
        }
      }
      start = clock();
    }
  } else {
    while (event.type != KEYBOARD_EVENT) {
      PollEvents(timeout);
      while (event_queue_.empty() == false && event.type != KEYBOARD_EVENT) {
        tui::Event ev = PopEvent();
        if (ev.type == KEYBOARD_EVENT) {
          event = ev;
        }
      }
    }
  }
  return event.keyboard;
}

unsigned int tui::GetCh(int timeout) { return WaitKeyboardEvent(timeout).key; }

void tui::PollEvents(int timeout_ms) {
  int count = PendingEvents(timeout_ms);
  for (int i = 0; i < count; i++) {
    character_stack_.push(std::cin.get());
  }
  ReadEvent();
}

unsigned int tui::PendingEvents(int timeout_ms) {
  int bytes = 0, result = 0;
  if (timeout_ms < 0) {
    bool wait = true;
    while (wait == true) {
      usleep(100);
      result = ioctl(0, FIONREAD, &bytes);
      wait = !bytes;
    }
  } else if (timeout_ms == 0) {
    result = ioctl(0, FIONREAD, &bytes);
  } else if (timeout_ms <= 1000) {
    clock_t start = clock(),
            end = start + (timeout_ms * CLOCKS_PER_SEC / 10000);
    bool wait = true;
    while (start < end && wait == true) {
      start = clock();
      result = ioctl(0, FIONREAD, &bytes);
      wait = !bytes;
    }
  } else {
    clock_t start = clock(),
            end = start + (timeout_ms * CLOCKS_PER_SEC / 10000);
    bool wait = true;
    while (start < end && wait == true) {
      start = clock();
      usleep(1000);
      result = ioctl(0, FIONREAD, &bytes);
      wait = !bytes;
    }
  }
  if (result != 0 || bytes <= 0) {
    return 0;
  }
  return static_cast<unsigned int>(bytes);
}

void tui::ReadEvent() {
  while (character_stack_.size() != 0) {
    unsigned int ch = character_stack_.front();
    tui::Event event;
    character_stack_.pop();
    if (ch != 27) {
      event.type = KEYBOARD_EVENT;
      event.keyboard.key = ch;
    } else {
      if (character_stack_.size() == 0) {
        event.type = KEYBOARD_EVENT;
        event.keyboard.key = ch;
      } else {
        ch = PopCharacter();
        if (ch == 91) {
          if (character_stack_.empty() == false &&
              character_stack_.front() == 60) {
            character_stack_.pop();
            event.type = MOUSE_EVENT;
            event.mouse = ReadMouseEvent();

          } else {
            event.type = KEYBOARD_EVENT;
            event.keyboard = ReadKeyBoardEvent(true);
          }

        } else if (ch == 79) {
          event.type = KEYBOARD_EVENT;
          event.keyboard = ReadKeyBoardEvent(false);
        }
      }
    }
    event_queue_.push(event);
  }
}

tui::Event::MouseEvent tui::ReadMouseEvent() {
  tui::Event::MouseEvent ms_event;
  unsigned int mb = 0, col = 0, row = 0;
  unsigned int ch = PopCharacter();
  while (ch != 59) {
    mb = (mb * 10) + (ch - 48);
    ch = PopCharacter();
  }
  ch = PopCharacter();
  while (ch != 59) {
    col = (col * 10) + (ch - 48);
    ch = PopCharacter();
  }
  ch = PopCharacter();
  while (ch != 77 && ch != 109) {
    row = (row * 10) + (ch - 48);
    ch = PopCharacter();
  }
  ms_event.x = col;
  ms_event.y = row;
  if (mb == 0 && ch == 77) {
    ms_event.button = MOUSE_BUTTON_LEFT;
    ms_event.type = MOUSE_BUTTON_DOWN;
  } else if (mb == 1 && ch == 77) {
    ms_event.button = MOUSE_BUTTON_RIGHT;
    ms_event.type = MOUSE_BUTTON_DOWN;
  } else if (mb == 2 && ch == 77) {
    ms_event.button = MOUSE_BUTTON_RIGHT;
    ms_event.type = MOUSE_BUTTON_DOWN;
  } else if (mb == 0 && ch == 109) {
    ms_event.button = MOUSE_BUTTON_LEFT;
    ms_event.type = MOUSE_BUTTON_UP;
  } else if (mb == 1 && ch == 109) {
    ms_event.button = MOUSE_BUTTON_RIGHT;
    ms_event.type = MOUSE_BUTTON_UP;
  } else if (mb == 2 && ch == 109) {
    ms_event.button = MOUSE_BUTTON_RIGHT;
    ms_event.type = MOUSE_BUTTON_UP;
  } else if (mb == 64) {
    ms_event.type = MOUSE_SCROLL_UP;
  } else if (mb == 65) {
    ms_event.type = MOUSE_SCROLL_DOWN;
  } else if (mb == 35) {
    ms_event.type = MOUSE_MOVE;
  } else if (mb == 32) {
    ms_event.type = MOUSE_MOVE;
    ms_event.button = MOUSE_BUTTON_LEFT;
  } else if (mb == 34) {
    ms_event.type = MOUSE_MOVE;
    ms_event.button = MOUSE_BUTTON_RIGHT;
  } else if (mb == 36) {
    ms_event.type = MOUSE_MOVE;
    ms_event.button = MOUSE_BUTTON_MIDDLE;
  }
  return ms_event;
}

tui::Event::KeyboardEvent tui::ReadKeyBoardEvent(bool start) {
  tui::Event::KeyboardEvent kb_event;
  if (start == false) {
    switch (PopCharacter()) {
      case 80:
        kb_event.key = KEY_F1;
        break;
      case 81:
        kb_event.key = KEY_F2;
        break;
      case 82:
        kb_event.key = KEY_F3;
        break;
      case 83:
        kb_event.key = KEY_F4;
        break;
      default:
        kb_event.key = KEY_ERR;
        break;
    }
  } else if (start == true) {
    switch (PopCharacter()) {
      case 49:
        switch (PopCharacter()) {
          case 53:
            kb_event.key = KEY_F5;
            PopCharacter();
            break;
          case 55:
            kb_event.key = KEY_F6;
            PopCharacter();
            break;
          case 56:
            kb_event.key = KEY_F7;
            PopCharacter();
            break;
          case 57:
            kb_event.key = KEY_F8;
            PopCharacter();
            break;
          default:
            kb_event.key = KEY_ERR;
            break;
        }
        break;
      case 50:
        switch (PopCharacter()) {
          case 48:
            kb_event.key = KEY_F9;
            PopCharacter();
            break;
          case 49:
            kb_event.key = KEY_F10;
            PopCharacter();
            break;
          case 52:
            kb_event.key = KEY_F12;
            PopCharacter();
            break;
          default:
            kb_event.key = KEY_ERR;
            break;
        }
        break;
      case 51:
        kb_event.key = KEY_DELETE;
        PopCharacter();
        break;
      case 65:
        kb_event.key = KEY_UP;
        break;
      case 66:
        kb_event.key = KEY_DOWN;
        break;
      case 67:
        kb_event.key = KEY_RIGHT;
        break;
      case 68:
        kb_event.key = KEY_LEFT;
        break;
      default:
        kb_event.key = KEY_ERR;
        break;
    }
  } else {
    kb_event.key = KEY_ERR;
  }
  return kb_event;
}

unsigned int tui::PopCharacter() {
  unsigned int ch = 0;
  if (character_stack_.empty() == false) {
    ch = character_stack_.front();
    character_stack_.pop();
  }
  return ch;
}

void tui::SetTimeout(int timeout) { timeout_ = timeout; }
int tui::GetTimeout() { return timeout_; }
