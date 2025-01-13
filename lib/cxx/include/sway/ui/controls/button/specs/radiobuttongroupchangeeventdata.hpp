#ifndef SWAY_UI_RADIOBUTTONGROUPCHANGEEVENTDATA_HPP
#define SWAY_UI_RADIOBUTTONGROUPCHANGEEVENTDATA_HPP

#include <sway/ui/_stdafx.hpp>

namespace sway::ui {

struct RadioButtonGroupChangeEventData : public core::EventData {
  core::NodeIndex nodeidx;

  // MTHD_OVERRIDE(auto serialize() const -> std::string) { return ""; }

  // MTHD_OVERRIDE(void deserialize(const std::string &jdata)) {}
};

}  // namespace sway::ui

#endif  // SWAY_UI_RADIOBUTTONGROUPCHANGEEVENTDATA_HPP
