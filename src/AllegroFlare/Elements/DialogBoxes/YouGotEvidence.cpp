

#include <AllegroFlare/Elements/DialogBoxes/YouGotEvidence.hpp>

#include <allegro5/allegro.h>


namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxes
{


YouGotEvidence::YouGotEvidence(std::string property)
   : AllegroFlare::Elements::DialogBoxes::Base(AllegroFlare::Elements::DialogBoxes::YouGotEvidence::TYPE)
   , property(property)
   , finished(false)
{
}


YouGotEvidence::~YouGotEvidence()
{
}


std::string YouGotEvidence::get_property() const
{
   return property;
}


bool YouGotEvidence::get_finished() const
{
   return finished;
}


void YouGotEvidence::update()
{
   if (finished) return;
   if (infer_age() > 1.0) // NOTE: giving it one second before can be dismissed
   {
      finished = true;
   }
   return;
}

void YouGotEvidence::advance()
{
   // TODO: rather than have this "finish" it should advance the animation to the end.  Then, if the dialog
   // has "advance()" called a second time, it will set finished to true.
   // NOTE: this is similar behavior to DialogBoxes/YouGotAnItem, it should be updated accordingly as well
   if (finished) return;
   finished = true;
}


} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


