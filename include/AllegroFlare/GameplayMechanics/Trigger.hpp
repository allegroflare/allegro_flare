#pragma once


#include <string>


namespace AllegroFlare
{
   namespace GameplayMechanics
   {
      class Trigger
      {
      private:
         bool triggered;

      protected:


      public:
         Trigger();
         ~Trigger();

         bool get_triggered() const;
         void trigger();
         std::string reset();
      };
   }
}



