#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


#include <iostream>

#include <AllegroFlare/DialogSystem/DialogSystem.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();
#include <AllegroFlare/Elements/DialogBoxes/Basic.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Wait.hpp>
#include <AllegroFlare/Elements/DialogBoxes/ChapterTitle.hpp>
#include <AllegroFlare/DialogSystem/Characters/Basic.hpp>
#include <AllegroFlare/DialogTree/YAMLLoader.hpp> // TODO: Consider alternative to this loader
#include <AllegroFlare/DialogTree/Nodes/Wait.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/Nodes/ChapterTitle.hpp>
#include <AllegroFlare/DialogSystem/CharacterRoster.hpp> // TODO: Remove this dependency
#include <AllegroFlare/DialogSystemDrivers/BasicCharacterDialogDriver.hpp> // TODO: Remove this dependency
#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/MultiModal.hpp>
#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/Dynamic.hpp>
#include <AllegroFlare/StringFormatValidator.hpp>
#include <AllegroFlare/DialogTree/BasicScreenplayTextLoader.hpp>
#include <AllegroFlare/EventNames.hpp>



class MyCustomNodeType : public AllegroFlare::DialogTree::Nodes::Base
{
public:
   MyCustomNodeType() : AllegroFlare::DialogTree::Nodes::Base("MyCustomNodeType") {}
};


class MyCustomDialogDriver : public AllegroFlare::DialogSystemDrivers::Base
{
public:
   MyCustomDialogDriver() : AllegroFlare::DialogSystemDrivers::Base("MyCustomDialogDriver") {}
   virtual void on_raw_script_line_activate(
          AllegroFlare::DialogSystem::DialogSystem* dialog_system,
          std::string activating_node_name,
          AllegroFlare::DialogTree::Nodes::Base* activating_node,
          void* user_data
       ) override
    {
      // TODO: Consider renaming this for clarity
      // TODO: Consider if this method needs to be removed or modififed
       return;
    };
    virtual void on_raw_script_line_finished(
          AllegroFlare::DialogSystem::DialogSystem* dialog_system,
          AllegroFlare::Elements::DialogBoxes::Base* active_dialog_box,
          AllegroFlare::DialogTree::Nodes::Base* active_dialog_node
       ) override
    {
      // TODO: Consider renaming this for clarity
      // TODO: Consider if this method needs to be removed or modififed
       return;
    };
};


static void extract_characters(int id, char& a, char& b, char& c, char& d)
{
   a = static_cast<char>((id >> 24) & 0xFF);
   b = static_cast<char>((id >> 16) & 0xFF);
   c = static_cast<char>((id >> 8) & 0xFF);
   d = static_cast<char>(id & 0xFF);
}

static std::string extract_characters2(int id) //, char& a, char& b, char& c, char& d)
{
   char a = static_cast<char>((id >> 24) & 0xFF);
   char b = static_cast<char>((id >> 16) & 0xFF);
   char c = static_cast<char>((id >> 8) & 0xFF);
   char d = static_cast<char>(id & 0xFF);
   std::stringstream result;
   result << a << b << c << d;
   return result.str();
}


class AllegroFlare_DialogSystem_DialogSystemTest : public ::testing::Test {};

class AllegroFlare_DialogSystem_DialogSystemTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   AllegroFlare::DialogSystem::CharacterRoster *create_and_assemble_character_roster()
   {
      AllegroFlare::DialogSystem::CharacterRoster *result_roster = new AllegroFlare::DialogSystem::CharacterRoster();

      AllegroFlare::DialogSystem::Characters::Basic *character = nullptr;
     
      character = new AllegroFlare::DialogSystem::Characters::Basic();
      character->set_display_name("Detective Cat");
      character->set_avatar_thumbnail_identifier("mystery-cat-128x128-01.gif");
      character->set_avatar_portrait_identifier("detective-01.gif");
      result_roster->add_character("DETECTIVE", character);

      character = new AllegroFlare::DialogSystem::Characters::Basic();
      character->set_display_name("Banker Cat");
      character->set_avatar_thumbnail_identifier("mystery-cat-128x128-01.gif");
      character->set_avatar_portrait_identifier("banker-01.gif");
      result_roster->add_character("BANKER", character);

      character = new AllegroFlare::DialogSystem::Characters::Basic();
      character->set_display_name("Commissioner Cat");
      character->set_avatar_thumbnail_identifier("mystery-cat-128x128-01.gif");
      character->set_avatar_portrait_identifier("commissioner-01.gif");
      character->set_expressions({
            { "happy", "smiling-01.gif" },
            { "unsure", "unsure-01.gif" },
         });
      result_roster->add_character("COMMISSIONER", character);

      character = new AllegroFlare::DialogSystem::Characters::Basic();
      character->set_display_name("Assistant Cat");
      character->set_avatar_thumbnail_identifier("mystery-cat-128x128-01.gif");
      character->set_avatar_portrait_identifier("assistant-01.gif");
      result_roster->add_character("ASSISTANT", character);

      return result_roster; // TODO: Delete after use
   }

   static bool my_load_node_bank_func(
         std::string filename,
         AllegroFlare::DialogTree::NodeBank* node_bank,
         void* user_data
      )
   {
      AllegroFlare::DialogTree::YAMLLoader yaml_loader;
      yaml_loader.load_file(filename);
      *node_bank = yaml_loader.get_node_bank();
      return true;
   }

   static bool my_basic_screenplay_load_node_bank_func(
         std::string filename,
         AllegroFlare::DialogTree::NodeBank* node_bank,
         void* user_data
      )
   {
      AllegroFlare::StringFormatValidator validator(filename);

      if (validator.ends_with(".screenplay.txt"))
      {
         AllegroFlare::DialogTree::BasicScreenplayTextLoader loader;
         loader.load_file(filename);
         (*node_bank) = loader.get_node_bank();
         //set_dialog_node_bank(node_bank());
         return true;
      }

      return false;
   }
};


