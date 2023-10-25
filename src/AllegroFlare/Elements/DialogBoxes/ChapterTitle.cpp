

#include <AllegroFlare/Elements/DialogBoxes/ChapterTitle.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxes
{


ChapterTitle::ChapterTitle(std::string title_text)
   : AllegroFlare::Elements::DialogBoxes::Base(AllegroFlare::Elements::DialogBoxes::ChapterTitle::TYPE)
   , title_text(title_text)
{
}


ChapterTitle::~ChapterTitle()
{
}


std::string ChapterTitle::get_title_text() const
{
   return title_text;
}




} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


