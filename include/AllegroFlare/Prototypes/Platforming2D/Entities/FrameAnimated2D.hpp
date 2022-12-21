#pragma once


#include <AllegroFlare/FrameAnimation/Animation.hpp>
#include <AllegroFlare/FrameAnimation/Book.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         namespace Entities
         {
            class FrameAnimated2D : public AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D
            {
            public:
               static constexpr char* TYPE = (char*)"Entities/FrameAnimated2D";

            private:
               AllegroFlare::FrameAnimation::Book* animation_book;
               AllegroFlare::FrameAnimation::Animation animation;

            protected:


            public:
               FrameAnimated2D(AllegroFlare::FrameAnimation::Book* animation_book=nullptr);
               virtual ~FrameAnimated2D();

               void set_animation_book(AllegroFlare::FrameAnimation::Book* animation_book);
               AllegroFlare::FrameAnimation::Book* get_animation_book() const;
               virtual void update() override;
               void refresh_bitmap();
               void set_animation_playback_rate(float multiplier=1.0f);
               void set_animation(std::string animation_name="[unset-animation_name]");
            };
         }
      }
   }
}



