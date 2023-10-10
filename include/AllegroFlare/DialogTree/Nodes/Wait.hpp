#pragma once


#include <AllegroFlare/DialogTree/Nodes/Base.hpp>
#include <AllegroFlare/Time.hpp>


namespace AllegroFlare
{
   namespace DialogTree
   {
      namespace Nodes
      {
         class Wait : public AllegroFlare::DialogTree::Nodes::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogTree/Nodes/Wait";

         private:
            float duration_sec;
            float started_at;

         protected:


         public:
            Wait(float duration_sec=0.0f, float started_at=0.0f);
            virtual ~Wait();

            float get_duration_sec() const;
            float get_started_at() const;
            virtual void initialize(float time_now=AllegroFlare::Time::absolute_now()) override;
            virtual void update(float time_now=AllegroFlare::Time::absolute_now()) override;
         };
      }
   }
}



