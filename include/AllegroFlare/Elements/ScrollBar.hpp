#pragma once




namespace AllegroFlare
{
   namespace Elements
   {
      class ScrollBar
      {
      private:
         float x;
         float y;
         float height;
         float handle_height;
         float scroll_bar_position;
         float rail_thickness;

      public:
         ScrollBar(float x=0.0f, float y=0.0f, float height=100.0f, float handle_height=50.0f, float scroll_bar_position=0.0f, float rail_thickness=16.0f);
         ~ScrollBar();

         void set_x(float x);
         void set_y(float y);
         void set_height(float height);
         void set_handle_height(float handle_height);
         void set_scroll_bar_position(float scroll_bar_position);
         void set_rail_thickness(float rail_thickness);
         float get_x();
         float get_y();
         float get_height();
         float get_handle_height();
         float get_scroll_bar_position();
         float get_rail_thickness();
         void render();
      };
   }
}



