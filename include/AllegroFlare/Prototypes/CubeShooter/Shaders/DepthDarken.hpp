#pragma once


#include <AllegroFlare/Shader.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace CubeShooter
      {
         namespace Shaders
         {
            class DepthDarken : private AllegroFlare::Shader
            {
            private:
               int torch_type;
               bool initialized;
               static std::string obtain_vertex_source();
               static std::string obtain_fragment_source();

            protected:


            public:
               DepthDarken();
               ~DepthDarken();

               void initialize();
               void set_torch_type(int type=0);
               void set_torch_on();
               void set_torch_off();
               void activate();
               void deactivate();
            };
         }
      }
   }
}



