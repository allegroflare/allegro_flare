

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

ALLEGRO_COLOR ColorKit::mix(ALLEGRO_COLOR c1, ALLEGRO_COLOR c2, float scale)
{
   // TODO: Clamp scale range [0.0 - 1.0]
   ALLEGRO_COLOR col;
   col.r = (c2.r - c1.r) * scale + c1.r;
   col.g = (c2.g - c1.g) * scale + c1.g;
   col.b = (c2.b - c1.b) * scale + c1.b;
   col.a = (c2.a - c1.a) * scale + c1.a;
   return col;
}


} // namespace AllegroFlare


