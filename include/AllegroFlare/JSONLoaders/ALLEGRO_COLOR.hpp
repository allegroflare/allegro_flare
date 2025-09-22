#pragma once


#include <lib/nlohmann/json.hpp>
#include <allegro5/allegro.h>


//namespace 
//{
  void to_json(nlohmann::json& j, const ALLEGRO_COLOR& object);
  void from_json(const nlohmann::json& j, ALLEGRO_COLOR& object);
//}


