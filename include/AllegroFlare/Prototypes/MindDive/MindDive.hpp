#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/Prototypes/MindDive/TunnelMesh.hpp>
#include <AllegroFlare/Vec2D.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace MindDive
      {
         class MindDive
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::Prototypes::MindDive::TunnelMesh tunnel_mesh;
            AllegroFlare::Vec2D surfer;
            AllegroFlare::Vec2D surfer_velocity;
            AllegroFlare::Camera2D camera;
            bool initialized;

         protected:


         public:
            MindDive(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            ~MindDive();

            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::Prototypes::MindDive::TunnelMesh &get_tunnel_mesh_ref();
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            void initialize();
            void reset_surfer_to_beginning();
            void surfer_move_right();
            void surfer_move_left();
            void surfer_accelerate();
            void surfer_stop();
            void surfer_move_horizontal_none();
            void render_tunnel();
            void render_surfer();
            void update();
            void render();
         };
      }
   }
}



