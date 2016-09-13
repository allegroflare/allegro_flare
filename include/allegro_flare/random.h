#ifndef __ALLEGRO_FLARE_RANDOM_HEADER
#define __ALLEGRO_FLARE_RANDOM_HEADER




#include <random>
#include <ctime>




class Random
{
private:
   std::mt19937 rng;
   unsigned int seed;

public:
   // Seeds the rng with the time.
   Random(unsigned int seed = (unsigned int)time(0))
   {}

   // Manually seeds the rng with a value.
   void set_seed(unsigned int new_seed)
   {
      seed = new_seed;
      rng.seed(seed);
   }

   // Retrieve the current RNG seed.
   unsigned int get_seed()
   {
      return seed;
   }

   // Returns random integer.
   template <typename T>
   T get_random_int(T max, T min = 0)
   {
      std::uniform_int_distribution<T> dist(min, max);
      return dist(rng);
   }

   // Returns random real number.
   template <typename T>
   T get_random_real(T max, T min = 0)
   {
      std::uniform_real_distribution<T> dist(min, max);
      return dist(rng);
   }

   // Returns true if the random number is one in [chance].
   bool get_one_in_chance(int chance)
   {
      if (get_next_int(chance - 1) == 0)
         return true;
      return false;
   }

   // Returns the result of rolling dice with a number of sides.
   int roll_dice(int number_of_die, int sides)
   {
      int result = 0;
      for (int i = 0; i < number_of_die; i++)
         result += get_next_int(sides, 1);
      return result;
   }
};




#endif
