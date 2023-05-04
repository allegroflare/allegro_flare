#pragma once


#include <AllegroFlare/MultitextureModel3D.hpp>
#include <string>


namespace AllegroFlare
{
   class MultitextureModel3DObjLoader
   {
   private:
      AllegroFlare::MultitextureModel3D* model;
      std::string filename;
      float scale;

   protected:


   public:
      MultitextureModel3DObjLoader(AllegroFlare::MultitextureModel3D* model=nullptr, std::string filename="[unset-filename]", float scale=1.0f);
      ~MultitextureModel3DObjLoader();

      void set_model(AllegroFlare::MultitextureModel3D* model);
      void set_filename(std::string filename);
      void set_scale(float scale);
      AllegroFlare::MultitextureModel3D* get_model() const;
      std::string get_filename() const;
      float get_scale() const;
      bool load();
   };
}