class AllegroFlare_DialogSystem_DialogSystemTestWithDialogSystemWithBasicCharacterDialogDriver
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   ALLEGRO_EVENT_QUEUE *event_queue;
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::DialogSystem::DialogSystem dialog_system;
   AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver dialog_system_driver;
   virtual void SetUp() override
   {
      AllegroFlare::Testing::WithAllegroRenderingFixture::SetUp();
      event_queue = al_create_event_queue();
      ASSERT_NE(nullptr, event_queue);

      // Initialize our event emitter
      event_emitter.initialize();
      al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

      // Setup the dialog system
      dialog_system.set_bitmap_bin(&get_bitmap_bin_ref());
      dialog_system.set_font_bin(&get_font_bin_ref());
      dialog_system.set_event_emitter(&event_emitter);
      dialog_system.initialize();

      // Setup the dialog system driver
      dialog_system_driver.set_bitmap_bin(&get_bitmap_bin_ref());

      // Share the dialog system driver with the dialog system
      dialog_system.set_driver(&dialog_system_driver);

      dialog_system.set_interparsable_on_operational_chunk_func(&interparsable_on_operational_chunk_func);
   }
   virtual void TearDown() override
   {
      al_destroy_event_queue(event_queue);
      AllegroFlare::Testing::WithAllegroRenderingFixture::TearDown();
   }
   static void interparsable_on_operational_chunk_func(
      std::string operational_text,
      AllegroFlare::Elements::DialogBoxes::Interparsable* this_interparsable_dialog_box,
      void* user_data
   )
   {
      // TODO
   }
};


static AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *create_driver(AllegroFlare::BitmapBin *bitmap_bin)
{
   AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
         new AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver();

   driver->set_handle_load_node_bank_from_file_func(
      &AllegroFlare_DialogSystem_DialogSystemTestWithAllegroRenderingFixture::my_load_node_bank_func
   );
   driver->set_handle_load_node_bank_from_file_func_user_data(nullptr); // Not sure what this would be used for
   //driver->
   driver->set_bitmap_bin(bitmap_bin);
   driver->initialize();

      //if (_driver && _driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
      //{
         //AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
            //static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(_driver);
         //driver->destroy();
         ////driver->initialize();
      //}
   return driver;
}


