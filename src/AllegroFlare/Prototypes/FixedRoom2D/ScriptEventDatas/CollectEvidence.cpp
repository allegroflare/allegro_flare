

#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/CollectEvidence.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{
namespace ScriptEventDatas
{


CollectEvidence::CollectEvidence(std::string evidence_dictionary_name_to_collect)
   : AllegroFlare::GameEventDatas::Base(AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::CollectEvidence::TYPE)
   , evidence_dictionary_name_to_collect(evidence_dictionary_name_to_collect)
{
}


CollectEvidence::~CollectEvidence()
{
}


void CollectEvidence::set_evidence_dictionary_name_to_collect(std::string evidence_dictionary_name_to_collect)
{
   this->evidence_dictionary_name_to_collect = evidence_dictionary_name_to_collect;
}


std::string CollectEvidence::get_evidence_dictionary_name_to_collect() const
{
   return evidence_dictionary_name_to_collect;
}




} // namespace ScriptEventDatas
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


