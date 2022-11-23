

#include <AllegroFlare/Prototypes/FixedRoom2D/DialogEventDatas/CreateYouGotEvidenceDialog.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{
namespace DialogEventDatas
{


CreateYouGotEvidenceDialog::CreateYouGotEvidenceDialog(std::string evidence_name, std::string evidence_bitmap_identifier)
   : AllegroFlare::GameEventDatas::Base(AllegroFlare::Prototypes::FixedRoom2D::DialogEventDatas::CreateYouGotEvidenceDialog::TYPE)
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
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


