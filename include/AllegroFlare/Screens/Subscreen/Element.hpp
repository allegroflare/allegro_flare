#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Subscreen/Panes/Base.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <vector>


namespace AllegroFlare
{
   namespace Screens
   {
      namespace Subscreen
      {
         class Element
         {
         public:
            static constexpr int BLACK_BARS_HEIGHT = 100;

         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            std::vector<AllegroFlare::Screens::Subscreen::Panes::Base*> panes;
            ALLEGRO_BITMAP* background_bitmap;
            int current_pane_cursor_pos;
            AllegroFlare::Camera2D pane_camera;
            float pane_camera_edge_bonk_depth;
            float pane_camera_dest_x_pos;
            AllegroFlare::Camera2D hud_camera;
            float black_bar_opacity;
            bool initialized;
            void render_background();
            void render_panes();
            void render_black_bars();
            void render_tabs();
            int infer_num_panes();
            ALLEGRO_FONT* obtain_tabs_font();

         protected:


         public:
            Element(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr);
            virtual ~Element();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_panes(std::vector<AllegroFlare::Screens::Subscreen::Panes::Base*> panes);
            void set_background_bitmap(ALLEGRO_BITMAP* background_bitmap);
            void set_black_bar_opacity(float black_bar_opacity);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::FontBin* get_font_bin() const;
            std::vector<AllegroFlare::Screens::Subscreen::Panes::Base*> get_panes() const;
            ALLEGRO_BITMAP* get_background_bitmap() const;
            float get_black_bar_opacity() const;
            bool get_initialized() const;
            std::vector<AllegroFlare::Screens::Subscreen::Panes::Base*> &get_panes_ref();
            virtual void initialize();
            void refresh();
            bool move_pane_right();
            bool move_pane_left();
            void move_cursor_up();
            void move_cursor_down();
            void move_cursor_right();
            void move_cursor_left();
            void pane_camera_zoom_in();
            void pane_camera_zoom_out();
            void update();
            void render();
            void render_hud();
            AllegroFlare::Screens::Subscreen::Panes::Base* infer_currently_active_pane();
            void clear_panes();
         };
      }
   }
}



