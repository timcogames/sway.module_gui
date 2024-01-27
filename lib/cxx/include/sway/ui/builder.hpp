#ifndef SWAY_UI_BUILDER_HPP
#define SWAY_UI_BUILDER_HPP

#include <sway/core.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(ui)

class Builder : public core::foundation::Object {
  DECLARE_CLASS_METADATA(Builder, core::foundation::Object)

public:
  Builder(core::foundation::Context *context);

  virtual ~Builder();

private:
};

NAMESPACE_END(ui)
NAMESPACE_END(sway)

#endif  // SWAY_UI_BUILDER_HPP
