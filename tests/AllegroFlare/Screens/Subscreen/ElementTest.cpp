
#include <gtest/gtest.h>

#include <AllegroFlare/Screens/Subscreen/Element.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <allegro5/allegro_primitives.h>


#include <AllegroFlare/Screens/Subscreen/Panes/Base.hpp>

class TestPaneA : public AllegroFlare::Screens::Subscreen::Panes::Base
{
private:
   AllegroFlare::FontBin *font_bin;

public:
   TestPaneA(AllegroFlare::FontBin *font_bin, std::string name)
      : AllegroFlare::Screens::Subscreen::Panes::Base("TestPaneA", name)
      , font_bin(font_bin)
   {};
   virtual void on_switch_in() override {};
   virtual void on_switch_out() override {};
   virtual void update() override {};
   virtual void render() override
   {
      // Just draw a nice little pane
      static constexpr float frame_width = 1920;
      static constexpr float frame_height = 1080;
      static constexpr float width = frame_width - 100 * 2;  // (1720)
      static constexpr float height = frame_height - 142 * 2; // (796)
      static constexpr float cx = frame_width / 2;
      static constexpr float cy = frame_height / 2;

      static constexpr float x1 = cx - width * 0.5;;
      static constexpr float y1 = cy - height * 0.5;
      static constexpr float x2 = cx + width * 0.5;
      static constexpr float y2 = cy + height * 0.5;

      al_draw_rectangle(x1, y1, x2, y2, ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2}, 2.0f);
      // TODO: Consider if font_bin should be verified
      static const std::string FONT_IDENTIFIER = "Inter-Medium.ttf -36";
      ALLEGRO_FONT* font = font_bin->operator[](FONT_IDENTIFIER);

      al_draw_text(
            font,
            ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2},
            1920 * 0.5,
            1080 * 0.5,
            ALLEGRO_ALIGN_CENTER,
            get_name().c_str()
         );
   };
};


class AllegroFlare_Screens_Subscreen_ElementTest : public ::testing::Test {};
class AllegroFlare_Screens_Subscreen_ElementTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_Screens_Subscreen_ElementTestWithAllegroRenderingFixtureAndPanes
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   AllegroFlare::Screens::Subscreen::Element subscreen_element;

   virtual void SetUp() override
   {
      AllegroFlare::Testing::WithAllegroRenderingFixture::SetUp();
      // TODO: Setup asset paths and create panes, e.g.:
      //get_bitmap_bin_ref().set_full_path("/Users/markoates/Repos/CatDetective/bin/data/bitmaps/");
      AllegroFlare::FontBin *font_bin = &get_font_bin_ref();
      AllegroFlare::BitmapBin *bitmap_bin = &get_bitmap_bin_ref();

      subscreen_element.set_bitmap_bin(bitmap_bin);
      subscreen_element.set_font_bin(font_bin);
      subscreen_element.set_panes({
         new TestPaneA(font_bin, "Pane 1: Inventory"),
         new TestPaneA(font_bin, "Pane 2: Map"),
         new TestPaneA(font_bin, "Pane 3: Settings"),
      });

      subscreen_element.initialize();
   }

   virtual void TearDown() override
   {
      // Delete all of the panes
      for (auto &pane : subscreen_element.get_panes_ref()) delete pane;
      subscreen_element.clear_panes();

      AllegroFlare::Testing::WithAllegroRenderingFixture::TearDown();
   }
};



TEST_F(AllegroFlare_Screens_Subscreen_ElementTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::Subscreen::Element subscreen_element;
}


