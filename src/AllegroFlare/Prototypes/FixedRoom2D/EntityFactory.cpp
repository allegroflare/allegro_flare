

#include <AllegroFlare/Prototypes/FixedRoom2D/EntityFactory.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


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
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::EntityFactory::create_chair_entity]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::EntityFactory::create_chair_entity]: error: guard \"bitmap_bin\" not met");
   }
   return create_entity("wooden-chair-png-transparent-image-pngpix-0.png", x, y, 0.1, "chair");
}

AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* EntityFactory::create_entity(std::string bitmap_image_identifier, float x, float y, float scale, std::string name, std::string on_interact_script_name)
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::EntityFactory::create_entity]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::EntityFactory::create_entity]: error: guard \"bitmap_bin\" not met");
   }
   ALLEGRO_BITMAP* bitmap = bitmap_bin->auto_get(bitmap_image_identifier);

   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* result = new
      AllegroFlare::Prototypes::FixedRoom2D::Entities::Base(bitmap);

   AllegroFlare::Placement2D &placement = result->get_placement_ref();
   result->set_on_cursor_interact_script_name(on_interact_script_name);

   placement.position = AllegroFlare::Vec2D{x, y};
   placement.scale = AllegroFlare::Vec2D{scale, scale};
   placement.align = AllegroFlare::Vec2D{0.5, 1.0};
   if (bitmap) placement.size = AllegroFlare::Vec2D{(float)al_get_bitmap_width(bitmap), (float)al_get_bitmap_height(bitmap)};

   result->set("name", name);

   return result;
}

AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* EntityFactory::create_entity_bmp(ALLEGRO_BITMAP* bitmap, float x, float y, float scale, std::string name, std::string on_interact_script_name)
{
   if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::EntityFactory::create_entity_bmp]: error: guard \"bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::EntityFactory::create_entity_bmp]: error: guard \"bitmap\" not met");
   }
   AllegroFlare::Prototypes::FixedRoom2D::Entities::Base* result = new
      AllegroFlare::Prototypes::FixedRoom2D::Entities::Base(bitmap);

   AllegroFlare::Placement2D &placement = result->get_placement_ref();
   result->set_on_cursor_interact_script_name(on_interact_script_name);

   placement.position = AllegroFlare::Vec2D{x, y};
   placement.scale = AllegroFlare::Vec2D{scale, scale};
   placement.align = AllegroFlare::Vec2D{0.5, 1.0};
   if (bitmap) placement.size = AllegroFlare::Vec2D{(float)al_get_bitmap_width(bitmap), (float)al_get_bitmap_height(bitmap)};

   result->set("name", name);

   return result;
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


