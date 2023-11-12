#pragma once


#include <AllegroFlare/Placement3D.hpp>
#include <allegro5/allegro.h>
#include <cstdint>
#include <string>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      namespace StagedCharacter
      {
         class Dynamic
         {
         private:
            enum State : uint32_t
            {
               STATE_UNDEF = 0,
               STATE_NORMAL,
               STATE_ENTERING,
               STATE_HIDING,
               STATE_HIDDEN,
            };
            std::string expression;
            ALLEGRO_BITMAP* expression_bitmap;
            AllegroFlare::Placement3D placement;
            AllegroFlare::Placement3D placement_destination;
            float opacity;
            uint32_t state;
            bool state_is_busy;
            float state_changed_at;
            void set_state(uint32_t state=STATE_UNDEF, bool override_if_busy=false);
            void update_state(float time_now=al_get_time());
            bool is_state(uint32_t possible_state=STATE_UNDEF);
            float infer_current_state_age(float time_now=al_get_time());

         protected:


         public:
            Dynamic();
            ~Dynamic();

            void update();
            void render();
            void enter();
            void exit();
            static bool is_valid_state(uint32_t state=STATE_UNDEF);
         };
      }
   }
}



