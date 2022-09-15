
#include <Wicked/StandardCompoundShader.hpp>

#include <iostream>


Shader *standard_compound_shader = nullptr;

Shader *__get_standard_compound_shader()
{
   if (standard_compound_shader) return standard_compound_shader;

   std::cout << "Building Entity::standard_compound_shader." << std::endl;
   standard_compound_shader = new Shader("data/shaders/standard_compound_vertex.glsl", "data/shaders/standard_compound_fragment.glsl");
   //standard_compound_shader->initialize();
   if (!standard_compound_shader)
   {
      std::cout << "There was a problem creating the compound shader for Entity" << std::endl;
   }
   return standard_compound_shader;
}



