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

/**
 * @file window.hpp
 * @brief Core window structure
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2017-12-01
 */
#ifndef TUI_WINDOW_HPP
#define TUI_WINDOW_HPP

#include <array>
#include <string>
#include <vector>

#include "../output/attr.hpp"
#include "../output/buffer.hpp"
// #include "canvas.hpp"

namespace tui {
  class Canvas;
  /**
   * @brief Core window object.
   *
   * The window object is how all display is sent to the screen. Windows are
   * structured to be a tree, where every window is a sub window. The only
   * window that is not a sub window is stdscr, which is the base window, which
   * everything is printed to before it is printed to the display.
   */
  class Window {
   public:
     /**
      * @brief Default constructor.
      * 
      * Generates base window clone of parent window position and dimensions.
      */
    Window();
    /**
     * @brief Constructor.
     * 
     * Generates window at position of parent window, and gven dimensions.
     *
     * @param w Width of window.
     * @param h Height of window.
     */
    Window(int w, int h);
    /**
     * @brief Constructor.
     * 
     * Generates window offset from parent window position by given values, and of given dimensions.
     *
     * @param x X position of window.
     * @param y Y position of window.
     * @param w Width of window.
     * @param h Height of window.
     */
    Window(int x, int y, int w, int h);
    /**
     * @brief Copy constructor.
     *
     * @param copy Window to copy.
     */
    Window(const Window& copy);
    /**
     * @brief Default destructor.
     * 
     * Destroys window, and window buffers.
     */
    ~Window();

    /**
     * @brief Swaps internal window buffers.
     */
    void Show();
    /**
     * @brief Swaps internal window buffers.
     */
    void Refresh();

    /**
     * @brief Resizes window to new dimensions.
     *
     * @todo Write resize function chain.
     * 
     * @param w New width of the window.
     * @param h New height of the window.
     */
    void Resize(int w, int h);
    /**
     * @brief Repositions the window relative to parent window.
     *
     * @todo Write position function chain.
     * 
     * @param x New x position of the window.
     * @param y New y position of the window.
     */
    void Position(int y, int x);

    /**
     * @brief Clears the windows write buffer.
     */
    void Clear();

    /**
     * @brief Prints wide stirng to window at current cursor position.
     *
     * @param str Fmt string to write.
     * @param ... Additional arguments.
     */
    void Print(std::wstring str, ...);
    /**
     * @brief Moves window cursor position and prints wide string to window.
     *
     * @param x X position of cursor.
     * @param y Y position of cursor,
     * @param str Fmt string to write.
     * @param ... Additional arguments.
     */
    void mvPrint(unsigned x, unsigned y, std::wstring str, ...);
    /**
     * @brief Prints wide string to window at current cursor position.
     *
     * @param str Fmt string to write
     * @param args Additional arguments.
     */
    void Print(std::wstring str, va_list args);
    /**
     * @brief Moves window cursor position and prints wide string to window.
     *
     * @param x X position of cursor.
     * @param y Y position of cursor.
     * @param str Fmt stirng to write.
     * @param args Additional arguments.
     */
    void mvPrint(unsigned x, unsigned y, std::wstring str, va_list args);
    /**
     * @brief Prints string to window at current cursor position.
     *
     * @param str Fmt string to write.
     * @param ... Additional arguments.
     */
    void Print(std::string str, ...);
    /**
     * @brief Moves window cursor position and prints string to window.
     *
     * @param x X position of cursor.
     * @param y Y position of cursor.
     * @param str Fmt string to write.
     * @param ... Additional arguments.
     */
    void mvPrint(unsigned x, unsigned y, std::string str, ...);
    /**
     * @brief Prints string to window at current cursor position.
     *
     * @param str Fmt string to write.
     * @param args Additional arguments.
     */
    void Print(std::string str, va_list args);
    /**
     * @brief Moves window cursor position and prints string to window.
     *
     * @param x X position of cursor.
     * @param y Y position of cursor.
     * @param str Fmt string to write.
     * @param args Additional arguments.
     */
    void mvPrint(unsigned x, unsigned y, std::string str, va_list args);
    /**
     * @brief Prints single character at current cursor position.
     *
     * @param ch Character to write.
     */
    void Print(unsigned int ch);
    /**
     * @brief Moves window cursor position and prints single chracter.
     *
     * @param x X positon of cursor.
     * @param y Y position of cursor.
     * @param ch Character to write.
     */
    void mvPrint(unsigned int x, unsigned int y, unsigned int ch);

