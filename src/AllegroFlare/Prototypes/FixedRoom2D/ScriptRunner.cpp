

#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptRunner.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <iostream>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


ScriptRunner::ScriptRunner()
   : audio_controller(nullptr)
   , af_inventory(nullptr)
   , inventory_window(nullptr)
   , script_dictionary(nullptr)
   , current_script()
   , flags(nullptr)
   , script_freshly_loaded_via_OPEN_SCRIPT(false)
{
}


ScriptRunner::~ScriptRunner()
{
}


void ScriptRunner::set_script_freshly_loaded_via_OPEN_SCRIPT(bool script_freshly_loaded_via_OPEN_SCRIPT)
{
   this->script_freshly_loaded_via_OPEN_SCRIPT = script_freshly_loaded_via_OPEN_SCRIPT;
}


bool ScriptRunner::get_script_freshly_loaded_via_OPEN_SCRIPT()
{
   return script_freshly_loaded_via_OPEN_SCRIPT;
}


bool ScriptRunner::load_script_by_dictionary_name(std::string script_dictionary_name)
{
   if (!(script_dictionary))
      {
         std::stringstream error_message;
         error_message << "ScriptRunner" << "::" << "load_script_by_dictionary_name" << ": error: " << "guard \"script_dictionary\" not met";
         throw std::runtime_error(error_message.str());
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
   load_current_script_lines(lines_from_dictionary_listing);

   return true;
}

bool ScriptRunner::load_current_script_lines(std::vector<std::string> script_lines)
{
   current_script = AllegroFlare::Prototypes::FixedRoom2D::Script(script_lines);
   current_script.initialize();
   return true;
}

bool ScriptRunner::parse_and_run_line(std::string raw_script_line, int line_num)
{
   if (!(audio_controller))
      {
         std::stringstream error_message;
         error_message << "ScriptRunner" << "::" << "parse_and_run_line" << ": error: " << "guard \"audio_controller\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(af_inventory))
      {
         std::stringstream error_message;
         error_message << "ScriptRunner" << "::" << "parse_and_run_line" << ": error: " << "guard \"af_inventory\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(flags))
      {
         std::stringstream error_message;
         error_message << "ScriptRunner" << "::" << "parse_and_run_line" << ": error: " << "guard \"flags\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(inventory_window))
      {
         std::stringstream error_message;
         error_message << "ScriptRunner" << "::" << "parse_and_run_line" << ": error: " << "guard \"inventory_window\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(script_dictionary))
      {
         std::stringstream error_message;
         error_message << "ScriptRunner" << "::" << "parse_and_run_line" << ": error: " << "guard \"script_dictionary\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::string DIALOG = "DIALOG";
   std::string GOTO_MARKER = "GOTO_MARKER";
   std::string CHOICE = "CHOICE";
   std::string PLAY_MUSIC = "PLAY_MUSIC";
   std::string MARKER = "MARKER";
   std::string SIGNAL = "SIGNAL"; // outputs text to the terminal
   std::string SET_CHARACTER_ART = "SET_CHARACTER_ART";
   std::string SET_CHARACTER_FRAMING = "SET_CHARACTER_FRAMING";
   std::string BEAT = "BEAT";
   std::string WAIT = "WAIT";
   std::string COLLECT = "COLLECT";
   std::string COLLECT_SILENTLY = "COLLECT_SILENTLY";
   std::string IF_IN_INVENTORY = "IF_IN_INVENTORY";
   std::string ADD_FLAG = "ADD_FLAG";
   std::string IF_FLAG = "IF_FLAG";
   std::string PHONE = "PHONE";
   std::string OPEN_SCRIPT = "OPEN_SCRIPT";
   std::string SET_BACKGROUND = "SET_BACKGROUND";
   std::string SET_TITLE = "SET_TITLE";
   //Disabled:: std::string CLEAR_DIALOGS = "CLEAR_DIALOGS";

   bool continue_directly_to_next_script_line = false;
   //Disabled:: Krampus21::DialogBoxes::Base* created_dialog = nullptr;
   std::string script_line = trim(raw_script_line);

   std::pair<std::string, std::string> command_and_argument = parse_command_and_argument(script_line);
   std::string command = command_and_argument.first;
   std::string argument = command_and_argument.second;

   if (command.empty() || command == DIALOG)
   {
      if (script_line.empty())
      {
         continue_directly_to_next_script_line = true;
      }
      else
      {
         //Disabled:: created_dialog = dialog_factory.create_basic_dialog(std::vector<std::string>{script_line});
      }
   }
   else if (command == PLAY_MUSIC)
   {
      // parse tokens
      std::vector<std::string> tokens = tokenize(argument);

      if (!assert_min_token_count(tokens, 1))
      {
         std::cout << "tokens must be at least 1 on line " << line_num << std::endl;
         return false;
      }
      std::string music_filename_identifier = tokens[0]; //"etherial-ambience-01.wav";

      audio_controller->play_music_track_by_identifier(music_filename_identifier);

      continue_directly_to_next_script_line = true;
   }
   else if (command == SET_TITLE)
   {
      // parse tokens
      std::vector<std::string> tokens = tokenize(argument);

      if (!assert_min_token_count(tokens, 1))
      {
         std::cout << "tokens must be at least 1 on line " << line_num << std::endl;
         return false;
      }

      std::string text = tokens[0];
      //Disabled:: created_dialog = dialog_factory.create_title_text_dialog(text);

      continue_directly_to_next_script_line = true;
   }
   //Disabled:: else if (command == CLEAR_DIALOGS)
   //{
      //Disabled:: if (current_dialog)
      //Disabled::{
         //Disabled:: if (current_dialog) delete current_dialog;
         //Disabled:: current_dialog = nullptr;
      //Disabled:: }

      //continue_directly_to_next_script_line = true;
   //}
   else if (command == SET_BACKGROUND)
   {
      // parse tokens
      std::vector<std::string> tokens = tokenize(argument);

      if (!assert_min_token_count(tokens, 1))
      {
         std::cout << "tokens must be at least 1 on line " << line_num << std::endl;
         return false;
      }

      //Disabled:: Krampus21::Backgrounds::Base* created_background = nullptr;
      //Disabled:: Krampus21::BackgroundFactory background_factory(obtain_bitmap_bin());

      if (tokens[0] == "none")
      {
         //Disabled:: if (current_background) delete current_background;
         //Disabled:: current_background = nullptr;
      }
      else if (tokens[0] == "monoplex")
      {
         // Disabled:: created_background = background_factory.create_monoplex();
      }
      else
      {
         std::string background_bitmap_filename_identifier = tokens[0];
         // Disabled:: created_background = background_factory.create_image(background_bitmap_filename_identifier);

         // TODO create a simple background with a good-ole image
      }

      //Disabled:: if (created_background)
      {
         //Disabled:: if (current_background) delete current_background;
         //Disabled:: current_background = created_background;
      }

      continue_directly_to_next_script_line = true;
   }
   else if (command == OPEN_SCRIPT)
   {
      //std::string script_auto_prefix = "scripts/";
      std::string script_auto_prefix = "";
      std::string script_to_load = script_auto_prefix + argument;

      //Disabled:: bool successful = load_script(script_to_load);
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
   else if (command == IF_IN_INVENTORY)
   {
      // tokenize
      std::vector<std::string> tokens = tokenize(argument);

      // validate
      // expect exactly 2 params
      if (!assert_token_count_eq(tokens, 2))
      {
         std::cout << "tokens must be equal to 2 on line " << line_num << std::endl;
         return false;
      }

      // get arguments
      int item_id = atoi(tokens[0].c_str());
      std::string consequence = tokens[1];

      // bonus:
      std::pair<std::string, std::string> consequence_command_and_argument = parse_command_and_argument(consequence);
      std::string consequence_command = consequence_command_and_argument.first;
      std::string consequence_argument = consequence_command_and_argument.second;
      // eval only GOTO
      if (consequence_command != "GOTO_MARKER")
      {
         std::cout << "IF_IN_INVENTORY consequence argument must be a GOTO_MARKER (line ["
                   << line_num
                   << "])"
                   << std::endl;
      }
      // TODO: eval MARKER target exists

      if (af_inventory->has_item(item_id))
      {
         parse_and_run_line(consequence, line_num);
      }
      continue_directly_to_next_script_line = true;
   }
   else if (command == IF_FLAG)
   {
      // tokenize
      std::vector<std::string> tokens = tokenize(argument);

      // validate
      // expect exactly 2 params
      if (!assert_token_count_eq(tokens, 2))
      {
         std::cout << "tokens must be equal to 2 on line " << line_num << std::endl;
         return false;
      }

      // get arguments
      int flag_id = atoi(tokens[0].c_str());
      std::string consequence = tokens[1];

      // bonus:
      std::pair<std::string, std::string> consequence_command_and_argument = parse_command_and_argument(consequence);
      std::string consequence_command = consequence_command_and_argument.first;
      std::string consequence_argument = consequence_command_and_argument.second;
      // eval only GOTO
      if (consequence_command != "GOTO_MARKER")
      {
         std::cout << "IF_IN_INVENTORY consequence argument must be a GOTO_MARKER (line ["
                   << line_num
                   << "])"
                   << std::endl;
      }
      // TODO: eval MARKER target exists

      if (flags->has_item(flag_id))
      {
         parse_and_run_line(consequence, line_num);
      }
      continue_directly_to_next_script_line = true;
   }
   else if (command == SIGNAL)
   {
      std::cout << argument << std::endl;
      continue_directly_to_next_script_line = true;
   }
   else if (command == CHOICE)
   {
      std::string choice_prompt = "[coice-prompt-text-not-extracted]";
      std::vector<std::pair<std::string, std::string>> choice_options = {};

      // tokenize
      std::vector<std::string> tokens = tokenize(argument);

      // validate
      // expect at least 3 tokens
      assert_min_token_count(tokens, 3);
      // expect an odd number of tokens
      assert_odd_token_count(tokens);

      // first token is the prompt
      choice_prompt = tokens[0];
      // next consecutive tokens are (choice_text, choice_value) pairs
      for (unsigned i=2; i<tokens.size(); i+=2)
      {
         if (tokens[i-1].empty() || tokens[i].empty())
         {
            std::cout << "WARNING: CHOICE argument on line [" << line_num << "] contains arguments that are empty. "
                      << "The full argument is \"" << argument << "\"" << std::endl;
         }
         choice_options.push_back({ tokens[i-1], tokens[i] });
      }

      //choice_options = { { "Boobar", "boobruhh" }, { "Zoozaz", "zazzle" } };
      //Disabled:: created_dialog = dialog_factory.create_choice_dialog(choice_prompt, choice_options);
   }
   else if (command == WAIT)
   {
      // this will prevent the next line from executing until after a delay
      int num_sec_to_wait = 2.0;
      if (!argument.empty())
      {
         num_sec_to_wait = atoi(argument.c_str());
      }

      //Disabled:: on_hold_for_wait_delay = true;
      //Disabled:: wait_delay_countdown_sec = num_sec_to_wait;
   }
   else if (command == BEAT)
   {
      // essentially, this will add a pause or "beat" to the story.
      //std::string identifier = "etherial-ambience-01.wav";
      //audio_controller.play_music_track_by_identifier(identifier);
      //continue_directly_to_next_script_line = true;
      //Disabled:: if (current_dialog)
      //Disabled::{
         //Disabled:: delete current_dialog;
         //Disabled:: current_dialog = nullptr;
      //Disabled::}
   }
   else if (command == COLLECT_SILENTLY || command == COLLECT)
   {
      int item_id = atoi(argument.c_str());
      std::tuple<std::string, std::string, std::string> item_definition = inventory_window->get_item_definition(item_id);
      std::string item_name = std::get<0>(item_definition);
      std::string item_bitmap_identifier = std::get<1>(item_definition);

      // add the item to the inventory
      af_inventory->add_item(item_id);

      // cout for debugging
      std::cout << "You got an item " << argument << std::endl;

      // construct the dialog
      if (command == COLLECT_SILENTLY)
      {
         continue_directly_to_next_script_line = true;
      }
      else if (command == COLLECT)
      {
         //Disabled:: Krampus21::DialogBoxes::YouGotAnItem* created_you_got_an_item_dialog_box =
            //Disabled:: dialog_factory.create_you_got_an_item_dialog(item_id, item_name, item_bitmap_identifier);
         //Disabled:: created_dialog = created_you_got_an_item_dialog_box;
      }
   }
   else if (command == ADD_FLAG)
   {
      int flag_id = atoi(argument.c_str());

      // add the item to the inventory
      flags->add_item(flag_id);

      // cout for debugging
      std::cout << "A flag was set on the flag num " << argument << std::endl;

      continue_directly_to_next_script_line = true;
   }
   else if (command == SET_CHARACTER_ART)
   {
      //Disabled:: character.set_sprite_record_identifier(argument);
      //Disabled:: continue_directly_to_next_script_line = true;
   }
   else if (command == SET_CHARACTER_FRAMING)
   {
      //Disabled:: if (argument == "wide") character.frame_wide();
      //Disabled:: else if (argument == "mid") character.frame_mid();
      //Disabled:: else if (argument == "close-up") character.frame_closeup();
      //Disabled:: else
      //Disabled:: {
         //Disabled:: std::cout << "WARNING: Unrecognized argument \"" << argument << "\" "
                   //Disabled:: << "for command \"" << command << "\"" << std::endl;
      //Disabled:: }
      continue_directly_to_next_script_line = true;
   }
   else if (command == MARKER)
   {
      continue_directly_to_next_script_line = true;
   }
   else if (command == GOTO_MARKER)
   {
      bool successful = current_script.goto_marker(argument);
      if (!successful)
      {
         std::cout << "WARNING: Attempted to GOTO_MARKER a marker named \"" << argument << "\" "
                   << "but that marker does not exist. This is from line ["
                   << line_num << "], which is \"" << script_line << "\"" << std::endl;
      }
      continue_directly_to_next_script_line = true;
   }
   else
   {
      std::cout << "WARNING: Unrecognized command \"" << command << "\"" << std::endl;
      continue_directly_to_next_script_line = true;
   }

   //Disabled:: if (created_dialog)
   //Disabled:: {
      //Disabled:: if (current_dialog) delete current_dialog;
      //Disabled:: current_dialog = created_dialog;
   //Disabled:: }

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
      //result.second = Blast::String::Trimmer(script_line).trim();
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
      //result.first = Blast::String::Trimmer(command_fragment_unsanitized).trim();
      //result.second = Blast::String::Trimmer(script_line.substr(pos+DELIMETER.size())).trim();
   }

   return result;
}

void ScriptRunner::play_current_script_line()
{
   bool continue_directly_to_next_script_line = false;
   int continue_count = 0;

   do
   {
      std::string script_line = current_script.get_current_line_text();
      int script_current_line_num = current_script.get_current_line_num();
      continue_directly_to_next_script_line = parse_and_run_line(script_line, script_current_line_num);

      if (continue_directly_to_next_script_line)
      {
         if (!get_script_freshly_loaded_via_OPEN_SCRIPT())
         {
            current_script.goto_next_line();
         }
         else
         {
            set_script_freshly_loaded_via_OPEN_SCRIPT(false);
         }
         if (current_script.get_finished()) break;
         continue_count++;
      }
      if (continue_count > 500)
      {
         continue_directly_to_next_script_line = false;
         std::cout << "ApplicationController::play_current_script_line: continued unstopped playing more than "
                   << "500 script lines without a stop. Assuming error and halting to avoid infinite loop."
                   << " That line was \"" << script_line << "\" which is on line ["
                   << script_current_line_num << "]" << std::endl;
      }
   } while (continue_directly_to_next_script_line);
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


