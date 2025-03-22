#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/SavingAndLoading/SaveSlot.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <cstdint>
#include <ctime>
#include <string>


namespace AllegroFlare
{
   namespace SavingAndLoading
   {
      class SaveSlotRenderer
      {
      public:
         static constexpr int DEFAULT_WIDTH = 640;
         static constexpr int DEFAULT_HEIGHT = 155;

      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         std::string screenshot_of_gameplay_at_save_identifier;
         std::string location_of_save;
         std::string date_and_time_of_save;
         std::string time_since_text;
         std::time_t time_since_value;
         uint32_t save_slot_type;
         float width;
         float height;
         ALLEGRO_FONT* obtain_location_name_font();
         ALLEGRO_FONT* obtain_details_font();

      protected:


      public:
         SaveSlotRenderer(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::string screenshot_of_gameplay_at_save_identifier="[unset-screenshot_of_gameplay_at_save_identifier]", std::string location_of_save="Location of Save", std::string date_and_time_of_save="12/14/2024 3:20PM", std::string time_since_text="12 minutes ago", std::time_t time_since_value=0, uint32_t save_slot_type=AllegroFlare::SavingAndLoading::SaveSlot::SAVE_SLOT_TYPE_UNDEF);
         ~SaveSlotRenderer();

         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_screenshot_of_gameplay_at_save_identifier(std::string screenshot_of_gameplay_at_save_identifier);
         void set_location_of_save(std::string location_of_save);
         void set_date_and_time_of_save(std::string date_and_time_of_save);
         void set_time_since_text(std::string time_since_text);
         void set_time_since_value(std::time_t time_since_value);
         void set_save_slot_type(uint32_t save_slot_type);
         void set_width(float width);
         void set_height(float height);
         std::string get_screenshot_of_gameplay_at_save_identifier() const;
         std::string get_location_of_save() const;
         std::string get_date_and_time_of_save() const;
         std::string get_time_since_text() const;
         std::time_t get_time_since_value() const;
         uint32_t get_save_slot_type() const;
         float get_width() const;
         float get_height() const;
         void __dependency_trigger(uint32_t dep1=AllegroFlare::SavingAndLoading::SaveSlot::SAVE_SLOT_TYPE_UNDEF);
         ALLEGRO_COLOR infer_time_since_text_color(std::time_t time_since_value=0);
         void render();
         bool save_slot_type_is_manual_save();
         static std::string obtain_save_slot_type_string_for_presentation(uint32_t save_slot_type=AllegroFlare::SavingAndLoading::SaveSlot::SAVE_SLOT_TYPE_UNDEF);
      };
   }
}



