#pragma once


#include <Wicked/Entities/Basic2D.hpp>
#include <string>


namespace Wicked
{
   namespace Entities
   {
      namespace Doors
      {
         class Basic2D : public Wicked::Entities::Basic2D
         {
         private:
            std::string target_map_name;
            float target_spawn_x;
            float target_spawn_y;

         protected:


         public:
            Basic2D(std::string target_map_name="[unset-target-map-name]", float target_spawn_x=0.0f, float target_spawn_y=0.0f);
            ~Basic2D();

            void set_target_map_name(std::string target_map_name);
            void set_target_spawn_x(float target_spawn_x);
            void set_target_spawn_y(float target_spawn_y);
            std::string get_target_map_name() const;
            float get_target_spawn_x() const;
            float get_target_spawn_y() const;
            std::string run();
         };
      }
   }
}



