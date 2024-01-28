#pragma once


#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         namespace EntityControlConnectors
         {
            class Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Prototypes/Platforming2D/EntityControlConnectors/Base";

            private:
               std::string type;

            protected:


            public:
               Base(std::string type=AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Base::TYPE);
               virtual ~Base();

               std::string get_type() const;
               virtual void update_player_controls_on_player_controlled_entity();
               virtual void key_down_func(ALLEGRO_EVENT* event=nullptr);
               virtual void key_up_func(ALLEGRO_EVENT* event=nullptr);
               bool is_type(std::string possible_type="");
            };
         }
      }
   }
}



