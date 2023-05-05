

#include <AllegroFlare/ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL.hpp>

#include <AllegroFlare/Logger.hpp>


namespace AllegroFlare
{


ALLEGRO_VERTEX_DECL *create_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL_vertex_declaration()
{
   if (!(al_is_system_installed()))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::create_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL_vertex_declaration",
         "Allegro must be initialized. (ai_is_system_installed() returned false)."
      );
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::create_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL_vertex_declaration",
         "Primitives addon must be initialized. (al_is_primitives_addon_initialized() returned false)."
      );
   }
   if (!al_get_current_display())
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::create_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL_vertex_declaration",
         "A valid display must be present (al_get_current_display() returned a nullptr)."
      );
   }

   ALLEGRO_VERTEX_ELEMENT elems[] = {
      {ALLEGRO_PRIM_POSITION, ALLEGRO_PRIM_FLOAT_3, offsetof(ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL, x)},
      {ALLEGRO_PRIM_TEX_COORD, ALLEGRO_PRIM_FLOAT_2, offsetof(ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL, u1)},
      // NOTE: This ALLEGRO_PRIM_TEX_COORD may need to be a ALLEGRO_PRIM_USER_ATTR. See the TILEO_TILE_VERTEX.
      //{ALLEGRO_PRIM_TEX_COORD, ALLEGRO_PRIM_FLOAT_2, offsetof(ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL, u2)},
      {ALLEGRO_PRIM_USER_ATTR+0, ALLEGRO_PRIM_FLOAT_2, offsetof(ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL, u2)},
      {ALLEGRO_PRIM_COLOR_ATTR, 0, offsetof(ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL, color)},
      {ALLEGRO_PRIM_USER_ATTR, ALLEGRO_PRIM_FLOAT_3, offsetof(ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL, nx)},
      {0, 0, 0}
   };

   return al_create_vertex_decl(elems, sizeof(ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL));
}


} // namespace AllegroFlare;


