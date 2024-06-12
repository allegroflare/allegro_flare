

#include <AllegroFlare/RenderSurfaces/Base.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace RenderSurfaces
{


Base::Base(std::string type)
   : type(type)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}





bool Base::is_target()
{
   return (al_get_target_bitmap() == obtain_surface());
}



float Base::get_center()
{
   return get_width() * 0.5f;
}

float Base::get_middle()
{
   return get_height() * 0.5f;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}

bool Base::is_a_display_surface()
{
   if (!((obtain_surface() != nullptr)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RenderSurfaces::Base::is_a_display_surface]: error: guard \"(obtain_surface() != nullptr)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RenderSurfaces::Base::is_a_display_surface]: error: guard \"(obtain_surface() != nullptr)\" not met");
   }
   ALLEGRO_BITMAP *parent = al_get_parent_bitmap(obtain_surface());
   ALLEGRO_BITMAP *sanitized = parent ? parent : obtain_surface();

   // NOTE: This technique below is not 100% accurate, specifically if there are multiple displays.
   // TODO: Update this to consider multiple displays
   return (sanitized == al_get_backbuffer(al_get_current_display()));
}


} // namespace RenderSurfaces
} // namespace AllegroFlare


