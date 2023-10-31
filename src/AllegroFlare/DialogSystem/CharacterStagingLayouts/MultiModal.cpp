

#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/MultiModal.hpp>

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


MultiModal::MultiModal()
   : AllegroFlare::DialogSystem::CharacterStagingLayouts::Base(AllegroFlare::DialogSystem::CharacterStagingLayouts::MultiModal::TYPE)
   , speaking_character_bitmap(nullptr)
   , speaking_character_bitmap_changed_at(0.0f)
   , surface_width(1920)
   , surface_height(1080)
{
}


MultiModal::~MultiModal()
{
}


void MultiModal::set_surface_width(int surface_width)
{
   this->surface_width = surface_width;
}


void MultiModal::set_surface_height(int surface_height)
{
   this->surface_height = surface_height;
}


int MultiModal::get_surface_width() const
{
   return surface_width;
}


int MultiModal::get_surface_height() const
{
   return surface_height;
}


void MultiModal::clear_speaking_character_bitmap()
{
   speaking_character_bitmap = nullptr;
   speaking_character_bitmap_changed_at = 0.0f;
   return;
}

void MultiModal::set_speaking_character_bitmap(ALLEGRO_BITMAP* speaking_character_bitmap, float time_now)
{
   if (!(speaking_character_bitmap))
   {
      std::stringstream error_message;
      error_message << "[MultiModal::set_speaking_character_bitmap]: error: guard \"speaking_character_bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("MultiModal::set_speaking_character_bitmap: error: guard \"speaking_character_bitmap\" not met");
   }
   // TODO: Test this method
   if (speaking_character_bitmap == this->speaking_character_bitmap) return;

   this->speaking_character_bitmap = speaking_character_bitmap;
   speaking_character_bitmap_changed_at = time_now;
   return;
}

void MultiModal::swap_speaking_character_bitmap(ALLEGRO_BITMAP* speaking_character_bitmap)
{
   if (!(speaking_character_bitmap))
   {
      std::stringstream error_message;
      error_message << "[MultiModal::swap_speaking_character_bitmap]: error: guard \"speaking_character_bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("MultiModal::swap_speaking_character_bitmap: error: guard \"speaking_character_bitmap\" not met");
   }
   // TODO: Test this method
   if (speaking_character_bitmap == this->speaking_character_bitmap) return;
   this->speaking_character_bitmap = speaking_character_bitmap;
   return;
}

void MultiModal::update(float time_now)
{
   // NOTE: Nothing to be done here at this time
   return;
}

void MultiModal::show(float time_now)
{
   // NOTE: Nothing to be done here at this time
   return;
}

void MultiModal::hide(float time_now)
{
   clear_speaking_character_bitmap();
   // NOTE: Nothing to be done here at this time
   return;
}

void MultiModal::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[MultiModal::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("MultiModal::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!speaking_character_bitmap) return;
   AllegroFlare::Placement2D character_bitmap_placement_transform(
      surface_width * 0.5,
      surface_height * 1.0,
      al_get_bitmap_width(speaking_character_bitmap),
      al_get_bitmap_height(speaking_character_bitmap)
   );
   character_bitmap_placement_transform.scale_to_fit_height(surface_height * 2);
   character_bitmap_placement_transform.start_transform();
   ALLEGRO_COLOR tint{1.0, 1.0, 1.0, 1.0}; // TODO: Use motion effects for introducing different characters
   al_draw_tinted_bitmap(speaking_character_bitmap, tint, 0, 0, 0);
   character_bitmap_placement_transform.restore_transform();
   return;
}


} // namespace CharacterStagingLayouts
} // namespace DialogSystem
} // namespace AllegroFlare


