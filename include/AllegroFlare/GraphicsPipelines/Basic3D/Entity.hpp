#pragma once


#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace GraphicsPipelines
   {
      namespace Basic3D
      {
         class Entity
         {
         private:

         protected:


         public:
            AllegroFlare::Model3D* model;
            ALLEGRO_BITMAP* texture;
            AllegroFlare::Placement3D placement;
            std::string model_obj_filename;
            std::string model_texture_filename;
            Entity();
            ~Entity();

         };
      }
   }
}



