#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


class AllegroFlare_Screens_CharacterNameInputTest : public ::testing::Test {};
class AllegroFlare_Screens_CharacterNameInputTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Screens/CharacterNameInput.hpp>
#include <AllegroFlare/EventNames.hpp> // for ALLEGRO_FLARE_EVENT_GAME_EVENT
#include <AllegroFlare/VirtualControllers/GenericController.hpp>


TEST_F(AllegroFlare_Screens_CharacterNameInputTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::CharacterNameInput character_name_input;
}


TEST_F(AllegroFlare_Screens_CharacterNameInputTest, render__before_initialized__raises_an_error)
{
   AllegroFlare::Screens::CharacterNameInput character_name_input;
   EXPECT_THROW_GUARD_ERROR(
      character_name_input.render(),
      "AllegroFlare::Screens::CharacterNameInput::render",
      "initialized"
   );
}


TEST_F(AllegroFlare_Screens_CharacterNameInputTestWithAllegroRenderingFixture,
   initialize__will_not_blow_up)
{
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   AllegroFlare::Screens::CharacterNameInput character_name_input(&event_emitter, &get_font_bin_ref());
   character_name_input.initialize();
}


TEST_F(AllegroFlare_Screens_CharacterNameInputTestWithAllegroRenderingFixture,
   //INTERACTIVE__will_work_as_expected)
   DISABLED__INTERACTIVE__will_work_as_expected)
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
   AllegroFlare::Screens::CharacterNameInput character_name_input_screen;
   character_name_input_screen.set_font_bin(&get_font_bin_ref());
   character_name_input_screen.set_font_size(-40);
   character_name_input_screen.set_event_emitter(&event_emitter);
   character_name_input_screen.initialize();

   // run the interactive test
   al_start_timer(primary_timer);
   while(!abort)
   {
      al_wait_for_event(event_queue, &event);

      switch(event.type)
      {
         case ALLEGRO_EVENT_KEY_CHAR:
            if (character_name_input_screen.mode_is_using_keyboard())
            {
               character_name_input_screen.key_char_func(&event);
            }
            else if (character_name_input_screen.mode_is_using_virtual_controls())
            {
               int button_num = 0;
               if (event.keyboard.keycode == ALLEGRO_KEY_UP)
                  button_num = AllegroFlare::VirtualControllers::GenericController::BUTTON_UP;
               if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
                  button_num = AllegroFlare::VirtualControllers::GenericController::BUTTON_DOWN;
               if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
                  button_num = AllegroFlare::VirtualControllers::GenericController::BUTTON_LEFT;
               if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                  button_num = AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT;
               if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
                  button_num = AllegroFlare::VirtualControllers::GenericController::BUTTON_A;
               if (event.keyboard.keycode == ALLEGRO_KEY_X)
                  button_num = AllegroFlare::VirtualControllers::GenericController::BUTTON_X;
               if (button_num != 0) 
               {
                  character_name_input_screen.virtual_control_button_down_func(
                     nullptr,
                     nullptr,
                     button_num,
                     event.keyboard.repeat
                  );
               }
            }
         break;

         case ALLEGRO_EVENT_TIMER:
            al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
            character_name_input_screen.primary_timer_func();
            al_flip_display();
         break;

         case ALLEGRO_FLARE_EVENT_GAME_EVENT:
            abort = true;
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


