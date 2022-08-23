#pragma once


#include <AllegroFlare/MotionComposer/Messages/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace MotionComposer
   {
      namespace Messages
      {
         class AddActor2D : public AllegroFlare::MotionComposer::Messages::Base
         {
         private:
            std::string property;

         public:
            AddActor2D(std::string property="[unset-property]");
            ~AddActor2D();

            std::string get_property();
         };
      }
   }
}



