#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/WorldMapViewer.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/WorldMapScreen.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <AllegroFlare/WorldMaps/Maps/Basic.hpp>
#include <allegro5/allegro.h>
#include <functional>


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
         AllegroFlare::Elements::WorldMapViewer map_viewer;
         std::function<void(AllegroFlare::Screens::WorldMapScreen*, void*)> on_exit_callback_func;
         void* on_exit_callback_func_user_data;
         bool initialized;

      protected:


      public:
         WorldMapScreen(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr);
         virtual ~WorldMapScreen();

         void set_on_exit_callback_func(std::function<void(AllegroFlare::Screens::WorldMapScreen*, void*)> on_exit_callback_func);
         void set_on_exit_callback_func_user_data(void* on_exit_callback_func_user_data);
         std::function<void(AllegroFlare::Screens::WorldMapScreen*, void*)> get_on_exit_callback_func() const;
         void* get_on_exit_callback_func_user_data() const;
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void initialize();
         void set_map(AllegroFlare::WorldMaps::Maps::Basic* map=nullptr);
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         virtual void primary_timer_func() override;
         virtual void virtual_control_button_up_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         virtual void virtual_control_axis_change_func(ALLEGRO_EVENT* ev=nullptr) override;
      };
   }
}



