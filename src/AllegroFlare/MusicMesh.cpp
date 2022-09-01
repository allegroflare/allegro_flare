

#include <AllegroFlare/MusicMesh.hpp>

#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


MusicMesh::MusicMesh(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
   , multi_mesh({})
   , max_num_symbols(AllegroFlare::MultiMesh::DEFAULT_NUM_ITEMS)
   , initialized(false)
{
}


MusicMesh::~MusicMesh()
{
}


bool MusicMesh::get_initialized() const
{
   return initialized;
}


void MusicMesh::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "MusicMesh" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   multi_mesh.initialize();
   initialized = true;
   return;
}

void MusicMesh::add_symbol()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "MusicMesh" << "::" << "add_symbol" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   return;
}

void MusicMesh::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "MusicMesh" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
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


} // namespace AllegroFlare


