#ifndef SWAY_UI_PAINTER_H
#define SWAY_UI_PAINTER_H

#include <sway/ui/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

class Painter {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	Painter();

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Освобождает захваченные ресурсы.
	 */
	~Painter();

private:
};

NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif // SWAY_UI_PAINTER_H
