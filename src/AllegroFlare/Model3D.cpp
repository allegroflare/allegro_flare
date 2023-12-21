


#include <AllegroFlare/Model3D.hpp>

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <AllegroFlare/Model3DObjLoader.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <cstdio>
#include <iostream>
#include <sstream>




namespace AllegroFlare
{



Model3D::Model3D()
   : initialized(false)
   , vertex_declaration(nullptr)
   , vertices()
   , vertex_buffer(nullptr)
   , texture(nullptr)
   , named_objects()
{
   //build_vertex_declaration();
}




Model3D::~Model3D()
{
   if (vertex_declaration) al_destroy_vertex_decl(vertex_declaration);
}


void Model3D::initialize()
{
   if (initialized) throw std::runtime_error("[AllegroFlare::Model3D::initialize]: error: cannot initialize "
                                             "more than once.");
   if (!al_is_system_installed() || !al_is_primitives_addon_initialized() || !al_get_current_display())
   {
      // TODO: al_get_current_display() is needed in this case because al_create_vertex_decl has a condition
      // requiring a display, here: https://github.com/liballeg/allegro5/blob/d2b6b61cb28e1ece3c78907f18c3e34725e3623e/addons/primitives/primitives.c#L211-L215
  
      throw std::runtime_error("[AllegroFlare::Model3D::initialize]: error: al_is_system_installed() or "
                               "al_is_primitives_addon_initialized() or al_get_current_display() not met.");
   }
   build_vertex_declaration();

   initialized = true;
}


void Model3D::build_vertex_declaration()
{
   if (vertex_declaration) return;

   ALLEGRO_VERTEX_ELEMENT elems[] = {
      {ALLEGRO_PRIM_POSITION, ALLEGRO_PRIM_FLOAT_3, offsetof(ALLEGRO_VERTEX_WITH_NORMAL, x)},
      {ALLEGRO_PRIM_TEX_COORD, ALLEGRO_PRIM_FLOAT_2, offsetof(ALLEGRO_VERTEX_WITH_NORMAL, u)},
      {ALLEGRO_PRIM_COLOR_ATTR, 0, offsetof(ALLEGRO_VERTEX_WITH_NORMAL, color)},
      {ALLEGRO_PRIM_USER_ATTR, ALLEGRO_PRIM_FLOAT_3, offsetof(ALLEGRO_VERTEX_WITH_NORMAL, nx)},
      {0, 0, 0}
   };

   vertex_declaration = al_create_vertex_decl(elems, sizeof(ALLEGRO_VERTEX_WITH_NORMAL));
}




bool Model3D::load_obj_file(const char *filename, float scale)
{
   validate_initialized_or_output_to_cerr("load_obj_file");
   Model3DObjLoader loader(this, filename, scale);
   return loader.load();
}




void Model3D::inspect_vertices()
{
   for (unsigned i=0; i<vertices.size(); i++)
   {
      printf(
         "[%d] %f %f %f : %f %f : %f %f %f\n",
         i,
         vertices[i].x, vertices[i].y, vertices[i].z,
         vertices[i].u, vertices[i].v,
         vertices[i].nx, vertices[i].ny, vertices[i].nz
      );
   }
}



void Model3D::inspect_status()
{
   std::stringstream output;
   output << "-             model:" << std::endl;
   output << "       num_vertices: " << vertices.size() << std::endl;
   output << "  has_vertex_buffer: " << (vertex_buffer ? "true" : "false") << std::endl;
   output << "  num_named_objects: " << named_objects.size() << std::endl;

   // output info for named objects
   if (named_objects.size() > 0) output << "      named_objects:" << std::endl;
   for (int i=0; i<named_objects.size(); i++)
   {
      output << "                     - named_object:" << std::endl;
      output << "                         identifier: \"" << named_objects[i].identifier << "\"" << std::endl;
      output << "                        num_indexes: " << named_objects[i].index_list.size() << std::endl;
   }

   std::cout << output.str();
}




void Model3D::validate_initialized_or_output_to_cerr(std::string calling_function)
{
   if (!initialized)
   {
      std::cerr << "[AllegroFlare::Model3D::" << calling_function << "]: error: initialized not met." << std::endl;
   }
}



void Model3D::validate_not_vertex_buffer(std::string calling_function)
{
   if (vertex_buffer)
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Model3D::" << calling_function << "]: error: This function is not supported "
                    << "in this current model state. The model is being rendered as a vertex_buffer.";
      throw std::runtime_error(error_message.str());
   }
}


