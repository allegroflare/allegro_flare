#pragma once


#include <allegro5/allegro.h>
#include <functional>
#include <string>


namespace AllegroFlare
{
   namespace Layouts
   {
      namespace Elements
      {
         class Text
         {
         private:

         protected:


         public:
            std::string name;
            float x;
            float y;
            float width;
            float height;
            float align_x;
            float align_y;
            std::string font_family;
            int font_size;
            ALLEGRO_COLOR color;
            float tmj_object_id;
            std::function<void()> on_focus;
            std::function<void()> on_blur;
            std::function<void()> on_activation;
            Text();
            ~Text();

         };
      }
   }
}



