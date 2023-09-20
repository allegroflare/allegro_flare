

#include <AllegroFlare/DialogSystem/DialogEventDatas/CloseDialog.hpp>




namespace AllegroFlare
{
namespace DialogSystem
{
namespace DialogEventDatas
{


CloseDialog::CloseDialog(std::string property)
   : AllegroFlare::GameEventDatas::Base(AllegroFlare::DialogSystem::DialogEventDatas::CloseDialog::TYPE)
   , property(property)
{
}


CloseDialog::~CloseDialog()
{
}


std::string CloseDialog::get_property() const
{
   return property;
}


bool CloseDialog::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}


} // namespace DialogEventDatas
} // namespace DialogSystem
} // namespace AllegroFlare


