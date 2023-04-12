

#include <AllegroFlare/Elements/Backgrounds/ClearToColor.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace Backgrounds
{


ClearToColor::ClearToColor(ALLEGRO_COLOR clear_color)
   : AllegroFlare::Elements::Backgrounds::Base(AllegroFlare::Elements::Backgrounds::ClearToColor::TYPE)
   , clear_color(clear_color)
{
}


ClearToColor::~ClearToColor()
{
}


void ClearToColor::set_clear_color(ALLEGRO_COLOR clear_color)
{
   this->clear_color = clear_color;
}


ALLEGRO_COLOR ClearToColor::get_clear_color() const
{
   return clear_color;
}


void ClearToColor::render()
{
   al_clear_to_color(clear_color);
   return;
}


} // namespace Backgrounds
} // namespace Elements
} // namespace AllegroFlare


