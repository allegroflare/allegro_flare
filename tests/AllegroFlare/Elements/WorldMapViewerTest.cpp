#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/Elements/WorldMapViewer.hpp>
#include <AllegroFlare/WorldMaps/Locations/Basic.hpp>
#include <AllegroFlare/WorldMaps/Locations/Player.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class AllegroFlare_Elements_WorldMapViewerTest : public ::testing::Test {};
class AllegroFlare_Elements_WorldMapViewerTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_Elements_WorldMapViewerTestWithMapAndWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   AllegroFlare::WorldMaps::Maps::Basic map;
   virtual void SetUp()
   {
      AllegroFlare::Testing::WithAllegroRenderingFixture::SetUp();
      map.set_background_image_identifier("overworld-map-02.png");
      map.set_locations({
         // TODO: Come up with some better location names
         { "home",   new AllegroFlare::WorldMaps::Locations::Basic("Home", 221, 423) },
         { "office2", new AllegroFlare::WorldMaps::Locations::Basic("Office", 611, 268) },
         { "office3", new AllegroFlare::WorldMaps::Locations::Basic("Office", 528, 414) },
         { "office4", new AllegroFlare::WorldMaps::Locations::Basic("Office", 807, 428) },
         { "office5", new AllegroFlare::WorldMaps::Locations::Basic("Office", 584, 713) },
         { "office6", new AllegroFlare::WorldMaps::Locations::Basic("Office", 1054, 335) },
         { "office7", new AllegroFlare::WorldMaps::Locations::Basic("Town 4", 1132, 772) },
         {
            "celestial_crossing_north",
            new AllegroFlare::WorldMaps::Locations::Basic("Celestial Crossing North", 1315, 473)
         },
         {
            "celestial_crossing_south",
            new AllegroFlare::WorldMaps::Locations::Basic("Celestial Crossing South", 1351, 551)
         },
         {
            "luminara",
            new AllegroFlare::WorldMaps::Locations::Basic("Luminara", 1662, 250)
         },
         //{
            //"celestial_crossing_north",
            //new AllegroFlare::WorldMaps::Locations::Basic("Celestial Crossing North", 1662, 250)
         //},
         {
            "crestwood_forest",
            new AllegroFlare::WorldMaps::Locations::Basic("Crestwood Forest", 961, 678)
         },
         {
            "player",
            new AllegroFlare::WorldMaps::Locations::Player(1262, 350)
         },
      });
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



TEST_F(AllegroFlare_Elements_WorldMapViewerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::WorldMapViewer crime_summary;
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTest, initialize__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::WorldMapViewer crime_summary;
   std::string expected_error_message =
      "WorldMapViewer::initialize: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(crime_summary.initialize(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTest, initialize__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::WorldMapViewer crime_summary;
   std::string expected_error_message =
      "WorldMapViewer::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(crime_summary.initialize(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTest, initialize__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::Elements::WorldMapViewer crime_summary;
   std::string expected_error_message =
      "WorldMapViewer::initialize: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(crime_summary.initialize(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTest, initialize__without_ttf_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::Elements::WorldMapViewer crime_summary;
   std::string expected_error_message =
      "WorldMapViewer::initialize: error: guard \"al_is_ttf_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(crime_summary.initialize(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTest, initialize__without_a_bitmap_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   AllegroFlare::Elements::WorldMapViewer crime_summary;
   std::string expected_error_message =
      "WorldMapViewer::initialize: error: guard \"bitmap_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(crime_summary.initialize(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTest, initialize__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   AllegroFlare::BitmapBin bitmap_bin;
   AllegroFlare::Elements::WorldMapViewer crime_summary(&bitmap_bin);
   std::string expected_error_message =
      "WorldMapViewer::initialize: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(crime_summary.initialize(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithAllegroRenderingFixture,
   render__before_initialization__witl_throw_an_error)
{
   AllegroFlare::Elements::WorldMapViewer crime_summary(&get_bitmap_bin_ref(), &get_font_bin_ref());
   std::string expected_error_message =
      "WorldMapViewer::render: error: guard \"initialized\" not met";
   EXPECT_THROW_WITH_MESSAGE(crime_summary.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithAllegroRenderingFixture,
   CAPTURE__render__when_there_are_no_pages__will_render_an_empty_text)
{
   get_bitmap_bin_ref().set_full_path("/Users/markoates/Repos/AllegroFlare/bin/data/bitmaps");
   AllegroFlare::Elements::WorldMapViewer crime_summary(&get_bitmap_bin_ref(), &get_font_bin_ref());
   crime_summary.initialize();
   crime_summary.render();
   al_flip_display();
   //sleep_for(1);
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithAllegroRenderingFixture,
   set_map__will_set_the_map)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithAllegroRenderingFixture,
   set_map__will_reset_the_document_camera_to_the_initial_zoom_and_position)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithAllegroRenderingFixture,
   set_map__will_fit_and_position_pages)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithMapAndWithAllegroRenderingFixture,
   CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Elements::WorldMapViewer crime_summary(&get_bitmap_bin_ref(), &get_font_bin_ref());
   crime_summary.set_map(&map);
   crime_summary.initialize();
   clear();
   crime_summary.render();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithMapAndWithAllegroRenderingFixture,
   CAPTURE__VISUAL__step_zoom_in__will_zoom_in_the_camera_by_one_step__and_loop_back_when_at_the_edge)
{
   AllegroFlare::Elements::WorldMapViewer crime_summary(&get_bitmap_bin_ref(), &get_font_bin_ref());
   crime_summary.set_map(&map);
   crime_summary.initialize();

   int zooms = 5;
   for (int i=0; i<zooms; i++)
   {
      crime_summary.step_zoom_in();
      crime_summary.update();

      clear();
      crime_summary.render();
      al_flip_display();
      sleep_for(0.01);
   }
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithMapAndWithAllegroRenderingFixture,
   CAPTURE__VISUAL__step_zoom_out__will_zoom_out_the_camera_by_one_step__and_loop_back_when_at_the_edge)
{
   AllegroFlare::Elements::WorldMapViewer crime_summary(&get_bitmap_bin_ref(), &get_font_bin_ref());
   crime_summary.set_map(&map);
   crime_summary.initialize();

   int zooms = 6;
   for (int i=0; i<zooms; i++)
   {
      crime_summary.step_zoom_out();
      crime_summary.update();

      clear();
      crime_summary.render();
      al_flip_display();
      sleep_for(0.01);
   }
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithMapAndWithAllegroRenderingFixture,
   CAPTURE__VISUAL__if_the_display_dimensions_are_different_from_virtual_dimensions_of_1920x1080__will_clip_properly)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithMapAndWithAllegroRenderingFixture,
   CAPTURE__VISUAL__with_the_cursor_over_a_location__will_render_as_expected)
{
   AllegroFlare::Elements::WorldMapViewer crime_summary(&get_bitmap_bin_ref(), &get_font_bin_ref());
   crime_summary.set_map(&map);
   crime_summary.initialize();

   //{ "office7", new AllegroFlare::WorldMaps::Locations::Basic("Town 4", 1132, 772) },
   crime_summary.set_cursor(AllegroFlare::Vec2D(1132, 772));

   //cursor_pos

   int zooms = 5;
   for (int i=0; i<zooms; i++)
   {
      //crime_summary.step_zoom_in();
      crime_summary.update();

      clear();
      crime_summary.render();
      al_flip_display();
      sleep_for(0.01);
   }
}


