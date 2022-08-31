#pragma once


#include <string>


namespace AllegroFlare
{
   namespace GameEventDatas
   {
      class Base
      {
      private:
         std::string type;

      protected:


      public:
         Base(std::string type="Base");
         ~Base();

         void set_type(std::string type);
         std::string get_type() const;
      };
   }
}



