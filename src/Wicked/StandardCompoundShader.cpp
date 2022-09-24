
#include <Wicked/StandardCompoundShader.hpp>

#include <iostream>

#include <AllegroFlare/UsefulPHP.hpp>



AllegroFlare::Shader *standard_compound_shader = nullptr;

AllegroFlare::Shader *__get_standard_compound_shader()
{
   if (standard_compound_shader) return standard_compound_shader;

   std::string vertex_filename = "data/shaders/standard_compound_vertex.glsl";
   std::string vertex_file_content = AllegroFlare::php::file_get_contents(vertex_filename);

   std::string fragment_filename = "data/shaders/standard_compound_fragment.glsl";
   std::string fragment_file_content = AllegroFlare::php::file_get_contents(vertex_filename);

   std::cout << "Building Entity::standard_compound_shader." << std::endl;

   standard_compound_shader = new AllegroFlare::Shader(vertex_file_content, fragment_file_content);
   standard_compound_shader->initialize();

   if (!standard_compound_shader)
   {
      std::cout << "There was a problem creating the compound shader." << std::endl;
   }
   return standard_compound_shader;
}



