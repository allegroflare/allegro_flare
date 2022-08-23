#pragma once


#include <lib/nlohmann/json.hpp>
#include <AllegroFlare/MotionComposer/Messages/Clear.hpp>


namespace AllegroFlare::MotionComposer::Messages
{
  void to_json(nlohmann::json& j, const Clear& object);
  void from_json(const nlohmann::json& j, Clear& object);
}


