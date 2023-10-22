#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/RollingCredits/RollingCredits.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/Version.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <cstddef>
#include <functional>
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
         float surface_width;
         float surface_height;
         float cached_calculated_height;
         AllegroFlare::Elements::RollingCredits::RollingCredits rolling_credits_component;
         std::function<void(AllegroFlare::Screens::Version*, void*)> on_exit_callback_func;
         void* on_exit_callback_func_user_data;
         std::string game_event_name_to_emit_on_exit;
         bool initialized;

      protected:


      public:
         Version(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr, float surface_width=1920, float surface_height=1080);
         virtual ~Version();

         void set_surface_width(float surface_width);
         void set_surface_height(float surface_height);
         void set_on_exit_callback_func(std::function<void(AllegroFlare::Screens::Version*, void*)> on_exit_callback_func);
         void set_on_exit_callback_func_user_data(void* on_exit_callback_func_user_data);
         void set_game_event_name_to_emit_on_exit(std::string game_event_name_to_emit_on_exit);
         float get_surface_width() const;
         float get_surface_height() const;
         float get_cached_calculated_height() const;
         std::function<void(AllegroFlare::Screens::Version*, void*)> get_on_exit_callback_func() const;
         void* get_on_exit_callback_func_user_data() const;
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
         static std::string truncate_to_n_characters(std::string str="", std::size_t num_characters=8);
      };
   }
}



