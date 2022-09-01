

#include <AllegroFlare/MusicMesh/MusicMesh.hpp>

#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace MusicMesh
{


MusicMesh::MusicMesh(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
   , stamps({})
{
}


MusicMesh::~MusicMesh()
{
}


std::vector<AllegroFlare::MusicMesh::Stamp> MusicMesh::get_stamps() const
{
   return stamps;
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


