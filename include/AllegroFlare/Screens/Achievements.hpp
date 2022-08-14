#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <string>
#include <tuple>
#include <vector>


namespace AllegroFlare
{
   namespace Screens
   {
      class Achievements
      {
      private:
         AllegroFlare::FontBin* font_bin;

      public:
         Achievements(AllegroFlare::FontBin* font_bin=nullptr);
         ~Achievements();

         void render();
         std::vector<std::tuple<std::string, std::string, std::string>> build_achievements();
      };
   }
}



