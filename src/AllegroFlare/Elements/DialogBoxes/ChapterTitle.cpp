

#include <AllegroFlare/Elements/DialogBoxes/ChapterTitle.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxes
{


ChapterTitle::ChapterTitle(std::string title_text, float duration)
   : AllegroFlare::Elements::DialogBoxes::Base(AllegroFlare::Elements::DialogBoxes::ChapterTitle::TYPE)
   , title_text(title_text)
   , duration(duration)
{
}


ChapterTitle::~ChapterTitle()
{
}


std::string ChapterTitle::get_title_text() const
{
   return title_text;
}


float ChapterTitle::get_duration() const
{
   return duration;
}


void ChapterTitle::update()
{
   if (get_finished()) return;

   if (infer_age() >= duration)
   {
      set_finished(true);
   }
   return;
}

bool ChapterTitle::ready_to_auto_advance()
{
   // Automatically advance if finished
   return get_finished();
}


} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


