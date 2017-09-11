#ifndef TUI_WINDOW_HPP
#define TUI_WINDOW_HPP

namespace tui {
  class Window {
   public:
   private:
    unsigned int window_index_;
    int window_pos_[4] = {0, 0, 0, 0};
  };
}  // namespace tui

#endif /* ifndef TUI_WINDOW_HPP */
