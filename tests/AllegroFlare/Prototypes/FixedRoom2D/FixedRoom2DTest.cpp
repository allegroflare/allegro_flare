
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/FixedRoom2D/FixedRoom2D.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithInteractionFixture.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/ConfigurationFactory.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityFactory.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/RoomFactory.hpp>



class AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTest : public ::testing::Test {};
class AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTestWithInteractionFixture
   : public AllegroFlare::Testing::WithInteractionFixture
{
public:
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D fixed_room_2d;

public:
   virtual void SetUp() override
   {
      AllegroFlare::Testing::WithInteractionFixture::SetUp();

      fixed_room_2d.set_font_bin(&get_font_bin_ref());
      fixed_room_2d.set_bitmap_bin(&get_bitmap_bin_ref());
      fixed_room_2d.set_event_emitter(&event_emitter);
      fixed_room_2d.initialize();
   }
   void load_configuration()
   {
      // TODO: Build configuration locally
      // TODO: Use room-01.png
      AllegroFlare::Prototypes::FixedRoom2D::Configuration configuration;

      //AllegroFlare::Prototypes::FixedRoom2D::Configuration result;

      AllegroFlare::InventoryIndex &inventory_index = configuration.get_inventory_index_ref();
      AllegroFlare::Inventory &af_inventory = configuration.get_af_inventory_ref();
      AllegroFlare::Inventory &flags = configuration.get_flags_ref();
      std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> &entity_dictionary =
         configuration.get_entity_dictionary_ref();
      std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*> &room_dictionary =
         configuration.get_room_dictionary_ref();
      std::map<std::string, std::string> &entity_room_associations =
         configuration.get_entity_room_associations_ref();
      std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script> &script_dictionary =
         configuration.get_script_dictionary_ref();
      std::string &starting_room_identifier = configuration.get_starting_room_identifier_ref();
      AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper &entity_collection_helper =
         fixed_room_2d.get_entity_collection_helper_ref();


      AllegroFlare::Prototypes::FixedRoom2D::EntityFactory entity_factory(&get_bitmap_bin_ref());
      AllegroFlare::Prototypes::FixedRoom2D::RoomFactory room_factory(
         &get_bitmap_bin_ref(),
         &get_font_bin_ref(),
         &event_emitter,
         &entity_collection_helper
      );

      inventory_index = AllegroFlare::InventoryIndex::build_placeholder_inventory_index();

      af_inventory.add_item(1);
      af_inventory.add_item(4);
      af_inventory.add_item(3);

      room_dictionary = {
         { "front_hall", room_factory.create_room() },
         //{ "study", room_factory.create_room() },
      };

      entity_dictionary = {
         { "background_1", entity_factory.create_entity(
               "room-01.png", 800, 600, 0.85, "Door 1", "observe_background_1")
            },
         { "robot_helmet", entity_factory.create_entity(
               "robot_helmet-01.png", 1400, 800, 0.85, "Door 1", "observe_robot_helmet")
            },
         //{ "pipe", entity_factory.create_entity(
               //"robot_helmet-01.png", 1400, 800, 0.85, "Door 1", "observe_robot_helmet")
            //},
         //{ "door2", entity_factory.create_entity(
               //"download-door-png-transparent-image-and-clipart-3.png", 500, 800, 0.85, "Door 2", "observe_door2") },
         //{ "chair", entity_factory.create_entity(
               //"wooden-chair-png-transparent-image-pngpix-0.png", 700, 800, 0.168, "Chair", "signal_hello") },
         //{ "table", entity_factory.create_entity(
               //"download-wooden-table-png-image-png-image-pngimg-3.png", 900, 800, 0.4, "table", "observe_table") },
         //{ "keys", entity_factory.create_entity(
               //"key-keychain-house-keys-door-photo-pixabay-25.png", 940, 590, 0.05, "keys", "collect_keys") },
      };

      entity_room_associations = {
         { "robot_helmet", "front_hall" },
         { "background_1", "front_hall" },
         //{ "door2", "study" },
         //{ "chair", "front_hall" },
         //{ "table", "front_hall" },
         //{ "keys", "front_hall" },
      };

      script_dictionary = {
         { "observe_robot_helmet", AllegroFlare::Prototypes::FixedRoom2D::Script({
               "DIALOG: Just a regular robot helmet. | I'm going to ignore it for now.",
               //"ENTER_ROOM: study",
         })},
         { "observe_background_1", AllegroFlare::Prototypes::FixedRoom2D::Script({
               "DIALOG: Nothing here. | I'm going to ignore it for now.",
               //"ENTER_ROOM: study",
         })},
         //{ "observe_door2", AllegroFlare::Prototypes::FixedRoom2D::Script({
               //"DIALOG: A regular door. | I'll to in.",
               //"ENTER_ROOM: front_hall",
         //})},
         //{ "signal_hello", AllegroFlare::Prototypes::FixedRoom2D::Script({
               //"SIGNAL: Hello!"})
         //},
         //{ "spawn_dialog", AllegroFlare::Prototypes::FixedRoom2D::Script({
               //"DIALOG: This was a scripted dialog!"
         //})},
         //{ "collect_keys", AllegroFlare::Prototypes::FixedRoom2D::Script({
               //"COLLECT: keys"
         //})},
         //{ "observe_table", AllegroFlare::Prototypes::FixedRoom2D::Script({
               //"DIALOG: Hmm. Interesting, there's a key on this table."
         //})},
      };

      starting_room_identifier = "front_hall";

      //enter_room("front_hall");
      //enter_room("study");















        //AllegroFlare::Prototypes::FixedRoom2D::ConfigurationFactory::build_testing_configuration(
          //&get_bitmap_bin_ref(), &get_font_bin_ref(), &event_emitter, &fixed_room_2d.get_entity_collection_helper_ref());
      fixed_room_2d.load_configuration(configuration);
   }
   void enter_start_room()
   {
      fixed_room_2d.enter_start_room();
   }
};



