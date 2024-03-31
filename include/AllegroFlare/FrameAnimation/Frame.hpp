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
         float align_x;
         float align_y;
         float anchor_x;
         float anchor_y;

      protected:


      public:
         Frame(uint32_t index=0, float duration=0.2f, float align_x=0.5f, float align_y=0.5f, float anchor_x=0.0f, float anchor_y=0.0f);
         ~Frame();

         uint32_t get_index() const;
         float get_duration() const;
         float get_align_x() const;
         float get_align_y() const;
         float get_anchor_x() const;
         float get_anchor_y() const;
      };
   }
}



