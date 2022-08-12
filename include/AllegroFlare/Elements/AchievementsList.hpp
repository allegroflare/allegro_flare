#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
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
         float achievements_box_height;
         float achievements_box_width;

      public:
         AchievementsList(AllegroFlare::FontBin* font_bin=nullptr, std::vector<std::tuple<bool, std::string, std::string>> achievements={}, float achievements_box_height=80.0f, float achievements_box_width=300.0f);
         ~AchievementsList();

         void set_achievements(std::vector<std::tuple<bool, std::string, std::string>> achievements);
         void set_achievements_box_height(float achievements_box_height);
         void set_achievements_box_width(float achievements_box_width);
         std::vector<std::tuple<bool, std::string, std::string>> get_achievements();
         float get_achievements_box_height();
         float get_achievements_box_width();
         void render();
         void draw_achievement_box(float x=0.0f, float y=0.0f);
         ALLEGRO_FONT* obtain_font();
      };
   }
}



