#ifndef SWAY_UI_WIDGETS_CARETSELECTIONRANGE_HPP
#define SWAY_UI_WIDGETS_CARETSELECTIONRANGE_HPP

#include <sway/ui/_stdafx.hpp>

namespace sway::ui {

/**
 * @brief \~english Structure for representing text selection. If nothing is selected, the index values are equal.
 * \~russian Структура для представления диапазона выделения текста. Если ничего не выделено, то значения индексов
 * равны.
 */
struct CaretSelectionRange {
  u32_t begin; /*!< \~english Index of the beginning of the selected fragment of text.
    \~russian Индекс начала выделенного фрагмента текста. */
  u32_t end; /*!< \~english Index of the end of the selected fragment of text.
    \~russian Индекс конца выделенного фрагмента текста. */

  /**
   * \~english
   * @brief Returns the selected text fragment.
   * @param[in] text Source text.
   * @return Selected text fragment.
   *
   * \~russian
   * @brief Возвращает выделенный фрагмент текста.
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

}  // namespace sway::ui

#endif  // SWAY_UI_WIDGETS_CARETSELECTIONRANGE_HPP
