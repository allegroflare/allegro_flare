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
               std::vector<std::vector<std::string>> elements;

            protected:


            public:
               Multicolumn(std::vector<std::vector<std::string>> elements={});
               ~Multicolumn();

               void set_elements(std::vector<std::vector<std::string>> elements);
               std::vector<std::vector<std::string>> get_elements() const;
               static std::vector<std::vector<std::string>> split_into_columns(std::vector<std::string> names={}, int num_columns=3);
            };
         }
      }
   }
}



