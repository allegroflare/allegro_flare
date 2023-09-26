

#include <AllegroFlare/DialogSystem/DialogEventDatas/SpawnDialogByName.hpp>




namespace AllegroFlare
{
namespace DialogSystem
{
namespace DialogEventDatas
{


SpawnDialogByName::SpawnDialogByName(std::string name)
   : AllegroFlare::GameEventDatas::Base(AllegroFlare::DialogSystem::DialogEventDatas::SpawnDialogByName::TYPE)
   , name(name)
{
}


SpawnDialogByName::~SpawnDialogByName()
{
}


std::string SpawnDialogByName::get_name() const
{
   return name;
}




} // namespace DialogEventDatas
} // namespace DialogSystem
} // namespace AllegroFlare


