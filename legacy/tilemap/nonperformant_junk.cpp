

//#include <tilemap/tile_map_collision_response.hpp>


//TileMapCollisionResponse::TileMapCollisionResponse(TileMap *tile_map, Sprite *sprite)
   //: tile_map(tile_map)
   //, sprite(sprite)
//{
//}


//TileMapCollisionResponse::~TileMapCollisionResponse()
//{
//}


//void test_vertical_map_collisions()
//{
   //bool char_collides_next = false;
   //bool char_collides_now = false;

   //if (velocity_y > 0.0f) // falling
   //{
      //if (block_type_at((int)(x), (int)(y+velocity_y)+1) == BLOCK_DESTRUCTABLE) return;
      //if (is_platform_block(block_type_at((int)(x), (int)(y+velocity_y)+1)))
      //{
         //char_collides_next = true;
      //}
      //if (is_platform_block(block_type_at((int)(x), (int)y)))
      //{
         //char_collides_now = true;
      //}
   //}
   //if ((!char_collides_now) && (char_collides_next))
   //{
      //velocity_y *= -1.0f; // reflect
      //velocity_y *= 0.4; // dampen
      //y = block_top_edge(((int)(y+velocity_y+8)+1)/16) - 1;
      //if (velocity_y < -1.0f)
      //{
         //// play a item bounce on wall sound here
         ////play_ball_bounce_sound(x - camera.x);
      //}
   //}
   //else if (velocity_y < 0.0f) // jumping
   //{
      //if (block_type_at((int)(x), (int)(y+velocity_y)-1) == BLOCK_DESTRUCTABLE) return;
      //if (is_ceiling_block(block_type_at((int)(x), (int)(y+velocity_y)-1)))
      //{
         //velocity_y *= -1.0f; // reflect
         //velocity_y *= 0.4; // dampen
         //y = block_bottom_edge(((int)(y+velocity_y-8)-1)/16) + 1;
         //// play a item bounce on wall sound here
         //// play_ball_bounce_sound(x - camera.x);
      //}
   //}
//}



//void test_horizontal_map_collisions()
//{
   //bool char_collides_next = false;
   //bool char_collides_now = false;

   //if (velocity_x > 0.0f) // falling
   //{
      //if (block_type_at((int)(x+velocity_x)+1, (int)(y)) == BLOCK_DESTRUCTABLE) return;
      //if (is_left_wall_block(block_type_at((int)(x+velocity_x)+1, (int)(y))))
      //{
         //char_collides_next = true;
      //}
      //if (is_left_wall_block(block_type_at((int)(x), (int)y)))
      //{
         //char_collides_now = true;
      //}
   //}
   //if ((!char_collides_now) && (char_collides_next))
   //{
      //velocity_x *= -1.0f;
      //velocity_y *= 0.4f;
      //x = block_left_edge(((int)(x+velocity_x+8)+1)/16) - 1;
      //// play a item bounce on wall sound here
      ////play_ball_bounce_sound(x - camera.x);
   //}

   //else if (velocity_x < 0.0f) // jumping
   //{
      //if (block_type_at((int)(x+velocity_x)-1, (int)(y)) == BLOCK_DESTRUCTABLE) return;
      //if (is_right_wall_block(block_type_at((int)(x+velocity_x)-1, (int)(y))))
      //{
         //velocity_x *= -1.0f;
         //velocity_x *= 0.4f;
         //x = block_right_edge(((int)(x+velocity_x-8)-1)/16) + 1;
         //// play a item bounce on wall sound here
         ////play_ball_bounce_sound(x - camera.x);
      //}
   //}
