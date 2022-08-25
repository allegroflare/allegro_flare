

#include <iostream>
#include <allegro5/allegro.h>
#include <AllegroFlare/Generators/LoremIpsumGenerator.hpp>


int main(int argc, char **argv)
{
   AllegroFlare::Generators::LoremIpsumGenerator lorem_ipsum_generator;

   std::cout << std::endl;
   std::cout << lorem_ipsum_generator.generate_words(150) << std::endl;
   std::cout << std::endl;
   return 0;
}





