



// // // // //
// This is the run script part of the file
// // // // //

#include <string>
#include <iostream>
#include <stdio.h>
#include <string>

#include <AllegroFlare/UsefulPHP.hpp>




struct RubyScriptResult
{
   bool exception_caught; // currently does not function
   std::string filename;
   std::string output;
};

// from http://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c
// use "_popen" and "_pclose" for windows
// and "popen" and "pclose" for other systems

#ifdef _WIN32
#define popen _popen
#define poclose _pclose
#endif

static std::string exec(const char* cmd) {
   FILE* pipe = popen(cmd, "r");
   if (!pipe) return "ERROR";
   char buffer[128];
   std::string result = "";
   while(!feof(pipe)) {
      if(fgets(buffer, 128, pipe) != NULL)
         result += buffer;
   }
   pclose(pipe);
   return result;
}

RubyScriptResult run_ruby_script(std::string script_filename, std::string args)
{
   RubyScriptResult result;
#ifdef _WIN32
   std::string exec_command = "C:/Ruby200/bin/setrbvars.bat & ruby ./data/scripts/" + script_filename + " " + args;
#else
   std::string exec_command = "ruby ./data/scripts/" + script_filename + " " + args;
#endif
   result.output = exec(exec_command.c_str());
   // profiling on my computer demonstrates that this method takes 0.09sec to 0.11sec to execute.
   // That's setting the environment vars, starting the interpreter, and running a simple script.
   // obviously, it's not ideal for realtime usage, but for now this is the simplest implementation
   // to begin development with ruby and scripting.

   result.filename = script_filename;
   result.exception_caught = false; // with this method, there is no way to catch the error in std err

   return result;
}





// // // // //
// This is the main Projec part of the file
// // // // //


#include <allegro_flare/allegro_flare.h>
#include <allegro_flare/music_notation.h>
#include <allegro_flare/drawing_interface_allegro5.h>

#include <algorithm>



using namespace allegro_flare;




class Project : public UIScreen
{
public:
   ALLEGRO_BITMAP *music_render;
   UITextInput *text_input;
   UIText *notation_text;
   std::string result_text;
   Project() : UIScreen(Framework::create_display())
      , music_render(al_create_bitmap(200, 80))
      , text_input(NULL)
      , notation_text(NULL)
      , result_text()
   {
      text_input = new UITextInput(this, display->center(), display->height()*2/3, 300, 40, "0 1 2 3 4 5");
      //text_input->attr.set("on_submit_send_text", "process music");
      notation_text = new UIText(this, display->center()-text_input->place.size.x/2, display->height()*2/3+45,
         "[notation_string]");
   }

   void primary_timer_func() override
   {
      static int last_width = 0;
      DrawingInterfaceAllegro5 drawing_interface;
      MusicNotation music_notation(&drawing_interface);

      UIScreen::primary_timer_func();

      last_width = music_notation.draw(display->center() - last_width/2, display->height()/3,
         "{staff_color=white color=white spacing=fixed ignore_spaces}" + result_text);
   }

   void on_message(UIWidget *parent, std::string message) override
   {
      // on any message, reset the result_text
      result_text = get_result_from_script(text_input->get_text());
      notation_text->set_text(result_text);
      std::cout << "message recieved" << std::endl;
   }

   static std::string get_result_from_script(std::string arguments)
   {
      RubyScriptResult result = run_ruby_script("music_calculator_ex_script.rb", arguments);
      return result.output;
   }

   static std::string convert_cell_format_to_notation(std::string cell)
   {
      // each note is in the format "[0q 6 2h 8 1 0]" which is
      // accidental scale_degree octave duration dots is_rest
      //b7q.

      // format
      //optional b* = num of flats
      //optional #* = optional numf of sharps
      //optional n == natural
      //optional v* == octave down
      //optional ^* == octave up
      //optional duration w=whole h=half q=quarter e=eighth s=16th t=32nd i=64th o=128th (default is q)
      //optional (\.)* number of dots
      //find each of the notes (regex would be perfect for this)

      std::string notation_string;

      std::vector<std::string> notes = php::explode(" ", cell);

      for (unsigned i=0; i<notes.size(); i++)
      {
         if (notes[i].empty()) continue;
         size_t duration_find = notes[i].find_last_of("whqestio");
         std::string duration_char = ((duration_find==std::string::npos) ? "q" : notes[i].substr(duration_find, 1));

         int scale_degree = 0;
         size_t scale_degree_pos = notes[i].find_first_of("0123456789");
         if (scale_degree_pos != std::string::npos) scale_degree = atoi(notes[i].substr(scale_degree_pos, 1).c_str());

         notation_string += duration_char + tostring(scale_degree);
      }

      return notation_string;
   }
};




int main(int argc, char **argv)
{
   Framework::initialize();
   Project *p = new Project();
   Framework::run_loop();
   return 0;
}




