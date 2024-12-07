#ifndef SWAY_UI_WIDGETS_CARETSELECTIONRANGE_HPP
#define SWAY_UI_WIDGETS_CARETSELECTIONRANGE_HPP

#include <sway/core.hpp>

#include <utility>

NS_BEGIN_SWAY()
NS_BEGIN(ui)

/**
 * \~russian @brief Структура для представления диапазона выделения текста.
 *                  Если ничего не выделено, то значения индексов равны.
 */
struct CaretSelectionRange {
  u32_t begin;  ///< Индекс начала выделенного фрагмента текста.
  u32_t end;  ///< Индекс конца выделенного фрагмента текста.

  /**
   * \~russian @brief Возвращает выделенный фрагмент текста.
   * @param[in] text Исходный текст.
   * @return Выделенный фрагмент текста.
   */
  [[nodiscard]] auto getSelectedText(const std::string &text) const -> std::string {
    return (begin != end) ? text.substr(begin, end - begin) : "";
  }

  friend auto operator<<(std::ostream &str, const CaretSelectionRange &range) -> std::ostream & {
    str << "{begin:" << range.begin << ", end:" << range.end << "}";
    return str;
  }
};

NS_END()  // namespace ui
NS_END()  // namespace sway

#endif  // SWAY_UI_WIDGETS_CARETSELECTIONRANGE_HPP