TEST_F(AllegroFlare_Screens_Subscreen_ElementTest,
   initialize__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Screens::Subscreen::Element subscreen_element;
   std::string expected_error_message =
      "Element::initialize: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(subscreen_element.initialize(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Screens_Subscreen_ElementTest,
   initialize__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Screens::Subscreen::Element subscreen_element;
   std::string expected_error_message =
      "Element::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(subscreen_element.initialize(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Screens_Subscreen_ElementTest,
   initialize__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::Screens::Subscreen::Element subscreen_element;
   std::string expected_error_message =
      "Element::initialize: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(subscreen_element.initialize(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Screens_Subscreen_ElementTest,
   initialize__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::Screens::Subscreen::Element subscreen_element;
   std::string expected_error_message =
      "Element::initialize: error: guard \"al_is_ttf_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(subscreen_element.initialize(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Screens_Subscreen_ElementTestWithAllegroRenderingFixture,
   render__without_initialization__will_throw_an_error)
{
   AllegroFlare::Screens::Subscreen::Element subscreen_element;
   std::string expected_error_message =
      "Element::render: error: guard \"initialized\" not met";
   EXPECT_THROW_WITH_MESSAGE(subscreen_element.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Screens_Subscreen_ElementTestWithAllegroRenderingFixture, initialize__will_work_as_expected)
{
   AllegroFlare::Screens::Subscreen::Element subscreen_element;
   subscreen_element.set_bitmap_bin(&get_bitmap_bin_ref());
   subscreen_element.set_font_bin(&get_font_bin_ref());
   subscreen_element.initialize();
}


TEST_F(AllegroFlare_Screens_Subscreen_ElementTestWithAllegroRenderingFixture,
   initialize__when_panes_are_present__will_work_as_expected)
{
   AllegroFlare::Screens::Subscreen::Element subscreen_element;
   AllegroFlare::FontBin *font_bin = &get_font_bin_ref();
   AllegroFlare::BitmapBin *bitmap_bin = &get_bitmap_bin_ref();
   subscreen_element.set_bitmap_bin(bitmap_bin);
   subscreen_element.set_font_bin(font_bin);
   subscreen_element.set_panes({
      new TestPaneA(font_bin, "Pane 1: Inventory"),
      new TestPaneA(font_bin, "Pane 2: Map"),
      new TestPaneA(font_bin, "Pane 3: Settings"),
   });
   subscreen_element.initialize();
}


TEST_F(AllegroFlare_Screens_Subscreen_ElementTestWithAllegroRenderingFixtureAndPanes,
   move_pane_right__when_there_are_more_panes_to_the_right__will_return_true)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_Subscreen_ElementTestWithAllegroRenderingFixtureAndPanes,
   move_pane_right__when_at_the_last_pane__will_return_false)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_Subscreen_ElementTestWithAllegroRenderingFixtureAndPanes,
   move_pane_left__when_there_are_more_panes_to_the_left__will_return_true)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_Subscreen_ElementTestWithAllegroRenderingFixtureAndPanes,
   move_pane_left__when_at_the_last_pane__will_return_false)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_Subscreen_ElementTestWithAllegroRenderingFixtureAndPanes,
   CAPTURE__render__will_not_blow_up)
{
   subscreen_element.render();
   al_flip_display();
}


TEST_F(AllegroFlare_Screens_Subscreen_ElementTestWithAllegroRenderingFixtureAndPanes,
   render__when_a_background_bitmap_is_present__will_render_the_background)
{
   // NOTE: Not sure if background should even be included here or not
   // TODO: Consider removing this test
}


