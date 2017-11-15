/* Copyright (C)
 * 2017 - Arden Rasmussen
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef TUI_INIT_HPP
#define TUI_INIT_HPP

#include <string>

#include "window/window.hpp"

namespace tui {

  /**
   * @brief Type color access enumeration
   *
   * Enum that is used to define the different color access that the current
   * terminal supports.
   */
  enum ColorSets { NO_COLOR = 0, COLOR_16 = 1, COLOR_256 = 2, TRUE_COLOR = 3 };
  enum InitFlags {
    ECHO = 0,
    NO_ECHO = 1,
    RAW = 2,
    NO_RAW = 3,
    CURSOR = 4,
    NO_CURSOR = 5
  };

  extern tui::Window stdscr;
  extern unsigned int _color_access;
  bool InitTui();
  bool TermTui();
  int HasColor();

  void Clear();

  void Refresh();

  void Print(std::wstring str, ...);
  void Print(std::string str, ...);
  void mvPrint(unsigned x, unsigned y, std::wstring str, ...);
  void mvPrint(unsigned x, unsigned y, std::string str, ...);

  std::wstring GetWString(std::string str);

  tui::Window CreateWindow();
  tui::Window CreateWindow(int w, int h);
  tui::Window CreateWindow(int x, int y, int w, int h);

}  // namespace tui

#endif /* ifndef TUI_INIT_HPP */
