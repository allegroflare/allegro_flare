

#include <AllegroFlare/JSONLoaders/AllegroFlare/Attributes.hpp>


namespace AllegroFlare
{


// JSON loader for Attributes
void to_json(nlohmann::json& j, const AllegroFlare::Attributes& v)
{
   j = nlohmann::json{
   //   {"x", v.x},  // these examples from Vec2D
   //   {"y", v.y},
   //   {"z", v.z},
   };
}


// JSON loader for Attributes
void from_json(const nlohmann::json& j, AllegroFlare::Attributes& v)
{
   //j.at("x").get_to(v.x);  // these examples from Vec2D
   //j.at("y").get_to(v.y);
   //j.at("z").get_to(v.z);
}


} // namespace AllegroFlare


