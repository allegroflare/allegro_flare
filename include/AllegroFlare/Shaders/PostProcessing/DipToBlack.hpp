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
         class DipToBlack : public AllegroFlare::Shaders::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/Shaders/PostProcessing/DipToBlack";

         private:
            int surface_width;
            int surface_height;
            float transition_playhead_position;
            ALLEGRO_COLOR color;
            bool initialized;
            static std::string obtain_vertex_source();
            static std::string obtain_fragment_source();

         protected:


         public:
            DipToBlack();
            ~DipToBlack();

            float get_transition_playhead_position() const;
            ALLEGRO_COLOR get_color() const;
            void initialize();
            void set_transition_playhead_position(float transition_playhead_position=0.0f);
            void set_color(ALLEGRO_COLOR color=ALLEGRO_COLOR{0, 0, 0, 1});
            void activate();
         };
      }
   }
}



