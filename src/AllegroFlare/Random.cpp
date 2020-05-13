#include <AllegroFlare/Random.hpp>


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




   int Random::get_random_int(int min, int max)
   {
      std::uniform_int_distribution<int> dist(min, max);
      return dist(random_number_generator);
   }




   float Random::get_random_float(float min, float max)
   {
      std::uniform_real_distribution<float> dist(min, max);
      return dist(random_number_generator);
   }




   double Random::get_random_double(double min, double max)
   {
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



