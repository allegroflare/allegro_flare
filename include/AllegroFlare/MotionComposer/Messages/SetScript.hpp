#pragma once


#include <AllegroFlare/MotionComposer/Messages/Base.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace MotionComposer
   {
      namespace Messages
      {
         class SetScript : public AllegroFlare::MotionComposer::Messages::Base
         {
         private:
            std::vector<std::string> script_lines;

         public:
            SetScript(std::vector<std::string> script_lines={});
            ~SetScript();

            void set_script_lines(std::vector<std::string> script_lines);
            std::vector<std::string> get_script_lines() const;
         };
      }
   }
}



