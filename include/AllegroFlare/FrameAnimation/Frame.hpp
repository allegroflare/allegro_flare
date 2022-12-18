#pragma once


#include <cstdint>


namespace AllegroFlare
{
   namespace FrameAnimation
   {
      class Frame
      {
      private:
         uint32_t index;
         float duration;

      protected:


      public:
         Frame(uint32_t index=0, float duration=0.2f);
         ~Frame();

         uint32_t get_index() const;
         float get_duration() const;
      };
   }
}



