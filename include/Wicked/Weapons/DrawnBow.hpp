#pragma once


#include <Wicked/Weapons/Base.hpp>


namespace Wicked
{
   namespace Weapons
   {
      class DrawnBow : public Wicked::Weapons::Base
      {
      private:
         float draw_back_value;
         bool being_drawn;

      protected:


      public:
         DrawnBow();
         ~DrawnBow();

         bool get_being_drawn() const;
         void stop_draw();
         void start_draw();
         float get_strength();
         bool at_max();
         float get_strength_value_styled();
         void update() override;
      };
   }
}



