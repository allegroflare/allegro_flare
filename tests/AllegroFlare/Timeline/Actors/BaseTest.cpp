
#include <gtest/gtest.h>

#include <AllegroFlare/Timeline/Actors/Base.hpp>


class ActorsBaseTestClass : public AllegroFlare::Timeline::Actors::Base
{
public:
   ActorsBaseTestClass()
     : Base("ActorsBaseTestClass")
   {}
   virtual void render(double time) override {}
   virtual void register_params() override {}
};


TEST(AllegroFlare_Timeline_Actors_BaseTest, derived_class_can_be_created_without_blowing_up)
{
   ActorsBaseTestClass actor;
}


TEST(AllegroFlare_Timeline_Actors_BaseTest, DISABLED__load_script__will_create_keyframes_on_the_tracks)
{
   // TODO
}



