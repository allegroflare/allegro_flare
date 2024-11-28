

#include <AllegroFlare/Prototypes/MeshFPS/Entities/Base.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace MeshFPS
{
namespace Entities
{


Base::Base(std::string type, AllegroFlare::Model3D* model, ALLEGRO_BITMAP* texture, AllegroFlare::Placement3D placement, AllegroFlare::Placement3D velocity, AllegroFlare::Physics::AABB2D hit_box_2d, AllegroFlare::PlayerInputControllers::Base* player_input_controller)
   : AllegroFlare::SceneGraph::Entities::Base(AllegroFlare::Prototypes::MeshFPS::Entities::Base::TYPE)
   , type(type)
   , model(model)
   , texture(texture)
   , placement(placement)
   , velocity(velocity)
   , hit_box_2d(hit_box_2d)
   , player_input_controller(player_input_controller)
   , box_corners({})
   , active(true)
   , visible(true)
   , affected_by_environmental_forces(true)
   , collides_with_environment(true)
   , collides_with_player(false)
   , collides_with_enemies(false)
{
}


Base::~Base()
{
}


void Base::set_type(std::string type)
{
   this->type = type;
}


void Base::set_model(AllegroFlare::Model3D* model)
{
   this->model = model;
}


void Base::set_texture(ALLEGRO_BITMAP* texture)
{
   this->texture = texture;
}


void Base::set_placement(AllegroFlare::Placement3D placement)
{
   this->placement = placement;
}


void Base::set_velocity(AllegroFlare::Placement3D velocity)
{
   this->velocity = velocity;
}


void Base::set_hit_box_2d(AllegroFlare::Physics::AABB2D hit_box_2d)
{
   this->hit_box_2d = hit_box_2d;
}


void Base::set_player_input_controller(AllegroFlare::PlayerInputControllers::Base* player_input_controller)
{
   this->player_input_controller = player_input_controller;
}


std::string Base::get_type() const
{
   return type;
}


AllegroFlare::Model3D* Base::get_model() const
{
   return model;
}


ALLEGRO_BITMAP* Base::get_texture() const
{
   return texture;
}


AllegroFlare::Placement3D Base::get_placement() const
{
   return placement;
}


AllegroFlare::Placement3D Base::get_velocity() const
{
   return velocity;
}


AllegroFlare::Physics::AABB2D Base::get_hit_box_2d() const
{
   return hit_box_2d;
}


AllegroFlare::PlayerInputControllers::Base* Base::get_player_input_controller() const
{
   return player_input_controller;
}


AllegroFlare::Placement3D &Base::get_placement_ref()
{
   return placement;
}


AllegroFlare::Placement3D &Base::get_velocity_ref()
{
   return velocity;
}


AllegroFlare::Physics::AABB2D &Base::get_hit_box_2d_ref()
{
   return hit_box_2d;
}


AllegroFlare::PlayerInputControllers::Base* &Base::get_player_input_controller_ref()
{
   return player_input_controller;
}


bool Base::has_player_input_controller()
{
   return (player_input_controller != nullptr);
}

void Base::destroy()
{
   // TODO: Override in the derived class
   return;
}

void Base::on_time_step(double time_step, double time_now)
{
   // TODO: Override in the derived class
   return;
}

void Base::on_tile_map_collision_stepper_step(AllegroFlare::Physics::TileMapCollisionStepperStepResult* collision_step_result)
{
   return;
}

void Base::on_enter_player_bbox_collision(AllegroFlare::Prototypes::MeshFPS::Entities::Base* player_entity)
{
   // To use, tag the entity with "AllegroFlare::Prototypes::MeshFPS::EntityFlags::COLLIDES_WITH_PLAYER", then
   // override this method in the derived class
   return;
}

void Base::on_exit_player_bbox_collision(AllegroFlare::Prototypes::MeshFPS::Entities::Base* player_entity)
{
   // To use, tag the entity with "AllegroFlare::Prototypes::MeshFPS::EntityFlags::COLLIDES_WITH_PLAYER", then
   // override this method in the derived class
   return;
}

void Base::on_enter_player_position_collision(AllegroFlare::Prototypes::MeshFPS::Entities::Base* player_entity)
{
   // To use, tag the entity with "AllegroFlare::Prototypes::MeshFPS::EntityFlags::COLLIDES_WITH_PLAYER", then
   // override this method in the derived class
   return;
}

void Base::on_exit_player_position_collision(AllegroFlare::Prototypes::MeshFPS::Entities::Base* player_entity)
{
   // To use, tag the entity with "AllegroFlare::Prototypes::MeshFPS::EntityFlags::COLLIDES_WITH_PLAYER", then
   // override this method in the derived class
   return;
}

void Base::on_player_inspect_or_use()
{
   // Called on inspection if this entity has
   // AllegroFlare::Prototypes::MeshFPS::EntityFlags::PLAYER_CAN_INSPECT_OR_USE
   // TODO: Override in the base class
   return;
}

bool Base::collides(AllegroFlare::Prototypes::MeshFPS::Entities::Base* other)
{
   if (!(other))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Entities::Base::collides]: error: guard \"other\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Entities::Base::collides]: error: guard \"other\" not met");
   }
   // TODO: Test
   AllegroFlare::Vec3D &pos1 = placement.position;
   AllegroFlare::Vec3D &size1 = placement.size;
   AllegroFlare::Vec3D &pos2 = other->placement.position;
   AllegroFlare::Vec3D &size2 = other->placement.size;
   return !(pos1.x >= pos2.x + size2.x || pos1.x + size1.x <= pos2.x ||
            pos1.y >= pos2.y + size2.y || pos1.y + size1.y <= pos2.y ||
            pos1.z >= pos2.z + size2.z || pos1.z + size1.z <= pos2.z);
}

