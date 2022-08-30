#pragma once


#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      class DialogRoll
      {
      private:
         std::vector<std::pair<std::string, std::string>> log;

      public:
         DialogRoll(std::vector<std::pair<std::string, std::string>> log={});
         ~DialogRoll();

         void set_log(std::vector<std::pair<std::string, std::string>> log);
         std::vector<std::pair<std::string, std::string>> get_log() const;
      };
   }
}



