

#include <framework/color.hpp>
#include <framework/framework.hpp>
#include <framework/placement2d.hpp>
#include <tilemap/sprite.hpp>
#include <tilemap/tile_map.hpp>
#include <tilemap/tile_map_collision_response.hpp>
#include <tilemap/tile_map_factory.hpp>


bool on_collide(TileMap *tile_map, Sprite *sprite, vec2i tile_coordinate, TileMapCollisionResponse::direction_t direction_of_collision, void *data)
{
   if (!data) return true;
   std::set<ALLEGRO_BITMAP *> *solid_tiles = static_cast<std::set<ALLEGRO_BITMAP *> *>(data);
   ALLEGRO_BITMAP *collided_tile = tile_map->get_tile(tile_coordinate.x, tile_coordinate.y);

   const bool is_solid_tile = solid_tiles->find(collided_tile) != solid_tiles->end();

   if (is_solid_tile)
   {
      switch(direction_of_collision)
      {
      case TileMapCollisionResponse::SPRITE_MOVING_UP:
         sprite->velocity.y = 0;
         sprite->placement.y = (tile_coordinate.y * 16) + 16;
         break;
      case TileMapCollisionResponse::SPRITE_MOVING_DOWN:
         sprite->velocity.y = 0;
         sprite->placement.y = (tile_coordinate.y * 16) - sprite->placement.size.y;
         break;
      case TileMapCollisionResponse::SPRITE_MOVING_LEFT:
         sprite->velocity.x = 0;
         sprite->placement.x = (tile_coordinate.x * 16) + 16;
         break;
      case TileMapCollisionResponse::SPRITE_MOVING_RIGHT:
         sprite->velocity.x = 0;
         sprite->placement.x = (tile_coordinate.x * 16) - sprite->placement.size.x;
         break;
      }
   }
   else
   {
      tile_map->set_tile(tile_coordinate.x, tile_coordinate.y, nullptr);
   }

   return true;
}


class Project : public Screen
{
public:
   ElementID sprite_root;
   TileMapFactory tile_map_factory;
   Placement2D camera;
   TileMap *current_tile_map;
   std::set<ALLEGRO_BITMAP *> solid_tiles;

   Project()
      : tile_map_factory()
      , sprite_root(nullptr)
      , current_tile_map(tile_map_factory.create_zoria_processed_map())
      , camera()
      , solid_tiles(tile_map_factory.get_zoria_solids())
   {
      (new Sprite(&sprite_root))->set("player_controlled");
      camera.size = -vec2d(1280/7, 720/7);
   }

   Sprite *player_controlled_sprite()
   {
      return static_cast<Sprite *>(sprite_root.find_first("player_controlled"));
   };

   std::vector<Sprite *> all_sprites_y_sorted()
   {
      std::vector<Sprite *> sprites = sprite_root.get_flat_list_of_descendants<Sprite>();
      std::sort(sprites.begin(), sprites.end(),[](const Sprite *a, const Sprite *b) {
            return a->placement.position.y < b->placement.position.y;
         });
      return sprites;
   };

   void update_scene()
   {
      std::vector<Sprite *> sprites = sprite_root.get_flat_list_of_descendants<Sprite>();
      for (auto &sprite : sprites) TileMapCollisionResponse{current_tile_map, sprite}.process(on_collide, &solid_tiles);

      Sprite *player_sprite = player_controlled_sprite();
      camera.position = -player_sprite->placement.position;
   }

   void render_scene()
   {
      ALLEGRO_BITMAP *bitmap = al_get_backbuffer(al_get_current_display());
      ALLEGRO_TRANSFORM trans;
      al_identity_transform(&trans);
      al_orthographic_transform(&trans, 0, 0, -1.0, al_get_bitmap_width(bitmap)/5, al_get_bitmap_height(bitmap)/5, 1.0);
      al_set_target_bitmap(bitmap);
      al_use_projection_transform(&trans);
      al_clear_to_color(color::hex("73ce26"));

      if (current_tile_map)
      {
         camera.start_transform();
         current_tile_map->draw();
         for (auto sprite : all_sprites_y_sorted()) sprite->draw();
         camera.restore_transform();
      }

      al_flip_display();
   }

   void process_event(ALLEGRO_EVENT &event) override
   {
      switch(event.type)
      {
      case ALLEGRO_EVENT_TIMER:
         update_scene();
         render_scene();
         break;
      case ALLEGRO_EVENT_KEY_DOWN:
         switch (event.keyboard.keycode)
         {
         case ALLEGRO_KEY_UP:
            player_controlled_sprite()->velocity.y = -2;
            break;
         case ALLEGRO_KEY_DOWN:
            player_controlled_sprite()->velocity.y = 2;
            break;
         case ALLEGRO_KEY_LEFT:
            player_controlled_sprite()->velocity.x = -2;
            break;
         case ALLEGRO_KEY_RIGHT:
            player_controlled_sprite()->velocity.x = 2;
            break;
         }
         break;
      case ALLEGRO_EVENT_KEY_UP:
         switch (event.keyboard.keycode)
         {
         case ALLEGRO_KEY_UP:
         case ALLEGRO_KEY_DOWN:
            player_controlled_sprite()->velocity.y = 0;
            break;
         case ALLEGRO_KEY_LEFT:
         case ALLEGRO_KEY_RIGHT:
            player_controlled_sprite()->velocity.x = 0;
            break;
         }
         break;
      case ALLEGRO_EVENT_KEY_CHAR:
         break;
      default:
         std::cout << "Unrecognized Event << " << std::endl;
         break;
      }
   }
};


int main(int argc, char **argv)
{
   Framework framework;
   Project project;
   framework.add_screen(&project);
   framework.loop();

   return 0;
}


