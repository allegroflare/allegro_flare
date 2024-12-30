

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
   , dynamic_faces({})
   , loaded(false)
{
}


CollisionMesh::~CollisionMesh()
{
   // NOTE: No additional work is expected here. The "model" member is externally owned and is expected
   // to be destroyed in its own schedule.  It's only needed by this class before "load()" is called.  Other objects
   // may have names to dynamic faces that will no longer be valid - it's expected that these objects will all be
   // desroyed along with the colision mesh at the same time, however.
   return;
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

std::vector<AllegroFlare::Physics::CollisionMeshFace>& CollisionMesh::get_dynamic_faces_ref()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMesh::get_dynamic_faces_ref]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMesh::get_dynamic_faces_ref]: error: guard \"loaded\" not met");
   }
   return dynamic_faces.get_data();
}

void CollisionMesh::add_dynamic_face(std::string name, AllegroFlare::Physics::CollisionMeshFace face)
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMesh::add_dynamic_face]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMesh::add_dynamic_face]: error: guard \"loaded\" not met");
   }
   dynamic_faces.add(name, face);
   return;
}

void CollisionMesh::activate_dynamic_face(std::string name)
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMesh::activate_dynamic_face]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMesh::activate_dynamic_face]: error: guard \"loaded\" not met");
   }
   dynamic_faces.get(name).disabled = false;
   return;
}

void CollisionMesh::deactivate_dynamic_face(std::string name)
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMesh::deactivate_dynamic_face]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMesh::deactivate_dynamic_face]: error: guard \"loaded\" not met");
   }
   dynamic_faces.get(name).disabled = true;
   return;
}

bool CollisionMesh::is_dynamic_face_active(std::string name)
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMesh::is_dynamic_face_active]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMesh::is_dynamic_face_active]: error: guard \"loaded\" not met");
   }
   return !dynamic_faces.get(name).disabled;
}

bool CollisionMesh::dynamic_face_exists(std::string name)
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMesh::dynamic_face_exists]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMesh::dynamic_face_exists]: error: guard \"loaded\" not met");
   }
   return dynamic_faces.contains(name);
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

std::vector<std::string> CollisionMesh::load_dynamic_faces(std::string root_name, AllegroFlare::Model3D* model)
{
   if (!(model))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMesh::load_dynamic_faces]: error: guard \"model\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMesh::load_dynamic_faces]: error: guard \"model\" not met");
   }
   // TODO: Note that model can change after loading, consider addressing this design flaw.
   auto m = model; // TODO: update this variable in the code below

   // TODO: Test this load
   bool silence_cout = true;
   if (!silence_cout) std::cout << "+CollisionMesh()" << std::endl;
   if (!m)
   {
      std::cout << "  !*model is NULL" << std::endl;
      return {};
   }
   if (m->get_num_named_objects() == 0)
   {
      std::cout << "  !*Model contains no named objects" << std::endl;
      return {};
   }

   std::vector<std::string> result_face_names = {};
   //std::vector<AllegroFlare::Physics::CollisionMeshFace*> result_faces = {};
   int result_face_name_num = 0;

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

         std::stringstream this_face_name;
         this_face_name << root_name << "-f#" << result_face_name_num;
         result_face_name_num++;

         AllegroFlare::Physics::CollisionMeshFace &result_face = dynamic_faces.allocate(this_face_name.str());

         result_face = AllegroFlare::Physics::CollisionMeshFace::build(
            m->vertexes[index_list[i]],
            m->vertexes[index_list[i+1]],
            m->vertexes[index_list[i+2]],
            o,
            i/3,
            AllegroFlare::vec3d(
               m->vertexes[index_list[i]].nx,
               m->vertexes[index_list[i]].ny,
               m->vertexes[index_list[i]].nz
            )
         );

         result_face_names.push_back(this_face_name.str());
         //result_faces.push_back(&result_face);


         /*
         faces.push_back(AllegroFlare::Physics::CollisionMeshFace::build(
            m->vertexes[index_list[i]],
            m->vertexes[index_list[i+1]],
            m->vertexes[index_list[i+2]],
            o,
            i/3,
            AllegroFlare::vec3d(
               m->vertexes[index_list[i]].nx,
               m->vertexes[index_list[i]].ny,
               m->vertexes[index_list[i]].nz
            )
         ));
         */
      }

      //std::pair<key_type, value_type&> allocate(const key_type &key)
      //{
         //if (key_to_index.find(key) != key_to_index.end())
         //{
            //throw std::invalid_argument("Key already exists");
         //}

         //key_to_index[key] = data.size();
         //data.emplace_back(); // Default-construct the new value
         //return {key, data.back()};
      //}
   }

   loaded = true;

   return result_face_names; //, result_faces };
}

void CollisionMesh::draw(ALLEGRO_COLOR col, ALLEGRO_COLOR dynamic_faces_color_on, ALLEGRO_COLOR dynamic_faces_color_off)
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
   // TODO: Assemble vertexes into one structure and then draw a single prim

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

   for (auto &face : dynamic_faces.get_data())
   {
      // Draw the face (hopefully it's trangulated)
      AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL vtx[4];
      vtx[0] = _create_vtx(face.v0, face.disabled ? dynamic_faces_color_off : dynamic_faces_color_on);
      vtx[1] = _create_vtx(face.v1, face.disabled ? dynamic_faces_color_off : dynamic_faces_color_on);
      vtx[2] = _create_vtx(face.v2, face.disabled ? dynamic_faces_color_off : dynamic_faces_color_on);
      vtx[3] = _create_vtx(face.v0, face.disabled ? dynamic_faces_color_off : dynamic_faces_color_on);
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


