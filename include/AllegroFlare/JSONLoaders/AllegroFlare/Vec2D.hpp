#pragma once


#include <lib/nlohmann/json.hpp>
#include <AllegroFlare/Vec2D.hpp>


namespace AllegroFlare
{
  void to_json(nlohmann::json& j, const Vec2D& object);
  void from_json(const nlohmann::json& j, Vec2D& object);
}


