

#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>

#include <AllegroFlare/ImageProcessing.hpp>
#include <sstream>
#include <iostream>
#include <AllegroFlare/Logger.hpp>


namespace AllegroFlare::TileMaps
{


PrimMeshAtlas::PrimMeshAtlas()
   : bitmap(nullptr)
   , bitmap_filename("unset-bitmap-filename.png")
   , tile_width(1)
   , tile_height(1)
   , tile_spacing(0)
   , tile_index()
{
}


PrimMeshAtlas::~PrimMeshAtlas()
{
   std::cout << "[~PrimMeshAtlas()] WARNING: tile atlas may contain a bitmap (and potentially depenedencies "
             << "reliant on it) that has not been properly freed. This destruction mechanism has not yet "
             << "been properly implemented."
             << std::endl;
   //clear();
}


ALLEGRO_BITMAP *PrimMeshAtlas::get_bitmap()
{
   return bitmap;
}


int PrimMeshAtlas::get_bitmap_width()
{
   if (!bitmap) return 0;
   return al_get_bitmap_width(bitmap);
}


int PrimMeshAtlas::get_bitmap_height()
{
   if (!bitmap) return 0;
   return al_get_bitmap_height(bitmap);
}


std::string PrimMeshAtlas::get_bitmap_filename() const
{
   return bitmap_filename;
}


void PrimMeshAtlas::set_bitmap_filename(std::string bitmap_filename)
{
   this->bitmap_filename = bitmap_filename;
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


void PrimMeshAtlas::set_tile_width(int tile_width)
{
   std::cout << "[PrimMeshAtlas::set_tile_width()] WARNING: setting the tile width will invalidate the mesh, please review."
             << std::endl;
   // TODO: important, the mesh needs to be refreshed if this value is changed
   this->tile_width = tile_width;
}


void PrimMeshAtlas::set_tile_height(int tile_height)
{
   std::cout << "[PrimMeshAtlas::set_tile_height()] WARNING: setting the tile height will invalidate the mesh, please review."
             << std::endl;
   // TODO: important, the mesh needs to be refreshed if this value is changed
   this->tile_height = tile_height;
}


 void PrimMeshAtlas::set_tile_spacing(int tile_spacing)
{
   std::cout << "[PrimMeshAtlas::set_tile_spacing()] WARNING: setting the tile spacing will invalidate the mesh, please review."
             << std::endl;
   // TODO: important, the mesh needs to be refreshed if this value is changed
   this->tile_spacing = tile_spacing;
}


int PrimMeshAtlas::get_tile_index_size()
{
   return tile_index.size();
}


void PrimMeshAtlas::clear()
{
   std::cout << "[PrimMeshAtlas::clear()] WARNING: this feature is destroying a bitmap that potentially may "
             << "have depenedencies (as sub-bitmaps). This destruction mechanism has not yet been properly "
             << "implemented."
             << std::endl;

   for (unsigned i=0; i<tile_index.size(); i++) al_destroy_bitmap(tile_index[i].get_sub_bitmap());
   if (bitmap) al_destroy_bitmap(bitmap);
   bitmap = NULL;
   tile_index.clear();
}


void PrimMeshAtlas::duplicate_bitmap_and_load(
      ALLEGRO_BITMAP *source_bitmap,
      int tile_width,
      int tile_height,
      int tile_spacing
   )
{
   this->tile_width = tile_width;
   this->tile_height = tile_height;
   this->tile_spacing = tile_spacing;

   if (!source_bitmap)
   {
      std::cout << "[PrimMeshAtlas::load()] ERROR: the ALLEGRO_BITMAP provided is NULL" << std::endl;
   }

   // clear the existing contents of this tile atlas (if any)
   clear();

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
}


bool PrimMeshAtlas::get_tile_uv(int index_num, int *u1, int *v1, int *u2, int *v2)
{
   if (index_num < 0 || index_num >= (int)tile_index.size()) return false;

   *u1 = tile_index[index_num].get_u1();
   *v1 = tile_index[index_num].get_v1();
   *u2 = tile_index[index_num].get_u2();
   *v2 = tile_index[index_num].get_v2();

   return true;
}


bool PrimMeshAtlas::get_tile_uv(int index_num, float *u1, float *v1, float *u2, float *v2)
{
   if (index_num < 0 || index_num >= (int)tile_index.size()) return false;

   *u1 = tile_index[index_num].get_u1();
   *v1 = tile_index[index_num].get_v1();
   *u2 = tile_index[index_num].get_u2();
   *v2 = tile_index[index_num].get_v2();

   return true;
}


ALLEGRO_BITMAP *PrimMeshAtlas::get_tile_sub_bitmap(int index_num)
{
   if (index_num < 0 || index_num >= (int)tile_index.size()) return nullptr;
   return tile_index[index_num].get_sub_bitmap();
}


std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> PrimMeshAtlas::get_tile_index()
{
   return tile_index;
}



} // namespace AllegroFlare