//}



   //void update_with_physics()
   //{
      //if (alive)
      //{
         //velocity_x *= (1.0 - drag);
         //velocity_y *= (1.0 - drag);
         ////if (velocity_x > 0) velocity_x -= 0.03f;
         ////else if (velocity_x < 0) velocity_x += 0.03f;

         //velocity_y += GRAVITY;
         //if (velocity_y > TERMINAL_VELOCITY) velocity_y = TERMINAL_VELOCITY;

         //test_vertical_map_collisions();
         //y += velocity_y;
         //test_horizontal_map_collisions();
         //x += velocity_x;

         //float min_motion_range = 0.05f;
         //if ((fabs(velocity_x) < min_motion_range) && (fabs(velocity_y) < min_motion_range))
         //{
            //velocity_x = 0;
            //velocity_y = 0;
         //}
      //}

      //if (outside_screen()) alive = false;
   //}




///////////////



//void update_enemy_position(EnemyBase *enemy_ptr)
//{
   //if (!enemy_ptr) return;
   ////	EnemyBase &enemy = *enemy_ptr;

   //// plug our values into a collision object
   //TileAndObjectCollision element;

   //element.x = enemy_ptr->x;
   //element.y = enemy_ptr->y;
   //element.w = enemy_ptr->w;
   //element.h = enemy_ptr->h;
   //element.velocity_x = enemy_ptr->velocity_x;
   //element.velocity_y = enemy_ptr->velocity_y;






   //float timestep = GAMEPLAY_FRAME_DURATION_PER_SEC;
   //std::vector<int2> collided_tiles;

   //// vertical tests
   ////	TileAndObjectCollision::test_enemy_map_collision_vertical(enemy_ptr, timestep);
   //collided_tiles = TileAndObjectCollision::test_tile_map_collision_axis(TileAndObjectCollision::Y_AXIS, element, timestep);
   //bool collides_on_ground = false;
   //for (int2 &t : collided_tiles)
   //{
      //if (element.velocity_y < 0.0)
      //{
         //if (is_bottom_edge_block(block_type_at_tile_coord(t.x, t.y)))
         //{
            //element.velocity_y = 0;
            //element.set_top(block_bottom_edge(t.y) + 0.0001);
         //}
      //}
      //else if (element.velocity_y > 0.0)
      //{
         //if (is_top_edge_block(block_type_at_tile_coord(t.x, t.y)))
         //{
            //element.velocity_y = 0;
            //element.set_bottom(block_top_edge(t.y) - 0.0001);
            //collides_on_ground = true;
         //}
      //}
   //}
   //element.y += element.velocity_y * timestep;

   //// horizontal tests
   //collided_tiles = TileAndObjectCollision::test_tile_map_collision_axis(TileAndObjectCollision::X_AXIS, element, timestep);
   ////TileAndObjectCollision::test_enemy_map_collision_horizontal(enemy_ptr, timestep);
   ////test_if_enemy_will_fall_off(enemy_ptr); // dont' avoid walking off clifs
   //bool collided_at_wall = false;
   //for (int2 &t : collided_tiles)
   //{
      //if (element.velocity_x < 0.0)
      //{
         //if (is_right_edge_block(block_type_at_tile_coord(t.x, t.y)))
         //{
            //element.velocity_x = 0;
            //element.set_left(block_right_edge(t.x) + 0.0001);
            //collided_at_wall = true;
         //}
      //}
      //else if (element.velocity_x > 0.0)
      //{
         //if (is_left_edge_block(block_type_at_tile_coord(t.x, t.y)))
         //{
            //element.velocity_x = 0;
            //element.set_right(block_left_edge(t.x) - 0.0001);
            //collided_at_wall = true;
         //}
      //}
   //}
   //element.x += element.velocity_x * timestep;



   //// plug it back into the original enemy

   //enemy_ptr->x = element.x;
   //enemy_ptr->y = element.y;
   //enemy_ptr->w = element.w;
   //enemy_ptr->h = element.h;
   //enemy_ptr->velocity_x = element.velocity_x;
   //enemy_ptr->velocity_y = element.velocity_y;

   ////std::cout << enemy_ptr->velocity_y << std::endl;

   //if (collides_on_ground)
   //{
      //enemy_ptr->on_ground = true;
   //}
   //if (collided_at_wall)
   //{
      ////enemy_ptr->turn_around();
      //enemy_ptr->facing_left = !enemy_ptr->facing_left;
      //enemy_ptr->bitmap_flip_h = !enemy_ptr->bitmap_flip_h;

      //if (enemy_ptr->facing_left) enemy_ptr->velocity_x = -0.5;
      //else enemy_ptr->velocity_x = 0.5;
      ////if (enemy_ptr->facing_left) enemy_ptr->velocity_x = -enemy_ptr->default_velocity;
      ////else enemy_ptr->velocity_x = enemy_ptr->default_velocity;
   //}


