

#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/InitiateDialog.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{
namespace ScriptEventDatas
{


InitiateDialog::InitiateDialog(std::vector<std::string> dialog_pages)
   : AllegroFlare::GameEventDatas::Base(AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::InitiateDialog::TYPE)
   , dialog_pages(dialog_pages)
{
}


InitiateDialog::~InitiateDialog()
{
}


void InitiateDialog::set_dialog_pages(std::vector<std::string> dialog_pages)
{
   this->dialog_pages = dialog_pages;
}


std::vector<std::string> InitiateDialog::get_dialog_pages() const
{
   return dialog_pages;
}




} // namespace ScriptEventDatas
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


