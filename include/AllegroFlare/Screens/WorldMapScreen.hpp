#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Screens
   {
      class WorldMapScreen : public AllegroFlare::Screens::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Screens/WorldMapScreen";

      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         bool initialized;

      protected:


      public:
         WorldMapScreen(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr);
         virtual ~WorldMapScreen();

         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void initialize();
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         void update();
         void render();
         virtual void primary_timer_func() override;
         virtual void virtual_control_button_up_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_axis_change_func(ALLEGRO_EVENT* ev=nullptr) override;
      };
   }
}



