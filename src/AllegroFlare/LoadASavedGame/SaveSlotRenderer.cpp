

#include <AllegroFlare/LoadASavedGame/SaveSlotRenderer.hpp>

#include <AllegroFlare/LoadASavedGame/SaveSlotRenderers/Basic.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlotRenderers/Empty.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Basic.hpp>
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


SaveSlotRenderer::SaveSlotRenderer(AllegroFlare::FontBin* font_bin, std::string quote)
   : font_bin(font_bin)
   , quote(quote)
{
}


SaveSlotRenderer::~SaveSlotRenderer()
{
}


void SaveSlotRenderer::render(AllegroFlare::LoadASavedGame::SaveSlots::Base* save_slot, float x, float y)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[SaveSlotRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SaveSlotRenderer::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[SaveSlotRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SaveSlotRenderer::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[SaveSlotRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SaveSlotRenderer::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[SaveSlotRenderer::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SaveSlotRenderer::render: error: guard \"font_bin\" not met");
   }
   float slot_width = 1920/2;
   float slot_height = 1080/8;
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
      error_message << "[SaveSlotRenderer::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SaveSlotRenderer::obtain_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Medium.ttf -52");
}


} // namespace LoadASavedGame
} // namespace AllegroFlare