void Base::calculate_box_corners()
{
   using AllegroFlare::Vec3D;

   box_corners.clear();
   box_corners.resize(8);

   float size_x = placement.size.x;
   float size_y = placement.size.y;
   float size_z = placement.size.z;
   float pos_x = placement.position.x;
   float pos_y = placement.position.y;
   float pos_z = placement.position.z;
    
   // Half sizes
   // TODO: Factor out the hsizes
   float hx = size_x;
   float hy = size_y;
   float hz = size_z;

   // Front face corners
   //box_corners[0] = Vec3D(pos_x - hx, pos_y + hy, pos_z - hz);  // top-front-left
   //box_corners[1] = Vec3D(pos_x + hx, pos_y + hy, pos_z - hz);  // top-front-right
   //box_corners[2] = Vec3D(pos_x + hx, pos_y - hy, pos_z - hz);  // bottom-front-right
   //box_corners[3] = Vec3D(pos_x - hx, pos_y - hy, pos_z - hz);  // bottom-front-left

   // Back face corners
   //box_corners[4] = Vec3D(pos_x - hx, pos_y + hy, pos_z + hz);  // top-back-left
   //box_corners[5] = Vec3D(pos_x + hx, pos_y + hy, pos_z + hz);  // top-back-right
   //box_corners[6] = Vec3D(pos_x + hx, pos_y - hy, pos_z + hz);  // bottom-back-right
   //box_corners[7] = Vec3D(pos_x - hx, pos_y - hy, pos_z + hz);  // bottom-back-left

   // Front face corners
   box_corners[0] = Vec3D(pos_x, pos_y + hy, pos_z);  // top-front-left
   box_corners[1] = Vec3D(pos_x + hx, pos_y + hy, pos_z);  // top-front-right
   box_corners[2] = Vec3D(pos_x + hx, pos_y, pos_z);  // bottom-front-right
   box_corners[3] = Vec3D(pos_x, pos_y, pos_z);  // bottom-front-left

   // Back face corners
   box_corners[4] = Vec3D(pos_x, pos_y + hy, pos_z + hz);  // top-back-left
   box_corners[5] = Vec3D(pos_x + hx, pos_y + hy, pos_z + hz);  // top-back-right
   box_corners[6] = Vec3D(pos_x + hx, pos_y, pos_z + hz);  // bottom-back-right
   box_corners[7] = Vec3D(pos_x, pos_y, pos_z + hz);  // bottom-back-left

   return;
}

ALLEGRO_COLOR Base::build_color(float opacity)
{
   ALLEGRO_COLOR color = ALLEGRO_COLOR{1.0, 0.65, 1.0, 1.0};
   return ALLEGRO_COLOR{color.r*opacity, color.g*opacity, color.b*opacity, color.a*opacity};
}

