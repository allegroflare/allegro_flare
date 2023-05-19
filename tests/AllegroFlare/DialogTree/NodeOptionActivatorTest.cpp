
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/NodeOptionActivator.hpp>

#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>


TEST(AllegroFlare_DialogTree_NodeOptionActivatorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::NodeOptionActivator node_option_activator;
}


TEST(AllegroFlare_DialogTree_NodeOptionActivatorTest, activate__will_not_blow_up)
{
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::DialogTree::NodeBank node_bank;
   AllegroFlare::DialogTree::Node* currently_active_node = new AllegroFlare::DialogTree::Node;
   int selection_choice = 0;

   AllegroFlare::DialogTree::NodeOptionActivator node_option_activator;
   node_option_activator.set_event_emitter(&event_emitter);
   node_option_activator.set_node_bank(&node_bank);
   node_option_activator.set_currently_active_node(currently_active_node);
   node_option_activator.set_selection_choice(selection_choice);

   node_option_activator.activate();

   // Cleanup
   delete currently_active_node;
}


