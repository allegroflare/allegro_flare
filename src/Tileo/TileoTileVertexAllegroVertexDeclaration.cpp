

#include <Tileo/TileoTileVertexAllegroVertexDeclaration.hpp>

#include <Tileo/TileoTileVertex.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Tileo
{


TileoTileVertexAllegroVertexDeclaration::TileoTileVertexAllegroVertexDeclaration()
   : vertex_declaration(nullptr)
   , initialized(false)
   , destroyed(false)
{
}


TileoTileVertexAllegroVertexDeclaration::~TileoTileVertexAllegroVertexDeclaration()
{
}


bool TileoTileVertexAllegroVertexDeclaration::get_initialized() const
{
   return initialized;
}


bool TileoTileVertexAllegroVertexDeclaration::get_destroyed() const
{
   return destroyed;
}


ALLEGRO_VERTEX_DECL* TileoTileVertexAllegroVertexDeclaration::get_vertex_declaration()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Tileo::TileoTileVertexAllegroVertexDeclaration::get_vertex_declaration]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::TileoTileVertexAllegroVertexDeclaration::get_vertex_declaration]: error: guard \"initialized\" not met");
   }
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[Tileo::TileoTileVertexAllegroVertexDeclaration::get_vertex_declaration]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::TileoTileVertexAllegroVertexDeclaration::get_vertex_declaration]: error: guard \"(!destroyed)\" not met");
   }
   return vertex_declaration;
}

TILEO_TILE_VERTEX TileoTileVertexAllegroVertexDeclaration::build_empty_vertex()
{
   TILEO_TILE_VERTEX v;
   v.x = v.y = v.z = 0;
   v.texture_u = v.texture_v = 0;
   v.normal_u = v.normal_v = 0;
   v.height_u = v.height_v = 0;
   v.height = 0;
   v.color = ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f};
   return v;
}

void TileoTileVertexAllegroVertexDeclaration::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Tileo::TileoTileVertexAllegroVertexDeclaration::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::TileoTileVertexAllegroVertexDeclaration::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Tileo::TileoTileVertexAllegroVertexDeclaration::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::TileoTileVertexAllegroVertexDeclaration::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Tileo::TileoTileVertexAllegroVertexDeclaration::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::TileoTileVertexAllegroVertexDeclaration::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[Tileo::TileoTileVertexAllegroVertexDeclaration::initialize]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::TileoTileVertexAllegroVertexDeclaration::initialize]: error: guard \"al_get_current_display()\" not met");
   }
   if (!((al_get_display_flags(al_get_current_display()) & ALLEGRO_PROGRAMMABLE_PIPELINE)))
   {
      std::stringstream error_message;
      error_message << "[Tileo::TileoTileVertexAllegroVertexDeclaration::initialize]: error: guard \"(al_get_display_flags(al_get_current_display()) & ALLEGRO_PROGRAMMABLE_PIPELINE)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::TileoTileVertexAllegroVertexDeclaration::initialize]: error: guard \"(al_get_display_flags(al_get_current_display()) & ALLEGRO_PROGRAMMABLE_PIPELINE)\" not met");
   }
   // TODO: guard a display created with ALLEGRO_OPENGL flag.  OPENGL will be expected, specifically
   // for using a GLSL shader when rendering

   // note that al_get_current_display() is required.  This is not noted in the allegro documentation, but a display
   // is expected when making calls to al_create_vertex_decl(), and can be seen by viewing the source code here:
   // https://github.com/liballeg/allegro5/blob/e8457df9492158f2c5f41676e70f0b98c7f5deeb/addons/primitives/primitives.c#L170

   //typedef struct
   //{
   //   float x, y, z;
   //   float texture_u, texture_v;
   //   float normal_u, normal_v;
   //   float height_u, height_v; // this one might not be used in the end
   //   float height;
   //   ALLEGRO_COLOR color;
   //} TILEO_TILE_VERTEX;

   ALLEGRO_VERTEX_ELEMENT elems[] = {
      {ALLEGRO_PRIM_POSITION, ALLEGRO_PRIM_FLOAT_3, offsetof(TILEO_TILE_VERTEX, x)},
      {ALLEGRO_PRIM_TEX_COORD, ALLEGRO_PRIM_FLOAT_2, offsetof(TILEO_TILE_VERTEX, texture_u)},
      {ALLEGRO_PRIM_USER_ATTR+0, ALLEGRO_PRIM_FLOAT_2, offsetof(TILEO_TILE_VERTEX, normal_u)},
      {ALLEGRO_PRIM_USER_ATTR+1, ALLEGRO_PRIM_FLOAT_2, offsetof(TILEO_TILE_VERTEX, height_u)},
      {ALLEGRO_PRIM_USER_ATTR+2, ALLEGRO_PRIM_FLOAT_1, offsetof(TILEO_TILE_VERTEX, height)},
      {ALLEGRO_PRIM_COLOR_ATTR, 0, offsetof(TILEO_TILE_VERTEX, color)},
      {0, 0, 0},
   };

   vertex_declaration = al_create_vertex_decl(elems, sizeof(TILEO_TILE_VERTEX));

   initialized = true;

   return;
}

void TileoTileVertexAllegroVertexDeclaration::destroy()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Tileo::TileoTileVertexAllegroVertexDeclaration::destroy]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::TileoTileVertexAllegroVertexDeclaration::destroy]: error: guard \"initialized\" not met");
   }
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[Tileo::TileoTileVertexAllegroVertexDeclaration::destroy]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Tileo::TileoTileVertexAllegroVertexDeclaration::destroy]: error: guard \"(!destroyed)\" not met");
   }
   if (!vertex_declaration)
   {
      throw std::runtime_error("there was an error destroying the TileoTileVertexWithNormal declaration.");
   }
   al_destroy_vertex_decl(vertex_declaration);
   vertex_declaration = nullptr;
   destroyed = true;
   return;
}


} // namespace Tileo


