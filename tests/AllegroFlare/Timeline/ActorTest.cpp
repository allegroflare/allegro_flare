
#include <gtest/gtest.h>

#include <AllegroFlare/Timeline/Actor.hpp>


class ActorTestClass : public AllegroFlare::Timeline::Actor
{
public:
   ActorTestClass()
     : Actor("ActorTestClass", 1)
   {}
   virtual void render(double time) override {}
   virtual void register_params() override {}
};


TEST(AllegroFlare_Timeline_ActorTest, derived_class_can_be_created_without_blowing_up)
{
   ActorTestClass actor;
}


TEST(AllegroFlare_Timeline_ActorTest, load_script__will_create_keyframes_on_the_tracks)
{
   ActorTestClass actor;
}



