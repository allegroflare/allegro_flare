

#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>

#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogTree
{
namespace Nodes
{


MultipageWithOptions::MultipageWithOptions(std::string speaker, std::vector<std::string> pages, std::vector<std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*>> options)
   : AllegroFlare::DialogTree::Nodes::Base(AllegroFlare::DialogTree::Nodes::MultipageWithOptions::TYPE)
   , speaker(speaker)
   , pages(pages)
   , options(options)
{
}


MultipageWithOptions::~MultipageWithOptions()
{
}


void MultipageWithOptions::set_speaker(std::string speaker)
{
   this->speaker = speaker;
}


void MultipageWithOptions::set_pages(std::vector<std::string> pages)
{
   this->pages = pages;
}


void MultipageWithOptions::set_options(std::vector<std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*>> options)
{
   this->options = options;
}


std::string MultipageWithOptions::get_speaker() const
{
   return speaker;
}


std::vector<std::string> MultipageWithOptions::get_pages() const
{
   return pages;
}


std::vector<std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*>> MultipageWithOptions::get_options() const
{
   return options;
}


std::pair<std::string, AllegroFlare::DialogTree::NodeOptions::Base*> MultipageWithOptions::get_option_num(int option_num)
{
   if (!((option_num >= 0)))
   {
      std::stringstream error_message;
      error_message << "[MultipageWithOptions::get_option_num]: error: guard \"(option_num >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("MultipageWithOptions::get_option_num: error: guard \"(option_num >= 0)\" not met");
   }
   if (!((option_num < options.size())))
   {
      std::stringstream error_message;
      error_message << "[MultipageWithOptions::get_option_num]: error: guard \"(option_num < options.size())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("MultipageWithOptions::get_option_num: error: guard \"(option_num < options.size())\" not met");
   }
   return options[option_num];
}

std::vector<std::string> MultipageWithOptions::build_options_as_text()
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

int MultipageWithOptions::num_pages()
{
   return pages.size();
}

int MultipageWithOptions::num_options()
{
   return options.size();
}


} // namespace Nodes
} // namespace DialogTree
} // namespace AllegroFlare


