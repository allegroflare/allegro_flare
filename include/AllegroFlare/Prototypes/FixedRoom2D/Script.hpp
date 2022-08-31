#pragma once


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
         class Script
         {
         private:
            std::vector<std::string> lines;
            int current_line_num;
            std::map<std::string, int> markers_index;
            bool initialized;
            bool finished;
            bool at_valid_line();
            int infer_current_line_index_num();

         protected:


         public:
            Script(std::vector<std::string> lines={});
            ~Script();

            std::vector<std::string> get_lines() const;
            int get_current_line_num() const;
            bool get_finished() const;
            void initialize();
            std::string get_current_line_text();
            bool goto_next_line();
            bool goto_marker(std::string identifier="[unset-marker-to-goto]");
            bool goto_line_num(int line_num=0);
            bool at_last_line();
            static std::pair<std::string, std::string> parse_command_and_argument(std::string script_line={});
            static std::map<std::string, int> build_markers_index(std::vector<std::string> script_lines={});
            static bool is_valid_command_string(std::string command="[unset-command]");
         };
      }
   }
}



