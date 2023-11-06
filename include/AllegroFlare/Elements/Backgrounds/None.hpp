#pragma once


#include <AllegroFlare/Elements/Backgrounds/Base.hpp>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace Backgrounds
      {
         class None : public AllegroFlare::Elements::Backgrounds::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/Backgrounds/None";

         private:

         protected:


         public:
            None();
            ~None();

         };
      }
   }
}



