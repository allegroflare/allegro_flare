
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/NodeOptionActivator.hpp>

#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>


class AllegroFlare_DialogTree_NodeOptionActivatorTest : public ::testing::Test {};


TEST_F(AllegroFlare_DialogTree_NodeOptionActivatorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::NodeOptionActivator node_option_activator;
}


TEST_F(AllegroFlare_DialogTree_NodeOptionActivatorTest, activate__will_not_blow_up)
{
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::DialogTree::NodeBank node_bank;
   node_bank.add_node(
      "node1",
      new AllegroFlare::DialogTree::Node(
            "speaker",
            { // pages
               "page1",
               "page2"
            },
            { // options
               { "exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog },
            }
         )
   );
   AllegroFlare::DialogTree::Node* currently_active_node = node_bank.find_node_by_name("node1");
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