TEST_F(AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D fixed_room_2d;
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTest,
   process_script_event__on_a_subscribed_event_type__with_unknown_event_data_type__will_output_an_error_message_to_cout)
{
   // TODO
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTestWithAllegroRenderingFixture,
   CAPTURE__VISUAL__when_no_room_is_loaded__will_render_a_void_room_and_an_empty_room_message)
{
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D fixed_room_2d;
   fixed_room_2d.set_font_bin(&get_font_bin_ref());
   fixed_room_2d.set_bitmap_bin(&get_bitmap_bin_ref());
   fixed_room_2d.set_event_emitter(&event_emitter);
   fixed_room_2d.initialize();

   clear();
   fixed_room_2d.render();
   al_flip_display();
   al_rest(1);
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTestWithInteractionFixture,
   FOCUS__CAPTURE__TIMED_INTERACTIVE__will_operate_as_expected)
{
   load_configuration();

   enter_start_room();

   while(interactive_test_wait_for_event())
   {
      ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER: {
            clear();

            fixed_room_2d.update();
            fixed_room_2d.render();

            interactive_test_render_status();
            al_flip_display();
         } break;

         case ALLEGRO_EVENT_MOUSE_AXES: {
            int cursor_distance_x = current_event.mouse.dx;
            int cursor_distance_y = current_event.mouse.dy;
            fixed_room_2d.move_cursor(cursor_distance_x, cursor_distance_y);
         } break;

         //// For example:
         //case ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT:
         //{
            //std::cout << "[AllegroFlare_Elements_MultiListTestWithAllegroRenderingFixture]: INFO: "
                      //<< "Play sound effect event was emitted. "
                      //<< std::endl;
         //}
         //break;

         //// For example:
         //case ALLEGRO_EVENT_KEY_DOWN:
         //{
            //bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            //switch(current_event.keyboard.keycode)
            //{
               //case ALLEGRO_KEY_ENTER:
                  //// Do something
               //break;
            //}
         //}
         //break;
      }
   }
   
}


