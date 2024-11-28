

#include <AllegroFlare/Physics/CollisionMesh.hpp>

#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Physics
{


CollisionMesh::CollisionMesh()
   : model(nullptr)
   , faces({})
   , loaded(false)
{
}


CollisionMesh::~CollisionMesh()
{
}


void CollisionMesh::set_model(AllegroFlare::Model3D* model)
{
   this->model = model;
}


bool CollisionMesh::get_loaded() const
{
   return loaded;
}


int CollisionMesh::get_num_faces()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMesh::get_num_faces]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMesh::get_num_faces]: error: guard \"loaded\" not met");
   }
   return faces.size();
}

std::vector<AllegroFlare::Physics::CollisionMeshFace>& CollisionMesh::get_faces_ref()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMesh::get_faces_ref]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMesh::get_faces_ref]: error: guard \"loaded\" not met");
   }
   return faces;
}

void CollisionMesh::load()
{
   if (!(model))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMesh::load]: error: guard \"model\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMesh::load]: error: guard \"model\" not met");
   }
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMesh::load]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMesh::load]: error: guard \"(!loaded)\" not met");
   }
   // TODO: Note that model can change after loading, consider addressing this design flaw.
   auto m = model; // TODO: update this variable in the code below

   // TODO: Test this load
   bool silence_cout = true;
   if (!silence_cout) std::cout << "+CollisionMesh()" << std::endl;
   if (!m) { std::cout << "  !*model is NULL" << std::endl; return; }
   if (m->get_num_named_objects() == 0) { std::cout << "  !*Model contains no named objects" << std::endl; return; }


   for (int o=0; o<m->get_num_named_objects(); o++)
   {
      if (!silence_cout) std::cout << "   parsing named object " << o << std::endl;
      //std::cout << "      has " << m->named_objects[o].index_list.size() << " vertexes" << std::endl;
      if (!silence_cout) std::cout << ")))" << std::endl;
      m->named_objects[0];
      if (!silence_cout) std::cout << ")))" << std::endl;
      if (!silence_cout) std::cout << o << std::endl;
      int size = m->named_objects[0].index_list.size();

      if (!silence_cout) std::cout << ")))" << std::endl;
      if (!silence_cout) std::cout << "      has " << size << " vertexes" << std::endl;
      if (!silence_cout) std::cout << ")))" << std::endl;
      if (m->named_objects[o].index_list.size() % 3 != 0)
      {
         if (!silence_cout) std::cout << "[CollisionMesh()] error: model's named_objects[].index_list.size() is not a multiple of 3; cannot load." << std::endl;
         break;
      }
      std::vector<int> &index_list = m->named_objects[o].index_list;
      for (int i=0; i<index_list.size(); i+=3)
      {
   /*
         if (m->objects[o].face_index_lists[f].size() != 3)
         {
            std::cout << "  !object " << o << " face " << f << " has " << m->objects[o].face_index_lists.size() << " vertexes." << std::endl;
            continue;
         }
   */
         //m->objects[o].face_index_lists.size();

         faces.push_back(AllegroFlare::Physics::CollisionMeshFace::build(
            m->vertexes[index_list[i]],
            m->vertexes[index_list[i+1]],
            m->vertexes[index_list[i+2]],
            o,
            i/3,
            AllegroFlare::vec3d(m->vertexes[index_list[i]].nx, m->vertexes[index_list[i]].ny, m->vertexes[index_list[i]].nz)
            // m->m->objects[o].get_face_normal(f)
            ));
      }
   }

   loaded = true;

   return;
}

void CollisionMesh::draw(ALLEGRO_COLOR col)
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMesh::draw]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMesh::draw]: error: guard \"loaded\" not met");
   }
   // TODO: Validate somewhere that face is triangulated
   // TODO: Modify render states to render without depth check (and restore after this call)
   // TODO: Draw faces as semitransparent, then draw lines, see if additive is an option
   // TODO: Draw centroids and normals
   // TODO: Move this to a vertex buffer and consolidate all the vertices/faces into triangles

   for (auto &face : faces)
   {
      // Draw the face (hopefully it's trangulated)
      AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL vtx[4];
      vtx[0] = _create_vtx(face.v0, col);
      vtx[1] = _create_vtx(face.v1, col);
      vtx[2] = _create_vtx(face.v2, col);
      vtx[3] = _create_vtx(face.v0, col);
      //al_draw_prim(vtx, NULL, NULL, 0, 3, ALLEGRO_PRIM_TRIANGLE_FAN);
      //al_draw_prim(vtx, NULL, NULL, 0, 3, ALLEGRO_PRIM_LINE_LIST);
      //al_draw_prim(vtx, model->vertex_declaration, NULL, 0, 3, ALLEGRO_PRIM_LINE_LIST);
      al_draw_prim(vtx, model->vertex_declaration, NULL, 0, 4, ALLEGRO_PRIM_LINE_STRIP);

      // TODO: Draw centroids and normals
      //draw_crosshair(face.centroid, color::dodgerblue, 0.5);
      //draw_3d_line(face.centroid, face.centroid+mesh.face.normal*0.75, color::aliceblue);
   }
}

AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL CollisionMesh::_create_vtx(AllegroFlare::Vec3D vec, ALLEGRO_COLOR col)
{
   //static AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL _create_vtx(AllegroFlare::vec3d vec, ALLEGRO_COLOR col)
   //{
      AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL ret_val;
      ret_val.x = vec.x;
      ret_val.y = vec.y;
      ret_val.z = vec.z;
      ret_val.u = 0;
      ret_val.v = 0;
      ret_val.nx = 0;
      ret_val.ny = 1;
      ret_val.nz = 0;
      ret_val.color = col;
      //return build_vertex(vec.x, vec.y, vec.z, col, 0, 0);
      return ret_val;
   //}
}


} // namespace Physics
} // namespace AllegroFlare


