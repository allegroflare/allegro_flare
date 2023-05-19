#pragma once


#include <AllegroFlare/DialogTree/Node.hpp>
#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/EventEmitter.hpp>


namespace AllegroFlare
{
   namespace DialogTree
   {
      class NodeOptionActivator
      {
      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::DialogTree::NodeBank* node_bank;
         AllegroFlare::DialogTree::Node* currently_active_node;
         int selection_choice;

      protected:


      public:
         NodeOptionActivator(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::DialogTree::NodeBank* node_bank=nullptr, AllegroFlare::DialogTree::Node* currently_active_node=nullptr, int selection_choice=0);
         ~NodeOptionActivator();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_node_bank(AllegroFlare::DialogTree::NodeBank* node_bank);
         void set_currently_active_node(AllegroFlare::DialogTree::Node* currently_active_node);
         void set_selection_choice(int selection_choice);
         AllegroFlare::EventEmitter* get_event_emitter() const;
         AllegroFlare::DialogTree::NodeBank* get_node_bank() const;
         AllegroFlare::DialogTree::Node* get_currently_active_node() const;
         int get_selection_choice() const;
         void activate();
      };
   }
}



