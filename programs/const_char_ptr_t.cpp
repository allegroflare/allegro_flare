#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <AllegroFlare/Generators/LoremIpsumGenerator.hpp>
#include <iostream>


typedef const char* const_char_ptr_t;


bool function(int line_num, const_char_ptr_t line, int size, void *extra)
{
   ALLEGRO_FONT *font = (ALLEGRO_FONT*)extra;
   std::string substr = line;
   substr = substr.substr(0, size);
   al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 200, 300+line_num*20, 0, substr.c_str());
   std::cout << "line," << std::endl;
   return true;
}


int main(int argc, char **argv)
{
   al_init();
   al_init_font_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   ALLEGRO_FONT *font = al_create_builtin_font();

   // using const_char_ptr_t as a type in a simple printf:
   const_char_ptr_t format = "foo bar bazz %d";
   int my_int = 32;
   printf(format, my_int);

   // using const_char_ptr_t as a type in a callback function:
   AllegroFlare::Generators::LoremIpsumGenerator ipsum_generator;
   std::string sentences_str = ipsum_generator.generate_sentences(6);
   const_char_ptr_t sentences = sentences_str.c_str();
   al_do_multiline_text(font, 330, sentences, function, font);
   al_flip_display();

   sleep(2);

   al_shutdown_font_addon();
   al_uninstall_system();
   return 0;
}


