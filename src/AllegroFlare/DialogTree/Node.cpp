

#include <AllegroFlare/DialogTree/Node.hpp>

#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogTree
{


Node::Node(std::string speaker, std::vector<std::string> pages, std::vector<std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*>> options)
   : speaker(speaker)
   , pages(pages)
   , options(options)
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


std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*> Node::get_option_num(int option_num)
{
   if (!((option_num >= 0)))
   {
      std::stringstream error_message;
      error_message << "[Node::get_option_num]: error: guard \"(option_num >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Node::get_option_num: error: guard \"(option_num >= 0)\" not met");
   }
   if (!((option_num < options.size())))
   {
      std::stringstream error_message;
      error_message << "[Node::get_option_num]: error: guard \"(option_num < options.size())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Node::get_option_num: error: guard \"(option_num < options.size())\" not met");
   }
   return options[option_num];
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


