

#include <AllegroFlare/TransitionFX/Base.hpp>



namespace AllegroFlare
{
namespace TransitionFX
{


Base::Base()
   : surface_A(nullptr)
   , surface_B(nullptr)
   , duration(2.0f)
   , position(0.0f)
   , finished(false)
   , initialized(false)
{
}


Base::~Base()
{
}


ALLEGRO_BITMAP* Base::get_surface_A()
{
   return surface_A;
}


ALLEGRO_BITMAP* Base::get_surface_B()
{
   return surface_B;
}


bool Base::get_finished()
{
   return finished;
}


void Base::update()
{
   position += 1.0 / 60.0;
   if (position >= duration) finished = true;
   return;
}

void Base::draw()
{
   float alpha = 1.0 - (duration - position) / duration;
   al_draw_bitmap(surface_A, 0, 0, 0);
   al_draw_tinted_bitmap(surface_B, ALLEGRO_COLOR{alpha, alpha, alpha, alpha}, 0, 0, 0);
   return;
}
} // namespace TransitionFX
} // namespace AllegroFlare


