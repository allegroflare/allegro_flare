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

         void set_rotation(std::size_t rotation);
         std::size_t get_rotation() const;
         std::string encode(std::string text="[unset-text]");
         std::string decode(std::string text="[unset-text]");
      };
   }
}



