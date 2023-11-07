#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <string>
#include <tuple>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxRenderers
      {
         class TextMessages
         {
         private:
            AllegroFlare::FontBin* font_bin;
            std::vector<std::tuple<std::string, std::string, float>> messages;
            float age;
            float phone_screen_width;
            float phone_screen_height;
            bool draw_background_fill;

         protected:


         public:
            TextMessages(AllegroFlare::FontBin* font_bin=nullptr, std::vector<std::tuple<std::string, std::string, float>> messages={}, float age=0, float phone_screen_width=1, float phone_screen_height=1);
            ~TextMessages();

            void set_draw_background_fill(bool draw_background_fill);
            bool get_draw_background_fill() const;
            void render();
            float build_sanitized_age();
         };
      }
   }
}