TEST_F(AllegroFlare_Elements_WorldMapViewerTestWithMapAndWithAllegroRenderingFixture,
//TEST_F(AllegroFlare_SoftwareKeyboard_SoftwareKeyboardTestWithAllegroRenderingFixture,
   // TODO: modify this to a TIMED_INTERACTIVE test
   //DISABLED__INTERACTIVE__will_work_as_expected)
   FOCUS__INTERACTIVE__will_work_as_expected)
{
   // setup system
   al_install_keyboard();
   al_install_joystick();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   bool abort = false;
   ALLEGRO_EVENT event;


   AllegroFlare::Elements::WorldMapViewer crime_summary(&get_bitmap_bin_ref(), &get_font_bin_ref());
   crime_summary.set_map(&map);
   crime_summary.initialize();

   // setup environment
   //AllegroFlare::EventEmitter event_emitter;
   //event_emitter.initialize();
   //al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   // initialize test subject
   //AllegroFlare::SoftwareKeyboard::SoftwareKeyboard software_keyboard(&event_emitter, &get_font_bin_ref());
   //software_keyboard.initialize();
   //software_keyboard.set_keys(AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::build_boilerplate_keyboard_keys());
   //AllegroFlare::Vec2D keyboard_dimensions =
      //AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::calculate_boilerplate_keyboard_dimensions();
   //software_keyboard.set_keyboard_dimensions(keyboard_dimensions.x, keyboard_dimensions.y);
   //software_keyboard.set_keyboard_position(1920/2, 1080/12*7 + 20);

   // run the interactive test
   al_start_timer(primary_timer);
   while(!abort)
   {
      al_wait_for_event(event_queue, &event);

      switch(event.type)
      {
         case ALLEGRO_EVENT_KEY_UP:
         {
            switch(event.keyboard.keycode)
            {
               case ALLEGRO_KEY_UP:
               case ALLEGRO_KEY_DOWN: {
                  crime_summary.unset_cursor_moving_vertical();
               } break;

               case ALLEGRO_KEY_LEFT:
               case ALLEGRO_KEY_RIGHT: {
                  crime_summary.unset_cursor_moving_horizontal();
               } break;

               default: {
               } break;
            }
         } break;

         case ALLEGRO_EVENT_KEY_DOWN:
         {
            switch(event.keyboard.keycode)
            {
               case ALLEGRO_KEY_UP:
                  crime_summary.set_cursor_moving_up();
               break;

               case ALLEGRO_KEY_DOWN:
                  crime_summary.set_cursor_moving_down();
               break;

               case ALLEGRO_KEY_RIGHT:
                  crime_summary.set_cursor_moving_right();
               break;

               case ALLEGRO_KEY_LEFT:
                  crime_summary.set_cursor_moving_left();
               break;

               case ALLEGRO_KEY_ENTER:
                  //{
                     //bool shift = (event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT);
                     //if (shift) { software_keyboard.press_key_by_name("SUBMIT"); }
                     //else { software_keyboard.press_key_under_cursor(); }
                  //}
               break;

               case ALLEGRO_KEY_BACKSPACE:
                  //software_keyboard.press_key_by_name("BACKSPACE");
               break;

               case ALLEGRO_KEY_SPACE:
                  //software_keyboard.press_key_by_name("SPACE");
               break;

               case ALLEGRO_KEY_PAD_PLUS:
                  crime_summary.step_zoom_in();
               break;

               case ALLEGRO_KEY_PAD_MINUS:
                  crime_summary.step_zoom_out();
               break;

               default:
                  //std::string s(1, event.keyboard.unichar);
                  //software_keyboard.press_key_by_name(s);
               break;
            }
         }
         break;

         //case ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT:
            //{
               //std::string *emitted_event_data = (std::string *)event.user.data1;
               //if (!emitted_event_data) throw std::runtime_error("Unexpected nullptr sound effect data error");
               //std::cout << "INFO: emitted sound effect event for sound \"" << *emitted_event_data << "\"" << std::endl;
            //}
         //break;

         //case ALLEGRO_FLARE_EVENT_GAME_EVENT:
            //{
               //AllegroFlare::GameEvent *data = static_cast<AllegroFlare::GameEvent *>((void *)event.user.data1);
               //if (!data) throw std::runtime_error("Unexpected GameEvent error");
               //if (data->is_type(
                  //AllegroFlare::SoftwareKeyboard::SoftwareKeyboard::DEFAULT_EVENT_TO_EMIT_ON_PRESSING_SUBMIT_KEY
               //)) abort = true;
            //}
         //break;

         case ALLEGRO_EVENT_TIMER:
            clear();
            crime_summary.update();
            crime_summary.render();
            //software_keyboard.render();
            al_flip_display();
         break;
      }

      if (event.type == ALLEGRO_EVENT_KEY_CHAR && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) abort = true;
   }
   
   // teardown
   // TODO: Audit if this teardown is complete. It may require other calls to destroy resources.
   al_destroy_event_queue(event_queue);
   al_destroy_timer(primary_timer);
   al_uninstall_keyboard();
}




