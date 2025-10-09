

#include <AllegroFlare/Physics/AABB3D.hpp>

#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Physics
{


AABB3D::AABB3D(AllegroFlare::Vec3D min, AllegroFlare::Vec3D max)
   : min(min)
   , max(max)
   , box_corners({})
   , box_color(ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0})
{
}


AABB3D::~AABB3D()
{
}


void AABB3D::set_min(AllegroFlare::Vec3D min)
{
   this->min = min;
}


void AABB3D::set_max(AllegroFlare::Vec3D max)
{
   this->max = max;
}


AllegroFlare::Vec3D AABB3D::get_min() const
{
   return min;
}


AllegroFlare::Vec3D AABB3D::get_max() const
{
   return max;
}


void AABB3D::expand(float amount)
{
   if (!((amount > 0.0f)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::AABB3D::expand]: error: guard \"(amount > 0.0f)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::AABB3D::expand]: error: guard \"(amount > 0.0f)\" not met");
   }
   min.x -= amount;
   min.y -= amount;
   min.z -= amount;
   max.x += amount;
   max.y += amount;
   max.z += amount;
   return;
}

AllegroFlare::Vec3D AABB3D::calculate_centroid()
{
   // TODO: Test this
   return (min + max) * 0.5f;
}

AllegroFlare::Vec3D AABB3D::calculate_size()
{
   // TODO: Test this
   return max - min;
}

bool AABB3D::collides(AllegroFlare::Physics::AABB3D* other, AllegroFlare::Vec3D self_offset, AllegroFlare::Vec3D other_offset)
{
   if (!(other))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::AABB3D::collides]: error: guard \"other\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::AABB3D::collides]: error: guard \"other\" not met");
   }
   // TODO: consider less assignment, add values directly into the conditional

   AllegroFlare::Vec3D a_min = min + self_offset;
   AllegroFlare::Vec3D a_max = max + self_offset;
   AllegroFlare::Vec3D b_min = other->min + other_offset;
   AllegroFlare::Vec3D b_max = other->max + other_offset;

   return (
      a_min.x <= b_max.x &&
      a_max.x >= b_min.x &&
      a_min.y <= b_max.y &&
      a_max.y >= b_min.y &&
      a_min.z <= b_max.z &&
      a_max.z >= b_min.z
   );
}

bool AABB3D::collides_with_point(AllegroFlare::Vec3D point, AllegroFlare::Vec3D self_offset, AllegroFlare::Vec3D other_offset)
{
   // TODO: Test this!!
   // TODO: consider less assignment, add values directly into the conditional

   AllegroFlare::Vec3D a_min = min + self_offset;
   AllegroFlare::Vec3D a_max = max + self_offset;
   point += other_offset;
   //AllegroFlare::Vec3D b_min = point + other_offset;
   //AllegroFlare::Vec3D b_max = point + other_offset;

   // TODO: Could simplify this calculation to not 
   return (
      a_min.x <= point.x &&
      a_max.x >= point.x &&
      a_min.y <= point.y &&
      a_max.y >= point.y &&
      a_min.z <= point.z &&
      a_max.z >= point.z
   );
}

