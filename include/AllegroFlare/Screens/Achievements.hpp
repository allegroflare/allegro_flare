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
         float cursor_dest_position;
         AllegroFlare::Elements::AchievementsList achievements_list;
         bool initialized;

      public:
         Achievements(AllegroFlare::FontBin* font_bin=nullptr, float cursor_dest_position=0.0f);
         virtual ~Achievements();

         AllegroFlare::Elements::AchievementsList &get_achievements_list_ref();
         void initialize();
         virtual void primary_timer_func() override;
         void update();
         void render();
         std::vector<std::tuple<std::string, std::string, std::string>> build_achievements();
      };
   }
}



