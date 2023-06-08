

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/SceneRenderer.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace GraphicsPipelines
{
namespace DynamicEntityPipeline
{


SceneRenderer::SceneRenderer(AllegroFlare::Shaders::Cubemap* cubemap_shader, AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool)
   : cubemap_shader(cubemap_shader)
   , entity_pool(entity_pool)
{
}


SceneRenderer::~SceneRenderer()
{
}


void SceneRenderer::set_cubemap_shader(AllegroFlare::Shaders::Cubemap* cubemap_shader)
{
   this->cubemap_shader = cubemap_shader;
}


void SceneRenderer::set_entity_pool(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool)
{
   this->entity_pool = entity_pool;
}


AllegroFlare::Shaders::Cubemap* SceneRenderer::get_cubemap_shader() const
{
   return cubemap_shader;
}


AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* SceneRenderer::get_entity_pool() const
{
   return entity_pool;
}


void SceneRenderer::render()
{
   if (!(entity_pool))
   {
      std::stringstream error_message;
      error_message << "[SceneRenderer::render]: error: guard \"entity_pool\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SceneRenderer::render: error: guard \"entity_pool\" not met");
   }
   if (!(cubemap_shader))
   {
      std::stringstream error_message;
      error_message << "[SceneRenderer::render]: error: guard \"cubemap_shader\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SceneRenderer::render: error: guard \"cubemap_shader\" not met");
   }
   // TODO: This function
   return;
}


} // namespace DynamicEntityPipeline
} // namespace GraphicsPipelines
} // namespace AllegroFlare


