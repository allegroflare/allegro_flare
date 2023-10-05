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
      public:
         static constexpr char* SPEAKER_INTERNAL = (char*)"internal";

      private:
         std::vector<std::pair<std::string, std::string>> log;

      protected:


      public:
         DialogRoll(std::vector<std::pair<std::string, std::string>> log={});
         ~DialogRoll();

         void set_log(std::vector<std::pair<std::string, std::string>> log);
         std::vector<std::pair<std::string, std::string>> get_log() const;
         void append_log(std::string speaker="[unset-speaker]", std::string text="[unset-text]", float time=0.0f);
      };
   }
}



