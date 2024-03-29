#pragma once


#include <lib/nlohmann/json.hpp>
#include <AllegroFlare/Camera3D.hpp>


namespace AllegroFlare
{
   // JSON loaders for Camera3D
   void to_json(nlohmann::json& j, const AllegroFlare::Camera3D& camera);
   void from_json(const nlohmann::json& j, AllegroFlare::Camera3D& camera);
}


