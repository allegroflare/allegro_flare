

#include <AllegroFlare/LoadASavedGame/SaveSlotRenderer.hpp>

#include <AllegroFlare/LoadASavedGame/SaveSlotRenderers/Basic.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlotRenderers/Common.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlotRenderers/Empty.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Basic.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Common.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Empty.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace LoadASavedGame
{


SaveSlotRenderer::SaveSlotRenderer(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, float slot_width, float slot_height)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , slot_width(slot_width)
   , slot_height(slot_height)
{
}


SaveSlotRenderer::~SaveSlotRenderer()
{
}


void SaveSlotRenderer::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void SaveSlotRenderer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void SaveSlotRenderer::set_slot_width(float slot_width)
{
   this->slot_width = slot_width;
}


void SaveSlotRenderer::set_slot_height(float slot_height)
{
   this->slot_height = slot_height;
}


AllegroFlare::BitmapBin* SaveSlotRenderer::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* SaveSlotRenderer::get_font_bin() const
{
   return font_bin;
}


float SaveSlotRenderer::get_slot_width() const
{
   return slot_width;
}


float SaveSlotRenderer::get_slot_height() const
{
   return slot_height;
}


void SaveSlotRenderer::render(AllegroFlare::LoadASavedGame::SaveSlots::Base* save_slot, float x, float y)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::SaveSlotRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::SaveSlotRenderer::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::SaveSlotRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::SaveSlotRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::SaveSlotRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::SaveSlotRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::SaveSlotRenderer::render]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::SaveSlotRenderer::render]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::SaveSlotRenderer::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::SaveSlotRenderer::render]: error: guard \"font_bin\" not met");
   }
   if (!(save_slot))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::SaveSlotRenderer::render]: error: guard \"save_slot\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::SaveSlotRenderer::render]: error: guard \"save_slot\" not met");
   }
   if (save_slot->is_type(AllegroFlare::LoadASavedGame::SaveSlots::Basic::TYPE))
   {
      // TODO: Test this rendering type
      AllegroFlare::LoadASavedGame::SaveSlots::Basic *as =
         static_cast<AllegroFlare::LoadASavedGame::SaveSlots::Basic*>(save_slot);

      AllegroFlare::LoadASavedGame::SaveSlotRenderers::Basic renderer;
      renderer.set_font_bin(font_bin);
      renderer.set_x(x);
      renderer.set_y(y);
      renderer.set_width(slot_width);
      renderer.set_height(slot_height);
      renderer.set_save_name(as->get_save_name());
      renderer.render();
   }
   else if (save_slot->is_type(AllegroFlare::LoadASavedGame::SaveSlots::Common::TYPE))
   {
      // TODO: Test this rendering type
      AllegroFlare::LoadASavedGame::SaveSlots::Common *as =
         static_cast<AllegroFlare::LoadASavedGame::SaveSlots::Common*>(save_slot);

      AllegroFlare::LoadASavedGame::SaveSlotRenderers::Common renderer;
      renderer.set_bitmap_bin(bitmap_bin);
      renderer.set_font_bin(font_bin);
      renderer.set_x(x);
      renderer.set_y(y);
      renderer.set_width(slot_width);
      renderer.set_height(slot_height);
      renderer.set_screenshot_of_gameplay_at_save_identifier(as->screenshot_of_gameplay_at_save_identifier);
      renderer.set_location_of_save(as->location_of_save);
      renderer.set_date_and_time_of_save(as->date_and_time_of_save);
      renderer.set_time_since_text(as->time_since_text);
      renderer.render();
   }
   else if (save_slot->is_type(AllegroFlare::LoadASavedGame::SaveSlots::Empty::TYPE))
   {
      // TODO: Test this rendering type
      AllegroFlare::LoadASavedGame::SaveSlotRenderers::Empty renderer;
      renderer.set_font_bin(font_bin);
      renderer.set_x(x);
      renderer.set_y(y);
      renderer.set_width(slot_width);
      renderer.set_height(slot_height);
      renderer.render();
   }
   else
   {
      // TODO: Test this thrown error
      std::stringstream error_message;
      error_message << "AllegroFlare::LoadASavedGame::SaveSlotRenderer::render error: "
                    << "Unhandled type \"" << save_slot->get_type() << "\"";
      throw std::runtime_error(error_message.str());
   }
   return;
}

ALLEGRO_FONT* SaveSlotRenderer::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::LoadASavedGame::SaveSlotRenderer::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::LoadASavedGame::SaveSlotRenderer::obtain_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Medium.ttf -52");
}


} // namespace LoadASavedGame
} // namespace AllegroFlare


