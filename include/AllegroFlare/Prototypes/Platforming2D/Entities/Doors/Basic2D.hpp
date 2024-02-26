#pragma once


#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         namespace Entities
         {
            namespace Doors
            {
               class Basic2D : public AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D
               {
               private:
                  std::string game_event_name_to_emit;
                  std::string target_map_name;
                  float target_spawn_x;
                  float target_spawn_y;
                  bool is_locked;

               protected:


               public:
                  Basic2D(std::string game_event_name_to_emit="[unset-game_event_name_to_emit]", std::string target_map_name="[unset-target_map_name]", float target_spawn_x=0.0f, float target_spawn_y=0.0f);
                  ~Basic2D();

                  void set_game_event_name_to_emit(std::string game_event_name_to_emit);
                  void set_target_map_name(std::string target_map_name);
                  void set_target_spawn_x(float target_spawn_x);
                  void set_target_spawn_y(float target_spawn_y);
                  void set_is_locked(bool is_locked);
                  std::string get_game_event_name_to_emit() const;
                  std::string get_target_map_name() const;
                  float get_target_spawn_x() const;
                  float get_target_spawn_y() const;
                  bool get_is_locked() const;
               };
            }
         }
      }
   }
}



