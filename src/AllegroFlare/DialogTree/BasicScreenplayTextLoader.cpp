

#include <AllegroFlare/DialogTree/BasicScreenplayTextLoader.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogTree
{


BasicScreenplayTextLoader::BasicScreenplayTextLoader(std::string text)
   : text(text)
   , node_bank({})
   , loaded(false)
{
}


BasicScreenplayTextLoader::~BasicScreenplayTextLoader()
{
}


bool BasicScreenplayTextLoader::get_loaded() const
{
   return loaded;
}


void BasicScreenplayTextLoader::set_text(std::string text)
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[BasicScreenplayTextLoader::set_text]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicScreenplayTextLoader::set_text: error: guard \"(!loaded)\" not met");
   }
   this->text = text;
   return;
}

AllegroFlare::DialogTree::NodeBank BasicScreenplayTextLoader::get_node_bank()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[BasicScreenplayTextLoader::get_node_bank]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicScreenplayTextLoader::get_node_bank: error: guard \"loaded\" not met");
   }
   return node_bank;
}

AllegroFlare::DialogTree::NodeBank BasicScreenplayTextLoader::load()
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[BasicScreenplayTextLoader::load]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicScreenplayTextLoader::load: error: guard \"(!loaded)\" not met");
   }
   std::vector<std::string> chunks = split(text, "\n\n");

   // TODO: Process the chunks and create nodes

   loaded = true;
   return node_bank;
}

std::vector<std::string> BasicScreenplayTextLoader::split(std::string input, std::string delimiter)
{
   std::vector<std::string> tokens;
   size_t start = 0, end = 0;
   while ((end = input.find(delimiter, start)) != std::string::npos)
   {
      tokens.push_back(input.substr(start, end - start));
      start = end + delimiter.length();
   }
   tokens.push_back(input.substr(start));
   return tokens;
}


} // namespace DialogTree
} // namespace AllegroFlare


