#pragma once


#include <AllegroFlare/Path2D.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro.h>
#include <functional>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Layouts
   {
      namespace Elements
      {
         class Polygon
         {
         private:

         protected:


         public:
            std::string name;
            float x;
            float y;
            float width;
            float height;
            std::vector<AllegroFlare::Vec2D> polygon;
            AllegroFlare::Path2D path;
            ALLEGRO_COLOR fill_color;
            float tmj_object_id;
            std::function<void()> on_focus;
            std::function<void()> on_blur;
            std::function<void()> on_activation;
            Polygon();
            ~Polygon();

         };
      }
   }
}



