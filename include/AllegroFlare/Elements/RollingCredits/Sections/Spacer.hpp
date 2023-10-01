#pragma once


#include <AllegroFlare/Elements/RollingCredits/Sections/Base.hpp>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace RollingCredits
      {
         namespace Sections
         {
            class Spacer : public AllegroFlare::Elements::RollingCredits::Sections::Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Elements/RollingCredits/Sections/Spacer";

            private:
               int height_px;

            protected:


            public:
               Spacer(int height_px=100);
               ~Spacer();

               int get_height_px() const;
               void set_height_px(int height_px=100);
            };
         }
      }
   }
}



