#pragma once


#include <lib/nlohmann/json.hpp>
#include <AllegroFlare/MotionComposer/Messages/AddActor2D.hpp>


namespace AllegroFlare::MotionComposer::Messages
{
  void to_json(nlohmann::json& j, const AddActor2D& object);
  void from_json(const nlohmann::json& j, AddActor2D& object);
}


