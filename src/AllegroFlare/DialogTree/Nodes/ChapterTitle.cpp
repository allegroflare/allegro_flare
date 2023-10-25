

#include <AllegroFlare/DialogTree/Nodes/ChapterTitle.hpp>




namespace AllegroFlare
{
namespace DialogTree
{
namespace Nodes
{


ChapterTitle::ChapterTitle(std::string title_text, float duration, std::string next_node_identifier)
   : AllegroFlare::DialogTree::Nodes::Base(AllegroFlare::DialogTree::Nodes::ChapterTitle::TYPE)
   , title_text(title_text)
   , duration(duration)
   , next_node_identifier(next_node_identifier)
{
}


ChapterTitle::~ChapterTitle()
{
}


void ChapterTitle::set_next_node_identifier(std::string next_node_identifier)
{
   this->next_node_identifier = next_node_identifier;
}


std::string ChapterTitle::get_title_text() const
{
   return title_text;
}


float ChapterTitle::get_duration() const
{
   return duration;
}


std::string ChapterTitle::get_next_node_identifier() const
{
   return next_node_identifier;
}




} // namespace Nodes
} // namespace DialogTree
} // namespace AllegroFlare


