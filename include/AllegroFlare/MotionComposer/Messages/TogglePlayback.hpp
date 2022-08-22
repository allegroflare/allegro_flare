#pragma once


#include <AllegroFlare/MotionComposer/Messages/Base.hpp>


namespace AllegroFlare
{
   namespace MotionComposer
   {
      namespace Messages
      {
         class TogglePlayback : public AllegroFlare::MotionComposer::Messages::Base
         {
         private:

         public:
            TogglePlayback();
            ~TogglePlayback();

         };
      }
   }
}



