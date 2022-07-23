#pragma once


#include <string>
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

         public:
            Script(std::vector<std::string> lines={});
            ~Script();

            void set_lines(std::vector<std::string> lines);
            std::vector<std::string> get_lines();
         };
      }
   }
}



