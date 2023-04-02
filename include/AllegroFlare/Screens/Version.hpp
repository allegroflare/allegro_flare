#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Screens
   {
      class Version : public AllegroFlare::Screens::Base
      {
      public:
         static constexpr char* DEFAULT_EVENT_NAME_ON_EXIT = (char*)"exit_achievements_screen";
         static constexpr char* TYPE = (char*)"AllegroFlare/Screens/Version";

      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::ModelBin* model_bin;
         std::string game_event_name_to_emit_on_exit;
         bool initialized;

      protected:


      public:
         Version(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr, std::string game_event_name_to_emit_on_exit=DEFAULT_EVENT_NAME_ON_EXIT);
         virtual ~Version();

         void set_game_event_name_to_emit_on_exit(std::string game_event_name_to_emit_on_exit);
         std::string get_game_event_name_to_emit_on_exit() const;
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
         void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void set_model_bin(AllegroFlare::ModelBin* model_bin=nullptr);
         void initialize();
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         void update();
         void render();
         virtual void primary_timer_func() override;
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
      };
   }
}



