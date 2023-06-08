#pragma once


#include <AllegroFlare/ElementID.hpp>
#include <string>


namespace AllegroFlare
{
   namespace GraphicsPipelines
   {
      namespace DynamicEntityPipeline
      {
         namespace Entities
         {
            class Base : public AllegroFlare::ElementID
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/Base";

            private:
               std::string type;

            protected:


            public:
               Base(std::string type=AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base::TYPE);
               ~Base();

               std::string get_type() const;
               bool is_type(std::string possible_type="");
            };
         }
      }
   }
}



