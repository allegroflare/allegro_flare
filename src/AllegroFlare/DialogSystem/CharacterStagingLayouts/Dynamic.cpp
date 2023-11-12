

#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/Dynamic.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogSystem
{
namespace CharacterStagingLayouts
{


Dynamic::Dynamic()
   : AllegroFlare::DialogSystem::CharacterStagingLayouts::Base(AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic::TYPE)
   , staged_characters({})
   , surface_width(1920)
   , surface_height(1080)
   , hidden(false)
{
}


Dynamic::~Dynamic()
{
}


void Dynamic::set_staged_characters(tsl::ordered_map<std::string, std::tuple<ALLEGRO_BITMAP*, AllegroFlare::Placement3D>> staged_characters)
{
   this->staged_characters = staged_characters;
}


void Dynamic::set_surface_width(int surface_width)
{
   this->surface_width = surface_width;
}


void Dynamic::set_surface_height(int surface_height)
{
   this->surface_height = surface_height;
}


tsl::ordered_map<std::string, std::tuple<ALLEGRO_BITMAP*, AllegroFlare::Placement3D>> Dynamic::get_staged_characters() const
{
   return staged_characters;
}


int Dynamic::get_surface_width() const
{
   return surface_width;
}


int Dynamic::get_surface_height() const
{
   return surface_height;
}


bool Dynamic::get_hidden() const
{
   return hidden;
}


void Dynamic::update(float time_now)
{
   // NOTE: Nothing to be done here at this time
   return;
}

void Dynamic::show(float time_now)
{
   // NOTE: Nothing to be done here at this time
   return;
}

void Dynamic::hide(float time_now)
{
   hidden = true; // TODO: Consider more elegant alternative to this "hard stop" on rendering
   return;
}

void Dynamic::clear()
{
   staged_characters.clear();
   return;
}

void Dynamic::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Dynamic::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Dynamic::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (hidden) return;

   for (auto &staged_character : staged_characters)
   {
      ALLEGRO_BITMAP *bitmap = std::get<0>(staged_character.second);
      if (!bitmap) return;

      AllegroFlare::Placement3D placement = std::get<1>(staged_character.second);
      //AllegroFlare::Placement2D character_bitmap_placement_transform(
         //surface_width * 0.5,
         //surface_height * 1.0,
         //al_get_bitmap_width(bitmap),
         //al_get_bitmap_height(bitmap)
      //);
      //character_bitmap_placement_transform.scale_to_fit_height(surface_height * 2);
      placement.start_transform();
      ALLEGRO_COLOR tint{1.0, 1.0, 1.0, 1.0}; // TODO: Use motion effects for introducing different characters
      al_draw_tinted_bitmap(bitmap, tint, 0, 0, 0);
      placement.restore_transform();
   }
   return;
}

void Dynamic::set_speaking_character_bitmap(ALLEGRO_BITMAP* speaking_character_bitmap, float time_now)
{
   if (!(speaking_character_bitmap))
   {
      std::stringstream error_message;
      error_message << "[Dynamic::set_speaking_character_bitmap]: error: guard \"speaking_character_bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Dynamic::set_speaking_character_bitmap: error: guard \"speaking_character_bitmap\" not met");
   }
   // TODO: Test this method
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic::set_speaking_character_bitmap",
      "This method is not implemented in this derived class"
   );

   //if (speaking_character_bitmap == this->speaking_character_bitmap) return;
   //this->speaking_character_bitmap = speaking_character_bitmap;
   //speaking_character_bitmap_changed_at = time_now;
   return;
}


} // namespace CharacterStagingLayouts
} // namespace DialogSystem
} // namespace AllegroFlare


