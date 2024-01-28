

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

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace EntityControlConnectors
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