    /**
     * @brief Moves cursor to given position.
     *
     * @param x X position of cursor.
     * @param y Y position of cursor.
     */
    void MoveCursor(unsigned x, unsigned y);

    /**
     * @brief Fills window with given character.
     *
     * @param ch Character to fill window with.
     */
    void Fill(unsigned int ch);
    /**
     * @brief Draws line of given character.
     *
     * @param x0 X position of start point.
     * @param y0 Y position of start point.
     * @param x1 X position of end point.
     * @param y1 Y position of end point.
     * @param ch Character to write.
     */
    void Line(unsigned x0, unsigned y0, unsigned x1, unsigned y1,
              unsigned int ch);

    /**
     * @brief Draws a box with unicode box drawing around the window.
     */
    void Box();
    /**
     * @brief Draws a box around the window.
     *
     * @param c Character to use for corners.
     * @param v Character to use for vertical lines.
     * @param h Character to use for horizontal lines.
     */
    void Box(unsigned c, unsigned v, unsigned h);
    /**
     * @brief Draws a box around the window.
     *
     * @param ul Character for upper left corner.
     * @param u Character for upper edge.
     * @param ur Character for upper right corner.
     * @param l Character for left edge.
     * @param r Character for right edge.
     * @param bl Character for bottom left corner.
     * @param b Charactere for bottom edge.
     * @param br Character for bottom right corner.
     */
    void Box(unsigned int ul, unsigned int u, unsigned int ur, unsigned int l,
             unsigned int r, unsigned int bl, unsigned int b, unsigned int br);
    void EraseBox();
    /**
     * @brief Enables buffer border protection.
     * 
     * @sa Buffer::border_
     */
    void EnableBorder();
    /**
     * @brief Disables buffer border protection.
     * 
     * @sa Buffer::border_
     */
    void DisableBorder();
    /**
     * @brief Enables buffer scroll.
     * 
     * @sa Buffer::scroll_
     */
    void EnableScroll();
    /**
     * @brief Disables buffer scroll.
     * 
     * @sa Buffer::scroll_
     */
    void DisableScroll();

    /**
     * @brief Enables text attribute
     *
     * @param attr Attribute to enable.
     * 
     * @sa Attr
     */
    void AttrOn(Attr attr);
    /**
     * @brief Disables text attribute.
     * 
     * Attribute must first be enabled for it to be disabled.
     *
     * @param attr Attritube to disable.
     * 
     * @sa Attr
     */
    void AttrOff(Attr attr);
    /**
     * @brief Sets the foreground and backaground color of text.
     *
     * @param color Pair of foreground and background color representations.
     * 
     * @sa ColorPair ColorValue Color
     */
    void SetColor(ColorPair color);
    /**
     * @brief Sets foreground color of text.
     *
     * @param color Color representation.
     * 
     * @sa Color
     */
    void SetColor(Color color);
    /**
     * @brief Sets foreground color of text.
     *
     * @param color Color representation.
     * 
     * @sa ColorValue
     */
    void SetColor(ColorValue color);
    /**
     * @brief Sets foreground color of text.
     *
     * @param color 256 bit color representation
     */
    void SetColor(unsigned char color);
    /**
     * @brief Sets foreground color of text.
     *
     * @param r 256 bit red value.
     * @param g 256 bit green value.
     * @param b 256 bit blue value.
     */
    void SetColor(unsigned char r, unsigned char g, unsigned char b);
    /**
     * @brief Sets background color of text.
     *
     * @param color Color representation.
     * 
     * @sa Color
     */
    void SetBackground(Color color);
    /**
     * @brief Sets background color of text.
     *
     * @param color Color representation.
     * 
     * @sa ColorValue
     */
    void SetBackground(ColorValue color);
    /**
     * @brief Sets background color of text.
     *
     * @param color 256 bit color representation
     */
    void SetBackground(unsigned char color);
    /**
     * @brief Sets background color of text.
     *
     * @param r 256 bit red value.
     * @param g 256 bit green value.
     * @param b 256 bit blue value.
     */
    void SetBackground(unsigned char r, unsigned char g, unsigned char b);