TEST_F(AllegroFlare_Screens_Subscreen_ElementTestWithAllegroRenderingFixtureAndPanes,
   DISABLED__INTERACTIVE__will_work_as_expected)
   //INTERACTIVE__will_work_as_expected)
{
   // Setup interactive components not already setup in WithAllegroRenderingFixture
   al_install_keyboard();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   //AllegroFlare::EventEmitter event_emitter;
   //event_emitter.initialize();
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   //al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   // Setup subject here
   // Fill our dependencies with test data
   //fill_evidence_sheet_inventory_dictionary_with_fixture_data();
   //fill_evidence_sheet_inventory_with_fixture_data();
   //fill_rap_sheets_inventory();
   //fill_rap_sheets_inventory_dictionary();

   // TODO: note this can only be called after initialization, indicating a design flaw.
   // This indicates a design issue, pointing to a the migration to concrete types for the panes inside Chronicle.
   //fill_crime_summary_pages(&chronicle);

   al_start_timer(primary_timer);
   bool abort = false;
   while(!abort)
   {
      ALLEGRO_EVENT current_event;
      al_wait_for_event(event_queue, &current_event);
      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            clear_display();
            subscreen_element.update();
            subscreen_element.render();
            //chronicle.update();
            //chronicle.render();
            al_flip_display();
         }
         break;

         case ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT:
         {
            std::cout << "[AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest]: INFO: "
                      << "Play sound effect event was emitted. "
                      << std::endl;
         }
         break;

         case ALLEGRO_EVENT_KEY_UP:
         {
            bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_UP:
                  //if (!shift) chronicle.cursor_up_unpressed();
               break;

               case ALLEGRO_KEY_DOWN:
                  //if (!shift) chronicle.cursor_down_unpressed();
               break;

               case ALLEGRO_KEY_LEFT:
                  //if (!shift) chronicle.cursor_left_unpressed();
               break;

               case ALLEGRO_KEY_RIGHT:
                  //if (!shift) chronicle.cursor_right_unpressed();
               break;
            }
         }
         break;

         case ALLEGRO_EVENT_KEY_DOWN:
         {
            bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_UP:
                  //if (!shift) chronicle.cursor_up_pressed();
               break;

               case ALLEGRO_KEY_DOWN:
                  //if (!shift) chronicle.cursor_down_pressed();
               break;

               case ALLEGRO_KEY_LEFT:
                  //if (!shift) chronicle.cursor_left_pressed();
               break;

               case ALLEGRO_KEY_RIGHT:
                  //if (!shift) chronicle.cursor_right_pressed();
               break;
            }
         }
         break;

         case ALLEGRO_EVENT_KEY_CHAR:
         {
            bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            switch(current_event.keyboard.keycode)
            {

               case ALLEGRO_KEY_UP:
                  //chronicle.move_cursor_up();
               break;

               case ALLEGRO_KEY_DOWN:
                  //chronicle.move_cursor_down();
               break;

               case ALLEGRO_KEY_N:
                  //chronicle.current_pane_page_next();
               break;

               case ALLEGRO_KEY_P:
                  //chronicle.current_pane_page_previous();
               break;

               case ALLEGRO_KEY_R:
                  //chronicle.reset_document_camera();
               break;

               case ALLEGRO_KEY_LEFT:
                  if (shift) { subscreen_element.move_pane_left(); }
                  else { subscreen_element.move_cursor_left(); }
               break;

               case ALLEGRO_KEY_RIGHT:
                  if (shift) { subscreen_element.move_pane_right(); }
                  else { subscreen_element.move_cursor_right(); }
               break;

               case ALLEGRO_KEY_PAD_MINUS:
               case ALLEGRO_KEY_MINUS: // (minus)
                  //chronicle.pane_camera_zoom_out();
               break;

               case ALLEGRO_KEY_PAD_PLUS:
               case ALLEGRO_KEY_EQUALS: // (plus)
                  //chronicle.pane_camera_zoom_in();
               break;

               case ALLEGRO_KEY_ESCAPE:
                  abort = true;
               break;
            }
         }
         break;
      }
   }

   //al_unregister_event_source(event_queue, &event_emitter.get_event_source_ref());
   al_destroy_timer(primary_timer);
}


























// NOTE: This example code below demonstrates test fixtures and setup for rendering and using Subscreen Element
// interactively

