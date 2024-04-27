#pragma once


#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Boss.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         namespace Entities
         {
            class BossZone : public AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Prototypes/Platforming2D/Entities/BossZone";

            private:
               AllegroFlare::Prototypes::Platforming2D::Entities::Boss* boss;

            protected:


            public:
               BossZone();
               ~BossZone();

               void set_boss(AllegroFlare::Prototypes::Platforming2D::Entities::Boss* boss);
               AllegroFlare::Prototypes::Platforming2D::Entities::Boss* get_boss() const;
            };
         }
      }
   }
}



