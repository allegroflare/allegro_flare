

#include <AllegroFlare/DialogTree/BasicScreenplayTextLoader.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogTree
{


BasicScreenplayTextLoader::BasicScreenplayTextLoader(std::string filename)
   : filename(filename)
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


void BasicScreenplayTextLoader::set_filename(std::string filename)
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[BasicScreenplayTextLoader::set_filename]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BasicScreenplayTextLoader::set_filename: error: guard \"(!loaded)\" not met");
   }
   this->filename = filename;
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


} // namespace DialogTree
} // namespace AllegroFlare


