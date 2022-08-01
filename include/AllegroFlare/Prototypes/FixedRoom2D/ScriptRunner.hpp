#pragma once


#include <AllegroFlare/AudioController.hpp>
#include <AllegroFlare/Elements/Inventory.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <AllegroFlare/Inventory.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Script.hpp>
#include <map>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         class ScriptRunner
         {
         private:
            AllegroFlare::AudioController* audio_controller;
            AllegroFlare::Inventory* af_inventory;
            AllegroFlare::Elements::Inventory* inventory_window;
            AllegroFlare::EventEmitter* event_emitter;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* script_dictionary;
            AllegroFlare::Inventory* flags;
            AllegroFlare::Prototypes::FixedRoom2D::Script current_script;
            bool script_freshly_loaded_via_OPEN_SCRIPT;

         public:
            ScriptRunner();
            ~ScriptRunner();

            void set_audio_controller(AllegroFlare::AudioController* audio_controller);
            void set_af_inventory(AllegroFlare::Inventory* af_inventory);
            void set_inventory_window(AllegroFlare::Elements::Inventory* inventory_window);
            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
            void set_script_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* script_dictionary);
            void set_flags(AllegroFlare::Inventory* flags);
            void set_script_freshly_loaded_via_OPEN_SCRIPT(bool script_freshly_loaded_via_OPEN_SCRIPT);
            bool get_script_freshly_loaded_via_OPEN_SCRIPT();
            bool load_script_by_dictionary_name(std::string script_dictionary_name="[unset-script_dictionary_name]");
            bool load_current_script_lines(std::vector<std::string> script_lines={});
            void play_current_script_line();
            bool parse_and_run_line(std::string raw_script_line="[empty-script-line]", int line_num=0, bool auto_assume_uncommanded_line_is_dialog=true);
            static std::pair<std::string, std::string> parse_command_and_argument(std::string script_line={});
            void emit_script_event(AllegroFlare::GameEventDatas::Base* event_data=nullptr);
            static std::vector<std::string> split(std::string string="", char delimiter=' ');
            static std::vector<std::string> tokenize(std::string str="", char delim='|');
            static bool assert_min_token_count(std::vector<std::string> tokens={}, int min=0);
            static bool assert_token_count_eq(std::vector<std::string> tokens={}, int value=0);
            static bool assert_odd_token_count(std::vector<std::string> tokens={}, int min=0);
            static std::string trim(std::string s="");
         };
      }
   }
}



