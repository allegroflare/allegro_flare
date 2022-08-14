#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <cstdint>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace NotificationRenderers
      {
         class AchievementUnlocked
         {
         private:
            AllegroFlare::FontBin* font_bin;

         public:
            AchievementUnlocked(AllegroFlare::FontBin* font_bin=nullptr);
            ~AchievementUnlocked();

            void render();
            void draw_achievement_box(float x=0.0f, float y=0.0f, std::string status="[unset-status]", std::string title="[unset-title]", std::string description="[unset-description]");
            int32_t infer_icon_character_by_status(std::string status="[unset-status]");
            ALLEGRO_COLOR infer_icon_color_by_status(std::string status="[unset-status]", ALLEGRO_COLOR icon_locked_color=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR icon_hidden_color=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR icon_achieved_color=ALLEGRO_COLOR{1, 1, 1, 1});
            std::string filter_item_title_through_status(std::string title="[unset-title]", std::string status="[unset-status]");
            std::string filter_item_description_through_status(std::string description="[unset-title]", std::string status="[unset-status]");
            ALLEGRO_FONT* obtain_item_title_font();
            ALLEGRO_FONT* obtain_item_description_font();
            ALLEGRO_FONT* obtain_icon_font();
            void draw_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, int x=0, int y=0, uint32_t icon=61444, int flags=0);
         };
      }
   }
}



