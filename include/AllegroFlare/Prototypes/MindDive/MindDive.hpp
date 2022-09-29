#pragma once


#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Prototypes/MindDive/TunnelMesh.hpp>
#include <AllegroFlare/Timer.hpp>
#include <AllegroFlare/Vec3D.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace MindDive
      {
         class MindDive
         {
         public:
            static constexpr int STATE_RACING = 1;
            static constexpr int STATE_WON = 2;
            static constexpr int STATE_WAITING_START = 3;

         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::Prototypes::MindDive::TunnelMesh* current_tunnel_mesh;
            AllegroFlare::Vec3D surfer_position;
            AllegroFlare::Vec3D surfer_velocity;
            AllegroFlare::Timer timer;
            AllegroFlare::Camera3D camera;
            int state;
            bool initialized;
            void start_timer();
            void reset_timer();
            void evaluate_surfer_past_goal();

         protected:


         public:
            MindDive(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr);
            ~MindDive();

            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::FontBin* get_font_bin() const;
            AllegroFlare::Prototypes::MindDive::TunnelMesh* &get_current_tunnel_mesh_ref();
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
            void initialize();
            void pause_timer();
            void reset();
            void start_racing();
            void surfer_move_right();
            void surfer_move_left();
            void surfer_accelerate();
            void surfer_reverse();
            void surfer_stop();
            void surfer_move_horizontal_none();
            void render_tunnel();
            void render_stopwatch();
            void render_surfer();
            void update();
            void render();
         };
      }
   }
}



