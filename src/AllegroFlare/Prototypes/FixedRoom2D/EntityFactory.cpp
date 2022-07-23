

#include <AllegroFlare/Prototypes/FixedRoom2D/EntityFactory.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


EntityFactory::EntityFactory(AllegroFlare::BitmapBin* bitmap_bin)
   : bitmap_bin(bitmap_bin)
{
}


EntityFactory::~EntityFactory()
{
}


AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* EntityFactory::create_chair_entity(float x, float y)
{
   if (!(bitmap_bin))
      {
         std::stringstream error_message;
         error_message << "EntityFactory" << "::" << "create_chair_entity" << ": error: " << "guard \"bitmap_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return create_entity("wooden-chair-png-transparent-image-pngpix-0.png", x, y, 0.1, "chair");
}

AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* EntityFactory::create_entity(std::string bitmap_image_identifier, float x, float y, float scale, std::string name)
{
   if (!(bitmap_bin))
      {
         std::stringstream error_message;
         error_message << "EntityFactory" << "::" << "create_entity" << ": error: " << "guard \"bitmap_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_BITMAP* bitmap = bitmap_bin->auto_get(bitmap_image_identifier);

   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* result = new
      AllegroFlare::Prototypes::FixedRoom2D::Entities::Base(bitmap);

   AllegroFlare::Placement2D &placement = result->get_placement_ref();

   placement.position = {x, y};
   placement.scale = {0.1, 0.1};
   placement.align = {0.5, 1.0};
   if (bitmap) placement.size = {(float)al_get_bitmap_width(bitmap), (float)al_get_bitmap_height(bitmap)};

   result->set("name", name);

   return result;
}
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


