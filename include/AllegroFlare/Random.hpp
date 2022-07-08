#pragma once



#include <random>
#include <ctime>
#include <algorithm>

#include <allegro5/allegro.h>




namespace AllegroFlare
{
   class Random
   {
   private:
      unsigned int primary_seed;
      std::mt19937 random_number_generator__for_get_random_int;
      std::mt19937 random_number_generator__for_get_random_bool;
      std::mt19937 random_number_generator__for_get_random_sign;
      std::mt19937 random_number_generator__for_get_random_float;
      std::mt19937 random_number_generator__for_get_random_double;
      std::mt19937 random_number_generator__for_get_one_in_chance;
      std::mt19937 random_number_generator__for_get_random_letter;
      std::mt19937 random_number_generator__for_get_random_letter_or_number;
      std::mt19937 random_number_generator__for_get_random_string;
      std::mt19937 random_number_generator__for_roll_dice;
      std::mt19937 random_number_generator__for_get_random_element;
      std::mt19937 random_number_generator__for_shuffle_elements;
      std::mt19937 random_number_generator__for_get_random_color;
      std::mt19937 random_number_generator__for_get_random_color_exhaustive;

      const std::vector<ALLEGRO_COLOR> color_palette;

      int extract_random_int(int min, int max, std::mt19937 &rng);
      unsigned char extract_random_letter(bool lowercase, std::mt19937 &rng);
      unsigned char extract_random_letter_or_number(std::mt19937 &rng);
      

   public:
      // Seeds the random number generator with the time.
      Random(unsigned int seed=(unsigned int)time(0));

      // Manually seeds the random number generator with a value.
      void set_seed(unsigned int new_seed);

      // Retrieve the current random number generator seed.
      unsigned int get_seed();

      // Returns a random bool.
      bool get_random_bool();

      // Returns a random sign (either 1 or -1).
      int get_random_sign();

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
         std::mt19937 &rng = random_number_generator__for_get_random_element;
         if (elements.empty())
         {
            throw std::runtime_error("[AllegroFlare::Random::get_random_elements] error: elements cannot be empty.");
         }
         return elements[extract_random_int(0, elements.size()-1, rng)];
      }

      // Shuffles the elements into a random order.
      template<class T>
      void shuffle_elements(std::vector<T> &elements)
      {
         std::shuffle(elements.begin(), elements.end(), random_number_generator__for_shuffle_elements);
      }

      // Returns true if a one-in-n chance event occurred.
      bool get_one_in_chance(int chance);

      // Returns the result of rolling dice with a number of sides.
      int roll_dice(int sides=6, int number_of_die=1);

      // Returns a random color
      ALLEGRO_COLOR get_random_color();

      // Returns a random color and will not to repeat a color until all possible colors have been returned.
      // The palette consists of the list of AllegroFlare::Color constants, which are from the X11 color codes.
      // There are 142 possible colors.
      ALLEGRO_COLOR get_random_color_exhaustive();

      // Returns the color palette used for get_random_color() and get_random_color_exhaustive()
      std::vector<ALLEGRO_COLOR> get_source_color_palette();
   };
}




