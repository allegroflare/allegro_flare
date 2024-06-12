

#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptRunner.hpp>

#include <AllegroFlare/Prototypes/FixedRoom2D/EventNames.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/CollectEvidence.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/CollectItem.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/EnterRoom.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/InitiateDialog.hpp>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


ScriptRunner::ScriptRunner(AllegroFlare::EventEmitter* event_emitter, std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* script_dictionary)
   : event_emitter(event_emitter)
   , script_dictionary(script_dictionary)
   , current_internally_running_script()
   , bool_eval_func(AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::default_bool_eval_func)
   , bool_eval_func_user_data(nullptr)
   , script_freshly_loaded_via_OPEN_SCRIPT(false)
   , paused_for_dialog_to_finish(false)
   , debug_output(false)
{
}


ScriptRunner::~ScriptRunner()
{
}


void ScriptRunner::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void ScriptRunner::set_script_dictionary(std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script>* script_dictionary)
{
   this->script_dictionary = script_dictionary;
}


void ScriptRunner::set_bool_eval_func(std::function<bool(std::string, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner*, void*)> bool_eval_func)
{
   this->bool_eval_func = bool_eval_func;
}


void ScriptRunner::set_bool_eval_func_user_data(void* bool_eval_func_user_data)
{
   this->bool_eval_func_user_data = bool_eval_func_user_data;
}


void ScriptRunner::set_script_freshly_loaded_via_OPEN_SCRIPT(bool script_freshly_loaded_via_OPEN_SCRIPT)
{
   this->script_freshly_loaded_via_OPEN_SCRIPT = script_freshly_loaded_via_OPEN_SCRIPT;
}


void ScriptRunner::set_paused_for_dialog_to_finish(bool paused_for_dialog_to_finish)
{
   this->paused_for_dialog_to_finish = paused_for_dialog_to_finish;
}


void ScriptRunner::set_debug_output(bool debug_output)
{
   this->debug_output = debug_output;
}


std::function<bool(std::string, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner*, void*)> ScriptRunner::get_bool_eval_func() const
{
   return bool_eval_func;
}


void* ScriptRunner::get_bool_eval_func_user_data() const
{
   return bool_eval_func_user_data;
}


bool ScriptRunner::get_script_freshly_loaded_via_OPEN_SCRIPT() const
{
   return script_freshly_loaded_via_OPEN_SCRIPT;
}


bool ScriptRunner::get_paused_for_dialog_to_finish() const
{
   return paused_for_dialog_to_finish;
}


bool ScriptRunner::get_debug_output() const
{
   return debug_output;
}


AllegroFlare::Prototypes::FixedRoom2D::Script &ScriptRunner::get_current_internally_running_script_ref()
{
   return current_internally_running_script;
}


bool ScriptRunner::load_script_by_dictionary_name(std::string script_dictionary_name)
{
   if (!(script_dictionary))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::load_script_by_dictionary_name]: error: guard \"script_dictionary\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::load_script_by_dictionary_name]: error: guard \"script_dictionary\" not met");
   }
   if (script_dictionary->count(script_dictionary_name) == 0)
   {
      std::stringstream available_script_names;
      available_script_names << "listing-available-item-names-not-yet-implemented";
      std::cout << "[.../FixedRoom/ScriptRunner::load_script_by_dictionary_name] error: could not load "
                << "item from the dictionary with the name \"" << script_dictionary_name << "\". It does not exist."
                << "The following names are listed in the dictionary: ["
                << available_script_names.str()
                << "]."
                << std::endl;
      return false;
   }

   std::vector<std::string> lines_from_dictionary_listing =
      script_dictionary->at(script_dictionary_name).get_lines();
   load_script_lines(lines_from_dictionary_listing);

   return true;
}

bool ScriptRunner::load_script_lines(std::vector<std::string> script_lines)
{
   current_internally_running_script = AllegroFlare::Prototypes::FixedRoom2D::Script(script_lines);
   current_internally_running_script.initialize();
   return true;
}

