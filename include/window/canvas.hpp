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

#ifndef TUI_CANVAS_HPP_
#define TUI_CANVAS_HPP_

#include <array>
#include <string>
#include <vector>

#include "window.hpp"

namespace tui {

  enum PixelFormat {
    TWO_BLOCK,
    BLOCK,
    VERTICAL_BLOCK,
    HORIZONTAL_BLOCK,
    QUARTER_BLOCK,
    BRAIL
  };

  class Canvas : public tui::Window {
   public:
    Canvas();
    Canvas(int w, int h);
    Canvas(int x, int y, int w, int h);
    Canvas(const Canvas& rhs);

    void SetPixel(PixelFormat format);

    void DrawPoint(unsigned int x, unsigned int y);

    unsigned int MaxX();
    unsigned int MaxY();

   private:
    void ResizeGrid();
    void DrawPixels();

    unsigned int pixel_format_ = BLOCK;
    std::vector<std::vector<bool>> pixel_data;
    std::array<unsigned int, 2> size_ = {{0, 0}};
  };
}  // namespace tui

#endif  // TUI_CANVAS_HPP_