/*
//#include <gtest/gtest.h>

//#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   //try { code; FAIL() << "Expected " # raised_exception_type; } \
   //catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   //catch (...) { FAIL() << "Expected " # raised_exception_type; }

//#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

//#include <CatDetective/Chronicle/Chronicle.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/InventoryDictionaryItems/WithAttributes.hpp>


class CatDetective_Chronicle_ChronicleTest : public ::testing::Test {};
class CatDetective_Chronicle_ChronicleTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class CatDetective_Chronicle_ChronicleTestWithAllegroRenderingFixtureAndDependencies
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   AllegroFlare::InventoryDictionary evidence_sheet_inventory_dictionary;
   AllegroFlare::Inventory evidence_sheet_inventory;
   AllegroFlare::InventoryDictionary rap_sheets_inventory_dictionary;
   AllegroFlare::Inventory rap_sheets_inventory;

   virtual void SetUp() override
   {
      AllegroFlare::Testing::WithAllegroRenderingFixture::SetUp();
      get_bitmap_bin_ref().set_full_path("/Users/markoates/Repos/CatDetective/bin/data/bitmaps/");
   }

   void fill_evidence_sheet_inventory_dictionary_with_fixture_data()
   {
      using AllegroFlare::InventoryDictionaryItems::WithAttributes;

      WithAttributes *scratches_on_the_vault = new WithAttributes();
      scratches_on_the_vault->set("name", "Scratches on the vault");
      scratches_on_the_vault->set("image_identifier", "scratches-on-vault-01.png");
      scratches_on_the_vault->set("description", "Multiple deep scratches were found at and around the vault's lock, "
                                                 "indicating there had been multiple unsuccessful attempts break into "
                                                 "the vault.");

      WithAttributes *paw_prints_in_the_dust = new WithAttributes();
      paw_prints_in_the_dust->set("name", "Paw prints in the dust");
      paw_prints_in_the_dust->set("image_identifier", "paw-prints-in-dust-01.png");
      paw_prints_in_the_dust->set("description", "Paw prints were found conspicuously scattered all across the ground "
                                                 "on dust that had apparently piled up while the thief was attempting "
                                                 "to scratch through the safe.");

      WithAttributes *spilled_milk = new WithAttributes();
      spilled_milk->set("name", "Spilled milk");
      spilled_milk->set("image_identifier", "spilled-milk-01.png");
      spilled_milk->set("description", "A glass of spilled milk was found near the scene of the crime. The splatter "
                                       "mark on the ground suggests that the glass had tipped over slowly when it "
                                       "spilled. A forensic analysis "
                                       "by the CCPD lab indicated that there were no paw prints on the glass.");

      evidence_sheet_inventory_dictionary.set_dictionary({
         { 1, scratches_on_the_vault },
         { 2, paw_prints_in_the_dust },
         { 3, spilled_milk},
      });
   }

   void fill_evidence_sheet_inventory_with_fixture_data()
   {
      evidence_sheet_inventory.add_items({ 1, 2, 3 });
   }

   void fill_rap_sheets_inventory_dictionary()
   {
      using AllegroFlare::InventoryDictionaryItems::WithAttributes;
      //AllegroFlare::InventoryDictionary result;

      WithAttributes *famous_fem = new WithAttributes();
      famous_fem->set("name", "Famous Fem Cat");
      famous_fem->set("age", "Young adult");
      famous_fem->set("breed", "Egyptian Mau");
      famous_fem->set("description", "One of the most famous celebrities on the planet. With more followers "
                                     "on Chirp than anybody else, Famous Fem Cat is a definitive voice "
                                     "of trends and style.");
      famous_fem->set("portrait_bitmap_identifier", "famous-fem-portrait-01.png");

      WithAttributes *mystery_cat = new WithAttributes();
      mystery_cat->set("name",  "Mystery Cat");
      mystery_cat->set("age",   "Unknown");
      mystery_cat->set("breed", "Unknown");
      mystery_cat->set("description", "Only appearing in the shadows, their role and identity is unknown. Somehow "
                                      "having access to insider information, they have an important need to share it.");
      mystery_cat->set("portrait_bitmap_identifier", "mystery-cat-profile-feature-01.png");

      //scratches_on_the_vault->set("name", "Police Commissioner Cat");
      //scratches_on_the_vault->set("age", "Young adult");
      //scratches_on_the_vault->set("breed", "Siamese");
      //scratches_on_the_vault->set("description", "One of the hottest celebrities on the planet. With more followers "
                                                 //"on Chirp than anybody else, Famous Fem Cat is a definitive voice "
                                                 //"of trends and style.");
      //scratches_on_the_vault->set("portrait_bitmap_identifier", "police-commissioner-portrait-01.png");


      //scratches_on_the_vault->set("image_identifier", "scratches-on-vault-01.png");

      // TODO: more evidence fixtures
      //paw-prints-in-dust-01.png

      rap_sheets_inventory_dictionary.set_dictionary({
         { 1, famous_fem  },
         { 2, mystery_cat },
      });
   }

   void fill_rap_sheets_inventory()
   {
      rap_sheets_inventory.add_items({ 1, 2 });
   }

   void fill_crime_summary_pages(CatDetective::Chronicle::Chronicle *chronicle)
   {
      chronicle->set_crime_summary_pages_and_fit_camera_range_to_first_page({
         { "crime-summary-pages-p1-02.png" },
         { "crime-summary-pages-p2-02.png" },
         { "crime-summary-pages-p3-02.png" },
      });
   }
};



TEST_F(CatDetective_Chronicle_ChronicleTestWithAllegroRenderingFixtureAndDependencies,
   INTERACTIVE__will_work_as_expected)
{
   // setup interactive components not already setup in WithAllegroRenderingFixture
   al_install_keyboard();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

    //fill our dependencies with test data
   fill_evidence_sheet_inventory_dictionary_with_fixture_data();
   fill_evidence_sheet_inventory_with_fixture_data();
   fill_rap_sheets_inventory();
   fill_rap_sheets_inventory_dictionary();

   // setup subject here
   CatDetective::Chronicle::Chronicle chronicle(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &rap_sheets_inventory_dictionary,
      &rap_sheets_inventory,
      &evidence_sheet_inventory_dictionary,
      &evidence_sheet_inventory
   );
   chronicle.initialize();

   // TODO: note this can only be called after initialization, indicating a design flaw.
   // This indicates a design issue, pointing to a the migration to concrete types for the panes inside Chronicle.
   fill_crime_summary_pages(&chronicle);

   al_start_timer(primary_timer);
   bool abort = false;
   while(!abort)
   {
      ALLEGRO_EVENT current_event;
      al_wait_for_event(event_queue, &current_event);
      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            clear_display();
            chronicle.update();
            chronicle.render();
            al_flip_display();
         }
         break;

         case ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT:
         {
            std::cout << "[AllegroFlare_Elements_InventoryWithAllegroRenderingFixtureTest]: INFO: "
                      << "Play sound effect event was emitted. "
                      << std::endl;
         }
         break;

         case ALLEGRO_EVENT_KEY_UP:
         {
            bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_UP:
                  if (!shift) chronicle.cursor_up_unpressed();
               break;

               case ALLEGRO_KEY_DOWN:
                  if (!shift) chronicle.cursor_down_unpressed();
               break;

               case ALLEGRO_KEY_LEFT:
                  if (!shift) chronicle.cursor_left_unpressed();
               break;

               case ALLEGRO_KEY_RIGHT:
                  if (!shift) chronicle.cursor_right_unpressed();
               break;
            }
         }
         break;

         case ALLEGRO_EVENT_KEY_DOWN:
         {
            bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_UP:
                  if (!shift) chronicle.cursor_up_pressed();
               break;

               case ALLEGRO_KEY_DOWN:
                  if (!shift) chronicle.cursor_down_pressed();
               break;

               case ALLEGRO_KEY_LEFT:
                  if (!shift) chronicle.cursor_left_pressed();
               break;

               case ALLEGRO_KEY_RIGHT:
                  if (!shift) chronicle.cursor_right_pressed();
               break;
            }
         }
         break;

         case ALLEGRO_EVENT_KEY_CHAR:
         {
            bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            switch(current_event.keyboard.keycode)
            {

               case ALLEGRO_KEY_UP:
                  chronicle.move_cursor_up();
               break;

               case ALLEGRO_KEY_DOWN:
                  chronicle.move_cursor_down();
               break;

               case ALLEGRO_KEY_N:
                  chronicle.current_pane_page_next();
               break;

               case ALLEGRO_KEY_P:
                  chronicle.current_pane_page_previous();
               break;

               case ALLEGRO_KEY_R:
                  chronicle.reset_document_camera();
               break;

               case ALLEGRO_KEY_LEFT:
                  if (shift) { chronicle.move_pane_left(); }
                  else { chronicle.move_cursor_left(); }
               break;

               case ALLEGRO_KEY_RIGHT:
                  if (shift) { chronicle.move_pane_right(); }
                  else { chronicle.move_cursor_right(); }
               break;

               case ALLEGRO_KEY_PAD_MINUS:
               case ALLEGRO_KEY_MINUS: // (minus)
                  chronicle.pane_camera_zoom_out();
               break;

               case ALLEGRO_KEY_PAD_PLUS:
               case ALLEGRO_KEY_EQUALS: // (plus)
                  chronicle.pane_camera_zoom_in();
               break;

               case ALLEGRO_KEY_ESCAPE:
                  abort = true;
               break;
            }
         }
         break;
      }
   }

   al_unregister_event_source(event_queue, &event_emitter.get_event_source_ref());
   al_destroy_timer(primary_timer);
   //al_flip_display();
   //sleep_for(1);
}
*/