void AABB3D::draw(AllegroFlare::Vec3D offset, ALLEGRO_COLOR color)
{
   box_color = color;
   // TODO: this function
   // SEE: This chat: https://chat.openai.com/chat/98d67e07-868f-4703-9675-49b9d0b48afd

   // TODO: Consider that this could be optimized
   std::vector<ALLEGRO_VERTEX> box_line_vertices = build_line_list_vertices(offset);
   std::vector<ALLEGRO_VERTEX> box_triangle_vertices = build_triangle_list_vertices_for_faces();
   al_draw_prim(&box_line_vertices[0], nullptr, nullptr, 0, box_line_vertices.size(), ALLEGRO_PRIM_LINE_LIST);
   al_draw_prim(&box_triangle_vertices[0], nullptr, nullptr, 0, box_triangle_vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   return;
}

void AABB3D::draw_dotted(AllegroFlare::Vec3D offset, ALLEGRO_COLOR color)
{
   box_color = color;
   // TODO: this function
   // SEE: This chat: https://chat.openai.com/chat/98d67e07-868f-4703-9675-49b9d0b48afd

   // TODO: Consider that this could be optimized
   std::vector<ALLEGRO_VERTEX> box_line_vertices = build_dotted_line_list_vertices(offset);
   std::vector<ALLEGRO_VERTEX> box_triangle_vertices = build_triangle_list_vertices_for_faces();
   al_draw_prim(&box_line_vertices[0], nullptr, nullptr, 0, box_line_vertices.size(), ALLEGRO_PRIM_LINE_LIST);
   al_draw_prim(&box_triangle_vertices[0], nullptr, nullptr, 0, box_triangle_vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   return;
}

void AABB3D::calculate_box_corners(AllegroFlare::Vec3D offset)
{
   using AllegroFlare::Vec3D;

   box_corners.clear();
   box_corners.resize(8);

   //float size_x = placement.size.x;
   //float size_y = placement.size.y;
   //float size_z = placement.size.z;
   //float pos_x = placement.position.x;
   //float pos_y = placement.position.y;
   //float pos_z = placement.position.z;
   float size_x = max.x - min.x;
   float size_y = max.y - min.y;
   float size_z = max.z - min.z;
   float pos_x = min.x + offset.x;
   float pos_y = min.y + offset.y;
   float pos_z = min.z + offset.z;
    
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

ALLEGRO_COLOR AABB3D::build_color(float opacity)
{
   ALLEGRO_COLOR color = box_color; //ALLEGRO_COLOR{1.0, 0.65, 1.0, 1.0};
   return ALLEGRO_COLOR{color.r*opacity, color.g*opacity, color.b*opacity, color.a*opacity};
}

std::vector<ALLEGRO_VERTEX> AABB3D::build_line_list_vertices(AllegroFlare::Vec3D offset)
{
   ALLEGRO_COLOR color = build_color(1.0);
   calculate_box_corners(offset);
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

std::vector<ALLEGRO_VERTEX> AABB3D::build_triangle_list_vertices_for_faces()
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

std::vector<ALLEGRO_VERTEX> AABB3D::build_dotted_line_list_vertices(AllegroFlare::Vec3D offset, float corner_dash_length, float dash_length, float gap_length)
{
   using AllegroFlare::Vec3D;

   ALLEGRO_COLOR color = build_color(1.0);
   calculate_box_corners(offset);
   if (box_corners.size() != 8) return {};

   std::vector<ALLEGRO_VERTEX> vertices;
   const float min_length_threshold = 0.0001f;
   const std::vector<std::pair<int, int>> edges = {
      {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Front face
      {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Back face
      {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Connecting edges
   };

   auto append_line = [&](const Vec3D& start, const Vec3D& end) {
      vertices.push_back(ALLEGRO_VERTEX{start.x, start.y, start.z, 0, 0, color});
      vertices.push_back(ALLEGRO_VERTEX{end.x, end.y, end.z, 0, 0, color});
   };

   for (const auto& edge : edges)
   {
      Vec3D p1 = box_corners[edge.first];
      Vec3D p2 = box_corners[edge.second];

      Vec3D edge_vector = p2 - p1;
      float edge_length = edge_vector.get_magnitude();

      if (edge_length < min_length_threshold) continue;

      // If the edge is too short for two corners, draw a single solid line
      if (edge_length <= (2 * corner_dash_length))
      {
         append_line(p1, p2);
         continue;
      }

      Vec3D direction = edge_vector.normalized();

      // 1. Draw solid corners
      Vec3D corner1_end = p1 + direction * corner_dash_length;
      append_line(p1, corner1_end);

      Vec3D corner2_start = p2 - direction * corner_dash_length;
      append_line(corner2_start, p2);

      // 2. Fill the middle with dashes
      float cycle_length = dash_length + gap_length;
      if (cycle_length < min_length_threshold) continue;

      Vec3D cursor = corner1_end;
      float remaining_length = edge_length - 2 * corner_dash_length;

      while (remaining_length > min_length_threshold)
      {
         float current_dash_len = std::fmin(dash_length, remaining_length);
         append_line(cursor, cursor + direction * current_dash_len);

         cursor += direction * cycle_length;
         remaining_length -= cycle_length;
      }
   }
   return vertices;
}


} // namespace Physics
} // namespace AllegroFlare


