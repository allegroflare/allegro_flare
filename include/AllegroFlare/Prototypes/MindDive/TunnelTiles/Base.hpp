#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace MindDive
      {
         namespace TunnelTiles
         {
            class Base
            {
            public:
               static constexpr char* TYPE = (char*)"TunnelTiles/Base";

            private:
               std::string type;

            protected:


            public:
               Base(std::string type=AllegroFlare::Prototypes::MindDive::TunnelTiles::Base::TYPE);
               ~Base();

               std::string get_type() const;
               bool is_type(std::string possible_type="");
            };
         }
      }
   }
}