void ScriptRunner::play_or_resume()
{
   paused_for_dialog_to_finish = false;
   if (current_internally_running_script.get_finished()) return;

   bool continue_directly_to_next_script_line = false;
   int continue_count = 0;

   do
   {
      std::string script_line = current_internally_running_script.get_current_line_text();
      int script_current_line_num = current_internally_running_script.get_current_line_num();
      continue_directly_to_next_script_line = parse_and_run_line(script_line, script_current_line_num);

      if (continue_directly_to_next_script_line)
      {
         if (!get_script_freshly_loaded_via_OPEN_SCRIPT())
         {
            current_internally_running_script.goto_next_line();
         }
         else
         {
            set_script_freshly_loaded_via_OPEN_SCRIPT(false);
         }
         if (current_internally_running_script.get_finished()) break;
         continue_count++;
      }

      if (continue_count > 500)
      {
         continue_directly_to_next_script_line = false;
         std::cout << "ApplicationController::play_or_resume: continued unstopped playing more than "
                   << "500 script lines without a stop. Assuming error and halting to avoid infinite loop."
                   << " That line was \"" << script_line << "\" which is on line ["
                   << script_current_line_num << "]" << std::endl;
      }
   } while (continue_directly_to_next_script_line);
   return;
}

bool ScriptRunner::default_bool_eval_func(std::string expression, AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner* script_runner, void* user_data)
{
   std::stringstream error_message;
   error_message << "[AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::default_bool_eval_func] error: "
                 << "ScripRunner is running with its default_bool_eval_func assigned to the the bool_eval_func. "
                 << "You should create your own function (with the expected signature) and assign it to the "
                 << "bool_eval_func so it can be used to evaluate the conditional logic in the context of your "
                 << "game.";
   throw std::runtime_error(error_message.str());
   return true;
}

