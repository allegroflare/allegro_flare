

#include <AllegroFlare/Timeline/ActorFactory.hpp>
#include <stdexcept>
#include <sstream>


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


AllegroFlare::BitmapBin* ActorFactory::get_bitmap_bin()
{
   return bitmap_bin;
}


AllegroFlare::Timeline::Actors::Actor2D* ActorFactory::create_actor2d_with_script(std::string identifier, std::string bitmap_identifier, std::string script)
{
   if (!(bitmap_bin))
      {
         std::stringstream error_message;
         error_message << "ActorFactory" << "::" << "create_actor2d_with_script" << ": error: " << "guard \"bitmap_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   AllegroFlare::Timeline::Actors::Actor2D* result = new AllegroFlare::Timeline::Actors::Actor2D();

   return result;
}
} // namespace Timeline
} // namespace AllegroFlare


