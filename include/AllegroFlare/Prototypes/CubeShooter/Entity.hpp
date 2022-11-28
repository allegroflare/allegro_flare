#pragma once


#include <AllegroFlare/ElementID.hpp>
#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace CubeShooter
      {
         class Entity : public AllegroFlare::ElementID
         {
         private:
            AllegroFlare::Placement3D placement;
            AllegroFlare::Placement3D velocity;
            AllegroFlare::Model3D* model_3d;
            float created_at;
            AllegroFlare::Vec3D min_bounding_box_coordinates;
            AllegroFlare::Vec3D max_bounding_box_coordinates;

         protected:


         public:
            Entity();
            ~Entity();

            void set_placement(AllegroFlare::Placement3D placement);
            void set_velocity(AllegroFlare::Placement3D velocity);
            void set_model_3d(AllegroFlare::Model3D* model_3d);
            void set_created_at(float created_at);
            void set_min_bounding_box_coordinates(AllegroFlare::Vec3D min_bounding_box_coordinates);
            void set_max_bounding_box_coordinates(AllegroFlare::Vec3D max_bounding_box_coordinates);
            AllegroFlare::Placement3D get_placement() const;
            AllegroFlare::Placement3D get_velocity() const;
            AllegroFlare::Model3D* get_model_3d() const;
            float get_created_at() const;
            AllegroFlare::Vec3D get_min_bounding_box_coordinates() const;
            AllegroFlare::Vec3D get_max_bounding_box_coordinates() const;
            AllegroFlare::Placement3D &get_placement_ref();
            AllegroFlare::Placement3D &get_velocity_ref();
            AllegroFlare::Model3D* &get_model_3d_ref();
            float infer_age(float time_now=0.0f);
            bool has_attribute(std::string attribute="[attribute]");
            void set_attribute(std::string attribute="[attribute]");
            void unset_attribute(std::string attribute="[attribute]");
         };
      }
   }
}



