

#include <AllegroFlare/JSONLoaders/ALLEGRO_COLOR.hpp>


//namespace 
//{


void to_json(nlohmann::json& j, const ALLEGRO_COLOR& v)
{
   j = nlohmann::json{
      { "r", v.r },
      { "g", v.g },
      { "b", v.b },
      { "a", v.a },
   };
}

void from_json(const nlohmann::json& j, ALLEGRO_COLOR& v)
{
   j.at("r").get_to(v.r);
   j.at("g").get_to(v.g);
   j.at("b").get_to(v.b);
   j.at("a").get_to(v.a);
}


//} // namespace 



