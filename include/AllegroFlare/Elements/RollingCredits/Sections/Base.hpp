#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace RollingCredits
      {
         namespace Sections
         {
            class Base
            {
            private:
               std::string type;

            public:
               Base(std::string type="Base");
               ~Base();

               std::string get_type() const;
               bool is_type(std::string possible_type="");
            };
         }
      }
   }
}



