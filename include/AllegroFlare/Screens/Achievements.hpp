#pragma once


#include <AllegroFlare/Achievements.hpp>
#include <AllegroFlare/Elements/AchievementsList.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Achievements.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <functional>
#include <string>
#include <tuple>
#include <vector>


namespace AllegroFlare
{
   namespace Screens
   {
      class Achievements : public AllegroFlare::Screens::Base
      {
      public:
         static constexpr char* DEFAULT_EVENT_NAME_ON_EXIT = (char*)"exit_achievements_screen";

      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::Achievements* achievements;
         float scrollbar_dest_position;
         AllegroFlare::Elements::AchievementsList achievements_list;
         std::function<void(AllegroFlare::Screens::Achievements*, void*)> on_exit_callback_func;
         void* on_exit_callback_func_user_data;
         std::string game_event_name_to_emit_on_exit;
         bool initialized;
         void update();
         void call_on_exit_callback();
         void move_scrollbar_position_to(float position=0.0f);
         void move_scrollbar_position_up();
         void move_scrollbar_position_down();
         void limit_scrollbar_dest_position();
         void emit_event_to_set_input_hints();

      protected:


      public:
         Achievements(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::Achievements* achievements=nullptr, float scrollbar_dest_position=0.0f, std::string game_event_name_to_emit_on_exit=DEFAULT_EVENT_NAME_ON_EXIT);
         virtual ~Achievements();

         void set_achievements(AllegroFlare::Achievements* achievements);
         void set_on_exit_callback_func(std::function<void(AllegroFlare::Screens::Achievements*, void*)> on_exit_callback_func);
         void set_on_exit_callback_func_user_data(void* on_exit_callback_func_user_data);
         void set_game_event_name_to_emit_on_exit(std::string game_event_name_to_emit_on_exit);
         std::function<void(AllegroFlare::Screens::Achievements*, void*)> get_on_exit_callback_func() const;
         void* get_on_exit_callback_func_user_data() const;
         std::string get_game_event_name_to_emit_on_exit() const;
         AllegroFlare::Elements::AchievementsList &get_achievements_list_ref();
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
         void refresh_achievements_list();
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         void initialize();
         virtual void primary_timer_func() override;
         void exit();
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
         void render();
         void set_placeholder_achievements();
         std::vector<std::tuple<std::string, std::string, std::string>> build_achievements();
         bool infer_scrollbar_is_showing();
      };
   }
}



