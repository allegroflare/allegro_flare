#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Script.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptRunner.hpp>
#include <functional>
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
            AllegroFlare::EventEmitter* event_emitter;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* script_dictionary;
            AllegroFlare::Prototypes::FixedRoom2D::Script current_internally_running_script;
            std::function<bool(std::string, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner*, void*)> bool_eval_func;
            void* bool_eval_func_user_data;
            bool script_freshly_loaded_via_OPEN_SCRIPT;
            bool paused_for_dialog_to_finish;
            bool debug_output;
            void emit_script_event(AllegroFlare::GameEventDatas::Base* event_data=nullptr);
            static std::vector<std::string> split(std::string string="", char delimiter=' ');
            static std::string trim(std::string s="");

         protected:


         public:
            ScriptRunner(AllegroFlare::EventEmitter* event_emitter=nullptr, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* script_dictionary=nullptr);
            ~ScriptRunner();

            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
            void set_script_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* script_dictionary);
            void set_bool_eval_func(std::function<bool(std::string, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner*, void*)> bool_eval_func);
            void set_bool_eval_func_user_data(void* bool_eval_func_user_data);
            void set_script_freshly_loaded_via_OPEN_SCRIPT(bool script_freshly_loaded_via_OPEN_SCRIPT);
            void set_paused_for_dialog_to_finish(bool paused_for_dialog_to_finish);
            void set_debug_output(bool debug_output);
            std::function<bool(std::string, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner*, void*)> get_bool_eval_func() const;
            void* get_bool_eval_func_user_data() const;
            bool get_script_freshly_loaded_via_OPEN_SCRIPT() const;
            bool get_paused_for_dialog_to_finish() const;
            bool get_debug_output() const;
            AllegroFlare::Prototypes::FixedRoom2D::Script &get_current_internally_running_script_ref();
            bool load_script_by_dictionary_name(std::string script_dictionary_name="[unset-script_dictionary_name]");
            bool load_script_lines(std::vector<std::string> script_lines={});
            void play_or_resume();
            static bool default_bool_eval_func(std::string expression="[unset-expression]", AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner* script_runner=nullptr, void* user_data=nullptr);
            bool parse_and_run_line(std::string raw_script_line="[empty-script-line]", int line_num=0, bool auto_assume_uncommanded_line_is_dialog=true);
            static std::pair<std::string, std::string> parse_command_and_argument(std::string script_line={});
            static std::vector<std::string> tokenize(std::string str="", char delim='|');
            static bool assert_min_token_count(std::vector<std::string> tokens={}, int min=0);
            static bool assert_token_count_eq(std::vector<std::string> tokens={}, int value=0);
            static bool assert_odd_token_count(std::vector<std::string> tokens={}, int min=0);
         };
      }
   }
}



