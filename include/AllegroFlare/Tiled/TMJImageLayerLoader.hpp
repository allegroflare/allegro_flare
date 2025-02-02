#pragma once


#include <AllegroFlare/Tiled/TMJImageLayer.hpp>
#include <allegro5/allegro.h>
#include <functional>
#include <lib/nlohmann/json.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Tiled
   {
      class TMJImageLayerLoader
      {
      private:
         std::string filename;
         std::vector<AllegroFlare::Tiled::TMJImageLayer> image_layers;
         bool loaded;
         static bool file_exists(std::string filename="[unset-filename]");

      protected:


      public:
         TMJImageLayerLoader(std::string filename="[unset-filename]");
         ~TMJImageLayerLoader();

         void for_each_image_layer(std::function<void(AllegroFlare::Tiled::TMJImageLayer*, void*)> function={}, void* user_data=nullptr);
         int get_num_image_layers();
         std::vector<AllegroFlare::Tiled::TMJImageLayer> get_image_layers();
         void load();
         std::string obtain_string_or_throw(std::string key="[unset-key]", nlohmann::json* object_json=nullptr);
         float obtain_float_or_throw(std::string key="[unset-key]", nlohmann::json* object_json=nullptr);
         float obtain_float_or_default(std::string key="[unset-key]", nlohmann::json* object_json=nullptr, float default_value=0.0f);
         ALLEGRO_COLOR obtain_color_or_default(std::string key="[unset-key]", nlohmann::json* object_json=nullptr, ALLEGRO_COLOR default_value=ALLEGRO_COLOR{1, 1, 1, 1});
         bool obtain_bool_or_default(std::string key="[unset-key]", nlohmann::json* object_json=nullptr, bool default_value=false);
         int obtain_int_or_throw(std::string key="[unset-key]", nlohmann::json* object_json=nullptr);
         void attempt_to_extract_custom_properties();
      };
   }
}



