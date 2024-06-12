

#include <AllegroFlare/Bone3DGraphRenderer.hpp>

#include <AllegroFlare/Useful3D/Useful3D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


Bone3DGraphRenderer::Bone3DGraphRenderer(AllegroFlare::FontBin* font_bin, AllegroFlare::Bone3D* root_bone)
   : font_bin(font_bin)
   , root_bone(root_bone)
{
}


Bone3DGraphRenderer::~Bone3DGraphRenderer()
{
}


void Bone3DGraphRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Bone3DGraphRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Bone3DGraphRenderer::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Bone3DGraphRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Bone3DGraphRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Bone3DGraphRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Bone3DGraphRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(root_bone))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Bone3DGraphRenderer::render]: error: guard \"root_bone\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Bone3DGraphRenderer::render]: error: guard \"root_bone\" not met");
   }
   render_recursive(root_bone);
   return;
}

void Bone3DGraphRenderer::render_recursive(AllegroFlare::Bone3D* bone)
{
   if (!(bone))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Bone3DGraphRenderer::render_recursive]: error: guard \"bone\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Bone3DGraphRenderer::render_recursive]: error: guard \"bone\" not met");
   }
   //allegro_flare::draw_3d_line(AllegroFlare::vec3d(0, 0, 0), bone->position);
   //al_draw_circle(0, 0, 8, ALLEGRO_COLOR{0.6, 0.7, 0.9, 0.9}, 2.0);

   bone->start_transform();

   al_draw_circle(0, 0, 13, ALLEGRO_COLOR{0.9, 0.65, 0.5, 0.9}, 1.0);

   // render self
   //al_draw_line(0, 0, 100, 100, ALLEGRO_COLOR{0.1, 0.1, 0.9, 1.0}, 2.0);

   // render children
   for (auto &child_bone : bone->get_children_ref())
   {
     render_recursive(child_bone);
   }
   bone->restore_transform();
   return;
}


} // namespace AllegroFlare


