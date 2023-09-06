

#include <AllegroFlare/JSONLoaders/AllegroFlare/Vec2B.hpp>


namespace AllegroFlare
{


void to_json(nlohmann::json& j, const Vec2B& v)
{
   j = nlohmann::json{
      {"x", v.get_x()},
      {"y", v.get_y()},
   };
}

void from_json(const nlohmann::json& j, Vec2B& v)
{
   j.at("x").get_to(v.get_x_ref());
   j.at("y").get_to(v.get_y_ref());
}


} // namespace AllegroFlare



