#pragma once


#include <AllegroFlare/MotionComposer/Messages/Base.hpp>


namespace AllegroFlare
{
   namespace MotionComposer
   {
      namespace Messages
      {
         class SetPlayheadPosition : public AllegroFlare::MotionComposer::Messages::Base
         {
         private:
            float position;

         public:
            SetPlayheadPosition(float position=0.0f);
            ~SetPlayheadPosition();

            void set_position(float position);
            float get_position() const;
            float &get_position_ref();
         };
      }
   }
}



