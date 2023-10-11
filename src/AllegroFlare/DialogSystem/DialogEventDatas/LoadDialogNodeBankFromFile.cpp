

#include <AllegroFlare/DialogSystem/DialogEventDatas/LoadDialogNodeBankFromFile.hpp>




namespace AllegroFlare
{
namespace DialogSystem
{
namespace DialogEventDatas
{


LoadDialogNodeBankFromFile::LoadDialogNodeBankFromFile(std::string yaml_filename)
   : AllegroFlare::GameEventDatas::Base(AllegroFlare::DialogSystem::DialogEventDatas::LoadDialogNodeBankFromFile::TYPE)
   , yaml_filename(yaml_filename)
{
}


LoadDialogNodeBankFromFile::~LoadDialogNodeBankFromFile()
{
}


std::string LoadDialogNodeBankFromFile::get_yaml_filename() const
{
   return yaml_filename;
}




} // namespace DialogEventDatas
} // namespace DialogSystem
} // namespace AllegroFlare


