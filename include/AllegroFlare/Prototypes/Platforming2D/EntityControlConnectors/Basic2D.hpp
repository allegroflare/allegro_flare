#pragma once


#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/EntityControlConnectors/Base.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         namespace EntityControlConnectors
         {
            class Basic2D : public AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Prototypes/Platforming2D/EntityControlConnectors/Basic2D";

            private:
               AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* basic_2d_entity;

            protected:


            public:
               Basic2D(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* basic_2d_entity=nullptr);
               virtual ~Basic2D();

               void set_basic_2d_entity(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* basic_2d_entity);
               AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* get_basic_2d_entity() const;
               virtual void key_down_func(ALLEGRO_EVENT* event=nullptr) override;
            };
         }
      }
   }
}



