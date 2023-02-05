
#include <iostream>
#include <sstream>
#include <allegro5/allegro.h>

std::string build_readable_keypress_string(int keycode, bool shift, bool alt, bool ctrl, bool command);

int main(int argc, char **argv)
{
   al_init();
   al_install_keyboard();

   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   al_register_event_source(event_queue, al_get_keyboard_event_source());

   ALLEGRO_DISPLAY *display = al_create_display(1280, 720);

   ALLEGRO_EVENT event;
   bool shutdown_program = false;
   while (!shutdown_program)
   {
      al_wait_for_event(event_queue, &event);
      switch(event.type)
      {
      case ALLEGRO_EVENT_KEY_DOWN:
         {
            int allegro_keycode = event.keyboard.keycode;
            bool shift = event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            bool alt = event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
            bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL;
            bool command = event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;

            std::cout << build_readable_keypress_string(allegro_keycode, shift, alt, ctrl, command);
            std::cout << std::flush;
         }
         break;
      case ALLEGRO_EVENT_KEY_CHAR:
         if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) shutdown_program = true;
         break;
      }
   }

   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
   al_uninstall_keyboard();
   al_uninstall_system();

   return 0;
}

std::string build_readable_keypress_string(int keycode, bool shift, bool alt, bool ctrl, bool command)
{
   std::stringstream ss;
   ss << "shift: " << shift
      << ", alt: " << alt
      << ", ctrl: " << ctrl
      << ", command: " << command
      << ", key: " << al_keycode_to_name(keycode)
      << std::endl;
   return ss.str();
}

