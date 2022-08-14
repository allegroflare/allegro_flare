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
         float position;
         float handle_height;
         float rail_thickness;
         float handle_thickness;

      public:
         ScrollBar(float x=0.0f, float y=0.0f, float height=100.0f, float position=0.0f, float handle_height=50.0f, float rail_thickness=8.0f, float handle_thickness=16.0f);
         ~ScrollBar();

         void set_x(float x);
         void set_y(float y);
         void set_height(float height);
         void set_position(float position);
         void set_handle_height(float handle_height);
         void set_rail_thickness(float rail_thickness);
         void set_handle_thickness(float handle_thickness);
         float get_x();
         float get_y();
         float get_height();
         float get_position();
         float get_handle_height();
         float get_rail_thickness();
         float get_handle_thickness();
         void render();
      };
   }
}



