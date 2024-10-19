

#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace TileMaps
{


PrimMeshAtlas::PrimMeshAtlas()
   : bitmap(nullptr)
   , bitmap_filename("[unset-bitmap_filename]")
   , tile_width(1)
   , tile_height(1)
   , tile_spacing(0)
   , tile_index()
   , initialized(false)
{
}


PrimMeshAtlas::~PrimMeshAtlas()
{
}


void PrimMeshAtlas::set_bitmap_filename(std::string bitmap_filename)
{
   this->bitmap_filename = bitmap_filename;
}


void PrimMeshAtlas::set_tile_width(int tile_width)
{
   if (get_initialized()) throw std::runtime_error("[PrimMeshAtlas::set_tile_width]: error: guard \"get_initialized()\" not met.");
   this->tile_width = tile_width;
}


void PrimMeshAtlas::set_tile_height(int tile_height)
{
   if (get_initialized()) throw std::runtime_error("[PrimMeshAtlas::set_tile_height]: error: guard \"get_initialized()\" not met.");
   this->tile_height = tile_height;
}


void PrimMeshAtlas::set_tile_spacing(int tile_spacing)
{
   if (get_initialized()) throw std::runtime_error("[PrimMeshAtlas::set_tile_spacing]: error: guard \"get_initialized()\" not met.");
   this->tile_spacing = tile_spacing;
}


std::string PrimMeshAtlas::get_bitmap_filename() const
{
   return bitmap_filename;
}


int PrimMeshAtlas::get_tile_width() const
{
   return tile_width;
}


int PrimMeshAtlas::get_tile_height() const
{
   return tile_height;
}


int PrimMeshAtlas::get_tile_spacing() const
{
   return tile_spacing;
}


std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> PrimMeshAtlas::get_tile_index() const
{
   return tile_index;
}


bool PrimMeshAtlas::get_initialized() const
{
   return initialized;
}


ALLEGRO_BITMAP* PrimMeshAtlas::get_bitmap()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::PrimMeshAtlas::get_bitmap]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::PrimMeshAtlas::get_bitmap]: error: guard \"initialized\" not met");
   }
   return bitmap;
}

void PrimMeshAtlas::clear()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::PrimMeshAtlas::clear]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::PrimMeshAtlas::clear]: error: guard \"initialized\" not met");
   }
   // TODO: Consider re-evaluating this warning, consider initialization scheduling on this class instead
   std::cout << "[PrimMeshAtlas::clear()] WARNING: this feature is destroying a bitmap that potentially may "
             << "have depenedencies (as sub-bitmaps). This destruction mechanism has not yet been properly "
             << "implemented."
             << std::endl;

   for (unsigned i=0; i<tile_index.size(); i++) al_destroy_bitmap(tile_index[i].get_sub_bitmap());
   if (bitmap) al_destroy_bitmap(bitmap);
   bitmap = NULL;
   tile_index.clear();
   return;
}

void PrimMeshAtlas::duplicate_bitmap_and_load(ALLEGRO_BITMAP* source_bitmap, int tile_width, int tile_height, int tile_spacing)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::PrimMeshAtlas::duplicate_bitmap_and_load]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::PrimMeshAtlas::duplicate_bitmap_and_load]: error: guard \"(!initialized)\" not met");
   }
   if (!(source_bitmap))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::PrimMeshAtlas::duplicate_bitmap_and_load]: error: guard \"source_bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::PrimMeshAtlas::duplicate_bitmap_and_load]: error: guard \"source_bitmap\" not met");
   }
   if (!((!al_is_sub_bitmap(source_bitmap))))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TileMaps::PrimMeshAtlas::duplicate_bitmap_and_load]: error: guard \"(!al_is_sub_bitmap(source_bitmap))\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TileMaps::PrimMeshAtlas::duplicate_bitmap_and_load]: error: guard \"(!al_is_sub_bitmap(source_bitmap))\" not met");
   }
   // TODO: Add test on the guard that this cannot be a sub-bitmap

   this->tile_width = tile_width;
   this->tile_height = tile_height;
   this->tile_spacing = tile_spacing;

   //if (!source_bitmap)
   //{
      //std::cout << "[PrimMeshAtlas::load()] ERROR: the ALLEGRO_BITMAP provided is NULL" << std::endl;
   //}

   // clear the existing contents of this tile atlas (if any)
   //clear();

   bitmap = al_clone_bitmap(source_bitmap);

   int tile_step_x = tile_width + (tile_spacing*2);
   int tile_step_y = tile_height + (tile_spacing*2);

   int num_columns = al_get_bitmap_width(bitmap) / tile_step_x;
   int num_rows = al_get_bitmap_height(bitmap) / tile_step_y;
   tile_index.resize(num_columns * num_rows);

   // TODO: add one empty spot for "0"

   for (unsigned index_num=0; index_num<tile_index.size(); index_num++)
   {
      int x1 = (index_num % num_columns) * tile_step_x + tile_spacing;
      int y1 = (index_num / num_columns) * tile_step_y + tile_spacing;
      int x2 = x1 + tile_width;
      int y2 = y1 + tile_height;

      tile_index[index_num].set_index_num(index_num);
      tile_index[index_num].set_bitmap_source(nullptr);
      tile_index[index_num].set_sub_bitmap(al_create_sub_bitmap(bitmap, x1, y1, x2-x1, y2-y1));
      tile_index[index_num].set_u1(x1);
      tile_index[index_num].set_v1(y1);
      tile_index[index_num].set_u2(x2);
      tile_index[index_num].set_v2(y2);
   }

   initialized = true;
   return;
}

int PrimMeshAtlas::get_tile_index_size()
{
   return tile_index.size();
   return 0;
}

int PrimMeshAtlas::get_bitmap_width()
{
   if (!bitmap) return 0; // TODO: Consider throwing here instead
   return al_get_bitmap_width(bitmap);
   return 0;
}

int PrimMeshAtlas::get_bitmap_height()
{
   if (!bitmap) return 0; // TODO: Consider throwing here instead
   return al_get_bitmap_height(bitmap);
   return 0;
}

bool PrimMeshAtlas::get_tile_uv(int index_num, int* u1, int* v1, int* u2, int* v2)
{
   // TODO: Investigate why there are two "get_tile_uv" methods, with int and float argument variants. Remove the
   // incorrect one if that's the case.
   if (index_num < 0 || index_num >= (int)tile_index.size()) return false;

   *u1 = tile_index[index_num].get_u1();
   *v1 = tile_index[index_num].get_v1();
   *u2 = tile_index[index_num].get_u2();
   *v2 = tile_index[index_num].get_v2();

   return true;
}

bool PrimMeshAtlas::get_tile_uv(int index_num, float* u1, float* v1, float* u2, float* v2)
{
   // TODO: Investigate why there are two "get_tile_uv" methods, with int and float argument variants. Remove the
   // incorrect one if that's the case.
   if (index_num < 0 || index_num >= (int)tile_index.size()) return false;

   *u1 = tile_index[index_num].get_u1();
   *v1 = tile_index[index_num].get_v1();
   *u2 = tile_index[index_num].get_u2();
   *v2 = tile_index[index_num].get_v2();

   return true;
   return false;
}

ALLEGRO_BITMAP* PrimMeshAtlas::get_tile_sub_bitmap(int index_num)
{
   if (index_num < 0 || index_num >= (int)tile_index.size()) return nullptr;
   return tile_index[index_num].get_sub_bitmap();
   return nullptr;
}


} // namespace TileMaps
} // namespace AllegroFlare


