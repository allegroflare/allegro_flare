

#include <AllegroFlare/MusicMesh/MusicMesh.hpp>

#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace MusicMesh
{


MusicMesh::MusicMesh(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
   , stamps()
   , next_id(1)
   , multi_mesh(4096)
   , multi_mesh_uv_atlas()
   , font_character_atlas_builder()
   , initialized(false)
{
}


MusicMesh::~MusicMesh()
{
}


void MusicMesh::set_multi_mesh_uv_atlas(AllegroFlare::MultiMeshUVAtlas multi_mesh_uv_atlas)
{
   this->multi_mesh_uv_atlas = multi_mesh_uv_atlas;
}


std::vector<AllegroFlare::MusicMesh::Stamp> MusicMesh::get_stamps() const
{
   return stamps;
}


uint32_t MusicMesh::get_next_id() const
{
   return next_id;
}


AllegroFlare::MultiMeshUVAtlas MusicMesh::get_multi_mesh_uv_atlas() const
{
   return multi_mesh_uv_atlas;
}


void MusicMesh::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "MusicMesh" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   font_character_atlas_builder.set_font_bin(font_bin);
   ALLEGRO_BITMAP *texture = font_character_atlas_builder.create();

   multi_mesh.set_texture(texture);
   multi_mesh.initialize();

   initialized = true;
   return;
}

void MusicMesh::add_music_symbol(float x, float y, uint32_t music_symbol_to_stamp)
{
   std::pair<AllegroFlare::Vec2D, AllegroFlare::Vec2D> uvs =
      font_character_atlas_builder.get_uv_for_index(music_symbol_to_stamp);
   AllegroFlare::Vec2D uv1 = uvs.first;
   AllegroFlare::Vec2D uv2 = uvs.second;


   ALLEGRO_FONT *font = obtain_font();
   //ALLEGRO_GLYPH glyph_data; // cannot use GLYPH because it requires ALLEGRO_UNSTABLE flag
   //bool result = al_get_glyph(font, 0, music_symbol_to_stamp, &glyph_data);
   //if (!result)
   //{
      //std::cout << "could_not_obtain_glyph" std::endl;
   //}


   // here
   float width = font_character_atlas_builder.get_column_width();
   float height = font_character_atlas_builder.get_row_height();
   int descent = font_character_atlas_builder.infer_font_descent();
   float offset_x = 0;
   float offset_y = -descent;
   int multi_mesh_id = multi_mesh.append_raw(x+offset_x, y+offset_y, width, height, uv1.x, uv1.y, uv2.x, uv2.y);
      //atlas_index_of_symbol);


   AllegroFlare::MusicMesh::Stamp stamp(next_id, x, y, multi_mesh_id);
   stamps.push_back(stamp);
   next_id++;
   return;
}

void MusicMesh::remove_stamp_at(int index_of_stamp)
{
   // TODO bounds checking
   uint32_t multi_mesh_id_to_remove = stamps[index_of_stamp].get_multi_mesh_id();
   uint32_t multi_mesh_id_to_swap = multi_mesh.remove(multi_mesh_id_to_remove);
   for (auto &stamp : stamps)
   {
      if (stamp.get_multi_mesh_id() == multi_mesh_id_to_swap)
      {
         stamp.reassign_multi_mesh_id(multi_mesh_id_to_swap);
         break;
      }
   }
}

void MusicMesh::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "MusicMesh" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "MusicMesh" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   multi_mesh.render();
   return;
}

ALLEGRO_FONT* MusicMesh::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "MusicMesh" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   return font_bin->auto_get("Purista Medium.otf -32");
}


} // namespace MusicMesh
} // namespace AllegroFlare


