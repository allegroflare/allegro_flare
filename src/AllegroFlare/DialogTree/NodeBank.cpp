

#include <AllegroFlare/DialogTree/NodeBank.hpp>

#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogTree
{


NodeBank::NodeBank()
   : nodes({})
{
}


NodeBank::~NodeBank()
{
}


void NodeBank::set_nodes(std::map<std::string, AllegroFlare::DialogTree::Nodes::Base*> nodes)
{
   this->nodes = nodes;
}


std::map<std::string, AllegroFlare::DialogTree::Nodes::Base*> &NodeBank::get_nodes_ref()
{
   return nodes;
}


uint32_t NodeBank::num_nodes()
{
   return nodes.size();
}

void NodeBank::add_node(std::string name, AllegroFlare::DialogTree::Nodes::Base* node)
{
   if (!(node))
   {
      std::stringstream error_message;
      error_message << "[NodeBank::add_node]: error: guard \"node\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NodeBank::add_node: error: guard \"node\" not met");
   }
   if (!((!node_exists_by_name(name))))
   {
      std::stringstream error_message;
      error_message << "[NodeBank::add_node]: error: guard \"(!node_exists_by_name(name))\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NodeBank::add_node: error: guard \"(!node_exists_by_name(name))\" not met");
   }
   nodes[name] = node;
}

void NodeBank::replace_node(std::string name, AllegroFlare::DialogTree::Nodes::Base* node)
{
   if (!(node))
   {
      std::stringstream error_message;
      error_message << "[NodeBank::replace_node]: error: guard \"node\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NodeBank::replace_node: error: guard \"node\" not met");
   }
   if (!(node_exists_by_name(name)))
   {
      std::stringstream error_message;
      error_message << "[NodeBank::replace_node]: error: guard \"node_exists_by_name(name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NodeBank::replace_node: error: guard \"node_exists_by_name(name)\" not met");
   }
   // TODO: Test this
   nodes[name] = node;
}

bool NodeBank::node_exists_by_name(std::string name)
{
   return (nodes.find(name) != nodes.end());
}

AllegroFlare::DialogTree::Nodes::Base* NodeBank::find_node_by_name(std::string name)
{
   if (nodes.find(name) == nodes.end()) return nullptr;
   return nodes[name];
}

void NodeBank::delete_all_nodes_and_clear()
{
   for (auto &node : nodes)
   {
      // TODO: Consider deleting or placing this in a try{} catch{}, Consider throwing if nullptr
      // TODO: Add test for deleted nodes (see AllegroFlare/Testing/MemoryAllocationDeallocationObserver)
      if (node.second != nullptr) delete node.second;
   }
   nodes.clear();
   return;
}

void NodeBank::merge(AllegroFlare::DialogTree::NodeBank* other_node_bank)
{
   if (!(other_node_bank))
   {
      std::stringstream error_message;
      error_message << "[NodeBank::merge]: error: guard \"other_node_bank\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NodeBank::merge: error: guard \"other_node_bank\" not met");
   }
   std::set<std::string> shared_node_names = find_shared_node_names(other_node_bank);
   if (!shared_node_names.empty())
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::DialogTree::NodeBank::merge",
         "Cannot merge two node_bank objects that do not have node names that are the same"
      );
   }

   std::map<std::string, AllegroFlare::DialogTree::Nodes::Base*> &other_nodes = other_node_bank->get_nodes_ref();
   nodes.insert(other_nodes.begin(), other_nodes.end());

   return;
}

std::set<std::string> NodeBank::find_shared_node_names(AllegroFlare::DialogTree::NodeBank* other_node_bank)
{
   if (!(other_node_bank))
   {
      std::stringstream error_message;
      error_message << "[NodeBank::find_shared_node_names]: error: guard \"other_node_bank\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NodeBank::find_shared_node_names: error: guard \"other_node_bank\" not met");
   }
   std::set<std::string> shared_names;
   for (auto &other_node : other_node_bank->get_nodes_ref())
   {
      if (this->node_exists_by_name(other_node.first)) shared_names.insert(other_node.first);
   }
   return shared_names;
}


} // namespace DialogTree
} // namespace AllegroFlare


