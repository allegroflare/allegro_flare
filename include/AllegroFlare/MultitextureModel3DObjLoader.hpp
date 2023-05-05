#pragma once


#include <AllegroFlare/MultitextureModel3D.hpp>
#include <string>


namespace AllegroFlare
{
   class MultitextureModel3DObjLoader
   {
   private:
      AllegroFlare::MultitextureModel3D* model;
      std::string base_obj_filename;
      std::string obj_filename_with_uv2_coordinates;
      float scale;

   protected:


   public:
      MultitextureModel3DObjLoader(AllegroFlare::MultitextureModel3D* model=nullptr, std::string base_obj_filename="[unset-obj_filename]", std::string obj_filename_with_uv2_coordinates="[unset-obj_filename_with_uv2_coordinates]", float scale=1.0f);
      ~MultitextureModel3DObjLoader();

      void set_model(AllegroFlare::MultitextureModel3D* model);
      void set_base_obj_filename(std::string base_obj_filename);
      void set_obj_filename_with_uv2_coordinates(std::string obj_filename_with_uv2_coordinates);
      void set_scale(float scale);
      AllegroFlare::MultitextureModel3D* get_model() const;
      std::string get_base_obj_filename() const;
      std::string get_obj_filename_with_uv2_coordinates() const;
      float get_scale() const;
      bool load();
      bool load_base_obj();
   };
}