    unsigned int GetWidth();
    unsigned int GetHeight();
    unsigned int GetX();
    unsigned int GetY();
    bool GetBorderEnabled();

    /**
     * @brief Gets pointer to windows internal buffer.
     *
     * @return Pointer to windows buffer.
     */
    tui::Buffer* GetBufferPointer();

    /**
     * @brief Generates a child window.
     * 
     * Child window is of the same dimensions and position as parent window.
     *
     * @return Child window.
     */
    tui::Window CreateWindow();
    /**
     * @brief Generates a child window.
     *
     * Child window is of given dimensions, and at the same position as parent window.
     * 
     * @param w Width of child window.
     * @param h Height of child window.
     *
     * @return Child window.
     */
    tui::Window CreateWindow(int w, int h);
    /**
     * @brief Generates a child window.
     * 
     * Child window is of given dimenstions, and at given position.
     *
     * @param x X position of child window.
     * @param y Y position of child window.
     * @param w Width of child window.
     * @param h Height of child window.
     *
     * @return Child window.
     */
    tui::Window CreateWindow(int x, int y, int w, int h);
    /**
     * @brief Generates a child canvas.
     * 
     * Child canvas is of the same dimensions and position as parent canvas.
     *
     * @return Child canvas.
     */
    tui::Canvas CreateCanvas();
    /**
     * @brief Generates a child canvas.
     *
     * Child canvas is of given dimensions, and at the same position as parent canvas.
     * 
     * @param w Width of child canvas.
     * @param h Height of child canvas.
     *
     * @return Child canvas.
     */
    tui::Canvas CreateCanvas(int w, int h);
    /**
     * @brief Generates a child canvas.
     * 
     * Child canvas is of given dimenstions, and at given position.
     *
     * @param x X position of child canvas.
     * @param y Y position of child canvas.
     * @param w Width of child canvas.
     * @param h Height of child canvas.
     *
     * @return Child canvas.
     */
    tui::Canvas CreateCanvas(int x, int y, int w, int h);

   protected:
    /**
     * @brief Declars if the buffer border protection is active.
     */
    bool border_active_ = false;
    /**
     * @brief Current (x,y) location of the window cursor.
     */
    std::array<unsigned, 2> cursor = {{0, 0}};
    /**
     * @brief Current position and dimensions of the window.
     * 
     * (Width, Height, X, Y)
     */
    std::array<int, 4> window_pos_ = {{0, 0, 0, 0}};
    /**
     * @brief Internal window buffer.
     * 
     * @sa Buffer
     */
    tui::Buffer window_buffer_;

    /**
     * @brief Set of active text attributes escape codes.
     */
    std::vector<std::string> active_attrs_;
    /**
     * @brief Active foreground color escape code.
     */
    std::string active_color_;
    /**
     * @brief Active background color escape code.
     */
    std::string active_background_color_;
    std::array<unsigned, 8> box_chars_ = {{0, 0, 0, 0, 0, 0, 0, 0}};
  };
}  // namespace tui

#endif /* ifndef TUI_WINDOW_HPP */
