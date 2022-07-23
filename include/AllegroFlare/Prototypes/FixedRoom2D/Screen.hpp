#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/FixedRoom2D.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         class Screen : public AllegroFlare::Screens::Base
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D fixed_room_2d;
            bool initialized;

         public:
            Screen(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr);
            virtual ~Screen();

            void initialize();
            virtual void on_activate() override;
            virtual void on_deactivate() override;
            virtual void primary_timer_func() override;
            virtual void key_char_func(ALLEGRO_EVENT* ev=nullptr) override;
         };
      }
   }
}



