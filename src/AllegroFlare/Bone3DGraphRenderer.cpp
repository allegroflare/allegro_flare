

#include <AllegroFlare/Bone3DGraphRenderer.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <stdexcept>
#include <sstream>
#include <allegro_flare/useful3d.h>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


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
         error_message << "Bone3DGraphRenderer" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_primitives_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Bone3DGraphRenderer" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Bone3DGraphRenderer" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(root_bone))
      {
         std::stringstream error_message;
         error_message << "Bone3DGraphRenderer" << "::" << "render" << ": error: " << "guard \"root_bone\" not met";
         throw std::runtime_error(error_message.str());
      }
   render_recursive(root_bone);
   return;
}

void Bone3DGraphRenderer::render_recursive(AllegroFlare::Bone3D* bone)
{
   if (!(bone))
      {
         std::stringstream error_message;
         error_message << "Bone3DGraphRenderer" << "::" << "render_recursive" << ": error: " << "guard \"bone\" not met";
         throw std::runtime_error(error_message.str());
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

ALLEGRO_FONT* Bone3DGraphRenderer::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Bone3DGraphRenderer" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Purista Medium.otf -32");
}
} // namespace AllegroFlare


