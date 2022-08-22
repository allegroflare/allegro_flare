
#include <gtest/gtest.h>

#include <AllegroFlare/Timeline/Track.hpp>


TEST(AllegroFlare_Timeline_TrackTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Timeline::Track track;
}


TEST(AllegroFlare_Timeline_TrackTest, get__when_there_are_no_keyframes__will_return_the_start_value)
{
   AllegroFlare::Timeline::Track track;
   EXPECT_EQ(0.0f, track.get(0.5));
}


TEST(AllegroFlare_Timeline_TrackTest, get__will_return_the_expected_value_interpolated_between_the_keyframes)
{
   // TODO: clear and manage keyframes, maybe copy them by value
   AllegroFlare::Timeline::Track track;
   track.set_keyframes({
      new AllegroFlare::Timeline::Keyframe(0.0, 0.0),
      new AllegroFlare::Timeline::Keyframe(1.0, 100.0),
      new AllegroFlare::Timeline::Keyframe(2.0, 0.0),
   });

   EXPECT_EQ(50.0f, track.get(0.5));
   EXPECT_EQ(10.0f, track.get(0.1));
   EXPECT_EQ(20.0f, track.get(0.2));

   //EXPECT_EQ(100.0f, track.get(1.0));
}


