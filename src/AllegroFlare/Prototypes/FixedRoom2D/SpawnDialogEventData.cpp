

#include <AllegroFlare/Prototypes/FixedRoom2D/SpawnDialogEventData.hpp>



namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


SpawnDialogEventData::SpawnDialogEventData(std::vector<std::string> dialog_pages)
   : AllegroFlare::GameEventDatas::Base("SpawnDialogEventData")
   , dialog_pages(dialog_pages)
{
}


SpawnDialogEventData::~SpawnDialogEventData()
{
}


void SpawnDialogEventData::set_dialog_pages(std::vector<std::string> dialog_pages)
{
   this->dialog_pages = dialog_pages;
}


std::vector<std::string> SpawnDialogEventData::get_dialog_pages()
{
   return dialog_pages;
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


