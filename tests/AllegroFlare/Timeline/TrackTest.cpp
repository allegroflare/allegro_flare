
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


TEST(AllegroFlare_Timeline_TrackTest,
   get__when_one_keyframe_is_present__will_return_the_value_of_the_keyframe_regardless_of_time)
{
   AllegroFlare::Timeline::Track track;
   track.set_keyframes({
      new AllegroFlare::Timeline::Keyframe(2.0, 123.0),
   });
   EXPECT_EQ(123.0f, track.get(-0.5));
}


TEST(AllegroFlare_Timeline_TrackTest,
   get__with_a_time_less_than_the_first_keyframe__will_return_the_value_of_the_first_keyframe)
{
   AllegroFlare::Timeline::Track track;
   track.set_keyframes({
      new AllegroFlare::Timeline::Keyframe(1.0, 20.0),
      new AllegroFlare::Timeline::Keyframe(2.0, 80.0),
      new AllegroFlare::Timeline::Keyframe(3.0, 160.0),
   });

   EXPECT_EQ(20.0f, track.get(0.999));
   EXPECT_EQ(20.0f, track.get(0.0));
   EXPECT_EQ(20.0f, track.get(-999.0));
}


TEST(AllegroFlare_Timeline_TrackTest,
   get__with_a_time_greater_than_the_last_keyframe__will_return_the_value_of_the_last_keyframe)
{
   AllegroFlare::Timeline::Track track;
   track.set_keyframes({
      new AllegroFlare::Timeline::Keyframe(0.0, 1.0),
      new AllegroFlare::Timeline::Keyframe(1.0, 4.0),
      new AllegroFlare::Timeline::Keyframe(2.0, 9.0),
   });

   EXPECT_EQ(9.0f, track.get(2.0001));
   EXPECT_EQ(9.0f, track.get(999.0));
}


TEST(AllegroFlare_Timeline_TrackTest,
   get__with_a_time_between_two_keyframes__will_interpolate_the_value_between_the_keyframes)
{
   AllegroFlare::Timeline::Track track;
   track.set_keyframes({
      new AllegroFlare::Timeline::Keyframe(0.0, 1.0),
      new AllegroFlare::Timeline::Keyframe(2.0, 2.0),
   });
   EXPECT_EQ(1.5f, track.get(1.0));
}


TEST(AllegroFlare_Timeline_TrackTest,
   get__with_this_particular_set_of_for_some_reason_buggy_keyframes__will_interpolate_as_expected)
{
   AllegroFlare::Timeline::Track track;
   track.set_keyframes({
      new AllegroFlare::Timeline::Keyframe(0.0, 0.0),
      new AllegroFlare::Timeline::Keyframe(0.2, 1.0),
      new AllegroFlare::Timeline::Keyframe(1.9, 1.0),
   });
   EXPECT_EQ(1.5f, track.get(1.0));
}


TEST(AllegroFlare_Timeline_TrackTest,
   get__with_a_time_on_a_keyframe__will_return_the_value_of_the_keyframe)
{
   AllegroFlare::Timeline::Track track;
   track.set_keyframes({
      new AllegroFlare::Timeline::Keyframe(0.0, 100.0),
      new AllegroFlare::Timeline::Keyframe(1.0, 200.0),
      new AllegroFlare::Timeline::Keyframe(2.0, 300.0),
      new AllegroFlare::Timeline::Keyframe(3.0, 400.0),
   });
   EXPECT_EQ(300.0f, track.get(2.0));
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

   EXPECT_EQ(100.0f, track.get(1.0));
}


