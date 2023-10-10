#pragma once


#include <AllegroFlare/Time.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogTree
   {
      namespace Nodes
      {
         class Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogTree/Nodes/Base";

         private:
            std::string type;
            bool is_finished;

         protected:


         public:
            Base(std::string type=AllegroFlare::DialogTree::Nodes::Base::TYPE);
            virtual ~Base();

            void set_is_finished(bool is_finished);
            std::string get_type() const;
            bool get_is_finished() const;
            virtual void initialize(float time_now=AllegroFlare::Time::absolute_now());
            virtual void update(float time_now=AllegroFlare::Time::absolute_now());
            bool is_type(std::string possible_type="");
         };
      }
   }
}



