#pragma once


#include <cstddef>
#include <string>


namespace AllegroFlare
{
   namespace Obfuscators
   {
      class Rotate
      {
      private:
         std::string rotation_set;
         std::size_t rotation;

      protected:


      public:
         Rotate();
         ~Rotate();

         void set_rotation_set(std::string rotation_set);
         void set_rotation(std::size_t rotation);
         std::string get_rotation_set() const;
         std::size_t get_rotation() const;
         bool rotation_set_contains_unique_characters();
         std::string encode(std::string text="[unset-text]");
         std::string decode(std::string text="[unset-text]");
      };
   }
}



