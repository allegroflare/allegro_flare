

#include <AllegroFlare/SavingAndLoading/SaveSlotRenderer.hpp>

#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>


namespace AllegroFlare
{
namespace SavingAndLoading
{


SaveSlotRenderer::SaveSlotRenderer(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, std::string screenshot_of_gameplay_at_save_identifier, std::string location_of_save, std::string date_and_time_of_save, std::string time_since_text, uint32_t save_slot_type)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , screenshot_of_gameplay_at_save_identifier(screenshot_of_gameplay_at_save_identifier)
   , location_of_save(location_of_save)
   , date_and_time_of_save(date_and_time_of_save)
   , time_since_text(time_since_text)
   , save_slot_type(save_slot_type)
   , width(DEFAULT_WIDTH)
   , height(DEFAULT_HEIGHT)
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


void SaveSlotRenderer::set_screenshot_of_gameplay_at_save_identifier(std::string screenshot_of_gameplay_at_save_identifier)
{
   this->screenshot_of_gameplay_at_save_identifier = screenshot_of_gameplay_at_save_identifier;
}


void SaveSlotRenderer::set_location_of_save(std::string location_of_save)
{
   this->location_of_save = location_of_save;
}


void SaveSlotRenderer::set_date_and_time_of_save(std::string date_and_time_of_save)
{
   this->date_and_time_of_save = date_and_time_of_save;
}


void SaveSlotRenderer::set_time_since_text(std::string time_since_text)
{
   this->time_since_text = time_since_text;
}


void SaveSlotRenderer::set_save_slot_type(uint32_t save_slot_type)
{
   this->save_slot_type = save_slot_type;
}


void SaveSlotRenderer::set_width(float width)
{
   this->width = width;
}


void SaveSlotRenderer::set_height(float height)
{
   this->height = height;
}


std::string SaveSlotRenderer::get_screenshot_of_gameplay_at_save_identifier() const
{
   return screenshot_of_gameplay_at_save_identifier;
}


std::string SaveSlotRenderer::get_location_of_save() const
{
   return location_of_save;
}


std::string SaveSlotRenderer::get_date_and_time_of_save() const
{
   return date_and_time_of_save;
}


std::string SaveSlotRenderer::get_time_since_text() const
{
   return time_since_text;
}


uint32_t SaveSlotRenderer::get_save_slot_type() const
{
   return save_slot_type;
}


float SaveSlotRenderer::get_width() const
{
   return width;
}


float SaveSlotRenderer::get_height() const
{
   return height;
}


void SaveSlotRenderer::__dependency_trigger(uint32_t dep1)
{
   return;
}

void SaveSlotRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SaveSlotRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SaveSlotRenderer::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SaveSlotRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SaveSlotRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SaveSlotRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SaveSlotRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SaveSlotRenderer::render]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SaveSlotRenderer::render]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SaveSlotRenderer::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SaveSlotRenderer::render]: error: guard \"font_bin\" not met");
   }
   float x = 0; // TODO: Factor out x
   float y = 0; // TODO: Factor out y
   float screenshot_width = 1920/9;
   float screenshot_x_padding = 20;
   float screenshot_height = 1080/9;
   //float x = 1920/2;
   //float y = 1080/3;
   ALLEGRO_FONT *location_name_font = obtain_location_name_font();
   float location_name_font_line_height = al_get_font_line_height(location_name_font);
   ALLEGRO_FONT *details_font = obtain_details_font();
   float details_font_line_height = al_get_font_line_height(details_font);
   //float h_location_name_font_line_height = al_get_font_line_height(location_name_font)/2;
   //float text_width = al_get_text_width(font, quote.c_str());
   //float text_height = al_get_font_line_height(font);
   float h_text_width = width/2;
   float h_text_height = height/2;
   AllegroFlare::Vec2D padding = {0, 0};
   float cumulative_line_spacing = 0;

   float text_x = x + screenshot_width + screenshot_x_padding*2;
   float text_y = y + 12;
   ALLEGRO_COLOR fill_color = ALLEGRO_COLOR{0.13, 0.13, 0.13, 1.0};
   ALLEGRO_COLOR border_color = ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0};

   { // fill and border
      // Draw the fill
      al_draw_filled_rounded_rectangle(
         x - padding.x,
         y - padding.y,
         x + width + padding.x,
         y + height + padding.y,
         8.0f,
         8.0f,
         fill_color
      );

      // Draw the border
      al_draw_rounded_rectangle(
         x - padding.x,
         y - padding.y,
         x + width + padding.x,
         y + height + padding.y,
         8.0f,
         8.0f,
         border_color,
         3.0f
      );
   }

   { // screenshot
      // Draw the screenshot frame
      float screenshot_x = x+screenshot_x_padding;
      float screenshot_y = y+height/2 - (int)(screenshot_height/2);
      //float screenshot_w = 350/2;
      //float screenshot_h = 220/2;
      al_draw_rectangle(
         screenshot_x,
         screenshot_y,
         screenshot_x + screenshot_width,
         screenshot_y + screenshot_height,
         border_color,
         2.0f
      );

      // Draw the image
      // NOTE: Any image will be stretched to fit the screenshot space
      // NOTE: Screenshots are 16:9
      ALLEGRO_BITMAP* screenshot = bitmap_bin->auto_get(screenshot_of_gameplay_at_save_identifier);
      if (!screenshot)
      {
         AllegroFlare::Logger::throw_error(THIS_CLASS_AND_METHOD_NAME,
            "screenshot is required in this component (for now)."
         );
      }

      al_draw_scaled_bitmap(
         screenshot,
         0,
         0,
         al_get_bitmap_width(screenshot),
         al_get_bitmap_height(screenshot),
         screenshot_x,
         screenshot_y,
         screenshot_width,
         screenshot_height,
         0
      );

      { // Save slot type (presented as text over the screenshot)
         float type_label_x = (int)(screenshot_x + screenshot_width * 0.5);
         float type_label_y = (int)(screenshot_y + screenshot_height - (details_font_line_height * 1.125));

         ALLEGRO_COLOR fill_color = ALLEGRO_COLOR{0.0, 0.0, 0.0, 0.6};
         ALLEGRO_COLOR text_color = ALLEGRO_COLOR{0.7, 0.7, 0.7, 0.7};

         al_draw_filled_rectangle(
            screenshot_x,
            screenshot_y + screenshot_height - details_font_line_height * 1.25,
            screenshot_x + screenshot_width,
            screenshot_y + screenshot_height,
            fill_color
         );

         al_draw_text(
            details_font,
            text_color,
            type_label_x,
            type_label_y,
            ALLEGRO_ALIGN_CENTER,
            obtain_save_slot_type_string_for_presentation(save_slot_type).c_str()
         );
      }
   }

   cumulative_line_spacing = 0;
   { // save data text
      // The location of the save
      al_draw_text(
         location_name_font,
         ALLEGRO_COLOR{1, 1, 1, 1},
         text_x,
         text_y+cumulative_line_spacing,
         ALLEGRO_ALIGN_LEFT,
         location_of_save.c_str()
      );
      cumulative_line_spacing += location_name_font_line_height + 1;

      // The date_and_time_of_save
      al_draw_text(
         details_font,
         ALLEGRO_COLOR{1, 1, 1, 1},
         text_x,
         text_y+cumulative_line_spacing,
         ALLEGRO_ALIGN_LEFT,
         date_and_time_of_save.c_str()
      );
      cumulative_line_spacing += details_font_line_height + 2;
   }

   { // time since text
      // The time_since text
      ALLEGRO_FONT *time_since_font = details_font;
      ALLEGRO_COLOR time_since_color = ALLEGRO_COLOR{0.5, 1.0, 0.83, 1.0}; // a minty green

      int time_since_font_line_height = al_get_font_line_height(time_since_font);

      al_draw_text(
         time_since_font,
         time_since_color,
         text_x,
         text_y+cumulative_line_spacing,
         //x + width - padding.x-screenshot_x_padding,
         //y + height - padding.y - time_since_font_line_height - 5,
         ALLEGRO_ALIGN_LEFT,
         time_since_text.c_str()
      );
   }

   return;
}

