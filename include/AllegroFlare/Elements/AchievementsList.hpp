#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <cstdint>
#include <string>
#include <tuple>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class AchievementsList
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::vector<std::tuple<bool, std::string, std::string>> achievements;
         float achievements_box_width;
         float achievements_box_height;
         int surface_width;
         int surface_height;

      public:
         AchievementsList(AllegroFlare::FontBin* font_bin=nullptr, std::vector<std::tuple<bool, std::string, std::string>> achievements={}, float achievements_box_width=800.0f, float achievements_box_height=150.0f);
         ~AchievementsList();

         void set_achievements(std::vector<std::tuple<bool, std::string, std::string>> achievements);
         void set_achievements_box_width(float achievements_box_width);
         void set_achievements_box_height(float achievements_box_height);
         void set_surface_width(int surface_width);
         void set_surface_height(int surface_height);
         std::vector<std::tuple<bool, std::string, std::string>> get_achievements();
         float get_achievements_box_width();
         float get_achievements_box_height();
         int get_surface_width();
         int get_surface_height();
         void render();
         void draw_achievement_box(float x=0.0f, float y=0.0f, bool is_achieved=false, std::string title="[unset-title]", std::string description="[unset-description]");
         static std::vector<std::tuple<bool, std::string, std::string>> build_placeholder_achievements();
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_FONT* obtain_description_font();
         ALLEGRO_FONT* obtain_icon_font();
         void draw_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, int x=0, int y=0, uint32_t icon=61444, int flags=0);
      };
   }
}



