#pragma once


#include <AllegroFlare/Layouts/Elements/CursorDestination.hpp>
#include <AllegroFlare/Layouts/Elements/Frame.hpp>
#include <AllegroFlare/Layouts/Elements/Polygon.hpp>
#include <AllegroFlare/Layouts/Elements/Text.hpp>
#include <AllegroFlare/Tiled/TMJObject.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Layouts
   {
      class ElementFactory
      {
      private:

      protected:


      public:
         ElementFactory();
         ~ElementFactory();

         static AllegroFlare::Layouts::Elements::Polygon build_polygon_from_tmj_object(AllegroFlare::Tiled::TMJObject* object=nullptr);
         static AllegroFlare::Layouts::Elements::Text build_text_from_tmj_object(AllegroFlare::Tiled::TMJObject* object=nullptr);
         static AllegroFlare::Layouts::Elements::CursorDestination build_cursor_destination_from_tmj_object(AllegroFlare::Tiled::TMJObject* object=nullptr);
         static AllegroFlare::Layouts::Elements::Frame build_frame_from_tmj_object(AllegroFlare::Tiled::TMJObject* object=nullptr);
         static float translate_alignment_string_to_float(std::string alignment_string="[unset-alignment_string]");
         static std::string extract_color_hex_or_default(AllegroFlare::Tiled::TMJObject* object=nullptr, std::string key="[unset-key]", std::string default_fallback="#ffffffff");
         static int extract_int_or_default(AllegroFlare::Tiled::TMJObject* object=nullptr, std::string key="[unset-key]", int default_fallback=0);
         int extract_int_or_throw(AllegroFlare::Tiled::TMJObject* object=nullptr, std::string key="[unset-key]");
      };
   }
}



