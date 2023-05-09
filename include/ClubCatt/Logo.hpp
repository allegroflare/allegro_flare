#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Timeline/Track.hpp>
#include <ClubCatt/Logo.hpp>
#include <allegro5/allegro.h>
#include <functional>
#include <string>


namespace ClubCatt
{
   class Logo
   {
   private:
      AllegroFlare::BitmapBin* bitmap_bin;
      AllegroFlare::ModelBin* model_bin;
      std::string model_identifier;
      std::string cube_texture1_identifier;
      std::string cube_texture2_identifier;
      AllegroFlare::Camera3D camera;
      AllegroFlare::Timeline::Track rotation_x_timeline;
      AllegroFlare::Timeline::Track rotation_y_timeline;
      AllegroFlare::Timeline::Track camera_spin_timeline;
      AllegroFlare::Timeline::Track texture_swap_timeline;
      AllegroFlare::Timeline::Track fade_out_timeline;
      AllegroFlare::Timeline::Track end_marker_timeline;
      float playback_speed_multiplier;
      bool finished;
      std::function<void(ClubCatt::Logo*, void*)> on_finished_callback;
      void* on_finished_callback_user_data;
      bool initialized;

   protected:


   public:
      Logo(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr);
      ~Logo();

      void set_on_finished_callback(std::function<void(ClubCatt::Logo*, void*)> on_finished_callback);
      void set_on_finished_callback_user_data(void* on_finished_callback_user_data);
      AllegroFlare::BitmapBin* get_bitmap_bin() const;
      AllegroFlare::ModelBin* get_model_bin() const;
      bool get_finished() const;
      std::function<void(ClubCatt::Logo*, void*)> get_on_finished_callback() const;
      void* get_on_finished_callback_user_data() const;
      void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
      void set_model_bin(AllegroFlare::ModelBin* model_bin=nullptr);
      void initialize();
      void destroy();
      void reset();
      void play();
      void update(float time_now=al_get_time());
      void draw(float time_now=al_get_time());
      ALLEGRO_BITMAP* get_display_backbuffer();
   };
}



