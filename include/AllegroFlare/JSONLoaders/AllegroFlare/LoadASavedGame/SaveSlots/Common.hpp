#pragma once


#include <lib/nlohmann/json.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Common.hpp>


namespace AllegroFlare::LoadASavedGame::SaveSlots
{
  void to_json(nlohmann::json& j, const Common& object);
  void from_json(const nlohmann::json& j, Common& object);
}


