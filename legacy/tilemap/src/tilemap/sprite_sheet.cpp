

#include <tilemap/sprite_sheet.hpp>


SpriteSheet::SpriteSheet(ALLEGRO_BITMAP *sprite_sheet_bitmap, int sprite_width, int sprite_height, int scale)
   : atlas(sprite_sheet_bitmap)
   , sprites()
   , sprite_width(sprite_width)
   , sprite_height(sprite_height)
   , num_rows(atlas ? al_get_bitmap_height(atlas) / sprite_height : 0)
   , num_columns(atlas ? al_get_bitmap_width(atlas) / sprite_width : 0)
   , scale(scale)
{
   if (!atlas) throw std::runtime_error("cannot create spritesheet with a nullptr atlas.");
   _create_atlas_copy();
   _create_sub_sprites();
}


void SpriteSheet::_create_atlas_copy()
{
   //atlas = create_pixel_perfect_scaled_render(atlas, scale);
   atlas = al_clone_bitmap(atlas);
}


bool SpriteSheet::_create_sub_sprites()
{
   if (!atlas) return false;

   for (unsigned cursor_y=0; cursor_y<num_rows; cursor_y++)
      for (unsigned cursor_x=0; cursor_x<num_columns; cursor_x++)
      {
         ALLEGRO_BITMAP *sub_bitmap = al_create_sub_bitmap(atlas,
               cursor_x * sprite_width * scale,
               cursor_y * sprite_height * scale,
               sprite_width * scale,
               sprite_height * scale);

         sprites.push_back(sub_bitmap);
      }

   return true;
}


SpriteSheet::~SpriteSheet()
{
   for (auto &sprite : sprites) al_destroy_bitmap(sprite);
   al_destroy_bitmap(atlas);
}


ALLEGRO_BITMAP *SpriteSheet::get_sprite(int index)
{
   if (index < 0 || index >= sprites.size()) return nullptr;
   return sprites[index];
}


int SpriteSheet::get_num_sprites()
{
   return sprites.size();
}


