
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/NodeOptionActivator.hpp>

#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>


class AllegroFlare_DialogTree_NodeOptionActivatorTest : public ::testing::Test {};


class AllegroFlare_DialogTree_NodeOptionActivatorTestWithSetup : public ::testing::Test
{
public:
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::DialogTree::NodeBank node_bank;
   AllegroFlare::DialogTree::Node* currently_active_node;
   AllegroFlare::DialogTree::NodeOptionActivator node_option_activator;

   AllegroFlare_DialogTree_NodeOptionActivatorTestWithSetup() {}
   virtual void SetUp() override
   {
      al_init();
      event_emitter.initialize();

      node_bank.add_node(
         "node1",
         new AllegroFlare::DialogTree::Node(
               // speaker
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
      currently_active_node = node_bank.find_node_by_name("node1");

      node_option_activator.set_event_emitter(&event_emitter);
      node_option_activator.set_node_bank(&node_bank);
      node_option_activator.set_currently_active_node(currently_active_node);
      node_option_activator.set_selection_choice(0);
   }
   virtual void TearDown() override
   {
      // TODO: Replace this with a teardown of the tree
      delete currently_active_node;
      al_uninstall_system();

   }
};


TEST_F(AllegroFlare_DialogTree_NodeOptionActivatorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::NodeOptionActivator node_option_activator;
}


TEST_F(AllegroFlare_DialogTree_NodeOptionActivatorTestWithSetup, activate__will_not_blow_up)
{

   node_option_activator.set_selection_choice(0);
   node_option_activator.activate();
}


