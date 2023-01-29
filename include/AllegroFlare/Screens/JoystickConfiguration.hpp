#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <cstddef>


namespace AllegroFlare
{
   namespace Screens
   {
      class JoystickConfiguration : public AllegroFlare::Screens::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Screens/JoystickConfiguration";

      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         std::size_t surface_width;
         std::size_t surface_height;
         bool initialized;

      protected:


      public:
         JoystickConfiguration(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::size_t surface_width=1920, std::size_t surface_height=1090);
         virtual ~JoystickConfiguration();

         void set_surface_width(std::size_t surface_width);
         void set_surface_height(std::size_t surface_height);
         std::size_t get_surface_width() const;
         std::size_t get_surface_height() const;
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void initialize();
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         void update();
         void render();
         virtual void primary_timer_func() override;
      };
   }
}



