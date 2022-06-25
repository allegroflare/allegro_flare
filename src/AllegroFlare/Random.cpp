#include <AllegroFlare/Random.hpp>

#include <algorithm>


namespace AllegroFlare
{
   Random::Random(unsigned int seed)
      : seed(seed)
   {
      set_seed(seed);
   }




   void Random::set_seed(unsigned int new_seed)
   {
      seed = new_seed;
      random_number_generator.seed(seed);
   }




   unsigned int Random::get_seed()
   {
      return seed;
   }




   bool Random::get_random_bool()
   {
      return random_number_generator() % 2;
   }




   int Random::get_random_int(int min, int max)
   {
      int fixed_min = std::min(min, max);
      int fixed_max = std::max(min, max);
      int range = fixed_max - fixed_min + 1;
      return random_number_generator() % range + fixed_min;
   }




   float Random::get_random_float(float min, float max)
   {
      // TODO: this does not produce repeatable sequences from the same seed across different platforms/complilers
      std::uniform_real_distribution<float> dist(min, max);
      return dist(random_number_generator);
   }




   double Random::get_random_double(double min, double max)
   {
      // TODO: this does not produce repeatable sequences from the same seed across different platforms/complilers
      std::uniform_real_distribution<double> dist(min, max);
      return dist(random_number_generator);
   }




   bool Random::get_one_in_chance(int chance)
   {
      if (get_random_int(0, chance - 1) == 0)
         return true;
      return false;
   }




   int Random::roll_dice(int number_of_die, int sides)
   {
      int result = 0;
      for (int i = 0; i < number_of_die; i++)
         result += get_random_int(sides, 1);
      return result;
   }




   ALLEGRO_COLOR Random::get_random_color()
   {
      return al_map_rgb(get_random_int(0, 255), get_random_int(0, 255), get_random_int(0, 255));
   }
}



