#pragma once


#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Boss.hpp>
#include <functional>


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
               std::function<void(AllegroFlare::Prototypes::Platforming2D::Entities::Boss*, void*)> on_death_begin_callback;
               void* on_death_begin_callback_user_data;
               std::function<void(AllegroFlare::Prototypes::Platforming2D::Entities::Boss*, void*)> on_death_end_callback;
               void* on_death_end_callback_user_data;

            protected:


            public:
               Boss();
               virtual ~Boss();

               void set_on_death_begin_callback(std::function<void(AllegroFlare::Prototypes::Platforming2D::Entities::Boss*, void*)> on_death_begin_callback);
               void set_on_death_begin_callback_user_data(void* on_death_begin_callback_user_data);
               void set_on_death_end_callback(std::function<void(AllegroFlare::Prototypes::Platforming2D::Entities::Boss*, void*)> on_death_end_callback);
               void set_on_death_end_callback_user_data(void* on_death_end_callback_user_data);
               std::function<void(AllegroFlare::Prototypes::Platforming2D::Entities::Boss*, void*)> get_on_death_begin_callback() const;
               void* get_on_death_begin_callback_user_data() const;
               std::function<void(AllegroFlare::Prototypes::Platforming2D::Entities::Boss*, void*)> get_on_death_end_callback() const;
               void* get_on_death_end_callback_user_data() const;
               std::function<void(AllegroFlare::Prototypes::Platforming2D::Entities::Boss*, void*)> &get_on_death_begin_callback_ref();
               void* &get_on_death_begin_callback_user_data_ref();
               std::function<void(AllegroFlare::Prototypes::Platforming2D::Entities::Boss*, void*)> &get_on_death_end_callback_ref();
               void* &get_on_death_end_callback_user_data_ref();
               virtual float get_health_bar_value();
               virtual float get_health_bar_max_value();
               void call_on_death_begin_callback();
               void call_on_death_end_callback();
            };
         }
      }
   }
}



