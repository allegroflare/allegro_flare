#pragma once


#include <lib/nlohmann/json.hpp>
#include <AllegroFlare/Attributes.hpp>


namespace AllegroFlare
{
   // JSON loaders for Vec3D
   void to_json(nlohmann::json& j, const AllegroFlare::Attributes& attributes);
   void from_json(const nlohmann::json& j, AllegroFlare::Attributes& attributes);
}


