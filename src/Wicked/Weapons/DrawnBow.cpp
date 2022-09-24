

#include <Wicked/Weapons/DrawnBow.hpp>

#include <AllegroFlare/Interpolators.hpp>


namespace Wicked
{
namespace Weapons
{


DrawnBow::DrawnBow()
   : Wicked::Weapons::Base()
   , draw_back_value(1.0f)
   , being_drawn(false)
{
}


DrawnBow::~DrawnBow()
{
}


bool DrawnBow::get_being_drawn() const
{
   return being_drawn;
}


void DrawnBow::stop_draw()
{
   if (!being_drawn) return;
   draw_back_value = 1.0f;
   being_drawn = false;
}

void DrawnBow::start_draw()
{
   if (being_drawn) return;
   draw_back_value = 1.0f;
   being_drawn = true;
}

float DrawnBow::get_strength()
{
   if (at_max()) return 1.0f;
   return (1.0f - draw_back_value);
}

bool DrawnBow::at_max()
{
   float strength = (1.0f - draw_back_value);
   if (strength >= (1.0f - 0.0001f)) return true;
   return false;
}

float DrawnBow::get_strength_value_styled()
{
   if (at_max()) return 1.0f;
   float strength = get_strength();
   return AllegroFlare::interpolator::tripple_fast_in(strength) * 0.85;
}

void DrawnBow::update()
{
   if (being_drawn)
   {
      float draw_back_rate = 0.025f;
      draw_back_value -= draw_back_rate;
      if (draw_back_value <= 0.0f) draw_back_value = 0.0f;
   }
   return;
}


} // namespace Weapons
} // namespace Wicked