static void destroy_driver(AllegroFlare::DialogSystemDrivers::Base* driver)
{
      if (driver && driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
      {
         AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *__driver =
            static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(driver);
         __driver->destroy();
         //driver->initialize();
      }
      else
      {
         throw std::runtime_error("in test: Could not destroy driver");
      }
}



TEST_F(AllegroFlare_DialogSystem_DialogSystemTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::DialogSystem dialog_system;
}



TEST_F(AllegroFlare_DialogSystem_DialogSystemTest, initialize__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::DialogSystem::DialogSystem dialog_system;
   EXPECT_THROW_GUARD_ERROR(
      dialog_system.initialize(),
      "AllegroFlare::DialogSystem::DialogSystem::initialize",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTest,
   initialize__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::DialogSystem::DialogSystem dialog_system;
   EXPECT_THROW_GUARD_ERROR(
      dialog_system.initialize(),
      "AllegroFlare::DialogSystem::DialogSystem::initialize",
      "al_is_primitives_addon_initialized()"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTest,
   initialize__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::DialogSystem::DialogSystem dialog_system;
   EXPECT_THROW_GUARD_ERROR(
      dialog_system.initialize(),
      "AllegroFlare::DialogSystem::DialogSystem::initialize",
      "al_is_font_addon_initialized()"
   );
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTest, initialize__without_a_bitmap_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::DialogSystem::DialogSystem dialog_system;
   EXPECT_THROW_GUARD_ERROR(
      dialog_system.initialize(),
      "AllegroFlare::DialogSystem::DialogSystem::initialize",
      "bitmap_bin"
   );
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_DialogSystem_DialogSystemTest, initialize__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::BitmapBin bitmap_bin;
   AllegroFlare::DialogSystem::DialogSystem dialog_system;
   dialog_system.set_bitmap_bin(&bitmap_bin);
   EXPECT_THROW_GUARD_ERROR(
      dialog_system.initialize(),
      "AllegroFlare::DialogSystem::DialogSystem::initialize",
      "font_bin"
   );
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_DialogSystem_DialogSystemTest, initialize__without_an_event_emitter__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::BitmapBin bitmap_bin;
   AllegroFlare::FontBin font_bin;
   AllegroFlare::DialogSystem::DialogSystem dialog_system;
   dialog_system.set_bitmap_bin(&bitmap_bin);
   dialog_system.set_font_bin(&font_bin);
   EXPECT_THROW_GUARD_ERROR(
      dialog_system.initialize(),
      "AllegroFlare::DialogSystem::DialogSystem::initialize",
      "event_emitter"
   );
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithAllegroRenderingFixture,
   CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::DialogSystem::DialogSystem dialog_system(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &event_emitter
   );
   dialog_system.initialize();
   AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver = create_driver(&get_bitmap_bin_ref());
   dialog_system.set_driver(driver);
   dialog_system.render();
   al_flip_display();
   delete driver;
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithDialogSystemWithBasicCharacterDialogDriver,
   activate_EmitGameEvent_dialog_node__will_emit_a_game_event_with_the_expected_data)
{
   // TODO: Test with an imediate_next_node_identifier
   AllegroFlare::DialogTree::Nodes::EmitGameEvent node("my_game_event", "");
   dialog_system.activate_EmitGameEvent_dialog_node(&node);

   // Check the emitted game event data is valid
   ALLEGRO_EVENT next_event;
   ASSERT_EQ(true, al_peek_next_event(event_queue, &next_event));
   ASSERT_EQ(ALLEGRO_FLARE_EVENT_GAME_EVENT, next_event.type);
   ASSERT_NE(0, next_event.user.data1);
   AllegroFlare::GameEvent *game_event = (AllegroFlare::GameEvent*)((intptr_t)next_event.user.data1);
   EXPECT_EQ("my_game_event", game_event->get_type());
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithDialogSystemWithBasicCharacterDialogDriver,
   activate_RawScriptLine_dialog_node__will_call_the_drivers_on_raw_script_line_activate_callback)
{
   // TODO: Test with an imediate_next_node_identifier
   AllegroFlare::DialogTree::Nodes::RawScriptLine node("interpret_this_line++", 123, "");
   dialog_system.activate_RawScriptLine_dialog_node(&node);

   // TODO: Check the callback was emitted game event data is valid
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithDialogSystemWithBasicCharacterDialogDriver,
   activate_MultipageWithOptions_dialog_node__will_call_the_drivers_on_raw_script_line_activate_callback)
{
   AllegroFlare::DialogTree::Nodes::MultipageWithOptions node(
      "JONAH",
      {
         "This is page 1.",
         //"This is page 2.", // NOTE: Support for multiple pages is broken for some downstream compatibility reason
                              // TODO: Restore support and figure out what the fix needs to be fixed downstream
      },
      {
         { "Goto another node", new AllegroFlare::DialogTree::NodeOptions::GoToNode("unused-test-node-name"), 0 },
         { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 },
      }
   );
   dialog_system.activate_MultipageWithOptions_dialog_node(&node);

   // TODO: Test consequence of activation
   //EXPECT_EQ(&node, dialog_system.get_active_dialog_node());
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithDialogSystemWithBasicCharacterDialogDriver,
   activate_Interparsable_dialog_node__will_activate_a_dialog_node_of_interparsable_type)
{
   AllegroFlare::DialogTree::Nodes::Interparsable node(
      "JONAH",
      {
         "This is (emphasis)page 1(/emphasis).",
         "This is page 2.", // NOTE: Support for multiple pages is broken for some downstream compatibility reason
                            // TODO: Restore support and figure out what the fix needs to be fixed downstream
      },
      {}
      //{
         //{ "Goto another node", new AllegroFlare::DialogTree::NodeOptions::GoToNode("unused-test-node-name"), 0 },
         //{ "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 },
      //}
   );
   dialog_system.activate_Interparsable_dialog_node(&node);

   // Test consequence of activation
   EXPECT_EQ(&node, dialog_system.get_active_dialog_node());
   // TODO: Consider testing additional consequence (not related to the dialog box which is actually in the next text)
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithDialogSystemWithBasicCharacterDialogDriver,
   activate_Interparsable_dialog_node__will_spawn_a_dialog_box_of_interparsable_type_with_the_expected_values)
{
   AllegroFlare::DialogTree::Nodes::Interparsable node(
      "JONAH",
      {
         "This is (emphasis)page 1(/emphasis).",
         "This is page 2.",
      },
      {}
      //{
         //{ "Goto another node", new AllegroFlare::DialogTree::NodeOptions::GoToNode("unused-test-node-name"), 0 },
         //{ "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 },
      //}
   );
   dialog_system.activate_Interparsable_dialog_node(&node);

   // TODO: Test consequence of activation
   //EXPECT_EQ(&node, dialog_system.get_active_dialog_node());
   AllegroFlare::Elements::DialogBoxes::Base *active_dialog_box = dialog_system.get_active_dialog_box();
   EXPECT_NE(nullptr, active_dialog_box);
   ASSERT_EQ(AllegroFlare::Elements::DialogBoxes::Interparsable::TYPE, active_dialog_box->get_type());
   auto as = static_cast<AllegroFlare::Elements::DialogBoxes::Interparsable*>(active_dialog_box);
   // TODO: Figure out how to test assignment of callback
   //EXPECT_EQ(
      //AllegroFlare_DialogSystem_DialogSystemTestWithDialogSystemWithBasicCharacterDialogDriver::
         //interparsable_on_operational_chunk_func,
      //as->get_on_operational_chunk_func()
   //); // HERE
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithDialogSystemWithBasicCharacterDialogDriver,
   activate_Wait_dialog_node__will_spawn_a_wait_dialog_with_the_expected_data)
{
   AllegroFlare::DialogTree::Nodes::Wait node(3, "my_next_node_name_after_wait");

   // Call the subject
   dialog_system.activate_Wait_dialog_node(&node);

   // Check the node is the expected node
   EXPECT_EQ(&node, dialog_system.get_active_dialog_node()); // TODO: Consider this a separate test

   // Check a dialog box was created with the expected data
   ASSERT_NE(nullptr, dialog_system.get_active_dialog_box());
   ASSERT_EQ(AllegroFlare::Elements::DialogBoxes::Wait::TYPE, dialog_system.get_active_dialog_box()->get_type());
   AllegroFlare::Elements::DialogBoxes::Wait *as =
      static_cast<AllegroFlare::Elements::DialogBoxes::Wait*>(dialog_system.get_active_dialog_box());
   EXPECT_FLOAT_EQ(3.0, as->get_duration()); // TODO: Fix name to "duration_seconds"
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithDialogSystemWithBasicCharacterDialogDriver,
   activate_dialog_node__when_a_node_type_does_not_exist__throws_an_error)
{
   MyCustomNodeType node;
   EXPECT_THROW_WITH_MESSAGE(
      dialog_system.activate_dialog_node(&node),
      std::runtime_error,
      "DialogSystem::DialogSystem::activate_dialog_node: error: Unable to handle dialog node activation on type "
         "\"MyCustomNodeType\". A condition is not provided to handle this type."
   );
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithDialogSystemWithBasicCharacterDialogDriver,
   activate_ChapterTitle_dialog_node__will_spawn_a_chapter_dialog_dialog_with_the_expected_data)
{
   AllegroFlare::DialogTree::Nodes::ChapterTitle node("Title of the Chapter", 3.0, "my_next_node_identifier");

   // Call the subject
   dialog_system.activate_ChapterTitle_dialog_node(&node);

   // Check the node is the expected node
   EXPECT_EQ(&node, dialog_system.get_active_dialog_node());

   // Check a dialog box was created with the expected data
   ASSERT_NE(nullptr, dialog_system.get_active_dialog_box());
   ASSERT_EQ(
      AllegroFlare::Elements::DialogBoxes::ChapterTitle::TYPE,
      dialog_system.get_active_dialog_box()->get_type()
   );
   AllegroFlare::Elements::DialogBoxes::ChapterTitle *as =
      static_cast<AllegroFlare::Elements::DialogBoxes::ChapterTitle*>(dialog_system.get_active_dialog_box());
   EXPECT_EQ("Title of the Chapter", as->get_title_text());
   EXPECT_FLOAT_EQ(3.0, as->get_duration());
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithDialogSystemWithBasicCharacterDialogDriver,
   activate_ExitDialog_dialog_node__will_deactivate_the_dialog_system)
{
   // Ensure the dialog system is currently active
   dialog_system.switch_in();
   ASSERT_EQ(true, dialog_system.get_switched_in());

   AllegroFlare::DialogTree::Nodes::ExitDialog node;

   // Call the subject
   dialog_system.activate_ExitDialog_dialog_node(&node);
   EXPECT_EQ(false, dialog_system.get_switched_in());
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithDialogSystemWithBasicCharacterDialogDriver,
   activate_ExitProgram_dialog_node__will_emit_an_event_to_shutdown_the_program)
{
   AllegroFlare::DialogTree::Nodes::ExitProgram node;

   // Call the subject
   dialog_system.activate_ExitProgram_dialog_node(&node);

   ALLEGRO_EVENT next_event;
   ASSERT_EQ(true, al_peek_next_event(event_queue, &next_event));
   EXPECT_EQ(ALLEGRO_FLARE_EVENT_EXIT_GAME, next_event.type) << extract_characters2(next_event.type);
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithAllegroRenderingFixture,
   // NOTE: Disabled for more rapid development testing, this test takes too long in rapid cycles
   CAPTURE__render__when_a_dialog_box_is_open__will_work_as_expected)
{
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   AllegroFlare::DialogSystem::DialogSystem dialog_system(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &event_emitter
   );
   dialog_system.initialize();
   dialog_system.set_driver(create_driver(&get_bitmap_bin_ref())); // TODO: Destroy this driver

   dialog_system.spawn_basic_dialog("Hugo", { "Hello, basic dialog", "Good to see you today" });

   int passes = 120;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }
   dialog_system.dialog_advance();
   passes = 120;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }
   dialog_system.dialog_advance();
   passes = 120;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithAllegroRenderingFixture,
   // NOTE: Disabled for more rapid development testing, this test takes too long in rapid cycles
   CAPTURE__load_dialog_node_bank_from_file__will_not_blow_up)
{
   std::string dialog_filename = get_fixtures_path() + "/dialogs/linear_dialog.yml";

   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   AllegroFlare::DialogSystem::DialogSystem dialog_system(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &event_emitter
   );
   dialog_system.initialize();
   dialog_system.set_driver(create_driver(&get_bitmap_bin_ref())); // TODO: Destroy this driver

   dialog_system.load_dialog_node_bank_from_file(dialog_filename);
   dialog_system.activate_dialog_node_by_name("start_node");

   int passes = 120;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }
   dialog_system.dialog_advance();
   passes = 120;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }
   dialog_system.dialog_advance();
   passes = 120;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithAllegroRenderingFixture,
   // NOTE: Disabled for more rapid development testing, this test takes too long in rapid cycles
   CAPTURE__load_dialog_node_bank_from_file__with_a_branching_dialog_that_includes_choices__will_not_blow_up)
{
   std::string dialog_filename = get_fixtures_path() + "/dialogs/branching_dialog.yml";

   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   AllegroFlare::DialogSystem::DialogSystem dialog_system(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &event_emitter
   );
   //dialog_system.set_load_node_bank_func(my_load_node_bank_func);
   dialog_system.initialize();
   dialog_system.set_driver(create_driver(&get_bitmap_bin_ref())); // TODO: Destroy this driver

   dialog_system.load_dialog_node_bank_from_file(dialog_filename);
   dialog_system.activate_dialog_node_by_name("start_node");

   int NUM_PASSES = 20;
   int passes = NUM_PASSES;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }
   dialog_system.dialog_advance(); // Advance the text to the end (and reveal the choice list box)
   dialog_system.move_dialog_cursor_position_down();
   dialog_system.dialog_advance(); // Advance the dialog (with the 2nd choice option selected)
   EXPECT_EQ("yuki_response_2", dialog_system.get_active_dialog_node_name());
   passes = NUM_PASSES;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }
   EXPECT_EQ(false, dialog_system.dialog_is_finished());
   dialog_system.dialog_advance(); // Skip to end of "yuki_response_2"
   EXPECT_EQ("yuki_response_2", dialog_system.get_active_dialog_node_name());
   EXPECT_EQ(false, dialog_system.dialog_is_finished()); // Node will not be finished until an update()

   // TODO: Sort out the remaining steps, and consider design option that does not require a call to update()
   // to advance as expected

   //dialog_system.dialog_advance();
   //EXPECT_EQ("ethan_response_2", dialog_system.get_active_dialog_node_name());

   passes = NUM_PASSES;
   for (int i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      dialog_system.update();
      dialog_system.render();
      al_flip_display();
   }

   //dialog_system.dialog_advance();
   //EXPECT_EQ("ethan_response_2", dialog_system.get_active_dialog_node_name());
   //dialog_system.dialog_advance(); // Skip to end

   //{ // Once
      //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      //dialog_system.update();
      //dialog_system.render();
      //al_flip_display();
   //}

   //dialog_system.dialog_advance();
   //EXPECT_EQ("", dialog_system.get_active_dialog_node_name());


   //dialog_system.dialog_advance();
   //passes = NUM_PASSES;
   //for (int i=0; i<passes; i++)
   //{
      //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      //dialog_system.update();
      //dialog_system.render();
      //al_flip_display();
   //}
   //dialog_system.dialog_advance();
   //passes = NUM_PASSES;
   //for (int i=0; i<passes; i++)
   //{
      //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      //dialog_system.update();
      //dialog_system.render();
      //al_flip_display();
   //}
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithAllegroRenderingFixture,
   // NOTE: Disabled for more rapid development testing, this test takes too long in rapid cycles
   TIMED_INTERACTIVE__without_a_character_roster__will_work_as_expected)
{
   // setup system
   al_install_keyboard();
   al_install_joystick();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   //al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   bool abort = false;
   ALLEGRO_EVENT event;

   // setup environment
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   // initialize test subject
   std::string dialog_filename = get_fixtures_path() + "/dialogs/branching_dialog_with_long_text.yml";
   std::string node_name_to_start = "start_node";
   AllegroFlare::DialogSystem::DialogSystem dialog_system(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &event_emitter
   );
   //dialog_system.set_load_node_bank_func(my_load_node_bank_func);
   dialog_system.initialize();
   dialog_system.set_driver(create_driver(&get_bitmap_bin_ref())); // TODO: Destroy this driver
   dialog_system.load_dialog_node_bank_from_file(dialog_filename);
   //dialog_system.set__driver(create_driver(&get_bitmap_bin_ref())); // TODO: Destroy this driver

   // run the interactive test
   al_start_timer(primary_timer);

   EXPECT_EQ(false, dialog_system.get_switched_in());
   float duration_until_abort_sec = 6.0f; // TODO: Add a countdown
   float interactive_started_at = al_get_time();
   bool abort_timer_in_effect = true;

   while(!abort)
   {
      if (abort_timer_in_effect && (al_get_time() - interactive_started_at) > duration_until_abort_sec) break;

      al_wait_for_event(event_queue, &event);

      switch(event.type)
      {
         case ALLEGRO_EVENT_KEY_CHAR:
         {
            abort_timer_in_effect = false;
            switch (event.keyboard.keycode)
            {
               case ALLEGRO_KEY_R: // R for "Reset"
                  dialog_system.activate_dialog_node_by_name(node_name_to_start);
                  EXPECT_EQ(true, dialog_system.get_switched_in()); // TODO: Move this to another test
               break;

               case ALLEGRO_KEY_UP:
                  dialog_system.move_dialog_cursor_position_up();
               break;

               case ALLEGRO_KEY_DOWN:
                  dialog_system.move_dialog_cursor_position_down();
               break;

               //case ALLEGRO_KEY_LEFT:
                  //dialog_system.move_dialog_cursor_position_left();
               //break;

               //case ALLEGRO_KEY_RIGHT:
                  //dialog_system.move_dialog_cursor_position_right();
               //break;

               case ALLEGRO_KEY_ENTER:
                  if (dialog_system.a_dialog_is_active())
                  {
                     dialog_system.dialog_advance();
                     if (!dialog_system.a_dialog_is_active())
                     {
                        EXPECT_EQ(false, dialog_system.get_switched_in()); // TODO: Move this to another test
                     }
                  }
               break;

               case ALLEGRO_KEY_ESCAPE:
                  abort = true;
               break;

               default:
               break;
            }
         }
         break;

         case ALLEGRO_EVENT_TIMER:
            al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
            dialog_system.update();
            dialog_system.render();
            if (!dialog_system.a_dialog_is_active())
            {
               ALLEGRO_FONT *user_prompt_font = get_user_prompt_font();
               al_draw_multiline_text(
                  user_prompt_font,
                  ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2},
                  1920/2,
                  1080/2-80,
                  1920,
                  al_get_font_line_height(user_prompt_font),
                  ALLEGRO_ALIGN_CENTER,
                  "There are no dialogs currently active\n(press ESC to exit, R to START dialog)"
               );
            }
            al_flip_display();
         break;
      }
   }
   
   // teardown
   // TODO: Audit if this teardown is complete. It may require other calls to destroy resources.

   al_destroy_event_queue(event_queue);
   al_destroy_timer(primary_timer);
   al_uninstall_keyboard();
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTestWithAllegroRenderingFixture,
   // NOTE: Disabled for more rapid development testing, this test takes too long in rapid cycles
   TIMED_INTERACTIVE__when_a_character_roster_is_present__and_an_active_character_staging_layout__will_work_as_expected)
{
   // setup system
   al_install_keyboard();
   al_install_joystick();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   //al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   bool abort = false;
   ALLEGRO_EVENT event;

   // setup environment
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   // initialize test subject
   std::string dialog_filename = get_fixtures_path() + "/dialogs/basic_screenplay_text.screenplay.txt";
   std::string node_name_to_start = "dialog_node_0";
   AllegroFlare::DialogSystem::CharacterRoster *character_roster = create_and_assemble_character_roster();
   AllegroFlare::DialogSystem::DialogSystem dialog_system(
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &event_emitter
   );

   dialog_system.initialize();

   //AllegroFlare::DialogSystemDrivers::* _driver = dialog_system.get__driver();
   // TODO: Destroy this driver
   //AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver = create_driver(&get_bitmap_bin_ref());
   //driver->set_handle_load_node_bank_from_file_func(0);
   dialog_system.set_driver(create_driver(&get_bitmap_bin_ref()));

   AllegroFlare::DialogSystemDrivers::Base* driver = dialog_system.get_driver();
   if (driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
   {
      AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *__driver =
         static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(driver);
      __driver->character_roster = character_roster; // TODO: Change this to a setter
      // TODO: Consider alternative place for all this assmeblage
      AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic *dynamic =
         new AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic(&get_bitmap_bin_ref());
      // TODO: Load from roster
      AllegroFlare::Placement3D standard_placement(1920/2, 1080/2 - 150, 0);
      standard_placement.size = {256.0f, 256.0f, 0.0f};
      standard_placement.scale = {3.6f, 3.6f, 1.0f};
      dynamic->add_staged_character("DETECTIVE",    { "-normal-", standard_placement } );
      dynamic->add_staged_character("BANKER",       { "-normal-", standard_placement } );
      dynamic->add_staged_character("COMMISSIONER", { "-normal-", standard_placement } );
      dynamic->add_staged_character("ASSISTANT",    { "-normal-", standard_placement } );
      dynamic->set_staged_character_expressions_db({
        { { "BANKER", "-normal-" }, "banker-01.gif" },
        { { "DETECTIVE", "-normal-" }, "detective-01.gif" },
        { { "COMMISSIONER", "-normal-" }, "commissioner-01.gif" },
        { { "ASSISTANT", "-normal-" }, "assistant-01.gif" },
      });
      dynamic->hide_all_characters();
      //dynamic->hide_character("COMMISSIONER");
      //dynamic->hide_character("DETECTIVE");
      //dynamic->hide_character("ASSISTANT");
         //new AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic(&get_bitmap_bin_ref());
      __driver->active_character_staging_layout = dynamic;
         //new AllegroFlare::DialogSystem::CharacterStagingLayouts::MultiModal(&get_bitmap_bin_ref());
      __driver->set_handle_load_node_bank_from_file_func(
         &AllegroFlare_DialogSystem_DialogSystemTestWithAllegroRenderingFixture::my_basic_screenplay_load_node_bank_func
      ); // For this specific test
   }

   //dialog_system.get_driver_ref().character_roster = character_roster; // TODO: Change this to a setter
   //dialog_system.initialize(); // NOTE: Initialization must happen before
   dialog_system.load_dialog_node_bank_from_file(dialog_filename);

   // run the interactive test
   al_start_timer(primary_timer);

   EXPECT_EQ(false, dialog_system.get_switched_in());
   float duration_until_abort_sec = 6.0f; // TODO: Add a countdown
   float interactive_started_at = al_get_time();
   bool abort_timer_in_effect = true;

   while(!abort)
   {
      if (abort_timer_in_effect && (al_get_time() - interactive_started_at) > duration_until_abort_sec) break;

      al_wait_for_event(event_queue, &event);

      switch(event.type)
      {
         case ALLEGRO_EVENT_KEY_CHAR:
         {
            abort_timer_in_effect = false;
            switch (event.keyboard.keycode)
            {
               case ALLEGRO_KEY_R: // R for "Reset"
                  dialog_system.activate_dialog_node_by_name(node_name_to_start);
                  EXPECT_EQ(true, dialog_system.get_switched_in()); // TODO: Move this to another test
               break;

               case ALLEGRO_KEY_UP:
                  dialog_system.move_dialog_cursor_position_up();
               break;

               case ALLEGRO_KEY_DOWN:
                  dialog_system.move_dialog_cursor_position_down();
               break;

               //case ALLEGRO_KEY_LEFT:
                  //dialog_system.move_dialog_cursor_position_left();
               //break;

               //case ALLEGRO_KEY_RIGHT:
                  //dialog_system.move_dialog_cursor_position_right();
               //break;

               case ALLEGRO_KEY_ENTER:
                  if (dialog_system.a_dialog_is_active())
                  {
                     dialog_system.dialog_advance();
                     if (!dialog_system.a_dialog_is_active())
                     {
                        EXPECT_EQ(false, dialog_system.get_switched_in()); // TODO: Move this to another test
                     }
                  }
               break;

               case ALLEGRO_KEY_ESCAPE:
                  abort = true;
               break;

               default:
               break;
            }
         }
         break;

         case ALLEGRO_EVENT_TIMER:
            al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
            dialog_system.update();
            dialog_system.render();
            if (!dialog_system.a_dialog_is_active())
            {
               ALLEGRO_FONT *user_prompt_font = get_user_prompt_font();
               al_draw_multiline_text(
                  user_prompt_font,
                  ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2},
                  1920/2,
                  1080/2-80,
                  1920,
                  al_get_font_line_height(user_prompt_font),
                  ALLEGRO_ALIGN_CENTER,
                  "There are no dialogs currently active\n(press ESC to exit, R to START dialog)"
               );
            }
            al_flip_display();
         break;
      }
   }

   // teardown
   // TODO: Audit if this teardown is complete. It may require other calls to destroy resources.

   delete character_roster;

   al_destroy_event_queue(event_queue);
   al_destroy_timer(primary_timer);
   al_uninstall_keyboard();
}


