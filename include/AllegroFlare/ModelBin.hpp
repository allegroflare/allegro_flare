#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <AllegroFlare/Bin.hpp>
#include <AllegroFlare/Model3D.hpp>


namespace AllegroFlare
{
   class ModelBin : public Bin<std::string, Model3D *>
   {
   public:
      ModelBin();
      ~ModelBin();
      Model3D *load_data(std::string identifier);
      void destroy_data(Model3D *bmp);
   };
}


