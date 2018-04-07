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
 * @file buffer.hpp
 * @brief Double buffer object.
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2017-12-02
 */
#ifndef TUI_OUTPUT_BUFFER_HPP
#define TUI_OUTPUT_BUFFER_HPP

#include <array>
#include <set>
#include <string>
#include <vector>

namespace tui {
/**
 * @brief Display buffer behind every window.
 *
 * The buffer class, should be interacted with as little as posible, instead
 * utilize the window class, as each window class has a buffer class.
 *
 * The buffer class contains a write and display buffer, and controls
 * writing
 * to its output stream/buffer.
 */
class Buffer {
 public:
  /**
   * @brief Abstraction of a char.
   *
   * The Char class abstractifies the char characters, and allows
   * initilization from either a char, unsigned int, or wide char. It also
   * stores all attribues applied to the individual characters.
   */
  class Char {
   public:
    /**
     * @brief Default constructor.
     */
    Char();
    /**
     * @brief Constructor.
     *
     * @param _ch unsigned integer representing character.
     */
    Char(unsigned int _ch);
    /**
     * @brief Constructor.
     *
     * @param _ch char representing character.
     */
    Char(char _ch);
    /**
     * @brief Constructor.
     *
     * @param _ch wide char reprsenting character.
     */
    Char(wchar_t _ch);
    /**
     * @brief Unsigned integer representation of character.
     */
    unsigned int ch;
    /**
     * @brief Set of attribute escape codes to be applied to character.
     */
    std::vector<std::string> attrs;
    /**
     * @brief Equals operand.
     *
     * Determins if the character and attribues are the same of two
     * different
     * characters.
     *
     * @param rhs character to compare against.
     *
     * @return `true` if the characters are the same, `false` otherwise.
     */
    bool operator==(const Char& rhs);
    /**
     * @brief Not equals operand.
     *
     * Determins if the character and attributes are different of two
     * different characters.
     *
     * @param rhs Character to compare against.
     *
     * @return `false` if the characters are the same, `true` otherwise.
     */
    bool operator!=(const Char& rhs);
    /**
     * @brief Print operator.
     *
     * @param out out stream to print character to.
     *
     * @return out stream containing character.
     */
    std::ostream& operator<<(std::ostream& out);
  };
  /**
   * @brief Default constructor.
   */
  Buffer();
  /**
   * @brief Constructor.
   *
   * Construct a double buffer object with specified width and height.
   *
   * @param w Width of buffer.
   * @param h Height of buffer.
   */
  Buffer(unsigned int w, unsigned int h);

  /**
   * @brief Clears write buffer.
   */
  void Clear();
  /**
   * @brief Swaps the buffers.
   *
   * Swaps the write and display buffer, redrawing the minimum number of
   * characters to update the screen.o
   *
   * @todo Add fast refresh, higher memory alternative.
   */
  void Swap();
  /**
   * @brief Swaps the buffers.
   */
  void Refresh();

  // TODO(2017-11-27, Arden): Write Resize function chain
  /**
   * @brief Resizes the buffers.
   *
   * Use this to enable window resizing capablities.
   *
   * @todo Write resize function chaing
   *
   * @param w Width of the new buffer.
   * @param h Height of the new buffer.
   */
  void Resize(unsigned int w, unsigned int h);

  /**
   * @brief Sets the buffer pair as the write buffers.
   *
   * Setting this to `true`, causes the buffer to write directly to
   * `stdout`, instead of a underlying buffer object.
   *
   * @param setting Boolean to set value to.
   */
  void SetDisplayBuffer(bool setting);
  /**
   * @brief Enables fast display mode
   *
   * For each display buffer, all characters in the write buffer are checked by
   * default. But if `fast_mode` is set to `true`, then the altered characters
   * are saved, and only those characters are updated when buffers are swaped.
   * This will cause the program to execute marginaly faster, and use marginaly
   * more memory.
   *
   * @param setting Boolean to set `fast_mode` to.
   */
  void SetFastMode(bool setting);
  /**
   * @brief Sets offset of display buffer.
   *
   * The offset is a static value that the output of the display buffer
   * shifts its output to, when writing.
   *
   * @param x X offset value.
   * @param y Y offset value.
   */
  void OffSet(unsigned int x, unsigned int y);
  /**
   * @brief Sets target parent buffer.
   *
   * This sets the parent buffer, that when this buffer is swaped, the
   * display buffer is written to the buffer target, unless display_ is set
   * to `true`.
   *
   * @param _target Pointer to target buffer object.
   */
  void SetTarget(tui::Buffer* _target);

