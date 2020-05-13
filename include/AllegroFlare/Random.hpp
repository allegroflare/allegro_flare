#pragma once



#include <random>
#include <ctime>

#include <allegro5/allegro.h>




namespace AllegroFlare
{
   class Random
   {
   private:
      std::mt19937 random_number_generator;
      unsigned int seed;

   public:
      // Seeds the random number generator with the time.
      Random(unsigned int seed=(unsigned int)time(0));

      // Manually seeds the random number generator with a value.
      void set_seed(unsigned int new_seed);

      // Retrieve the current random number generator seed.
      unsigned int get_seed();

      // Returns a random integer.
      int get_random_int(int min, int max);

      // Returns a random floating point number.
      float get_random_float(float min, float max);

      // Returns a random double.
      double get_random_double(double min, double max);

      // Returns true if the random number is one in chance (inclusive).
      bool get_one_in_chance(int chance);

      // Returns the result of rolling dice with a number of sides.
      int roll_dice(int number_of_die, int sides);

      // Returns a random color
      ALLEGRO_COLOR get_random_color();
   };
}




