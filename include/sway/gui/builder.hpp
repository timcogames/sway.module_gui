#ifndef SWAY_GUI_BUILDER_HPP
#define SWAY_GUI_BUILDER_HPP

#include <sway/gui/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gui)

class Builder : public core::foundation::Object {
  DECLARE_OBJECT(Builder, core::foundation::Object)

public:
  /**
   * @brief Конструктор класса.
   * Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] context Контекст подсистемы.
   *
   */
  Builder(core::foundation::Context *context);

  /**
   * @brief Деструктор класса.
   * Освобождает захваченные ресурсы.
   *
   */
  virtual ~Builder();

private:
};

NAMESPACE_END(gui)
NAMESPACE_END(sway)

#endif  // SWAY_GUI_BUILDER_HPP