std::string SaveSlotRenderer::obtain_save_slot_type_string_for_presentation(uint32_t save_slot_type)
{
   static const std::unordered_map<uint32_t, std::string> event_names {
      { AllegroFlare::SavingAndLoading::SaveSlot::SAVE_SLOT_TYPE_MANUAL_SAVE, "Manual Save" },
      { AllegroFlare::SavingAndLoading::SaveSlot::SAVE_SLOT_TYPE_AUTO_SAVE, "Autosave" },
      { AllegroFlare::SavingAndLoading::SaveSlot::SAVE_SLOT_TYPE_QUICK_SAVE, "Quicksave" },
   };

   auto it = event_names.find(save_slot_type);

   if (it == event_names.end())
   {
      return "SAVE_SLOT_TYPE_UNKNOWN";
   }
   else
   {
      return it->second;
   }
}

ALLEGRO_FONT* SaveSlotRenderer::obtain_location_name_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SaveSlotRenderer::obtain_location_name_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SaveSlotRenderer::obtain_location_name_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Oswald-Medium.ttf -54");
}

ALLEGRO_FONT* SaveSlotRenderer::obtain_details_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SavingAndLoading::SaveSlotRenderer::obtain_details_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SavingAndLoading::SaveSlotRenderer::obtain_details_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("RobotoCondensed-Regular.ttf -32");
}


} // namespace SavingAndLoading
} // namespace AllegroFlare


