#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/WorldMapRenderers/Basic.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();
#include <AllegroFlare/WorldMaps/Maps/Basic.hpp>
#include <AllegroFlare/WorldMaps/Locations/Basic.hpp>


class AllegroFlare_WorldMapRenderers_BasicTest : public ::testing::Test {};
class AllegroFlare_WorldMapRenderers_BasicTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_WorldMapRenderers_BasicTestWithMapAndWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   AllegroFlare::WorldMaps::Maps::Basic map;
   virtual void SetUp()
   {
      AllegroFlare::Testing::WithAllegroRenderingFixture::SetUp();
      map.set_locations({
         { "home",   new AllegroFlare::WorldMaps::Locations::Basic("Home", 20, 20) },
         //{ "office", new AllegroFlare::WorldMaps::Locations::Basic(80, 120) },
         //{ "store",  new AllegroFlare::WorldMaps::Locations::Basic(-100, -30) },
      });
   }
   virtual void TearDown()
   {
      // Cleanup
      //for (auto &location : map.get_locations())
      //{
         //delete location.second;
         //location.second = nullptr;
      //}
      AllegroFlare::Testing::WithAllegroRenderingFixture::TearDown();
   }
};



TEST_F(AllegroFlare_WorldMapRenderers_BasicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::WorldMapRenderers::Basic basic;
}


TEST_F(AllegroFlare_WorldMapRenderers_BasicTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::WorldMapRenderers::Basic basic;
   std::string expected_error_message =
      "Basic::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(basic.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_WorldMapRenderers_BasicTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::WorldMapRenderers::Basic basic;
   std::string expected_error_message =
      "Basic::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(basic.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_WorldMapRenderers_BasicTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::WorldMapRenderers::Basic basic;
   std::string expected_error_message =
      "Basic::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(basic.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_WorldMapRenderers_BasicTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::WorldMapRenderers::Basic basic;
   std::string expected_error_message =
      "Basic::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(basic.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_WorldMapRenderers_BasicTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::WorldMapRenderers::Basic basic(&get_font_bin_ref());
   basic.render();
   al_flip_display();
   sleep_for(1);
}


