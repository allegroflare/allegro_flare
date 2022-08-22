#pragma once


#include <AllegroFlare/Elements/RollingCredits/Sections/Base.hpp>
#include <string>
#include <tuple>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace RollingCredits
      {
         namespace Sections
         {
            class StandardColumn : public AllegroFlare::Elements::RollingCredits::Sections::Base
            {
            private:
               std::vector<std::tuple<std::string, std::string>> elements;

            public:
               StandardColumn(std::vector<std::tuple<std::string, std::string>> elements={});
               ~StandardColumn();

               void set_elements(std::vector<std::tuple<std::string, std::string>> elements);
               std::vector<std::tuple<std::string, std::string>> get_elements();
            };
         }
      }
   }
}



