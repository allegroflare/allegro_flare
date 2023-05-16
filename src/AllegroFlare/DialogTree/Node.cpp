

#include <AllegroFlare/DialogTree/Node.hpp>




namespace AllegroFlare
{
namespace DialogTree
{


Node::Node()
   : speaker("[unset-speaker]")
   , pages({"[unset-pages]"})
   , options({})
{
}


Node::~Node()
{
}


void Node::set_speaker(std::string speaker)
{
   this->speaker = speaker;
}


void Node::set_pages(std::vector<std::string> pages)
{
   this->pages = pages;
}


void Node::set_options(std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*> options)
{
   this->options = options;
}


std::string Node::get_speaker() const
{
   return speaker;
}


std::vector<std::string> Node::get_pages() const
{
   return pages;
}


std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*> Node::get_options() const
{
   return options;
}




} // namespace DialogTree
} // namespace AllegroFlare


