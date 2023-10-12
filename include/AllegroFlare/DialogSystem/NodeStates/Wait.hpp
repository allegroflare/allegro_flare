#pragma once


#include <AllegroFlare/DialogSystem/NodeStates/Base.hpp>
#include <AllegroFlare/DialogTree/Nodes/Wait.hpp>
#include <AllegroFlare/Time.hpp>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      namespace NodeStates
      {
         class Wait : public AllegroFlare::DialogSystem::NodeStates::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystem/NodeStates/Wait";

         private:
            AllegroFlare::DialogTree::Nodes::Wait* wait_node;
            float started_at;
            bool is_finished;

         protected:


         public:
            Wait(AllegroFlare::DialogTree::Nodes::Wait* wait_node=nullptr);
            virtual ~Wait();

            AllegroFlare::DialogTree::Nodes::Wait* get_wait_node() const;
            float get_started_at() const;
            bool get_is_finished() const;
            void initialize(float time_now=AllegroFlare::Time::absolute_now());
            virtual void update(float time_now=AllegroFlare::Time::absolute_now()) override;
         };
      }
   }
}



