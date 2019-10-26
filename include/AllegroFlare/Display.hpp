#pragma once


#include <vector>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   class Framework;

   /**
    * @class Display
    * @author Mark Oates
    * @file Display.hpp
    * @brief Holds an ALLEGRO_DISPLAY object.
    */
   class Display
   {
   public:
      enum resolution_t
      {
         RESOLUTION_XGA,
         RESOLUTION_WXGA,
         RESOLUTION_WXGA_PLUS, // WXGA+
         RESOLUTION_HD_1080,
         RESOLUTION_HD_720,
         RESOLUTION_RETINA,
         FULLSCREEN_AUTO
      };

   private:
      friend class Framework;
      friend class Screens; // <- eh for now, because of the display <-> screen relationship
      static std::vector<Display *> displays; // used to be "instance"
      static Display *find_display(ALLEGRO_DISPLAY *display);
      ALLEGRO_COLOR _background_color;
      int _width, _height;

   public:
      
      /**
      * @brief Do not use directly, use through Framework::create_display
      */
      Display(int width, int height, int display_flags); // you must use AllegroFlare::create_display
      virtual ~Display();

      ALLEGRO_DISPLAY *al_display;
      virtual void display_close_func();

      void set_as_target_bitmap(); // untested

      /**
       * @brief 
       * @return Returns the screen width 
       */
      int width();
      /**
       * @brief 
       * @return Returns the screen height 
       */
      int height();
      float middle();
      float center();

      /**
       * @brief Force buffer to be actually drawn on screen
       */
      void flip();
      
      /**
       * @brief Sets default background color (when nothing is being drawn on the Display)
       * @param color The color used to fill the window
       */
      void background_color(const ALLEGRO_COLOR &color);
      void clear();
   };
}


