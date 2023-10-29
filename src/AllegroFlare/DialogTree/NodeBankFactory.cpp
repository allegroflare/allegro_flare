

#include <AllegroFlare/DialogTree/NodeBankFactory.hpp>

#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitProgram.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>
#include <AllegroFlare/DialogTree/Nodes/Wait.hpp>


namespace AllegroFlare
{
namespace DialogTree
{


NodeBankFactory::NodeBankFactory()
{
}


NodeBankFactory::~NodeBankFactory()
{
}


AllegroFlare::DialogTree::NodeBank NodeBankFactory::build_common_system_dialogs_node_bank()
{
   // TODO: Find out where to place constants
   AllegroFlare::DialogTree::NodeBank node_bank;

   //using AllegroFlare::DialogTree::NodeOptions;

   node_bank.add_node(
         "System::INTERNAL::wait_before_exit_program",
         new AllegroFlare::DialogTree::Nodes::Wait(1.0, "System::INTERNAL::exit_program_no_confirm")
      );
   node_bank.add_node("System::INTERNAL::exit_program_no_confirm", new AllegroFlare::DialogTree::Nodes::ExitProgram());
   node_bank.add_node(
         "confirm_exit_program",
         new AllegroFlare::DialogTree::Nodes::MultipageWithOptions
         (
            "system",
            { "Are you sure you want to exit?" },
            { 
               //{ "Yes", new AllegroFlare::DialogTree::NodeOptions::GoToNode("exit_program") },
               {
                  "Yes",
                  new AllegroFlare::DialogTree::NodeOptions::GoToNode("System::INTERNAL::wait_before_exit_program"),
                  AllegroFlare::BitFlags<uint32_t>(0)
               },
               {
                  "No",
                  new AllegroFlare::DialogTree::NodeOptions::ExitDialog(),
                  AllegroFlare::BitFlags<uint32_t>(0)
               },
            }
         )
      );

   return node_bank;
}


} // namespace DialogTree
} // namespace AllegroFlare


