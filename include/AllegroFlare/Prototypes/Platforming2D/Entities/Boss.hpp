#pragma once


#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         namespace Entities
         {
            class Boss : public AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Prototypes/Platforming2D/Entities/Boss";

            private:
               float health;
               float max_health;

            protected:


            public:
               Boss();
               ~Boss();

               void set_health(float health);
               void set_max_health(float max_health);
               float get_health() const;
               float get_max_health() const;
            };
         }
      }
   }
}



