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
            static constexpr char* TYPE = (char*)"AllegroFlare/Shaders/PostProcessing/Wipe";

         private:
            int surface_width;
            int surface_height;
            float transition_playhead_position;
            bool initialized;
            static std::string obtain_vertex_source();
            static std::string obtain_fragment_source();

         protected:


         public:
            Wipe();
            ~Wipe();

            float get_transition_playhead_position() const;
            void initialize();
            void set_transition_playhead_position(float transition_playhead_position=0.0f);
            void activate();
         };
      }
   }
}



