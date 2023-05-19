

#include <AllegroFlare/DialogTree/Node.hpp>

#include <AllegroFlare/Logger.hpp>


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


void Node::set_options(std::vector<std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*>> options)
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


std::vector<std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*>> Node::get_options() const
{
   return options;
}


std::vector<std::string> Node::build_options_as_text()
{
   // TODO: Test this function
   std::vector<std::string> result;
   result.reserve(options.size());
   for (auto &option : options)
   {
      // TODO: Consider if this check is necessary
      if (!option.second)
      {
         AllegroFlare::Logger::throw_error("AllegroFlare/DialogTree/Node", "an option contains a nullptr");
      }
      result.push_back(option.first);
   }
   return result;
}

int Node::num_options()
{
   return options.size();
}


} // namespace DialogTree
} // namespace AllegroFlare