void Model3D::destroy_and_clear_vertex_buffer()
{
   if (vertex_buffer)
   {
      al_destroy_vertex_buffer(vertex_buffer);
      vertex_buffer = nullptr;
      return;
   }
}


void Model3D::clear()
{
   validate_initialized_or_output_to_cerr("clear");

   vertices.clear();
   named_objects.clear();
   destroy_and_clear_vertex_buffer();
}



void Model3D::append(AllegroFlare::Model3D &other)
{
   // Either model contains named objects, append is not supported
   if ((named_objects.size() > 0) || (other.named_objects.size() > 0))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Model3D::append] error: "
                    << "Models cannot be merged because one or the other contains named objects. If you wish to "
                    << "merge, you will need to flatten (flatten_single_named_object()) the model. Merging models "
                    << "with named objects is not supported for the time being.";
      throw std::runtime_error(error_message.str());
   }

   // Output warning if the textures do not match
   if (other.texture && (other.texture != texture))
   {
      std::cout << "[AllegroFlare::Model3D::append]: warning: The object being appended contains a texture that is "
                << "different from this source model's texture. The source model's texture will be used."
                << std::endl;
   }

   // Destroy our existing vertex buffer if it exists
   if (vertex_buffer)
   {
      std::cout << "[AllegroFlare::Model3D::append]: warning: The source model contains a vertex buffer. It will "
                << "be destroyed and will need to be recreated if you wish to use one with the newly merged data."
                << std::endl;

      destroy_and_clear_vertex_buffer();
   }

   vertices.insert(vertices.end(), other.vertices.begin(), other.vertices.end());
}



// returns true if flattened or if is already flattened
bool Model3D::flatten_single_named_object()
{
   validate_initialized_or_output_to_cerr("flatten_single_named_object");
   validate_not_vertex_buffer("flatten_single_named_object");

   // if there are more than one named object, throw an error
   if (get_num_named_objects() > 1)
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Model3D::flatten_single_named_object] error: "
                    << "Cannot flatten model because it contains more than one named object "
                    << "(" << get_num_named_objects() << " named object(s)).";
      throw std::runtime_error(error_message.str());
   }

   if (named_objects[0].texture)
   {
      std::cout << "[AllegroFlare::Model3D::flatten_single_named_object]: warning: The named object (identifier: \""
                << named_objects[0].identifier << "\") contains a bitmap.  It may be left dangling as it is "
                << "flattened."
                << std::endl;
   }

   named_objects.clear();
   return true;
}



int Model3D::get_num_vertices()
{
   // NOTE: This was previously named "get_num_vertexes"
   return vertices.size();
}




int Model3D::get_num_named_objects()
{
   return named_objects.size();
}



void Model3D::promote_to_vertex_buffer()
{
   validate_initialized_or_output_to_cerr("promote_to_vertex_buffer");
   if (vertex_buffer) return;

   if (get_num_named_objects() >= 1)
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Model3D::promote_to_vertex_buffer] error: "
                    << "Cannot promote because it contains more than one named object "
                    << "(" << get_num_named_objects() << " named object(s)).";
      throw std::runtime_error(error_message.str());
   }

   vertex_buffer = al_create_vertex_buffer(
      vertex_declaration,
      &vertices[0],
      vertices.size(),
      ALLEGRO_PRIM_BUFFER_STATIC
   );
}



