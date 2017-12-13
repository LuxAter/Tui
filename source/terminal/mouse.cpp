#include "terminal/mouse.hpp"

#include <stdio.h>

void tui::EnabledMouse(MouseReporting report_method){
  if (report_method == MOUSE_REPORTING){
    printf("\033[?1000h");
    printf("\033[?1006h");
  }else if(report_method == MOUSE_HIGHLIGHT){
    printf("\033[?1001h");
    printf("\033[?1006h");
  }else if(report_method == MOUSE_BUTTON_MOVEMENT){
    printf("\033[?1002h");
    printf("\033[?1006h");
  }else if(report_method == MOUSE_MOVEMENT){
    printf("\033[?1003h");
    printf("\033[?1006h");
  }
}

void tui::DisableMouse(MouseReporting report_method){
  if(report_method == MOUSE_REPORTING){
    printf("\033[?1006l");
    printf("\033[?1000l");
  }else if(report_method == MOUSE_HIGHLIGHT){
    printf("\033[?1006l");
    printf("\033[?1001l");
  }else if(report_method == MOUSE_BUTTON_MOVEMENT){
    printf("\033[?1006l");
    printf("\033[?1002l");
  }else if(report_method == MOUSE_MOVEMENT){
    printf("\033[?1006l");
    printf("\033[?1003l");
  }
}
