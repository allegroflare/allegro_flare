

#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>

#include <AllegroFlare/ImageProcessing.hpp>
#include <sstream>
#include <iostream>


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















PrimMeshAtlas::TileAtlasBuilder::TileAtlasBuilder(int tile_w, int tile_h, std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> tile_index)
   : tile_w(tile_w)
   , tile_h(tile_h)
   , tile_index(tile_index)
{
}


PrimMeshAtlas::TileAtlasBuilder::~TileAtlasBuilder()
{
}


ALLEGRO_BITMAP *PrimMeshAtlas::TileAtlasBuilder::build_extruded()
{
   //al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP);

   ALLEGRO_STATE prev;
   al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
   ALLEGRO_BITMAP *target = al_create_bitmap(1536, 1536); // TODO: make this a little better
   //ALLEGRO_BITMAP *target = al_create_bitmap(512, 512);
   al_set_target_bitmap(target);


   al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));


   int step_x = tile_w + 2;
   int step_y = tile_h + 2;

   int num_rows = al_get_bitmap_height(target) / step_x;
   int num_cols = al_get_bitmap_width(target) / step_y;


   // step 1:
   // draw each tile onto the new tile_atlas bitmap, each with an extra padding of 1px

   for (int y=0; y<num_rows; y++)
      for (int x=0; x<num_cols; x++)
      {
         int index_num = x + y*num_cols;
         if (index_num >= (int)tile_index.size()) goto tile_drawing_finished;

         int draw_x = x*step_x + 1;
         int draw_y = y*step_y + 1;

         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x, draw_y, 0);
      }

   tile_drawing_finished:


   // step 2:
   // "extrude" the pixels on the edges of each tile

   for (int y=0; y<num_rows; y++)
      for (int x=0; x<num_cols; x++)
      {
         int index_num = x + y*num_cols;
         if (index_num >= (int)tile_index.size()) goto edge_extruding_finished;

         int draw_x = x*step_x + 1;
         int draw_y = y*step_y + 1;


         // draw the top row of pixels
         al_set_clipping_rectangle(draw_x, draw_y-1, tile_w, 1);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x, draw_y-1, 0);

         // draw the bottom row of pixels
         al_set_clipping_rectangle(draw_x, draw_y+tile_h, tile_w, 1);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x, draw_y+1, 0);

         // draw the left row of pixels
         al_set_clipping_rectangle(draw_x-1, draw_y, 1, tile_h);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x-1, draw_y, 0);

         // draw the right row of pixels
         al_set_clipping_rectangle(draw_x+tile_w, draw_y, 1, tile_h);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x+1, draw_y, 0);


         // draw just the top-left pixel
         al_set_clipping_rectangle(draw_x-1, draw_y-1, 1, 1);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x-1, draw_y-1, 0);

         // draw just the bottom-left pixel
         al_set_clipping_rectangle(draw_x-1, draw_y+tile_h, 1, 1);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x-1, draw_y+1, 0);

         // draw just the top-right pixel
         al_set_clipping_rectangle(draw_x+tile_w, draw_y-1, 1, 1);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x+1, draw_y-1, 0);

         // draw just the top-right pixel
         al_set_clipping_rectangle(draw_x+tile_w, draw_y+tile_h, 1, 1);
         al_draw_bitmap(tile_index[index_num].get_sub_bitmap(), draw_x+1, draw_y+1, 0);
      }

   edge_extruding_finished:

   al_set_clipping_rectangle(0, 0, al_get_bitmap_width(target), al_get_bitmap_height(target));


   //
   // wrap it all up

   al_restore_state(&prev);


   //
   // to solve an odd bug, the bitmap will be cloned so that OPENGL will correctly create the mipmaps
   ALLEGRO_BITMAP *cloned = al_clone_bitmap(target);
   al_destroy_bitmap(target);
   target = cloned;


   return target;
}



//#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>

ALLEGRO_BITMAP *PrimMeshAtlas::TileAtlasBuilder::build_scaled_and_extruded(
      ALLEGRO_BITMAP *original_bitmap,
      int scale,
      int tile_width,
      int tile_height
   )
{
   // TODO: Confirm the lifecycle of this sprite sheet:
   //    - the original bitmap
   //    - the duplicated bitmap
   //    - the created sub-bitmaps

   //ALLEGRO_BITMAP *original_bitmap = al_load_bitmap(TEST_TILE_ATLAS_BITMAP_PATH);
   // TODO: require al_init
   // TODO: require al_init_image_addon
   if (!al_is_system_installed()) throw std::runtime_error("AAAxixxA");// al_init();
   //al_init_image_addon();
   //al_init_color_addon();

   //ALLEGRO_BITMAP* source_bitmap = original_bitmap; //al_load_bitmap(TEST_TILE_ATLAS_BITMAP_PATH);
   //ASSERT_NE(nullptr, source_bitmap);

   //Tileo::Atlas atlas;
   //atlas.duplicate_bitmap_and_load(source_bitmap, 16, 16, 0);

   //int scale=3;
   ALLEGRO_BITMAP *scaled = PrimMeshAtlas::TileAtlasBuilder::create_pixel_perfect_scaled_render(original_bitmap, scale);

   AllegroFlare::TileMaps::PrimMeshAtlas atlas;
      //atlas.duplicate_bitmap_and_load(scaled, 16*scale, 16*scale, 0);
      atlas.duplicate_bitmap_and_load(scaled, tile_width*scale, tile_height*scale, 0);
      al_destroy_bitmap(scaled);
      std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> tile_index = atlas.get_tile_index();
      //PrimMeshAtlas::TileAtlasBuilder tile_atlas_builder(16*scale, 16*scale, tile_index);
      PrimMeshAtlas::TileAtlasBuilder tile_atlas_builder(tile_width*scale, tile_height*scale, tile_index);
      //atlas.clear();


      ALLEGRO_BITMAP *result = tile_atlas_builder.build_extruded();
   //al_save_bitmap(build_test_filename_png("buid__will_create_an_atlas").c_str(), result);

   atlas.clear();

   //al_destroy_bitmap(scaled);
   //al_destroy_bitmap(result);
   //atlas.clear();
   //al_destroy_bitmap(source_bitmap);
   //al_shutdown_image_addon();
   //al_uninstall_system();

   return result;
}


//ALLEGRO_BITMAP build_scaled_and_extruded(ALLEGRO_BITMAP *bitmap, int scale, AllegroFlare::TileMaps::Atlas &atlas)
ALLEGRO_BITMAP *PrimMeshAtlas::TileAtlasBuilder::create_pixel_perfect_scaled_render(ALLEGRO_BITMAP *bitmap, int scale)
{
   if (!bitmap)
   {
      throw std::runtime_error("PrimMeshAtlas::TileAtlasBuilder::create_pixel_perfect_scaled_render error: needs valid bitmap");
   }
   if (scale <= 0 || scale > 6)
   {
     throw std::runtime_error("PrimMeshAtlas::TileAtlasBuilder::create_pixel_perfect_scaled_render error: needs valid scale value");
   }


   AllegroFlare::ImageProcessing image_processing(bitmap);
   // scale up the original bitmap
   ALLEGRO_BITMAP *scaled = image_processing.create_pixel_perfect_scaled_render(scale);

   return scaled;

   // cut into an atlas

   
   // get the tile_index


   // use build_extruded with original_tile_width * scale, original_tile_height * width
}




























} // namespace AllegroFlare


