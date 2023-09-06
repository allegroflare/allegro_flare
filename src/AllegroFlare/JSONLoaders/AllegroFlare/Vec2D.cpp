

#include <AllegroFlare/JSONLoaders/AllegroFlare/Vec2D.hpp>


namespace AllegroFlare
{


void to_json(nlohmann::json& j, const Vec2D& v)
{
   j = nlohmann::json{
      {"x", v.x},
      {"y", v.y},
   };
}

void from_json(const nlohmann::json& j, Vec2D& v)
{
   j.at("x").get_to(v.x);
   j.at("y").get_to(v.y);
}


} // namespace AllegroFlare



