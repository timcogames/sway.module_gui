#ifndef SWAY_GUI_PAINTER_HPP
#define SWAY_GUI_PAINTER_HPP

#include <sway/gui/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gui)

class Painter {
public:
  /**
   * @brief Конструктор класса.
   * Выполняет инициализацию нового экземпляра класса.
   *
   */
  Painter();

  /**
   * @brief Деструктор класса.
   * Освобождает захваченные ресурсы.
   *
   */
  ~Painter();

private:
};

NAMESPACE_END(gui)
NAMESPACE_END(sway)

#endif  // SWAY_GUI_PAINTER_HPP
