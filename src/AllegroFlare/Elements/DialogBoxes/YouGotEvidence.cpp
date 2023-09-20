

#include <AllegroFlare/Elements/DialogBoxes/YouGotEvidence.hpp>

#include <allegro5/allegro.h>


namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxes
{


YouGotEvidence::YouGotEvidence(std::string evidence_name, std::string evidence_bitmap_identifier)
   : AllegroFlare::Elements::DialogBoxes::Base(AllegroFlare::Elements::DialogBoxes::YouGotEvidence::TYPE)
   , evidence_name(evidence_name)
   , evidence_bitmap_identifier(evidence_bitmap_identifier)
{
}


YouGotEvidence::~YouGotEvidence()
{
}


std::string YouGotEvidence::get_evidence_name() const
{
   return evidence_name;
}


std::string YouGotEvidence::get_evidence_bitmap_identifier() const
{
   return evidence_bitmap_identifier;
}


void YouGotEvidence::update()
{
   if (get_finished()) return;
   if (infer_age() > 1.0) // NOTE: giving it one second before can be dismissed
   {
      set_finished(true);
   }
   return;
}

void YouGotEvidence::advance()
{
   // TODO: rather than have this "finish" it should advance the animation to the end.  Then, if the dialog
   // has "advance()" called a second time, it will set finished to true.
   // NOTE: this is similar behavior to DialogBoxes/YouGotAnItem, it should be updated accordingly as well
   if (get_finished()) return;
   set_finished(true);
}


} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