//}




/////////////////




//#include <algorithm>

//bool is_top_edge_block(int type);
//bool is_bottom_edge_block(int type);
//bool is_left_edge_block(int type);
//bool is_right_edge_block(int type);


//class TileAndObjectCollision
//{
//public:
   //float x;
   //float y;
   //float w;
   //float h;
   //float velocity_x;
   //float velocity_y;

   //bool collides(const TileAndObjectCollision &other)
   //{
      //if (other.x > (x+w)) return false;
      //if (other.y > (y+h)) return false;
      //if (other.x+other.w < x) return false;
      //if (other.y+other.h < y) return false;
      //return true;
   //}
   //float get_left() { return x; }
   //float get_right() { return x+w; }
   //float get_bottom() { return y+h; }
   //float get_top() { return y; }

   //void set_left(float x) { this->x = x; }
   //void set_right(float x) { this->x = x - w; }
   //void set_bottom(float y) { this->y = y - h; }
   //void set_top(float y) { this->y = y; }

   //static bool on_enter_new_tiles_moving_downward(TileAndObjectCollision &obj, std::vector<int2> tiles)
   //{
      //bool collided_at_surface_edge = false;
      //for (int2 &t : tiles)
      //{
         //if (is_top_edge_block(block_type_at_tile_coord(t.x, t.y)))
         //{
            //obj.velocity_y = 0;
            //obj.set_bottom(block_top_edge(t.y) - 0.0001);
            //collided_at_surface_edge = true;
         //}
      //}
      //return collided_at_surface_edge;
   //}

   //static bool on_enter_new_tiles_moving_upward(TileAndObjectCollision &obj, std::vector<int2> tiles)
   //{
      //bool collided_at_surface_edge = false;
      //for (int2 &t : tiles)
      //{
         //if (is_bottom_edge_block(block_type_at_tile_coord(t.x, t.y)))
         //{
            //obj.velocity_y = 0;
            //obj.set_top(block_bottom_edge(t.y) + 0.0001);
            //collided_at_surface_edge = true;
         //}
      //}
      //return collided_at_surface_edge;
   //}

   //static bool on_enter_new_tiles_moving_right(TileAndObjectCollision &obj, std::vector<int2> tiles)
   //{
      //bool collided_at_surface_edge = false;
      //for (int2 &t : tiles)
      //{
         //if (is_left_edge_block(block_type_at_tile_coord(t.x, t.y)))
         //{
            //obj.velocity_x = 0;
            //obj.set_right(block_left_edge(t.x) - 0.0001);
            //collided_at_surface_edge = true;
         //}
      //}
      //return collided_at_surface_edge;
   //}

   //static bool on_enter_new_tiles_moving_left(TileAndObjectCollision &obj, std::vector<int2> tiles)
   //{
      //bool collided_at_surface_edge = false;
      //for (int2 &t : tiles)
      //{
         //if (is_right_edge_block(block_type_at_tile_coord(t.x, t.y)))
         //{
            //obj.velocity_x = 0;
            //obj.set_left(block_right_edge(t.x) + 0.0001);
            //collided_at_surface_edge = true;
         //}
      //}
      //return collided_at_surface_edge;
   //}


