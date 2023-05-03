

#include <AllegroFlare/ColorKit.hpp>




namespace AllegroFlare
{


ColorKit::ColorKit()
{
}


ColorKit::~ColorKit()
{
}


ALLEGRO_COLOR ColorKit::invert(ALLEGRO_COLOR color)
{
   return ALLEGRO_COLOR{1.0f - color.r, 1.0f - color.g, 1.0f - color.b, 1.0f};
}

ALLEGRO_COLOR ColorKit::fade(ALLEGRO_COLOR color, float amount)
{
   return ALLEGRO_COLOR{color.r*amount, color.g*amount, color.b*amount, 1.0f*amount};
}


} // namespace AllegroFlare


