#pragma once


#include <lib/nlohmann/json.hpp>
#include <AllegroFlare/Vec2B.hpp>


namespace AllegroFlare
{
  void to_json(nlohmann::json& j, const Vec2B& object);
  void from_json(const nlohmann::json& j, Vec2B& object);
}


