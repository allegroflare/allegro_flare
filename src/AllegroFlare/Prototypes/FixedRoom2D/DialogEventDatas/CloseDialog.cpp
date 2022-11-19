

#include <AllegroFlare/Prototypes/FixedRoom2D/DialogEventDatas/CloseDialog.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{
namespace DialogEventDatas
{


CloseDialog::CloseDialog(AllegroFlare::Elements::DialogBoxes::Base* dialog)
   : AllegroFlare::GameEventDatas::Base("SpawnDialog")
   , dialog(dialog)
{
}


CloseDialog::~CloseDialog()
{
}


void CloseDialog::set_dialog(AllegroFlare::Elements::DialogBoxes::Base* dialog)
{
   this->dialog = dialog;
}


AllegroFlare::Elements::DialogBoxes::Base* CloseDialog::get_dialog() const
{
   return dialog;
}




} // namespace DialogEventDatas
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