bool ScriptRunner::parse_and_run_line(std::string raw_script_line, int line_num, bool auto_assume_uncommanded_line_is_dialog)
{
   if (!(script_dictionary))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::parse_and_run_line]: error: guard \"script_dictionary\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::parse_and_run_line]: error: guard \"script_dictionary\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::parse_and_run_line]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::parse_and_run_line]: error: guard \"event_emitter\" not met");
   }
   std::string DIALOG = "DIALOG";
   std::string GOTO_MARKER = "GOTO_MARKER";
   std::string ENTER_ROOM = "ENTER_ROOM";
   std::string MARKER = "MARKER";
   std::string SIGNAL = "SIGNAL"; // outputs text to the terminal
   std::string COLLECT = "COLLECT";
   std::string COLLECT_EVIDENCE = "COLLECT_EVIDENCE";
   std::string OPEN_SCRIPT = "OPEN_SCRIPT";
   std::string PLAY_SOUND_EFFECT = "PLAY_SOUND_EFFECT";
   std::string PLAY_MUSIC_TRACK = "PLAY_MUSIC_TRACK";
   std::string IF = "IF";

   bool continue_directly_to_next_script_line = false;

   std::string script_line = trim(raw_script_line);
   std::pair<std::string, std::string> command_and_argument = parse_command_and_argument(script_line);
   std::string command = command_and_argument.first;
   std::string argument = command_and_argument.second;

   if (debug_output) std::cout << "EVALUATING(" << line_num << "): " << raw_script_line << std::endl;


   // skip blank lines
   if (command.empty() && argument.empty())
   {
      continue_directly_to_next_script_line = true;
      return continue_directly_to_next_script_line;
   }

   // autoset a line without a command as a DIALOG command
   if (auto_assume_uncommanded_line_is_dialog && command.empty()) command = DIALOG;

   // evaluate the different commands
   if (command == DIALOG)
   {
      std::vector<std::string> tokens = tokenize(argument);
      AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::InitiateDialog *initiate_dialog_event_data =
         new AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::InitiateDialog(tokens);

      current_internally_running_script.goto_next_line();
      paused_for_dialog_to_finish = true; // should this be in the event processing?

      emit_script_event(initiate_dialog_event_data);
   }
   else if (command == IF)
   {
      std::vector<std::string> tokens = tokenize(argument);
      if (!assert_token_count_eq(tokens, 3))
      {
         std::cout << "IF - expecting argument on line " << line_num << " to contain 3 arguments, "
                   << "(CONDITION_EXPRESSION | DO_IF_TRUE | DO_IF_FALSE), each expression separated "
                   << "by the BAR character ('|'), but it does not match this format." << std::endl;
         return false;
      }

      if (!bool_eval_func)
      {
         std::stringstream error_message;
         error_message << "AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner error: "
                    << "THING_THAT_HAPPENED";
         throw std::runtime_error(error_message.str());
      }

      std::string conditional_expression = tokens[0];
      bool expression_result = bool_eval_func(conditional_expression, this, bool_eval_func_user_data);

      if (expression_result)
      {
         // run "true statement" (probably a GOTO)
         std::string if_condition_true_expression = tokens[1];
         parse_and_run_line(if_condition_true_expression, line_num, auto_assume_uncommanded_line_is_dialog);
      }
      else
      {
         // run "false statement" (probably a GOTO)
         std::string if_condition_false_expression = tokens[2];
         parse_and_run_line(if_condition_false_expression, line_num, auto_assume_uncommanded_line_is_dialog);
      }

      continue_directly_to_next_script_line = true;
   }
   else if (command == ENTER_ROOM)
   {
      std::vector<std::string> tokens = tokenize(argument);
      if (!assert_token_count_eq(tokens, 1))
      {
         std::cout << "ENTER_ROOM - expecting 1 and only 1 argument on line " << line_num << std::endl;
         return false;
      }

      std::string room_name = tokens[0];

      AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::EnterRoom *enter_room_event_datas =
         new AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::EnterRoom(room_name);
      emit_script_event(enter_room_event_datas);
   }
   else if (command == OPEN_SCRIPT)
   {
      std::string script_to_load = argument;

      bool successful = load_script_by_dictionary_name(script_to_load);

      if (successful)
      {
         //Disabled:: if (current_dialog)
         //Disabled:: {
            //Disabled:: delete current_dialog;
            //Disabled:: current_dialog = nullptr;
         //Disabled::}
         // consider stopping music? I think not.  The opening script should start, stop, or change the music
         // if needed.  Also, if the same music is already playing from the previous script...
         // it wont' stop it then start it... instead it will keep playing seamlessly
         continue_directly_to_next_script_line = true;

         // setting this flag is required so that the advancer does not automatically move to the next
         // line after oening the new script file
         set_script_freshly_loaded_via_OPEN_SCRIPT(true);
      }
   }
   else if (command == SIGNAL)
   {
      std::cout << argument << std::endl;
      continue_directly_to_next_script_line = true;
   }
   else if (command == COLLECT)
   {
      int item_id = atoi(argument.c_str());
      std::string item_id_as_str = std::to_string(item_id);
      //std::tuple<std::string, std::string, std::string> item_definition = inventory_window->get_item_definition(item_id);
      //std::string item_name = std::get<0>(item_definition);
      //std::string item_bitmap_identifier = std::get<1>(item_definition);

      // add the item to the inventory
      //af_inventory->add_item(item_id); // TODO: remove this and handle it in the reception of the event. Note,
                                       //// the CollectItem event datas will need to be modified

      current_internally_running_script.goto_next_line();
      paused_for_dialog_to_finish = true; // should this be in the event processing?

      // construct the dialog
      //if (command == COLLECT_SILENTLY)
      //{
         //continue_directly_to_next_script_line = true;
      //}
      AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::CollectItem *event_data =
         new AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::CollectItem(item_id_as_str);
      emit_script_event(event_data);
   }
   else if (command == COLLECT_EVIDENCE)
   {
      std::string item_name = argument;

      current_internally_running_script.goto_next_line();
      paused_for_dialog_to_finish = true;

      AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::CollectEvidence *event_data =
         new AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::CollectEvidence(item_name);
      emit_script_event(event_data);
   }
   else if (command == MARKER)
   {
      continue_directly_to_next_script_line = true;
   }
   else if (command == GOTO_MARKER)
   {
      bool successful = current_internally_running_script.goto_marker(argument);
      if (!successful)
      {
         std::stringstream error_message;
         error_message << "[AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner] error: "
                       << "Attempted to GOTO_MARKER a marker named \"" << argument << "\" "
                       << "but that marker does not exist. This is from line ["
                       << line_num << "], which is \"" << script_line << "\"" << std::endl;
         throw std::runtime_error(error_message.str());
      }
      continue_directly_to_next_script_line = true;
   }
   else if (command == PLAY_SOUND_EFFECT)
   {
      std::vector<std::string> tokens = tokenize(argument);
      if (!assert_token_count_eq(tokens, 1))
      {
         std::cout << "PLAY_SOUND_EFFECT - expecting 1 and only 1 argument on line " << line_num << std::endl;
         return false;
      }

      std::string sound_effect_name_to_play = tokens[0];

      event_emitter->emit_play_sound_effect_event(sound_effect_name_to_play);

      continue_directly_to_next_script_line = true;
   }
   else if (command == PLAY_MUSIC_TRACK)
   {
      std::vector<std::string> tokens = tokenize(argument);
      if (!assert_token_count_eq(tokens, 1))
      {
         std::cout << "PLAY_MUSIC_TRACK - expecting 1 and only 1 argument on line " << line_num << std::endl;
         return false;
      }

      std::string music_track_name_to_play = tokens[0];

      event_emitter->emit_play_music_track_event(music_track_name_to_play);

      continue_directly_to_next_script_line = true;
   }
   else
   {
      std::cout << "[AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::parse_and_run_line]: WARNING: "
                << "Unrecognized command \"" << command << "\"" << std::endl;
      continue_directly_to_next_script_line = true;
   }

   return continue_directly_to_next_script_line;
}