std::vector<ALLEGRO_VERTEX> Base::build_line_list_vertices()
{
   ALLEGRO_COLOR color = build_color(1.0);
   calculate_box_corners();
   std::vector<ALLEGRO_VERTEX> vertices(24); // 12 lines, 2 vertices per line

   // Front face edges
   vertices[0].x = box_corners[0].x;
   vertices[0].y = box_corners[0].y;
   vertices[0].z = box_corners[0].z;
   vertices[0].color = color;

   vertices[1].x = box_corners[1].x;
   vertices[1].y = box_corners[1].y;
   vertices[1].z = box_corners[1].z;
   vertices[1].color = color;

   vertices[2].x = box_corners[1].x;
   vertices[2].y = box_corners[1].y;
   vertices[2].z = box_corners[1].z;
   vertices[2].color = color;

   vertices[3].x = box_corners[2].x;
   vertices[3].y = box_corners[2].y;
   vertices[3].z = box_corners[2].z;
   vertices[3].color = color;

   vertices[4].x = box_corners[2].x;
   vertices[4].y = box_corners[2].y;
   vertices[4].z = box_corners[2].z;
   vertices[4].color = color;

   vertices[5].x = box_corners[3].x;
   vertices[5].y = box_corners[3].y;
   vertices[5].z = box_corners[3].z;
   vertices[5].color = color;

   vertices[6].x = box_corners[3].x;
   vertices[6].y = box_corners[3].y;
   vertices[6].z = box_corners[3].z;
   vertices[6].color = color;

   vertices[7].x = box_corners[0].x;
   vertices[7].y = box_corners[0].y;
   vertices[7].z = box_corners[0].z;
   vertices[7].color = color;

   // Back face edges
   vertices[8].x = box_corners[4].x;
   vertices[8].y = box_corners[4].y;
   vertices[8].z = box_corners[4].z;
   vertices[8].color = color;

   vertices[9].x = box_corners[5].x;
   vertices[9].y = box_corners[5].y;
   vertices[9].z = box_corners[5].z;
   vertices[9].color = color;

   vertices[10].x = box_corners[5].x;
   vertices[10].y = box_corners[5].y;
   vertices[10].z = box_corners[5].z;
   vertices[10].color = color;

   vertices[11].x = box_corners[6].x;
   vertices[11].y = box_corners[6].y;
   vertices[11].z = box_corners[6].z;
   vertices[11].color = color;

   vertices[12].x = box_corners[6].x;
   vertices[12].y = box_corners[6].y;
   vertices[12].z = box_corners[6].z;
   vertices[12].color = color;

   vertices[13].x = box_corners[7].x;
   vertices[13].y = box_corners[7].y;
   vertices[13].z = box_corners[7].z;
   vertices[13].color = color;

   vertices[14].x = box_corners[7].x;
   vertices[14].y = box_corners[7].y;
   vertices[14].z = box_corners[7].z;
   vertices[14].color = color;

   vertices[15].x = box_corners[4].x;
   vertices[15].y = box_corners[4].y;
   vertices[15].z = box_corners[4].z;
   vertices[15].color = color;

   // Connecting edges
   vertices[16].x = box_corners[0].x;
   vertices[16].y = box_corners[0].y;
   vertices[16].z = box_corners[0].z;
   vertices[16].color = color;

   vertices[17].x = box_corners[4].x;
   vertices[17].y = box_corners[4].y;
   vertices[17].z = box_corners[4].z;
   vertices[17].color = color;

   vertices[18].x = box_corners[1].x;
   vertices[18].y = box_corners[1].y;
   vertices[18].z = box_corners[1].z;
   vertices[18].color = color;

   vertices[19].x = box_corners[5].x;
   vertices[19].y = box_corners[5].y;
   vertices[19].z = box_corners[5].z;
   vertices[19].color = color;

   vertices[20].x = box_corners[2].x;
   vertices[20].y = box_corners[2].y;
   vertices[20].z = box_corners[2].z;
   vertices[20].color = color;

   vertices[21].x = box_corners[6].x;
   vertices[21].y = box_corners[6].y;
   vertices[21].z = box_corners[6].z;
   vertices[21].color = color;

   vertices[22].x = box_corners[3].x;
   vertices[22].y = box_corners[3].y;
   vertices[22].z = box_corners[3].z;
   vertices[22].color = color;

   vertices[23].x = box_corners[7].x;
   vertices[23].y = box_corners[7].y;
   vertices[23].z = box_corners[7].z;
   vertices[23].color = color;

   return vertices;
}