void Model3D::draw()
{
   validate_initialized_or_output_to_cerr("draw");

   if (vertex_buffer)
   {
      al_draw_vertex_buffer(vertex_buffer, texture, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
      return;
   }

   if (vertices.empty()) return;

   if (named_objects.empty())
   {
      al_draw_prim(&vertices[0], vertex_declaration, texture, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   }
   else
   {
      // draw each of the named objects individually
      // TODO: this is not optimized, revisit this in the future
      for (unsigned i=0; i<named_objects.size(); i++)
      {
         draw_object(i);
      }
   }
}




bool Model3D::draw_object(int index)
{
   validate_initialized_or_output_to_cerr("draw_object");
   validate_not_vertex_buffer("draw_object");

   if (index < 0 || index > (int)named_objects.size()) return false;

   named_object &object = named_objects[index];

   al_draw_indexed_prim(&vertices[0], vertex_declaration,
         (object.texture) ? object.texture : texture,
         &object.index_list[0], object.index_list.size(), ALLEGRO_PRIM_TRIANGLE_LIST);

   return true;
}



bool Model3D::draw_object(std::string name)
{
   validate_initialized_or_output_to_cerr("draw_object");
   validate_not_vertex_buffer("draw_object");

   bool object_exists = false;
   for (unsigned i=0; i<named_objects.size(); i++)
   {
      if (named_objects[i].identifier == name)
      {
         draw_object(i);
         object_exists = true;
      }
   }
   return object_exists;
}




void Model3D::set_texture(ALLEGRO_BITMAP *tx)
{
   validate_initialized_or_output_to_cerr("set_texture");
   texture = tx;
}




bool Model3D::set_named_object_texture(int index, ALLEGRO_BITMAP *tx)
{
   validate_initialized_or_output_to_cerr("set_named_object_texture");
   validate_not_vertex_buffer("set_named_object_texture");

   if (index < 0 || index > (int)named_objects.size()) return false;
   named_objects[index].texture = tx;
   return true;
}




bool Model3D::set_named_object_texture(std::string object_name, ALLEGRO_BITMAP *tx)
{
   validate_initialized_or_output_to_cerr("set_named_object_texture");
   validate_not_vertex_buffer("set_named_object_texture");

   bool object_exists = false;
   for (unsigned i=0; i<named_objects.size(); i++)
   {
      if (named_objects[i].identifier == object_name)
      {
         named_objects[i].texture = tx;
         object_exists = true;
      }
   }
   return object_exists;
}




void Model3D::scale(float scale)
{
   validate_initialized_or_output_to_cerr("scale");
   validate_not_vertex_buffer("scale");

   for (unsigned i=0; i<vertices.size(); i++)
   {
      vertices[i].x *= scale;
      vertices[i].y *= scale;
      vertices[i].z *= scale;
   }
}



void Model3D::displace(AllegroFlare::Vec3D displacement)
{
   validate_initialized_or_output_to_cerr("displace");
   validate_not_vertex_buffer("displace");

   for (unsigned i=0; i<vertices.size(); i++)
   {
      vertices[i].x += displacement.x;
      vertices[i].y += displacement.y;
      vertices[i].z += displacement.z;
   }
}




vec3d Model3D::get_min_vertex_coordinate()
{
   validate_initialized_or_output_to_cerr("get_min_vertex_coordinate");
   if (vertices.empty()) return vec3d(0, 0, 0);

   vec3d min_coord = vec3d(vertices[0].x, vertices[0].y, vertices[0].z);
   for (unsigned i=1; i<vertices.size(); i++)
   {
      if (vertices[i].x < min_coord.x) min_coord.x = vertices[i].x;
      if (vertices[i].y < min_coord.y) min_coord.y = vertices[i].y;
      if (vertices[i].z < min_coord.z) min_coord.z = vertices[i].z;
   }
   return min_coord;
}




vec3d Model3D::get_max_vertex_coordinate()
{
   validate_initialized_or_output_to_cerr("get_max_vertex_coordinate");
   if (vertices.empty()) return vec3d(0, 0, 0);

   vec3d max_coord = vec3d(vertices[0].x, vertices[0].y, vertices[0].z);
   for (unsigned i=0; i<vertices.size(); i++)
   {
      if (vertices[i].x > max_coord.x) max_coord.x = vertices[i].x;
      if (vertices[i].y > max_coord.y) max_coord.y = vertices[i].y;
      if (vertices[i].z > max_coord.z) max_coord.z = vertices[i].z;
   }
   return max_coord;
}



AllegroFlare::Physics::AABB3D Model3D::build_bounding_box()
{
   return AllegroFlare::Physics::AABB3D(get_min_vertex_coordinate(), get_max_vertex_coordinate());
}



void Model3D::remove_named_object(std::string object_name)
{
   // TODO: Test this feature
   validate_initialized_or_output_to_cerr("remove_named_object");
   validate_not_vertex_buffer("remove_named_object");

   named_object *found_named_object = nullptr;
   int named_object_found_at_index = -1;

   bool object_exists = false;
   for (unsigned i=0; i<named_objects.size(); i++)
   {
      if (named_objects[i].identifier == object_name)
      {
         found_named_object = &named_objects[i];
         named_object_found_at_index = i;
         break;
      }
   }

   if (!found_named_object)
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Model3D::remove_named_object] error: "
                    << "Looking for named_object named \"" << object_name << "\" but it does not exist.";
      throw std::runtime_error(error_message.str());
   }

   // TODO: Handle the case of this implementation as described in this error message
   // TODO: Modify this warning to use AllegroFlare::Logger
   std::stringstream warning_message;
   warning_message << "[AllegroFlare::Model3D::remove_named_object] warning: "
                   << "Removing named object within Model3D. Note that (for the time being) all vertices associated "
                   << "with the named object will remain in the list of vertices. This could have unintended "
                   << "side-effects. In the future, update this operation to remove the named objects vertices "
                   << "from the list of vertices, ensuring that there are no other named objects that rely on those "
                   << "vertices. Also, indices of all remaining named objects will need to be shifted to the new "
                   << "vertices positions.";
   std::cout << warning_message.str() << std::endl;

   named_objects.erase(named_objects.begin() + named_object_found_at_index);
}



