#pragma once


#include <AllegroFlare/Shaders/Base.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Shaders
   {
      namespace PostProcessing
      {
         class Blinds : public AllegroFlare::Shaders::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/Shaders/PostProcessing/Blinds";

         private:
            int surface_width;
            int surface_height;
            float transition_playhead_position;
            int num_blinds;
            ALLEGRO_COLOR blinds_color;
            bool initialized;
            static std::string obtain_vertex_source();
            static std::string obtain_fragment_source();

         protected:


         public:
            Blinds();
            ~Blinds();

            float get_transition_playhead_position() const;
            int get_num_blinds() const;
            ALLEGRO_COLOR get_blinds_color() const;
            void initialize();
            void set_transition_playhead_position(float transition_playhead_position=0.0f);
            void set_num_blinds(int num_blinds=14);
            void set_blinds_color(ALLEGRO_COLOR blinds_color=ALLEGRO_COLOR{0, 0, 0, 1});
            void activate();
         };
      }
   }
}



