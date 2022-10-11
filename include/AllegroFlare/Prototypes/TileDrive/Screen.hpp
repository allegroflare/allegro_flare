#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Prototypes/TileDrive/TileDrive.hpp>
#include <AllegroFlare/SampleBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace TileDrive
      {
         class Screen : public AllegroFlare::Screens::Base
         {
         private:
            AllegroFlare::EventEmitter* event_emitter;
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::SampleBin* sample_bin;
            AllegroFlare::Prototypes::TileDrive::TileDrive tile_drive;
            bool initialized;

         protected:


         public:
            Screen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::SampleBin* sample_bin=nullptr);
            virtual ~Screen();

            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
            AllegroFlare::EventEmitter* get_event_emitter() const;
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::FontBin* get_font_bin() const;
            AllegroFlare::SampleBin* get_sample_bin() const;
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            void set_sample_bin(AllegroFlare::SampleBin* sample_bin=nullptr);
            void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
            void initialize();
            virtual void key_down_func(ALLEGRO_EVENT* event=nullptr) override;
            virtual void key_up_func(ALLEGRO_EVENT* event=nullptr) override;
         };
      }
   }
}



