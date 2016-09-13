#pragma once

#include <random>
#include <ctime>

namespace io
{
   class Random
   {
   public:
      // Seeds the rng with the time.
      Random() { rng.seed((unsigned int)time(0)); }

      // Manually seeds the rng with a value.
      void Seed(unsigned int value) { rng.seed(value); }

      // Returns random integer.
      template <typename T>
         T GetNextInt(T max, T min = 0)
         {
            std::uniform_int_distribution<T> dist(min, max);
            return dist(rng);
         }

      // Returns random real number.
      template <typename T>
         T GetNextReal(T max, T min = 0)
         {
            std::uniform_real_distribution<T> dist(min, max);
            return dist(rng);
         }

      // Returns true if the random number is one in [chance].
      bool OneIn(int chance)
      {
         if (GetNextInt(chance - 1) == 0)
            return true;
         return false;
      }

      // Returns the result of rolling dice with a number of sides.
      int RollDice(int number, int sides)
      {
         int result = 0;
         for (int i = 0; i < number; i++)
            result += GetNextInt(sides, 1);
         return result;
      }

   private:
      std::mt19937 rng;
   };
}




