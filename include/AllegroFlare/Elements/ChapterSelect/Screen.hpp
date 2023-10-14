#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/Backgrounds/Base.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/Base.hpp>
#include <AllegroFlare/Elements/ChapterSelect/ChapterSelect.hpp>
#include <AllegroFlare/Elements/ChapterSelect/Screen.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro.h>
#include <functional>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace ChapterSelect
      {
         class Screen : public AllegroFlare::Screens::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/ChapterSelect/Screen";

         private:
            AllegroFlare::EventEmitter* event_emitter;
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::Elements::ChapterSelect::ChapterSelect chapter_select_element;
            AllegroFlare::Elements::Backgrounds::Base* background;
            std::function<void(AllegroFlare::Elements::ChapterSelect::Screen*, void*)> on_menu_choice_callback_func;
            void* on_menu_choice_callback_func_user_data;
            std::function<void(AllegroFlare::Elements::ChapterSelect::Screen*, void*)> on_exit_screen_callback_func;
            void* on_exit_screen_callback_func_user_data;
            bool initialized;
            void select_menu_option();

         protected:


         public:
            Screen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr);
            virtual ~Screen();

            void set_background(AllegroFlare::Elements::Backgrounds::Base* background);
            void set_on_menu_choice_callback_func(std::function<void(AllegroFlare::Elements::ChapterSelect::Screen*, void*)> on_menu_choice_callback_func);
            void set_on_menu_choice_callback_func_user_data(void* on_menu_choice_callback_func_user_data);
            void set_on_exit_screen_callback_func(std::function<void(AllegroFlare::Elements::ChapterSelect::Screen*, void*)> on_exit_screen_callback_func);
            void set_on_exit_screen_callback_func_user_data(void* on_exit_screen_callback_func_user_data);
            AllegroFlare::Elements::Backgrounds::Base* get_background() const;
            std::function<void(AllegroFlare::Elements::ChapterSelect::Screen*, void*)> get_on_menu_choice_callback_func() const;
            void* get_on_menu_choice_callback_func_user_data() const;
            std::function<void(AllegroFlare::Elements::ChapterSelect::Screen*, void*)> get_on_exit_screen_callback_func() const;
            void* get_on_exit_screen_callback_func_user_data() const;
            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
            void initialize();
            void set_elements(std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> elements={});
            virtual void on_activate() override;
            virtual void on_deactivate() override;
            void update();
            void render();
            void activate_menu_option();
            void exit_screen();
            virtual void primary_timer_func() override;
            virtual void virtual_control_button_up_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
            virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
            virtual void virtual_control_axis_change_func(ALLEGRO_EVENT* ev=nullptr) override;
            bool is_processing_user_input();
         };
      }
   }
}



