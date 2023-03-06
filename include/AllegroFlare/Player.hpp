#pragma once


#include <cstdint>
#include <string>


namespace AllegroFlare
{
   class Player
   {
   private:
      uint32_t id;
      std::string name;

   protected:


   public:
      Player(uint32_t id=0, std::string name="Player");
      ~Player();

      void set_id(uint32_t id);
      void set_name(std::string name);
      uint32_t get_id() const;
      std::string get_name() const;
   };
}



