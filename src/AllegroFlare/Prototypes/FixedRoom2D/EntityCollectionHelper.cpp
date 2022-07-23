

#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


EntityCollectionHelper::EntityCollectionHelper(std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entities)
   : entities(entities)
{
}


EntityCollectionHelper::~EntityCollectionHelper()
{
}


void EntityCollectionHelper::set_entities(std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* entities)
{
   this->entities = entities;
}


std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*>* EntityCollectionHelper::get_entities()
{
   return entities;
}


std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> EntityCollectionHelper::select_all_in_room(std::string room_name)
{
   if (!(entities))
      {
         std::stringstream error_message;
         error_message << "EntityCollectionHelper" << "::" << "select_all_in_room" << ": error: " << "guard \"entities\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> result;
   for (auto &entity : *entities)
   {
      // if entity has the attribute, include it in the result
   }
   return result;
}
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


