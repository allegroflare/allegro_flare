#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro_font.h>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Screens
   {
      class GameOverScreen : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::FontBin* font_bin;
         std::string title_text;
         std::vector<std::pair<std::string, std::string>> menu_options;
         int cursor_position;
         std::string title_font_name;
         int title_font_size;
         std::string menu_font_name;
         int menu_font_size;
         static std::string DEFAULT_TITLE_TEXT;
         static std::vector<std::pair<std::string, std::string>> DEFAULT_MENU_OPTIONS;
         bool initialized;
         void move_cursor_up();
         void move_cursor_down();
         void select_menu_option();
         std::string infer_current_menu_option_value();
         std::string infer_current_menu_option_label();
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_FONT* obtain_menu_font();

      protected:


      public:
         GameOverScreen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::string title_text=DEFAULT_TITLE_TEXT, std::string title_font_name="Inter-Medium.ttf", int title_font_size=-80, std::string menu_font_name="Inter-Medium.ttf", int menu_font_size=-48);
         virtual ~GameOverScreen();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_title_text(std::string title_text);
         void set_title_font_name(std::string title_font_name);
         void set_title_font_size(int title_font_size);
         void set_menu_font_name(std::string menu_font_name);
         void set_menu_font_size(int menu_font_size);
         std::string get_title_font_name() const;
         int get_title_font_size() const;
         std::string get_menu_font_name() const;
         int get_menu_font_size() const;
         bool get_initialized() const;
         void set_menu_options(std::vector<std::pair<std::string, std::string>> menu_options={});
         void initialize();
         virtual void primary_timer_func() override;
         void render();
         void draw_primary_text();
         void draw_menu();
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
      };
   }
}



