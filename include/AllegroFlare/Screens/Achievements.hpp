#pragma once


#include <AllegroFlare/Elements/AchievementsList.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <string>
#include <tuple>
#include <vector>


namespace AllegroFlare
{
   namespace Screens
   {
      class Achievements : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::FontBin* font_bin;
         float scrollbar_dest_position;
         AllegroFlare::Elements::AchievementsList achievements_list;
         bool initialized;

      public:
         Achievements(AllegroFlare::FontBin* font_bin=nullptr, float scrollbar_dest_position=0.0f);
         virtual ~Achievements();

         AllegroFlare::Elements::AchievementsList &get_achievements_list_ref();
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void initialize();
         virtual void primary_timer_func() override;
         void update();
         void move_cursor_up();
         void move_cursor_down();
         virtual void virtual_control_button_down_func(int player_num=0, int button_num=0, bool is_repeat=false) override;
         void render();
         std::vector<std::tuple<std::string, std::string, std::string>> build_achievements();
         void limit_scrollbar_dest_position();
      };
   }
}



