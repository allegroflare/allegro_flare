#pragma once


#include <AllegroFlare/Vec2D.hpp>


namespace AllegroFlare
{
   namespace Elements
   {
      class SelectionCursorBox
      {
      public:
         static constexpr float DEFAULT_CURSOR_REPOSITION_MULTIPLIER = 0.6f;

      private:
         AllegroFlare::Vec2D cursor_destination;
         AllegroFlare::Vec2D cursor_size_destination;
         float cursor_reposition_multiplier;
         AllegroFlare::Vec2D cursor_location;
         AllegroFlare::Vec2D cursor_size;

      protected:


      public:
         SelectionCursorBox();
         ~SelectionCursorBox();

         float get_cursor_reposition_multiplier() const;
         void render();
      };
   }
}



