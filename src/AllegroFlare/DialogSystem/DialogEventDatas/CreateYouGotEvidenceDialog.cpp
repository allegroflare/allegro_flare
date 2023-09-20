

#include <AllegroFlare/DialogSystem/DialogEventDatas/CreateYouGotEvidenceDialog.hpp>




namespace AllegroFlare
{
namespace DialogSystem
{
namespace DialogEventDatas
{


CreateYouGotEvidenceDialog::CreateYouGotEvidenceDialog(std::string evidence_name, std::string evidence_bitmap_identifier)
   : AllegroFlare::GameEventDatas::Base(AllegroFlare::DialogSystem::DialogEventDatas::CreateYouGotEvidenceDialog::TYPE)
   , evidence_name(evidence_name)
   , evidence_bitmap_identifier(evidence_bitmap_identifier)
{
}


CreateYouGotEvidenceDialog::~CreateYouGotEvidenceDialog()
{
}


std::string CreateYouGotEvidenceDialog::get_evidence_name() const
{
   return evidence_name;
}


std::string CreateYouGotEvidenceDialog::get_evidence_bitmap_identifier() const
{
   return evidence_bitmap_identifier;
}




} // namespace DialogEventDatas
} // namespace DialogSystem
} // namespace AllegroFlare