//public:

   //enum AXIS
   //{
      //X_AXIS,
      //Y_AXIS,
   //};

   //static std::vector<int2> test_tile_map_collision_axis(AXIS axis, TileAndObjectCollision element, float timestep = GAMEPLAY_FRAME_DURATION_PER_SEC)
   //{
      //float velocity_amt = element.velocity_x * timestep;
      //float now_x = element.x;
      //float next_x = element.x + velocity_amt;
      //float next_y = element.y;
      //float size_of_body = element.w;
      //float length_of_edge = element.h;
      //float cursor_step_amt = 16;






      //if (axis == Y_AXIS)
      //{
         //velocity_amt = element.velocity_y * timestep;
         //now_x = element.y;
         //next_x = element.y + velocity_amt;
         //next_y = element.x;
         //size_of_body = element.h;
         //length_of_edge = element.w;
      //}







      //// if moving right, test along the right edge
      //if (velocity_amt > 0.0) // moving right
      //{
         //now_x += size_of_body;
         //next_x += size_of_body;
      //}

      //int column_x_now = now_x / 16;
      //int column_x_next = next_x / 16;
      //std::vector<int2> collided_tiles;

      //if (column_x_now != column_x_next)
      //{

         ////std::cout << "PASS" << std::endl;
         //// the player has passed from one row of tiles into the next
         //// collect the tiles along the "next" left edge
         //int num_passes = ceil(length_of_edge / 16);
         //float step_cursor = 0;

         //collided_tiles.reserve(num_passes);
         //for (unsigned i=0; i<num_passes; i++)
         //{
            //if (i==(num_passes-1)) step_cursor = length_of_edge;

            //if (axis == X_AXIS) collided_tiles.push_back(world_to_tile_coordinates(next_x, next_y + step_cursor));
            //else if (axis == Y_AXIS) collided_tiles.push_back(world_to_tile_coordinates(next_y + step_cursor, next_x));

            //step_cursor += cursor_step_amt;
         //}
      //}

      //return collided_tiles;
   //}
   //[>
      //static std::vector<int2> test_tile_map_collision_horizontal(TileAndObjectCollision element, float timestep = GAMEPLAY_FRAME_DURATION_PER_SEC)
      //{
      //float now_x = element.x;
      //float next_x = element.x + element.velocity_x * timestep;

   //// if moving right, test along the right edge
   //if (element.velocity > 0.0) // moving right
   //{
   //now_x += element.w;
   //next_x += element.w;
   //}

   //int column_x_now = now_x / 16;
   //int column_x_next = next_x / 16;

   //if (column_x_now != column_x_next)
   //{
   //// the player has passed from one row of tiles into the next
   //// collect the tiles along the "next" left edge
   //int num_passes = ceil(element.h / 16);
   //float step_cursor = 0;

   //collided_tiles.reserve(num_passes);
   //for (unsigned i=0; i<num_passes; i++)
   //{
   //if (i==num_passes) step_cursor = element.h;
   //collided_tiles.push_back(world_to_tile_coordinates(next_x + step_cursor, next_y));
   //step_cursor += 16;
   //}
   //}

   //return collided_tiles;
   //}
   //*/

   //// new map collision detections
   //static void test_enemy_map_collision_vertical(EnemyBase *enemy_ptr, float timestep = GAMEPLAY_FRAME_DURATION_PER_SEC)
   //{
      //if (enemy_ptr == NULL) return;

      //TileAndObjectCollision element;

      //element.x = enemy_ptr->x;
      //element.y = enemy_ptr->y;
      //element.w = enemy_ptr->w;
      //element.h = enemy_ptr->h;
      //element.velocity_x = enemy_ptr->velocity_x;
      //element.velocity_y = enemy_ptr->velocity_y;

      //float step_velocity_y = element.velocity_y*timestep;
      //bool lands_on_ground = false;
      ////float step_velocity_y = enemy_ptr.velocity_y*timestep;
      ////float step_velocity_y = enemy_ptr.velocity_y*timestep;


      //if (step_velocity_y > 0.0f) // falling
      //{
         //float dur = 0; // eeks, potential floating point errors (I am trusting in you computer to not fail me...)
         //std::vector<int2> collided_tiles;

         //float now_x = element.x;
         //float now_y = element.y + element.h; // + 1 puts it on the bottom edge
         //float next_x = now_x;
         //float next_y = now_y + step_velocity_y;

         //int num_passes = ceil(element.w / 16.0);

         //for (int i=0; i<=num_passes; i++)
         //{
            //bool char_collides_next = false;
            //bool char_collides_now = false;

            //if (is_top_edge_block(block_type_at(now_x + dur, now_y)))
               //char_collides_now = true;

            //if (is_top_edge_block(block_type_at(next_x + dur, next_y)))
               //char_collides_next = true;

            //if (!char_collides_now && char_collides_next)
            //{
               //// the player has just "entered" into this tile
               //int2 collided_tile = world_to_tile_coordinates(next_x + dur, next_y);
               //collided_tiles.push_back(collided_tile);
            //}

            //dur += 16;
            //dur = std::min(dur, element.w);
         //};

         //// calculate what to do if there was a new collision
         ////enemy.on_bottom_collides_with_ground_tiles(collided_tiles);
         //lands_on_ground = on_enter_new_tiles_moving_downward(element, collided_tiles);

      //}
      //else if (step_velocity_y < 0.0f) // jumping
      //{
         ////int dur=-1;
         //float dur = 0.0;
         //std::vector<int2> collided_tiles;

         //float now_x = element.x;
         //float now_y = element.y; // + 1 puts it on the bottom edge
         //float next_x = now_x;
         //float next_y = now_y + step_velocity_y;

         //int num_passes = ceil(element.w / 16.0);

         //for (int i=0; i<=num_passes; i++)
         //{
            //if (is_bottom_edge_block(block_type_at(next_x + dur, next_y)))
            //{
               //int2 collided_tile = world_to_tile_coordinates(next_x + dur, next_y);
               //collided_tiles.push_back(collided_tile);
            //}

            //dur += 16;
            //dur = std::min(dur, element.w);
         //}

         ////if (collides)
         //on_enter_new_tiles_moving_upward(element, collided_tiles);
      //}


      //[>
      //// here just do the assignment for now,
      //// in theory, this function will eventually act directly on the object
      //*/
      //enemy_ptr->x = element.x;
      //enemy_ptr->y = element.y;
      //enemy_ptr->w = element.w;
      //enemy_ptr->h = element.h;
      //enemy_ptr->velocity_x = element.velocity_x;
      //enemy_ptr->velocity_y = element.velocity_y;
      //if (lands_on_ground && !enemy_ptr->on_ground) enemy_ptr->on_ground = true;
   //}




   //// new map collision detections
   //static void test_enemy_map_collision_horizontal(EnemyBase *enemy_ptr, float timestep)
   //{
      //if (enemy_ptr == NULL) return;

      //bool collided_at_wall = false;

      //TileAndObjectCollision element;

      //element.x = enemy_ptr->x;
      //element.y = enemy_ptr->y;
      //element.w = enemy_ptr->w;
      //element.h = enemy_ptr->h;
      //element.velocity_x = enemy_ptr->velocity_x;
      //element.velocity_y = enemy_ptr->velocity_y;

      //float step_velocity_x = element.velocity_x*timestep;




      //if (step_velocity_x > 0.0f) // moving right
      //{
         //float dur = 0; // eeks, potential floating point errors (I am trusting in you computer to not fail me...)
         //std::vector<int2> collided_tiles;

         //float now_x = element.x + element.w;
         //float now_y = element.y; // + 1 puts it on the bottom edge
         //float next_x = now_x + step_velocity_x;
         //float next_y = now_y;

         //int num_passes = ceil(element.h / 16.0);

         //for (int i=0; i<=num_passes; i++)
         //{
            //bool char_collides_next = false;
            //bool char_collides_now = false;

            //if (is_left_edge_block(block_type_at(now_x, now_y + dur)))
               //char_collides_now = true;

            //if (is_left_edge_block(block_type_at(next_x, next_y + dur)))
               //char_collides_next = true;

            //if (!char_collides_now && char_collides_next)
            //{
               //// the player has just "entered" into this tile
               //int2 collided_tile = world_to_tile_coordinates(next_x, next_y + dur);
               //collided_tiles.push_back(collided_tile);
            //}

            //dur += 16;
            //dur = std::min(dur, element.h);
         //};

         //// calculate what to do if there was a new collision
         ////enemy.on_bottom_collides_with_ground_tiles(collided_tiles);
         ////lands_on_ground = on_enter_new_tiles_moving_downward(element, collided_tiles);
         //collided_at_wall = on_enter_new_tiles_moving_right(element, collided_tiles);

      //}
      //else if (step_velocity_x < 0.0f) // moving left
      //{
         ////int dur=-1;
         //float dur = 0.0;
         //std::vector<int2> collided_tiles;

         //float now_x = element.x;
         //float now_y = element.y;
         //float next_x = now_x + step_velocity_x;
         //float next_y = now_y;

         //int num_passes = ceil(element.h / 16.0);

         //for (int i=0; i<=num_passes; i++)
         //{
            //if (is_right_edge_block(block_type_at(next_x, next_y + dur)))
            //{
               //int2 collided_tile = world_to_tile_coordinates(next_x, next_y + dur);
               //collided_tiles.push_back(collided_tile);
            //}

            //dur += 16;
            //dur = std::min(dur, element.h);
         //}

         ////if (collides)
         //collided_at_wall = (on_enter_new_tiles_moving_left(element, collided_tiles) || collided_at_wall);
         ////if (collided) enemy.turn_around();
      //}


      //[>
      //// here just do the assignment for now,
      //// in theory, this function will eventually act directly on the object
      //*/
      //enemy_ptr->x = element.x;
      //enemy_ptr->y = element.y;
      //enemy_ptr->w = element.w;
      //enemy_ptr->h = element.h;
      //enemy_ptr->velocity_x = element.velocity_x;
      //enemy_ptr->velocity_y = element.velocity_y;
      //if (collided_at_wall)
      //{
         ////enemy_ptr->turn_around();
         //enemy_ptr->facing_left = !enemy_ptr->facing_left;
         //enemy_ptr->bitmap_flip_h = !enemy_ptr->bitmap_flip_h;

         //if (enemy_ptr->facing_left) enemy_ptr->velocity_x = -0.5;
         //else enemy_ptr->velocity_x = 0.5;
         ////if (enemy_ptr->facing_left) enemy_ptr->velocity_x = -enemy_ptr->default_velocity;
         ////else enemy_ptr->velocity_x = enemy_ptr->default_velocity;
      //}
   //}
