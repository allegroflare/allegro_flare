

#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/SpawnDialog.hpp>



namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{
namespace ScriptEventDatas
{


SpawnDialog::SpawnDialog(std::vector<std::string> dialog_pages)
   : AllegroFlare::GameEventDatas::Base("SpawnDialog")
   , dialog_pages(dialog_pages)
{
}


SpawnDialog::~SpawnDialog()
{
}


void SpawnDialog::set_dialog_pages(std::vector<std::string> dialog_pages)
{
   this->dialog_pages = dialog_pages;
}


std::vector<std::string> SpawnDialog::get_dialog_pages() const
{
   return dialog_pages;
}


} // namespace ScriptEventDatas
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


