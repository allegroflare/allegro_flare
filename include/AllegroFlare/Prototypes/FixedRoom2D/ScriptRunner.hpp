#pragma once


#include <AllegroFlare/AudioController.hpp>
#include <AllegroFlare/Elements/Inventory.hpp>
#include <AllegroFlare/Inventory.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Script.hpp>
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
            AllegroFlare::Prototypes::FixedRoom2D::Script* script;
            AllegroFlare::Inventory* flags;
            bool script_freshly_loaded_via_OPEN_SCRIPT;

         public:
            ScriptRunner();
            ~ScriptRunner();

            void set_script_freshly_loaded_via_OPEN_SCRIPT(bool script_freshly_loaded_via_OPEN_SCRIPT);
            bool get_script_freshly_loaded_via_OPEN_SCRIPT();
            bool parse_and_run_line(std::string raw_script_line="[empty-script-line]", int line_num=0);
            static std::pair<std::string, std::string> parse_command_and_argument(std::string script_line={});
            void play_current_script_line();
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



