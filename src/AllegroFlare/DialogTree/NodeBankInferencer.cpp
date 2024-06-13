

#include <AllegroFlare/DialogTree/NodeBankInferencer.hpp>

#include <AllegroFlare/DialogTree/Nodes/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>
#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogTree
{


NodeBankInferencer::NodeBankInferencer(AllegroFlare::DialogTree::NodeBank* node_bank)
   : node_bank(node_bank)
   , unrecognized_node_type_callback_func(0)
{
}


NodeBankInferencer::~NodeBankInferencer()
{
}


void NodeBankInferencer::set_node_bank(AllegroFlare::DialogTree::NodeBank* node_bank)
{
   this->node_bank = node_bank;
}


void NodeBankInferencer::set_unrecognized_node_type_callback_func(std::function<bool()> unrecognized_node_type_callback_func)
{
   this->unrecognized_node_type_callback_func = unrecognized_node_type_callback_func;
}


AllegroFlare::DialogTree::NodeBank* NodeBankInferencer::get_node_bank() const
{
   return node_bank;
}


std::function<bool()> NodeBankInferencer::get_unrecognized_node_type_callback_func() const
{
   return unrecognized_node_type_callback_func;
}


std::vector<std::string> NodeBankInferencer::obtain_list_of_speaking_characters()
{
   if (!(node_bank))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::DialogTree::NodeBankInferencer::obtain_list_of_speaking_characters]: error: guard \"node_bank\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::DialogTree::NodeBankInferencer::obtain_list_of_speaking_characters]: error: guard \"node_bank\" not met");
   }
   std::vector<std::string> speakers;

   for (auto &node : node_bank->get_nodes_ref())
   {
      if (node.second->is_type(AllegroFlare::DialogTree::Nodes::MultipageWithOptions::TYPE))
      {
         AllegroFlare::DialogTree::Nodes::MultipageWithOptions *as =
            static_cast<AllegroFlare::DialogTree::Nodes::MultipageWithOptions*>(node.second);
         speakers.push_back(as->get_speaker());
      }
      else if (node.second->is_type(AllegroFlare::DialogTree::Nodes::ExitDialog::TYPE))
      {
         // Do nothing for this node type
      }
      else
      {
         // The node type is not known
         bool is_handled = false;
         if (unrecognized_node_type_callback_func)
         {
            is_handled = unrecognized_node_type_callback_func();
         }

         if (!is_handled)
         {
            AllegroFlare::Logger::throw_error(
                  "AllegroFlare::DialogTree::NodeBankInferencer::obtain_list_of_speaking_characters",
                  "Unhandled case for type \"" + node.second->get_type() + "\""
            );
         }
      }
   }

   return make_unique_and_retain_ordering(speakers);
}

bool NodeBankInferencer::character_names_are_present(std::vector<std::string> character_names_that_must_be_present)
{
   std::vector<std::string> actual_speaking_characters = obtain_list_of_speaking_characters();
   for (const std::string& character_names_that_must_be_present : character_names_that_must_be_present)
   {
      if (std::find(
               actual_speaking_characters.begin(),
               actual_speaking_characters.end(),
               character_names_that_must_be_present
            ) == actual_speaking_characters.end())
      {
         return false;
      }
   }
   return true;
}

std::vector<std::string> NodeBankInferencer::find_missing_character_names(std::vector<std::string> character_names_that_must_be_present)
{
   std::vector<std::string> missing_character_names;
   std::vector<std::string> actual_speaking_characters = obtain_list_of_speaking_characters();
   for (const std::string& character_names_that_must_be_present : character_names_that_must_be_present)
   {
      if (std::find(
               actual_speaking_characters.begin(),
               actual_speaking_characters.end(),
               character_names_that_must_be_present
            ) == actual_speaking_characters.end())
      {
         missing_character_names.push_back(character_names_that_must_be_present);
      }
   }
   return make_unique_and_retain_ordering(missing_character_names);
}

std::vector<std::string> NodeBankInferencer::make_unique_and_retain_ordering(std::vector<std::string> list)
{
   std::vector<std::string> uniqueVector;
   for (auto &element : list)
   {
      if (std::find(uniqueVector.begin(), uniqueVector.end(), element) == uniqueVector.end())
      {
         uniqueVector.push_back(element);
      }
   }
   return uniqueVector;
}


} // namespace DialogTree
} // namespace AllegroFlare


