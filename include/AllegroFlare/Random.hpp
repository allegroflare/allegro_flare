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

      // Returns a random bool.
      bool get_random_bool();

      // Returns a random integer.
      int get_random_int(int min, int max);

      // Returns a random floating point number.
      float get_random_float(float min, float max);

      // Returns a random double.
      double get_random_double(double min, double max);

      // Returns a random letter from A-Z.
      // If `lowercase=true`, then the same letter would be returned but in a lowercase.
      unsigned char get_random_letter(bool lowercase=false);

      // Returns a random character.
      unsigned char get_random_letter_or_number();

      // Returns a random string.
      std::string get_random_string(unsigned int length);

      // Returns a random element from an std::vector.
      // If the vector is empty, will throw an error.
      template<class T>
      T get_random_element(std::vector<T> &elements)
      {
         if (elements.empty())
         {
            throw std::runtime_error("[AllegroFlare::Random::get_random_elements] error: elements cannot be empty.");
         }
         return elements[get_random_int(0, elements.size()-1)];
      }

      // Returns true if a one-in-n chance event occurred.
      bool get_one_in_chance(int chance);

      // Returns the result of rolling dice with a number of sides.
      int roll_dice(int sides=6, int number_of_die=1);

      // Returns a random color
      ALLEGRO_COLOR get_random_color();
   };
}




