#pragma once


#include <string>


namespace AllegroFlare
{
   namespace TileMaps
   {
      namespace AutoTile
      {
         namespace Filters
         {
            class Base
            {
            public:
               static constexpr char* TYPE = (char*)"Filters/Base";

            private:
               std::string type;

            protected:


            public:
               Base(std::string type=AllegroFlare::TileMaps::AutoTile::Filters::Base::TYPE);
               ~Base();

               std::string get_type() const;
               bool is_type(std::string possible_type="");
            };
         }
      }
   }
}



