#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace RollingCredits
      {
         namespace SectionRenderers
         {
            class Base
            {
            private:
               std::string type;

            public:
               Base(std::string type="Base");
               virtual ~Base();

               std::string get_type() const;
               virtual float render(bool only_calculate_height_dont_render=false);
               bool is_type(std::string possible_type="");
            };
         }
      }
   }
}



