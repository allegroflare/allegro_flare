#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/WorldMapRenderers/Basic.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();
#include <AllegroFlare/WorldMaps/Maps/Basic.hpp>
#include <AllegroFlare/WorldMaps/Locations/Basic.hpp>
#include <AllegroFlare/Logger.hpp>


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
      map.set_background_image_identifier("overworld-map-02.png");
      map.set_locations({
         { "home",   new AllegroFlare::WorldMaps::Locations::Basic("Home", 221, 423) },
         { "office", new AllegroFlare::WorldMaps::Locations::Basic("Office", 1351, 551) },
         { "office2", new AllegroFlare::WorldMaps::Locations::Basic("Office", 611, 268) },
         { "office3", new AllegroFlare::WorldMaps::Locations::Basic("Office", 528, 414) },
         { "office4", new AllegroFlare::WorldMaps::Locations::Basic("Office", 807, 428) },
         { "office5", new AllegroFlare::WorldMaps::Locations::Basic("Office", 584, 713) },

         { "office6", new AllegroFlare::WorldMaps::Locations::Basic("Office", 1054, 335) },
         { "office7", new AllegroFlare::WorldMaps::Locations::Basic("Office", 1132, 772) },
         { "office8", new AllegroFlare::WorldMaps::Locations::Basic("Office", 1315, 473) },
         { "office9", new AllegroFlare::WorldMaps::Locations::Basic("Office", 1662, 250) },
         { "office10", new AllegroFlare::WorldMaps::Locations::Basic("Office", 961, 678) }, // Forrest

         //{ "store",  new AllegroFlare::WorldMaps::Locations::Basic("Store", -100, -30) },
      });
      //map.set_background_image_identifier("overworld-map-02.png");
   }
   virtual void TearDown()
   {
      // Cleanup
      for (auto &location : map.get_locations())
      {
         delete location.second;
         location.second = nullptr;
      }
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
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "AllegroFlare::WorldMapRenderers::Basic::render",
      "al_is_system_installed()"
   );
   EXPECT_THROW_WITH_MESSAGE(basic.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_WorldMapRenderers_BasicTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::WorldMapRenderers::Basic basic;
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "AllegroFlare::WorldMapRenderers::Basic::render",
      "al_is_primitives_addon_initialized()"
   );
   EXPECT_THROW_WITH_MESSAGE(basic.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_WorldMapRenderers_BasicTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::WorldMapRenderers::Basic basic;
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "AllegroFlare::WorldMapRenderers::Basic::render",
      "al_is_font_addon_initialized()"
   );
   EXPECT_THROW_WITH_MESSAGE(basic.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_WorldMapRenderers_BasicTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::WorldMaps::Maps::Basic map;
   map.set_background_image_identifier("overworld-map-02.png");
   AllegroFlare::WorldMapRenderers::Basic basic(&get_bitmap_bin_ref(), &get_font_bin_ref(), &map);
   basic.render();
   al_flip_display();
}


TEST_F(AllegroFlare_WorldMapRenderers_BasicTestWithMapAndWithAllegroRenderingFixture,
   CAPTURE__render__with_locations_on_the_map__will_not_blow_up)
{
   AllegroFlare::WorldMapRenderers::Basic renderer(&get_bitmap_bin_ref(), &get_font_bin_ref(), &map);
   clear();
   renderer.render();
   al_flip_display();
   sleep_for(1);
}


