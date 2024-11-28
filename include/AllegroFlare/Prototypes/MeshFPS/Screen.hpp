#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/CollisionObservers/Simple.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/GameConfigurations/Base.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Physics/CollisionMesh.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Prototypes/MeshFPS/Entities/Base.hpp>
#include <AllegroFlare/Prototypes/MeshFPS/Screen.hpp>
#include <AllegroFlare/Screens/Gameplay.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <functional>
#include <vector>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace MeshFPS
      {
         class Screen : public AllegroFlare::Screens::Gameplay
         {
         private:
            AllegroFlare::EventEmitter* event_emitter;
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::ModelBin* model_bin;
            AllegroFlare::GameConfigurations::Base* game_configuration;
            AllegroFlare::Camera2D hud_camera;
            AllegroFlare::Camera3D live_camera;
            std::vector<AllegroFlare::Prototypes::MeshFPS::Entities::Base*>* entities;
            AllegroFlare::Physics::CollisionMesh* collision_mesh;
            AllegroFlare::Model3D* visual_mesh;
            int gems_collected;
            AllegroFlare::CollisionObservers::Simple collision_observer;
            std::function<void(AllegroFlare::Prototypes::MeshFPS::Screen*, void*)> on_finished_callback_func;
            void* on_finished_callback_func_user_data;
            bool initialized;

         protected:


         public:
            Screen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr, AllegroFlare::GameConfigurations::Base* game_configuration=nullptr, std::vector<AllegroFlare::Prototypes::MeshFPS::Entities::Base*>* entities=nullptr, AllegroFlare::Physics::CollisionMesh* collision_mesh=nullptr);
            virtual ~Screen();

            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_font_bin(AllegroFlare::FontBin* font_bin);
            void set_model_bin(AllegroFlare::ModelBin* model_bin);
            void set_game_configuration(AllegroFlare::GameConfigurations::Base* game_configuration);
            void set_hud_camera(AllegroFlare::Camera2D hud_camera);
            void set_live_camera(AllegroFlare::Camera3D live_camera);
            void set_entities(std::vector<AllegroFlare::Prototypes::MeshFPS::Entities::Base*>* entities);
            void set_collision_mesh(AllegroFlare::Physics::CollisionMesh* collision_mesh);
            void set_visual_mesh(AllegroFlare::Model3D* visual_mesh);
            void set_gems_collected(int gems_collected);
            void set_on_finished_callback_func(std::function<void(AllegroFlare::Prototypes::MeshFPS::Screen*, void*)> on_finished_callback_func);
            void set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data);
            AllegroFlare::EventEmitter* get_event_emitter() const;
            AllegroFlare::GameConfigurations::Base* get_game_configuration() const;
            AllegroFlare::Camera2D get_hud_camera() const;
            AllegroFlare::Camera3D get_live_camera() const;
            std::vector<AllegroFlare::Prototypes::MeshFPS::Entities::Base*>* get_entities() const;
            AllegroFlare::Physics::CollisionMesh* get_collision_mesh() const;
            AllegroFlare::Model3D* get_visual_mesh() const;
            int get_gems_collected() const;
            std::function<void(AllegroFlare::Prototypes::MeshFPS::Screen*, void*)> get_on_finished_callback_func() const;
            void* get_on_finished_callback_func_user_data() const;
            bool get_initialized() const;
            void initialize();
            virtual void on_activate() override;
            virtual void on_deactivate() override;
            AllegroFlare::Prototypes::MeshFPS::Entities::Base* find_0th_entity();
            void create_and_set_player_input_controller_for_0th_entity();
            void update();
            void render();
            void call_on_finished_callback_func();
            virtual void game_event_func(AllegroFlare::GameEvent* game_event=nullptr) override;
            virtual void primary_update_func(double time_now=0.0f, double delta_time=1.0f) override;
            virtual void primary_render_func() override;
            virtual void key_down_func(ALLEGRO_EVENT* ev=nullptr) override;
            virtual void key_up_func(ALLEGRO_EVENT* ev=nullptr) override;
            virtual void virtual_control_button_up_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
            virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
            virtual void virtual_control_axis_change_func(ALLEGRO_EVENT* ev=nullptr) override;
            ALLEGRO_FONT* obtain_hud_font();
         };
      }
   }
}