TEST_F(AllegroFlare_DialogSystem_DialogSystemTest,
   update__when_the_currently_active_node_is_of_type_Wait__will_wait_until_the_time_has_finished_before_continuing)
{
   // Setup our test context
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::BitmapBin bitmap_bin;
   AllegroFlare::FontBin font_bin;
   AllegroFlare::DialogSystem::DialogSystem dialog_system;
   dialog_system.set_bitmap_bin(&bitmap_bin);
   dialog_system.set_font_bin(&font_bin);
   dialog_system.set_event_emitter(&event_emitter);
   bitmap_bin.set_full_path(""); // Required to be valid


   AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *driver =
      new AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver();
   if (driver->is_type(AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver::TYPE))
   {
      AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver *__driver =
         static_cast<AllegroFlare::DialogSystemDrivers::BasicCharacterDialogDriver*>(driver);
      __driver->set_bitmap_bin(&bitmap_bin);
      // TODO: Consider alternative place for all this assmeblage
      AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic *dynamic =
         new AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic(&bitmap_bin);
      dynamic->add_staged_character("SPEAKING_CHARACTER", { "-normal-", {} } );
      //dynamic->add_staged_character("SPEAKING_CHARACTER");
      dynamic->set_staged_character_expressions_db({
        { { "SPEAKING_CHARACTER", "-normal-" }, "banker-01.gif" },
      });
      __driver->active_character_staging_layout = dynamic;
      //__driver->active_character_staging_layout = new AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic(
         //&bitmap_bin
      //);
      __driver->initialize();
   }

   dialog_system.set_driver(driver);


   event_emitter.initialize();

   // Build up a node_bank with a wait node
   AllegroFlare::DialogTree::NodeBank node_bank;
   //node_bank.add_node("chapter_title", new AllegroFlare::DialogTree::Nodes::Wait(1, "next_node"));
   node_bank.add_node("wait_node_1", new AllegroFlare::DialogTree::Nodes::Wait(1, "next_node"));
   node_bank.add_node("next_node", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(
         "SPEAKING_CHARACTER", // TODO: Improve this test data
         { "I'm a speaker" },
         {
            //{ "Exit program", new AllegroFlare::DialogTree::NodeOptions::ExitProgram() }
            { "Exit dialog", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 }
         }
      ));

   // Use our assembled node_bank
   dialog_system.set_dialog_node_bank(node_bank);
   dialog_system.initialize();

   // Start on the wait node
   dialog_system.activate_dialog_node_by_name("wait_node_1");
   dialog_system.update(al_get_time()); // TODO: Use AllegroFlare::Time
   EXPECT_EQ("wait_node_1", dialog_system.get_active_dialog_node_name());
   dialog_system.update(al_get_time()); // TODO: Use AllegroFlare::Time
   EXPECT_EQ("wait_node_1", dialog_system.get_active_dialog_node_name());
   al_rest(1.2);
   dialog_system.update(al_get_time()); // TODO: Use AllegroFlare::Time
   EXPECT_EQ("next_node", dialog_system.get_active_dialog_node_name());

   delete driver->active_character_staging_layout; // TODO: Figure out where this should go

   // Shutdown our test context
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


// TODO: Add tests for ChapterTitle


