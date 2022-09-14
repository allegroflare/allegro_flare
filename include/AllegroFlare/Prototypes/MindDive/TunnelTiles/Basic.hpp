#pragma once


#include <AllegroFlare/Prototypes/MindDive/TunnelTiles/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace MindDive
      {
         namespace TunnelTiles
         {
            class Basic : public AllegroFlare::Prototypes::MindDive::TunnelTiles::Base
            {
            public:
               static constexpr char* TYPE = "TunnelTiles/Basic";

            private:
               std::string property;

            protected:


            public:
               Basic(std::string property="[unset-property]");
               ~Basic();

               std::string get_property() const;
            };
         }
      }
   }
}



