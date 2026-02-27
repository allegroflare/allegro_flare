#pragma once


#include <AllegroFlare/Layouts/Elements/CursorDestination.hpp>
#include <AllegroFlare/Layouts/Elements/Frame.hpp>
#include <AllegroFlare/Layouts/Elements/Polygon.hpp>
#include <AllegroFlare/Layouts/Elements/Text.hpp>
#include <AllegroFlare/TileMaps/TileMesh.hpp>
#include <map>
#include <string>


namespace AllegroFlare
{
   namespace Layouts
   {
      class Layer
      {
      private:

      protected:


      public:
         AllegroFlare::TileMaps::TileMesh tile_mesh;
         std::map<std::string, AllegroFlare::Layouts::Elements::Text> text_slots;
         std::map<std::string, std::string> text_data;
         std::map<int, AllegroFlare::Layouts::Elements::Polygon> polygons;
         std::map<int, AllegroFlare::Layouts::Elements::CursorDestination> cursor_destinations;
         std::map<int, AllegroFlare::Layouts::Elements::Frame> frames;
         Layer();
         ~Layer();

      };
   }
}