std::vector<AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL> Model3D::extract_named_object_vertices(std::string object_name)
{
   // TODO: Consider that there could be multiple named objects with the same name; Throw in this case.
   named_object *found_named_object = nullptr;

   bool object_exists = false;
   for (unsigned i=0; i<named_objects.size(); i++)
   {
      if (named_objects[i].identifier == object_name)
      {
         found_named_object = &named_objects[i];
         break;
      }
   }

   if (!found_named_object)
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Model3D::extract_named_object_vertices] error: "
                    << "Looking for named_object named \"" << object_name << "\" but it does not exist.";
      throw std::runtime_error(error_message.str());
   }

   std::vector<AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL> result;

   for (auto &vertex_index_num : found_named_object->index_list)
   {
      result.push_back(vertices[vertex_index_num]);
   }

   return result;
}


std::vector<std::vector<AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL>>
   Model3D::extract_named_objects_vertices(std::string object_name)
{
   // TODO: Test this method
   std::vector<std::vector<AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL>> result;

   for (unsigned i=0; i<named_objects.size(); i++)
   {
      if (named_objects[i].identifier == object_name)
      {
         std::vector<AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL> local_result;
         for (auto &vertex_index_num : named_objects[i].index_list)
         {
            local_result.push_back(vertices[vertex_index_num]);
         }
         result.push_back(local_result);
      }
   }

   return result;
}


}// Namespace AllegroFlare