std::vector<ALLEGRO_VERTEX> Base::build_triangle_list_vertices_for_faces()
{
   ALLEGRO_COLOR color = build_color(0.08);
   std::vector<ALLEGRO_VERTEX> vertices(36); // 12 triangles, 3 vertices per triangle

   // Front face (2 triangles)
   vertices[0] = ALLEGRO_VERTEX{box_corners[0].x, box_corners[0].y, box_corners[0].z, 0, 0, color};
   vertices[1] = ALLEGRO_VERTEX{box_corners[1].x, box_corners[1].y, box_corners[1].z, 0, 0, color};
   vertices[2] = ALLEGRO_VERTEX{box_corners[2].x, box_corners[2].y, box_corners[2].z, 0, 0, color};

   vertices[3] = ALLEGRO_VERTEX{box_corners[2].x, box_corners[2].y, box_corners[2].z, 0, 0, color};
   vertices[4] = ALLEGRO_VERTEX{box_corners[3].x, box_corners[3].y, box_corners[3].z, 0, 0, color};
   vertices[5] = ALLEGRO_VERTEX{box_corners[0].x, box_corners[0].y, box_corners[0].z, 0, 0, color};

   // Back face (2 triangles)
   vertices[6] = ALLEGRO_VERTEX{box_corners[5].x, box_corners[5].y, box_corners[5].z, 0, 0, color};
   vertices[7] = ALLEGRO_VERTEX{box_corners[4].x, box_corners[4].y, box_corners[4].z, 0, 0, color};
   vertices[8] = ALLEGRO_VERTEX{box_corners[7].x, box_corners[7].y, box_corners[7].z, 0, 0, color};

   vertices[9] = ALLEGRO_VERTEX{box_corners[7].x, box_corners[7].y, box_corners[7].z, 0, 0, color};
   vertices[10] = ALLEGRO_VERTEX{box_corners[6].x, box_corners[6].y, box_corners[6].z, 0, 0, color};
   vertices[11] = ALLEGRO_VERTEX{box_corners[5].x, box_corners[5].y, box_corners[5].z, 0, 0, color};

   // Left face (2 triangles)
   vertices[12] = ALLEGRO_VERTEX{box_corners[4].x, box_corners[4].y, box_corners[4].z, 0, 0, color};
   vertices[13] = ALLEGRO_VERTEX{box_corners[0].x, box_corners[0].y, box_corners[0].z, 0, 0, color};
   vertices[14] = ALLEGRO_VERTEX{box_corners[3].x, box_corners[3].y, box_corners[3].z, 0, 0, color};

   vertices[15] = ALLEGRO_VERTEX{box_corners[3].x, box_corners[3].y, box_corners[3].z, 0, 0, color};
   vertices[16] = ALLEGRO_VERTEX{box_corners[7].x, box_corners[7].y, box_corners[7].z, 0, 0, color};
   vertices[17] = ALLEGRO_VERTEX{box_corners[4].x, box_corners[4].y, box_corners[4].z, 0, 0, color};

   // Right face (2 triangles)
   vertices[18] = ALLEGRO_VERTEX{box_corners[1].x, box_corners[1].y, box_corners[1].z, 0, 0, color};
   vertices[19] = ALLEGRO_VERTEX{box_corners[5].x, box_corners[5].y, box_corners[5].z, 0, 0, color};
   vertices[20] = ALLEGRO_VERTEX{box_corners[6].x, box_corners[6].y, box_corners[6].z, 0, 0, color};

   vertices[21] = ALLEGRO_VERTEX{box_corners[6].x, box_corners[6].y, box_corners[6].z, 0, 0, color};
   vertices[22] = ALLEGRO_VERTEX{box_corners[2].x, box_corners[2].y, box_corners[2].z, 0, 0, color};
   vertices[23] = ALLEGRO_VERTEX{box_corners[1].x, box_corners[1].y, box_corners[1].z, 0, 0, color};

   // Top face (2 triangles)
   vertices[24] = ALLEGRO_VERTEX{box_corners[4].x, box_corners[4].y, box_corners[4].z, 0, 0, color};
   vertices[25] = ALLEGRO_VERTEX{box_corners[5].x, box_corners[5].y, box_corners[5].z, 0, 0, color};
   vertices[26] = ALLEGRO_VERTEX{box_corners[1].x, box_corners[1].y, box_corners[1].z, 0, 0, color};

   vertices[27] = ALLEGRO_VERTEX{box_corners[1].x, box_corners[1].y, box_corners[1].z, 0, 0, color};
   vertices[28] = ALLEGRO_VERTEX{box_corners[0].x, box_corners[0].y, box_corners[0].z, 0, 0, color};
   vertices[29] = ALLEGRO_VERTEX{box_corners[4].x, box_corners[4].y, box_corners[4].z, 0, 0, color};

   // Bottom face (2 triangles)
   vertices[30] = ALLEGRO_VERTEX{box_corners[3].x, box_corners[3].y, box_corners[3].z, 0, 0, color};
   vertices[31] = ALLEGRO_VERTEX{box_corners[2].x, box_corners[2].y, box_corners[2].z, 0, 0, color};
   vertices[32] = ALLEGRO_VERTEX{box_corners[6].x, box_corners[6].y, box_corners[6].z, 0, 0, color};

   vertices[33] = ALLEGRO_VERTEX{box_corners[6].x, box_corners[6].y, box_corners[6].z, 0, 0, color};
   vertices[34] = ALLEGRO_VERTEX{box_corners[7].x, box_corners[7].y, box_corners[7].z, 0, 0, color};
   vertices[35] = ALLEGRO_VERTEX{box_corners[3].x, box_corners[3].y, box_corners[3].z, 0, 0, color};

   return vertices;
}


} // namespace Entities
} // namespace MeshFPS
} // namespace Prototypes
} // namespace AllegroFlare


