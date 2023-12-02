#pragma once


#include <AllegroFlare/Elements/RollingCredits/Sections/Base.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace RollingCredits
      {
         namespace Sections
         {
            class Multicolumn : public AllegroFlare::Elements::RollingCredits::Sections::Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Elements/RollingCredits/Sections/Multicolumn";

            private:
               std::vector<std::string> elements;

            protected:


            public:
               Multicolumn(std::vector<std::string> elements={});
               ~Multicolumn();

               std::vector<std::string> get_elements() const;
            };
         }
      }
   }
}



