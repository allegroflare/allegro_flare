#pragma once


#include <AllegroFlare/Prototypes/FixedRoom2D/FixedRoom2D.hpp>
#include <AllegroFlare/Screens/Base.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         class Screen : public AllegroFlare::Screens::Base
         {
         private:
            AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D fixed_room_2d;

         public:
            Screen();
            virtual ~Screen();

            virtual void on_activate() override;
            virtual void on_deactivate() override;
            virtual void primary_timer_func() override;
         };
      }
   }
}