  /**
   * @brief Write wide string to buffer.
   *
   * Writes a wide string to the buffer, with set attributes, and colors.
   * The function begins writing at the provided position, and if a string
   * reaches the end of the buffer, it is wrapped to the next line of the
   * buffer. If the end of the buffer is reached, the buffer either scrolls,
   * or clears and begins that the begining again.

   * @param x X position to start the text.
   * @param y Y position to start the text.
   * @param str String to write to the buffer.
   * @param attrs Set of attributes to apply to the text.
   * @param color Foreground color to apply to the text.
   * @param background_color Background color to apply to the text.
   */
  void Write(unsigned int& x, unsigned int& y, std::wstring str,
             std::vector<std::string> attrs, std::string color,
             std::string background_color);
  /**
   * @brief Write single character to the buffer.
   *
   * Writes a single character to the buffer, with set attributes, and colors.
   *
   * @param x X position of the character.
   * @param y Y position of the character.
   * @param ch Character to write.
   * @param attrs Set of attributes to apply to the text.
   * @param color Foreground color to apply to the text.
   * @param background_color Background color to apply to the text.
   */
  void Write(unsigned int& x, unsigned int& y, unsigned int ch,
             std::vector<std::string> attrs, std::string color,
             std::string background_color);
  /**
   * @brief Write character object to the buffer.
   *
   * Writes a single characcter object to the buffer.
   *
   * @param x X position of the character.
   * @param y Y position of the character.
   * @param ch Character to write.
   *
   * @sa Char
   */
  void Write(unsigned int x, unsigned int y, Char ch);
  /**
   * @brief Writes to the sub object buffer.
   *
   * Writes a single character to the sub object buffer. The sub object buffer
   * is used for child buffers to write to and it holds priority over the
   * default write uffer.
   *
   * @param x X position of the character.
   * @param y Y position of the character.
   * @param ch Character to write.
   *
   * @sa Char
   */
  void WriteSub(unsigned int x, unsigned int y, Char ch);

  /**
   * @brief Fills the write buffer with suplied character.
   *
   * @param ch Character to fill buffer with.
   *
   * @sa Char
   */
  void Fill(Char ch);
  /**
   * @brief Fills a line of characters
   *
   * @param a_x Starting x position of the line.
   * @param a_y Starting y posiiton of the line.
   * @param b_x Ending x position of the line.
   * @param b_y Ending y position of the line.
   * @param ch Charactger to write along the line.
   *
   * @sa Char
   */
  void FillLine(unsigned int a_x, unsigned int a_y, unsigned int b_x,
                unsigned int b_y, Char ch);

  std::array<unsigned, 2> GetBufferSize();
  /**
   * @brief Flag if a border exists.
   *
   * This flag causes te buffer to prevent the outer most characters from
   * being writen to. Thus preserving any characters being used as a border.
   */
  bool border_ = false;
  /**
   * @brief Flag if buffer should scroll.
   *
   * This flags controls the end of buffer behaviour, if it is `true`, the the
   * buffer will shift all previous lines up a single line, and write the new
   * line to the bottom most row. If it is `false`, then the buffer is
   * cleared, and the new line is written to the top most row.
   */
  bool scroll_ = true;

 private:
  void WriteChar(Char ch, int x, int y);
  void RollBuffer();
  std::string GetChar(unsigned int ch);
  void StorePosition(unsigned x, unsigned y);

  bool fast_mode = true;
  tui::Buffer* target = nullptr;
  std::vector<std::vector<Char>> display_buffer, write_buffer, sub_buffer;
  std::set<std::array<unsigned, 2>> updated_data_;
  std::array<unsigned int, 2> size = {{0, 0}};
  std::array<unsigned int, 2> offset = {{0, 0}};
  bool display_ = false;
};

}  // namespace tui

#endif /* ifndef TUI_OUTPUT_BUFFER_HPP */
