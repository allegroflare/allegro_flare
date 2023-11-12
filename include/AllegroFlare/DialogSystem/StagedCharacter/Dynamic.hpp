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
            AllegroFlare::Placement3D placement;
            ALLEGRO_BITMAP* expression_bitmap;
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
            Dynamic(std::string expression="[unset-bitmap_identifier]", AllegroFlare::Placement3D placement={});
            ~Dynamic();

            void set_expression(std::string expression);
            void set_placement(AllegroFlare::Placement3D placement);
            void set_expression_bitmap(ALLEGRO_BITMAP* expression_bitmap);
            void set_opacity(float opacity);
            std::string get_expression() const;
            AllegroFlare::Placement3D get_placement() const;
            ALLEGRO_BITMAP* get_expression_bitmap() const;
            float get_opacity() const;
            void update();
            void render();
            void enter();
            void exit();
            static bool is_valid_state(uint32_t state=STATE_UNDEF);
         };
      }
   }
}



