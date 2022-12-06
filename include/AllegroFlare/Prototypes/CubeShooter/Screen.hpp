#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/ElementID.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Prototypes/CubeShooter/Entity.hpp>
#include <AllegroFlare/Prototypes/CubeShooter/EntityFactory.hpp>
#include <AllegroFlare/Prototypes/CubeShooter/PlayerMovementControl.hpp>
#include <AllegroFlare/Prototypes/CubeShooter/Shaders/DepthDarken.hpp>
#include <AllegroFlare/Prototypes/CubeShooter/Shaders/Fog.hpp>
#include <AllegroFlare/Prototypes/CubeShooter/Shaders/Multiply.hpp>
#include <AllegroFlare/SampleBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Shader.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace CubeShooter
      {
         class Screen : public AllegroFlare::Screens::Base
         {
         public:
            static constexpr char* TYPE = (char*)"CubeShooter/Screen";

         private:
            AllegroFlare::EventEmitter* event_emitter;
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::SampleBin* sample_bin;
            AllegroFlare::ModelBin* model_bin;
            AllegroFlare::ElementID scene_root;
            AllegroFlare::Prototypes::CubeShooter::EntityFactory entity_factory;
            AllegroFlare::Prototypes::CubeShooter::Entity* player_controlled_entity;
            AllegroFlare::Prototypes::CubeShooter::PlayerMovementControl player_movement_control;
            AllegroFlare::Camera3D camera;
            AllegroFlare::Shader* shader;
            AllegroFlare::Prototypes::CubeShooter::Shaders::Multiply multiply_shader;
            AllegroFlare::Prototypes::CubeShooter::Shaders::Fog fog_shader;
            AllegroFlare::Prototypes::CubeShooter::Shaders::DepthDarken depth_darken_shader;
            bool initialized;

         protected:


         public:
            Screen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::SampleBin* sample_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr);
            virtual ~Screen();

            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
            void set_sample_bin(AllegroFlare::SampleBin* sample_bin=nullptr);
            void set_model_bin(AllegroFlare::ModelBin* model_bin=nullptr);
            void initialize();
            void load_level();
            virtual void on_activate() override;
            virtual void on_deactivate() override;
            void update();
            bool collides(AllegroFlare::Prototypes::CubeShooter::Entity* entity_a=nullptr, AllegroFlare::Prototypes::CubeShooter::Entity* entity_b=nullptr);
            void render_crosshair(AllegroFlare::Vec3D position);
            void render();
            virtual void primary_timer_func() override;
            virtual void key_down_func(ALLEGRO_EVENT* event=nullptr) override;
            virtual void key_up_func(ALLEGRO_EVENT* event=nullptr) override;
         };
      }
   }
}



