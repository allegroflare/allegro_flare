#pragma once


#include <AllegroFlare/Elements/Backgrounds/Base.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace Backgrounds
      {
         class ClearToColor : public AllegroFlare::Elements::Backgrounds::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/Backgrounds/ClearToColor";

         private:
            ALLEGRO_COLOR clear_color;

         protected:


         public:
            ClearToColor(ALLEGRO_COLOR clear_color=ALLEGRO_COLOR{0, 0, 0, 0});
            virtual ~ClearToColor();

            void set_clear_color(ALLEGRO_COLOR clear_color);
            ALLEGRO_COLOR get_clear_color() const;
            virtual void render();
         };
      }
   }
}



