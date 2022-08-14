#pragma once


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

      public:
         Achievements(AllegroFlare::FontBin* font_bin=nullptr);
         virtual ~Achievements();

         virtual void primary_timer_func() override;
         void update();
         void render();
         std::vector<std::tuple<std::string, std::string, std::string>> build_achievements();
      };
   }
}



