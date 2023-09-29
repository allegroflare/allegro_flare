

#include <AllegroFlare/DialogTree/NodeBank.hpp>

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

bool NodeBank::node_exists_by_name(std::string name)
{
   return (nodes.find(name) != nodes.end());
}

AllegroFlare::DialogTree::Nodes::Base* NodeBank::find_node_by_name(std::string name)
{
   if (!(node_exists_by_name(name)))
   {
      std::stringstream error_message;
      error_message << "[NodeBank::find_node_by_name]: error: guard \"node_exists_by_name(name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NodeBank::find_node_by_name: error: guard \"node_exists_by_name(name)\" not met");
   }
   // TODO: This guard results in a double lookup. Might be faster to integrate it below.
   if (nodes.find(name) == nodes.end()) return nullptr;
   return nodes[name];
}


} // namespace DialogTree
} // namespace AllegroFlare


