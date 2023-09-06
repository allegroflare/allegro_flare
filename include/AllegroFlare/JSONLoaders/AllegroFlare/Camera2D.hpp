#pragma once


#include <lib/nlohmann/json.hpp>
#include <AllegroFlare/Camera2D.hpp>


namespace AllegroFlare
{
  void to_json(nlohmann::json& j, const Camera2D& object);
  void from_json(const nlohmann::json& j, Camera2D& object);
}


