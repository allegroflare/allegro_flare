
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_MotionComposer_TrackViewTest : public ::testing::Test
{};

class AllegroFlare_MotionComposer_TrackViewTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/MotionComposer/TrackView.hpp>


TEST_F(AllegroFlare_MotionComposer_TrackViewTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MotionComposer::TrackView track_view;
}


TEST_F(AllegroFlare_MotionComposer_TrackViewTest, DISABLED__render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::MotionComposer::TrackView track_view;
   std::string expected_error_message =
      "TrackView::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(track_view.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_MotionComposer_TrackViewTestWithAllegroRenderingFixture, DISABLED__render__will_not_blow_up)
{
   AllegroFlare::MotionComposer::TrackView track_view;
   track_view.render();
}


TEST_F(AllegroFlare_MotionComposer_TrackViewTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_the_track_as_expected)
{
   AllegroFlare::Timeline::Track track("opacity", 1.0, {
      new AllegroFlare::Timeline::Keyframe(2.0, 0.4),
      new AllegroFlare::Timeline::Keyframe(4.0, 0.6),
      new AllegroFlare::Timeline::Keyframe(5.0, 0.2),
      new AllegroFlare::Timeline::Keyframe(5.5, 0.3),
   });
   AllegroFlare::MotionComposer::TrackView track_view(&get_font_bin_ref(), &track);
   track_view.set_selection_cursor_x(1);

   AllegroFlare::Placement2D place = build_centered_placement(track_view.get_width(), track_view.get_height());

   clear();
   place.start_transform();
   track_view.render();
   place.restore_transform();
   al_flip_display();
   sleep_for(1);
}


