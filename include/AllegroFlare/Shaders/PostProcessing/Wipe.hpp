#pragma once


#include <AllegroFlare/Shaders/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Shaders
   {
      namespace PostProcessing
      {
         class Wipe : public AllegroFlare::Shaders::Base
         {
         public:
            static constexpr char* DIRECTION_UNDEF = (char*)"undefined";
            static constexpr char* DIRECTION_LEFT = (char*)"left";
            static constexpr char* DIRECTION_RIGHT = (char*)"right";
            static constexpr char* TYPE = (char*)"AllegroFlare/Shaders/PostProcessing/Wipe";

         private:
            int surface_width;
            int surface_height;
            float transition_playhead_position;
            std::string direction;
            bool initialized;
            static std::string obtain_vertex_source();
            static std::string obtain_fragment_source();

         protected:


         public:
            Wipe();
            ~Wipe();

            float get_transition_playhead_position() const;
            std::string get_direction() const;
            void initialize();
            void set_transition_playhead_position(float transition_playhead_position=0.0f);
            void set_direction(std::string direction=AllegroFlare::Shaders::PostProcessing::Wipe::DIRECTION_UNDEF);
            static bool is_valid_direction(std::string possibly_valid_direction=AllegroFlare::Shaders::PostProcessing::Wipe::DIRECTION_UNDEF);
            void activate();
         };
      }
   }
}



