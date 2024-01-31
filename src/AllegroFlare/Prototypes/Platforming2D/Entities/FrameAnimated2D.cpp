

#include <AllegroFlare/Prototypes/Platforming2D/Entities/FrameAnimated2D.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{
namespace Entities
{


FrameAnimated2D::FrameAnimated2D(AllegroFlare::FrameAnimation::Book* animation_book)
   : AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D()
   , animation_book(animation_book)
   , animation({})
{
}


FrameAnimated2D::~FrameAnimated2D()
{
}


void FrameAnimated2D::set_animation_book(AllegroFlare::FrameAnimation::Book* animation_book)
{
   this->animation_book = animation_book;
}


AllegroFlare::FrameAnimation::Book* FrameAnimated2D::get_animation_book() const
{
   return animation_book;
}


void FrameAnimated2D::update()
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::update(); // just updates the movement strategy
   //Basic2D
   animation.update();
   refresh_bitmap();

   //fit_to_bitmap(); // TODO: see if there is a better way/place to have the bitmap fitting
   //place.position += velocity.position; // <-- this is now managed in the stepper
   //place.rotation += velocity.rotation;

   //place.scale += velocity.scale; // TODO: figure out what/how to apply scale velocity
   // TODO: align, size, anchor, flip

   return;
}

void FrameAnimated2D::refresh_bitmap()
{
   set_bitmap(animation.get_frame_now());
   //fit_to_bitmap(); // This may be redundant, however it's not yet determined if Animation/Book will
                    // always be returning fixed size bitmaps.  Also, in some scenarios it's likely the
                    // collision box will be different from the bitmap, and for the time being it appears
                    // the two are considered the same.
   return;
}

void FrameAnimated2D::set_animation_playback_rate(float multiplier)
{
   animation.set_playspeed_multiplier(multiplier);
   return;
}

bool FrameAnimated2D::get_animation_finished()
{
   return animation.get_finished();
}

int FrameAnimated2D::get_current_animation_frame_num()
{
   return animation.get_frame_num_now();
}

void FrameAnimated2D::set_animation(std::string animation_name)
{
   if (!(animation_book))
   {
      std::stringstream error_message;
      error_message << "[FrameAnimated2D::set_animation]: error: guard \"animation_book\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FrameAnimated2D::set_animation: error: guard \"animation_book\" not met");
   }
   if (!(animation_book->animation_exists(animation_name)))
   {
      std::stringstream error_message;
      error_message << "[FrameAnimated2D::set_animation]: error: guard \"animation_book->animation_exists(animation_name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FrameAnimated2D::set_animation: error: guard \"animation_book->animation_exists(animation_name)\" not met");
   }
   animation = animation_book->find_animation_by_name(animation_name);
   animation.initialize();
   animation.start(); // NOTE: consider if automatic "start" is needed here
   refresh_bitmap();
   return;
}


} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


