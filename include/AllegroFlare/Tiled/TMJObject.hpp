#pragma once


#include <AllegroFlare/Tiled/TMJObjectCustomProperties.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Tiled
   {
      class TMJObject
      {
      private:

      protected:


      public:
         std::string type;
         int id;
         std::string name;
         float x;
         float y;
         float width;
         float height;
         std::vector<AllegroFlare::Vec2D> polygon;
         bool text__is_present;
         std::string text__text;
         std::string text__font_name;
         int text__font_size;
         std::string text__align_horizontal;
         std::string text__align_vertical;
         AllegroFlare::Tiled::TMJObjectCustomProperties custom_properties;
         std::string object_layer_name;
         TMJObject();
         ~TMJObject();

         AllegroFlare::Vec2D center();
      };
   }
}



