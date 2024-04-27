

#include <AllegroFlare/Prototypes/Platforming2D/Entities/Boss.hpp>

#include <AllegroFlare/Logger.hpp>


namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{
namespace Entities
{


Boss::Boss()
   : AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D()
   , on_death_begin_callback()
   , on_death_begin_callback_user_data(nullptr)
   , on_death_end_callback()
   , on_death_end_callback_user_data(nullptr)
{
}


Boss::~Boss()
{
}


void Boss::set_on_death_begin_callback(std::function<void(AllegroFlare::Prototypes::Platforming2D::Entities::Boss*, void*)> on_death_begin_callback)
{
   this->on_death_begin_callback = on_death_begin_callback;
}


void Boss::set_on_death_begin_callback_user_data(void* on_death_begin_callback_user_data)
{
   this->on_death_begin_callback_user_data = on_death_begin_callback_user_data;
}


void Boss::set_on_death_end_callback(std::function<void(AllegroFlare::Prototypes::Platforming2D::Entities::Boss*, void*)> on_death_end_callback)
{
   this->on_death_end_callback = on_death_end_callback;
}


void Boss::set_on_death_end_callback_user_data(void* on_death_end_callback_user_data)
{
   this->on_death_end_callback_user_data = on_death_end_callback_user_data;
}


std::function<void(AllegroFlare::Prototypes::Platforming2D::Entities::Boss*, void*)> Boss::get_on_death_begin_callback() const
{
   return on_death_begin_callback;
}


void* Boss::get_on_death_begin_callback_user_data() const
{
   return on_death_begin_callback_user_data;
}


std::function<void(AllegroFlare::Prototypes::Platforming2D::Entities::Boss*, void*)> Boss::get_on_death_end_callback() const
{
   return on_death_end_callback;
}


void* Boss::get_on_death_end_callback_user_data() const
{
   return on_death_end_callback_user_data;
}


std::function<void(AllegroFlare::Prototypes::Platforming2D::Entities::Boss*, void*)> &Boss::get_on_death_begin_callback_ref()
{
   return on_death_begin_callback;
}


void* &Boss::get_on_death_begin_callback_user_data_ref()
{
   return on_death_begin_callback_user_data;
}


std::function<void(AllegroFlare::Prototypes::Platforming2D::Entities::Boss*, void*)> &Boss::get_on_death_end_callback_ref()
{
   return on_death_end_callback;
}


void* &Boss::get_on_death_end_callback_user_data_ref()
{
   return on_death_end_callback_user_data;
}


float Boss::get_health_bar_value()
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::Prototypes::Platforming2D::Entities::Boss::get_health_bar_value",
      "This is expected to be an override in the base class."
   );
   return 0.0f;
}

float Boss::get_health_bar_max_value()
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::Prototypes::Platforming2D::Entities::Boss::get_health_bar_max_value",
      "This is expected to be an override in the base class."
   );
   return 0.0f;
}

void Boss::call_on_death_begin_callback()
{
   // TODO: Consider guarding for on_death_begin_callback, consider that a user may simply not want to have a
   // callback, consider adding a warning and/or disabling the warning with a flag
   // TODO: Test this
   if (on_death_begin_callback) on_death_begin_callback(this, on_death_begin_callback_user_data);
   return;
}

void Boss::call_on_death_end_callback()
{
   // TODO: Consider guarding with on_death_end_callback, consider that a user may simply not want to have a
   // callback, consider adding a warning and/or disabling the warning with a flag
   // TODO: Test this
   if (on_death_end_callback) on_death_end_callback(this, on_death_end_callback_user_data);
   return;
}


} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


