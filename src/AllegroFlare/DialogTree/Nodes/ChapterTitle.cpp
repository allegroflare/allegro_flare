

#include <AllegroFlare/DialogTree/Nodes/ChapterTitle.hpp>




namespace AllegroFlare
{
namespace DialogTree
{
namespace Nodes
{


ChapterTitle::ChapterTitle(std::string title_text)
   : AllegroFlare::DialogTree::Nodes::Base(AllegroFlare::DialogTree::Nodes::ChapterTitle::TYPE)
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




} // namespace Nodes
} // namespace DialogTree
} // namespace AllegroFlare


