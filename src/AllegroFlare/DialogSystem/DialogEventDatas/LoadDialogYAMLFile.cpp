

#include <AllegroFlare/DialogSystem/DialogEventDatas/LoadDialogYAMLFile.hpp>




namespace AllegroFlare
{
namespace DialogSystem
{
namespace DialogEventDatas
{


LoadDialogYAMLFile::LoadDialogYAMLFile(std::string yaml_filename)
   : AllegroFlare::GameEventDatas::Base(AllegroFlare::DialogSystem::DialogEventDatas::LoadDialogYAMLFile::TYPE)
   , yaml_filename(yaml_filename)
{
}


LoadDialogYAMLFile::~LoadDialogYAMLFile()
{
}


std::string LoadDialogYAMLFile::get_yaml_filename() const
{
   return yaml_filename;
}




} // namespace DialogEventDatas
} // namespace DialogSystem
} // namespace AllegroFlare


