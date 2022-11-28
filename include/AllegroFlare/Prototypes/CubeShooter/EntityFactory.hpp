#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/ElementID.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Prototypes/CubeShooter/Entity.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace CubeShooter
      {
         class EntityFactory
         {
         private:
            AllegroFlare::ElementID* scene_root;
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::ModelBin* model_bin;
            bool initialized;

         protected:


         public:
            EntityFactory(AllegroFlare::ElementID* scene_root=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr);
            ~EntityFactory();

            void set_scene_root(AllegroFlare::ElementID* scene_root);
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_model_bin(AllegroFlare::ModelBin* model_bin);
            AllegroFlare::ElementID* get_scene_root() const;
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::ModelBin* get_model_bin() const;
            void initialize();
            AllegroFlare::Prototypes::CubeShooter::Entity* add_cube(float x=0.0f, float y=0.0f, float z=0.0f);
            AllegroFlare::Prototypes::CubeShooter::Entity* add_player_bullet(float x=0.0f, float y=0.0f, float z=0.0f);
            AllegroFlare::Prototypes::CubeShooter::Entity* add_player_ship(float x=0.0f, float y=0.0f, float z=0.0f);
            AllegroFlare::Prototypes::CubeShooter::Entity* add_world_mesh();
         };
      }
   }
}



