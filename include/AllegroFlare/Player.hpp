#pragma once


#include <cstdint>
#include <string>


namespace AllegroFlare
{
   class Player
   {
   private:
      std::string name;
      uint32_t id;

   protected:


   public:
      Player(std::string name="Player", uint32_t id=0);
      ~Player();

      void set_name(std::string name);
      void set_id(uint32_t id);
      std::string get_name() const;
      uint32_t get_id() const;
   };
}



