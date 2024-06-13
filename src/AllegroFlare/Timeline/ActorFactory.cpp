

#include <AllegroFlare/Timeline/ActorFactory.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Timeline
{


ActorFactory::ActorFactory(AllegroFlare::BitmapBin* bitmap_bin)
   : bitmap_bin(bitmap_bin)
{
}


ActorFactory::~ActorFactory()
{
}


void ActorFactory::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


AllegroFlare::BitmapBin* ActorFactory::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::Timeline::Actors::Actor2D* ActorFactory::create_actor2d_with_script(std::string identifier, std::string bitmap_identifier, std::string script)
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Timeline::ActorFactory::create_actor2d_with_script]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Timeline::ActorFactory::create_actor2d_with_script]: error: guard \"bitmap_bin\" not met");
   }
   AllegroFlare::Timeline::Actors::Actor2D* result = new AllegroFlare::Timeline::Actors::Actor2D(
      identifier,
      bitmap_identifier,
      bitmap_bin->auto_get(bitmap_identifier)
   );
   if (!script.empty()) result->load_script(script);
   return result;
}


} // namespace Timeline
} // namespace AllegroFlare