//};




//// new map collision detections
//void test_enemy_map_collision_vertical(EnemyBase *enemy_ptr, float timestep = GAMEPLAY_FRAME_DURATION_PER_SEC)
//{
   //if (enemy_ptr == NULL) return;

   //EnemyBase &enemy = *enemy_ptr;
   //float element_x = enemy.x;
   //float element_y = enemy.y;
   //float element_w = enemy.w;
   //float element_h = enemy.h;
   //float step_velocity_y = enemy.velocity_y*timestep;


   //if (step_velocity_y > 0.0f) // falling
   //{
      //bool char_collides_next = false;
      //bool char_collides_now = false;
      //int dur=-1;
      //while(dur<(int)element_w+1)
      //{
         //if (is_platform_block(block_type_at((int)(element_x)+dur, (int)(element_y+step_velocity_y)+(int)element_h+1)))
         //{
            //char_collides_next = true;
         //}
         //if (is_platform_block(block_type_at((int)(element_x)+dur, (int)(element_y)+(int)element_h)))
         //{
            //char_collides_now = true;
         //}
         //dur++;
      //}
      //if ((!char_collides_now) && (char_collides_next))
      //{
         //enemy.velocity_y = 0.0f;
         //enemy.y = block_top_edge(((int)(element_y+step_velocity_y+8)+(int)element_h+1)/16) - (int)(element_h) - 1;
         ////if (pic == jump_pic) pic = gimp_pic;
         //enemy.on_ground = true;
         //enemy.on_bottom_collides_with_ground_tiles({int2(0, 0)} [> do this part today <]);
      //}
   //}
   //else if (step_velocity_y < 0.0f) // jumping
   //{
      //int dur=-1;
      //bool collides = false;
      //while(dur<(int)element_w+1)
      //{
         //if (is_ceiling_block(block_type_at((int)(element_x)+dur, (int)(element_y+step_velocity_y)-1)))
         //{
            //dur = (int)element_w+1;
            //enemy.velocity_y = 0.0f;
            //enemy.y = block_bottom_edge(((int)(element_y+step_velocity_y-8)-1)/16) + 1;
            //collides = true;
         //}
         //else dur++;
      //}

      //if (collides) enemy.on_collides_with_ceiling_tile(0, 0 [> do this part today <]);
   //}
