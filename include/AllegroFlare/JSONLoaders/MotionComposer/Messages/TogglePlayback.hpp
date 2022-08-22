#pragma once


#include <lib/nlohmann/json.hpp>
#include <AllegroFlare/MotionComposer/Messages/TogglePlayback.hpp>


namespace AllegroFlare::MotionComposer::Messages
{
  void to_json(nlohmann::json& j, const TogglePlayback& object);
  void from_json(const nlohmann::json& j, TogglePlayback& object);
}


