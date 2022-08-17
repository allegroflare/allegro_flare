
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

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
   ASSERT_THROW_WITH_MESSAGE(track_view.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_MotionComposer_TrackViewTestWithAllegroRenderingFixture, DISABLED__render__will_not_blow_up)
{
   AllegroFlare::MotionComposer::TrackView track_view;
   track_view.render();
}


TEST_F(AllegroFlare_MotionComposer_TrackViewTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_the_track_as_expected)
{
   AllegroFlare::Timeline::Track track("opacity", 1.0);
   AllegroFlare::MotionComposer::TrackView track_view(&get_font_bin_ref(), &track);

   clear();
   track_view.render();
   al_flip_display();
   sleep(1);
}


