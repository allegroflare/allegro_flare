

#include <AllegroFlare/DialogTree/NodeBankInferencer.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogTree
{


NodeBankInferencer::NodeBankInferencer(AllegroFlare::DialogTree::NodeBank* node_bank)
   : node_bank(node_bank)
{
}


NodeBankInferencer::~NodeBankInferencer()
{
}


void NodeBankInferencer::set_node_bank(AllegroFlare::DialogTree::NodeBank* node_bank)
{
   this->node_bank = node_bank;
}


AllegroFlare::DialogTree::NodeBank* NodeBankInferencer::get_node_bank() const
{
   return node_bank;
}


std::vector<std::string> NodeBankInferencer::obtain_list_of_speaking_characters()
{
   if (!(node_bank))
   {
      std::stringstream error_message;
      error_message << "[NodeBankInferencer::obtain_list_of_speaking_characters]: error: guard \"node_bank\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NodeBankInferencer::obtain_list_of_speaking_characters: error: guard \"node_bank\" not met");
   }
   std::vector<std::string> speakers;

   // TODO: Iterate all nodes on the node_bank, if type contains a speaker, add to the list;

   return make_unique_and_retain_ordering(speakers);
}

std::vector<std::string> NodeBankInferencer::make_unique_and_retain_ordering(std::vector<std::string> list)
{
   std::vector<std::string> uniqueVector;

   for (auto &element : list)
   {
      // Check if the element is not in the uniqueVector
      if (std::find(uniqueVector.begin(), uniqueVector.end(), element) == uniqueVector.end()) {
         // If not found, add it to uniqueVector
         uniqueVector.push_back(element);
      }
   }

   // uniqueVector now contains unique elements while retaining the order
   //for (auto &element : uniqueVector) {
      //std::cout << element << " ";
   //}

   return uniqueVector;
}


} // namespace DialogTree
} // namespace AllegroFlare


