#pragma once


#include <vector>
#include <string>


namespace AllegroFlare
{
   namespace Timeline
   {
      class ScriptLoader
      {
      private:
         unsigned current_line_index;
         std::vector<std::string> lines;
         static std::string remove_comments(std::string &line);

      public:
         ScriptLoader();
         ScriptLoader(std::string script);
         ~ScriptLoader();

         bool at_end();
         std::string get_next_line(bool remove_comments=true);
      };
   }
}



