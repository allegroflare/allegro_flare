

#include <AllegroFlare/Prototypes/Platforming2D/EntityControlConnectors/Base.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{
namespace EntityControlConnectors
{


Base::Base(std::string type)
   : type(type)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


void Base::update_player_controls_on_player_controlled_entity()
{
   // TODO: Throw on not implemented
   // TODO: Add "time_now" and "delta_time" parameter
   return;
}

void Base::key_down_func(ALLEGRO_EVENT* event)
{
   // TODO: Throw on not implemented

   // Typically something like:

   //switch (event->keyboard.keycode)
   //{
      //case ALLEGRO_KEY_LEFT:
         // ...
      //break;

      //case ALLEGRO_KEY_RIGHT:
         // ...
      //break;

      //case ALLEGRO_KEY_UP:
         // ...
      //break;

      //case ALLEGRO_KEY_DOWN:
         // ...
      //break;

      //case ALLEGRO_KEY_SPACE:
         // ...
      //break;
   //}

   return;
}

void Base::key_up_func(ALLEGRO_EVENT* event)
{
   // TODO: Throw on not implemented
   // NOTE: See "key_down_func" for a typical example usage
   return;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace EntityControlConnectors
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


