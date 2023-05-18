

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


void NodeBank::set_nodes(std::map<std::string, AllegroFlare::DialogTree::Node*> nodes)
{
   this->nodes = nodes;
}


uint32_t NodeBank::num_nodes()
{
   return nodes.size();
}

void NodeBank::add_node(std::string name, AllegroFlare::DialogTree::Node* node)
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

AllegroFlare::DialogTree::Node* NodeBank::find_node_by_name(std::string name)
{
   if (nodes.find(name) == nodes.end()) return nullptr;
   return nodes[name];
}


} // namespace DialogTree
} // namespace AllegroFlare


