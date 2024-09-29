#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <string>


void validate(int return_value, std::string func_name)
{
   if (return_value != 1) throw std::runtime_error(func_name + " failed.");
}

void validate_not_null(void *value, std::string message)
{
   if (value == nullptr) throw std::runtime_error(message + " failed.");
}

int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = nullptr;
   ALLEGRO_FONT *font = nullptr;

   validate(al_init(), "al_init()");
   validate(al_init_font_addon(), "al_init_font_addon()");
   validate(al_init_ttf_addon(), "al_init_ttf_addon()");
   validate(al_init_image_addon(), "al_init_image_addon()");
   validate(al_init_primitives_addon(), "al_init_primitives_addon()");

   // Turn on antialaising
   al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_REQUIRE);
   al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_REQUIRE);

   // Setup pipeline
   //al_set_new_display_flags(ALLEGRO_OPENGL) //fine
   //al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_OPENGL_3_0) //fine
   al_set_new_display_flags(ALLEGRO_OPENGL |  ALLEGRO_PROGRAMMABLE_PIPELINE); // broken.
   //al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_OPENGL_3_0 | ALLEGRO_PROGRAMMABLE_PIPELINE) // broken.

   validate_not_null(display = al_create_display(800, 600), "display");
   validate_not_null(font = al_load_font("bin/data/fonts/Abel-Regular.ttf", -80, 0), "font loading");

   al_clear_to_color(ALLEGRO_COLOR{0.2, 0.21, 0.25, 1.0});
   al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 400, 300-80, ALLEGRO_ALIGN_CENTER, "Hello Text!");
   al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 400, 300, ALLEGRO_ALIGN_CENTER, "1234567890");

   //al_save_bitmap("output.png", al_get_backbuffer(display));
   al_flip_display();
   al_rest(1);

   al_uninstall_system();

   return 0;
}