std::pair<std::string, std::string> ScriptRunner::parse_command_and_argument(std::string script_line)
{
   std::pair<std::string, std::string> result{"", ""};
   std::string DELIMETER = ": ";

   std::size_t pos = script_line.find(DELIMETER);

   if (pos == std::string::npos)
   {
      result.first = "";
      std::string _intermed = script_line;
      result.second = trim(_intermed);
   }
   else
   {
      std::string command_fragment_unsanitized = script_line.substr(0, pos);

      // TODO validate format of command (all caps, underscore, no spaces)
      // here

      std::string _intermed = command_fragment_unsanitized;
      result.first = trim(_intermed);
      std::string _intermed2 = script_line.substr(pos+DELIMETER.size());
      result.second = trim(_intermed2);
   }

   return result;
}

void ScriptRunner::emit_script_event(AllegroFlare::GameEventDatas::Base* event_data)
{
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::emit_script_event]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner::emit_script_event]: error: guard \"event_emitter\" not met");
   }
   AllegroFlare::GameEvent game_event(
      AllegroFlare::Prototypes::FixedRoom2D::EventNames::SCRIPT_EVENT_NAME,
      event_data
   );

   event_emitter->emit_game_event(game_event);
   return;
}

std::vector<std::string> ScriptRunner::split(std::string string, char delimiter)
{
   std::vector<std::string> elems;
   auto result = std::back_inserter(elems);
   std::stringstream ss(string);
   std::string item;
   while (std::getline(ss, item, delimiter)) { *(result++) = item; }
   return elems;
}

std::vector<std::string> ScriptRunner::tokenize(std::string str, char delim)
{
   std::vector<std::string> tokens = split(str, delim);
   for (auto &token : tokens) token = trim(token);
   return tokens;
}

bool ScriptRunner::assert_min_token_count(std::vector<std::string> tokens, int min)
{
   return (tokens.size() >= min);
}

bool ScriptRunner::assert_token_count_eq(std::vector<std::string> tokens, int value)
{
   return (tokens.size() == value);
}

bool ScriptRunner::assert_odd_token_count(std::vector<std::string> tokens, int min)
{
   return (tokens.size() % 2);
}

std::string ScriptRunner::trim(std::string s)
{
   // ltrim
   s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c);}));
   // rtrim
   s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) {return !std::isspace(c);}).base(), s.end());
   return s;
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


