

#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>



namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{
namespace Entities
{


Base::Base(ALLEGRO_BITMAP* bitmap, AllegroFlare::Placement2D placement)
   : AllegroFlare::ElementID()
   , bitmap(bitmap)
   , placement(placement)
   , cursor_is_over(false)
{
}


Base::~Base()
{
}


void Base::set_bitmap(ALLEGRO_BITMAP* bitmap)
{
   this->bitmap = bitmap;
}


void Base::set_placement(AllegroFlare::Placement2D placement)
{
   this->placement = placement;
}


void Base::set_cursor_is_over(bool cursor_is_over)
{
   this->cursor_is_over = cursor_is_over;
}


ALLEGRO_BITMAP* Base::get_bitmap()
{
   return bitmap;
}


AllegroFlare::Placement2D Base::get_placement()
{
   return placement;
}


bool Base::get_cursor_is_over()
{
   return cursor_is_over;
}


void Base::render()
{
   if (!bitmap) return;
   placement.start_transform();
   if (cursor_is_over) al_draw_tinted_bitmap(bitmap, ALLEGRO_COLOR{0.12, 0.56, 1.0, 1.0}, 0, 0, 0);
   else al_draw_bitmap(bitmap, 0, 0, 0);
   placement.restore_transform();
   return;
}

void Base::update()
{
   return;
}

void Base::on_cursor_enter()
{
   return;
}

void Base::on_cursor_leave()
{
   return;
}

void Base::on_cursor_interact()
{
   return;
}
} // namespace Entities
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


