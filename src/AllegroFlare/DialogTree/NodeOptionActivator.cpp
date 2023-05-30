

#include <AllegroFlare/DialogTree/NodeOptionActivator.hpp>

#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace DialogTree
{


NodeOptionActivator::NodeOptionActivator(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::DialogTree::NodeBank* node_bank, AllegroFlare::DialogTree::Node* currently_active_node, int selection_choice)
   : event_emitter(event_emitter)
   , node_bank(node_bank)
   , currently_active_node(currently_active_node)
   , selection_choice(selection_choice)
{
}


NodeOptionActivator::~NodeOptionActivator()
{
}


void NodeOptionActivator::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void NodeOptionActivator::set_node_bank(AllegroFlare::DialogTree::NodeBank* node_bank)
{
   this->node_bank = node_bank;
}


void NodeOptionActivator::set_currently_active_node(AllegroFlare::DialogTree::Node* currently_active_node)
{
   this->currently_active_node = currently_active_node;
}


void NodeOptionActivator::set_selection_choice(int selection_choice)
{
   this->selection_choice = selection_choice;
}


AllegroFlare::EventEmitter* NodeOptionActivator::get_event_emitter() const
{
   return event_emitter;
}


AllegroFlare::DialogTree::NodeBank* NodeOptionActivator::get_node_bank() const
{
   return node_bank;
}


AllegroFlare::DialogTree::Node* NodeOptionActivator::get_currently_active_node() const
{
   return currently_active_node;
}


int NodeOptionActivator::get_selection_choice() const
{
   return selection_choice;
}


void NodeOptionActivator::activate()
{
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[NodeOptionActivator::activate]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NodeOptionActivator::activate: error: guard \"event_emitter\" not met");
   }
   if (!(node_bank))
   {
      std::stringstream error_message;
      error_message << "[NodeOptionActivator::activate]: error: guard \"node_bank\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NodeOptionActivator::activate: error: guard \"node_bank\" not met");
   }
   if (!(currently_active_node))
   {
      std::stringstream error_message;
      error_message << "[NodeOptionActivator::activate]: error: guard \"currently_active_node\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NodeOptionActivator::activate: error: guard \"currently_active_node\" not met");
   }
   if (!((selection_choice >= 0)))
   {
      std::stringstream error_message;
      error_message << "[NodeOptionActivator::activate]: error: guard \"(selection_choice >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NodeOptionActivator::activate: error: guard \"(selection_choice >= 0)\" not met");
   }
   if (!((selection_choice < currently_active_node->num_options())))
   {
      std::stringstream error_message;
      error_message << "[NodeOptionActivator::activate]: error: guard \"(selection_choice < currently_active_node->num_options())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("NodeOptionActivator::activate: error: guard \"(selection_choice < currently_active_node->num_options())\" not met");
   }
   AllegroFlare::DialogTree::NodeOptions::Base* node_option =
      currently_active_node->get_option_num(selection_choice).second;
   std::string node_option_type = node_option->get_type();

   std::map<std::string, std::function<void()>> types_map = {
      { AllegroFlare::DialogTree::NodeOptions::ExitDialog::TYPE, [this, node_option]() {
         AllegroFlare::DialogTree::NodeOptions::ExitDialog* as_exit_dialog_node_option =
            static_cast<AllegroFlare::DialogTree::NodeOptions::ExitDialog*>(node_option);
         event_emitter->emit_dialog_close_event();
      }},
      { AllegroFlare::DialogTree::NodeOptions::GoToNode::TYPE, [this, node_option]() {
         // TODO: Test this case
         AllegroFlare::DialogTree::NodeOptions::GoToNode* as_go_to_node_dialog_node_option =
            static_cast<AllegroFlare::DialogTree::NodeOptions::GoToNode*>(node_option);
         std::string target_node_name = as_go_to_node_dialog_node_option->get_target_node_name();
         event_emitter->emit_dialog_open_event(target_node_name);
      }},
   };

   // locate and call the function to handle the item
   if (types_map.count(node_option_type) == 0)
   {
      // item not found
      std::stringstream error_message;
      error_message << "[DialogTree::NodeOptionActivator::activate]: error: Cannot activate a node with the "
                    << "node_option_type \"" << node_option_type << "\", a handling for that type does not exist.";
      throw std::runtime_error(error_message.str());
   }
   else
   {
      // call the item
      types_map[node_option_type]();
   }

   return;
}


} // namespace DialogTree
} // namespace AllegroFlare