//}


//// new map collision detections
//void test_enemy_map_collision_horizontal(EnemyBase *enemy_ptr, float timestep)
//{
   //if (enemy_ptr == NULL) return;

   //EnemyBase &enemy = *enemy_ptr;
   //float element_x = enemy.x;
   //float element_y = enemy.y;
   //float element_w = enemy.w;
   //float element_h = enemy.h;
   //float step_velocity_x = enemy.velocity_x * GAMEPLAY_FRAME_DURATION_PER_SEC;


   //if (step_velocity_x > 0.0f)
   //{
      //bool collided = false;
      //int y_step_cursor=0;


      //while(y_step_cursor<(int)element_h+1)
      //{
         //if (is_right_wall_block(block_type_at((int)(element_x+step_velocity_x)+(int)element_w+1, (int)(element_y)+y_step_cursor)))
         //{
            //y_step_cursor = (int)element_h+1;
            //enemy.velocity_x = 0.0f;
            //enemy.x = block_left_edge(((int)(element_x+step_velocity_x+8)+(int)element_w+1)/16) - ((int)element_w) - 1;
            //collided = true;
         //}
         //else y_step_cursor+=16;
         //if (y_step_cursor > (int)element_h)
         //{
            //if (is_right_wall_block(block_type_at((int)(element_x+step_velocity_x)+(int)element_w+1, (int)(element_y)+(int)element_h)))
            //{
               //y_step_cursor = (int)element_h+1;
               //enemy.velocity_x = 0.0f;
               //enemy.x = block_left_edge(((int)(element_x+step_velocity_x+8)+(int)element_w+1)/16) - ((int)element_w) - 1;
               //collided = true;
            //}
         //}
      //}

      //if (collided) enemy.on_collides_with_wall_tile(0, 0 [> do this part today <]);
   //}
   //else if (step_velocity_x < 0.0f)
   //{
      //bool collided = false;
      //int dur=0;
      //while(dur<(int)element_h+1)
      //{
         //if (is_left_wall_block(block_type_at((int)(element_x+step_velocity_x)-1, (int)(element_y)+dur)))
         //{
            //dur = (int)element_h+1;
            //enemy.velocity_x = 0.0f;
            //enemy.x = block_right_edge(((int)(element_x+step_velocity_x-8)-1)/16) + 1;
            //collided = true;
            ////turn_around();
         //}
         //else dur+=16;
         //if (dur > (int)element_h)
         //{
            //if (is_left_wall_block(block_type_at((int)(element_x+step_velocity_x)-1, (int)(element_y)+(int)element_h)))
            //{
               //dur = (int)element_h+1;
               //enemy.velocity_x = 0.0f;
               //enemy.x = block_right_edge(((int)(element_x+step_velocity_x-8)-1)/16) + 1;
               //collided = true;
               ////turn_around();
            //}
         //}
      //}

      //if (collided) enemy.on_collides_with_wall_tile(0, 0 [> do this part today <]);
   //}
//}







//void process()
//{
//}



