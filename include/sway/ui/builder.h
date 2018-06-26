#ifndef SWAY_UI_BUILDER_H
#define SWAY_UI_BUILDER_H

#include <sway/graphics/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

class Builder : public core::foundation::Object {
	DECLARE_OBJECT(Builder, core::foundation::Object)

public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 * 
	 * \param[in] context
	 *    Контекст подсистемы.
	 */
	Builder(core::foundation::Context * context);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Освобождает захваченные ресурсы.
	 */
	virtual ~Builder();

private:
};

NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif // SWAY_UI_BUILDER_H
