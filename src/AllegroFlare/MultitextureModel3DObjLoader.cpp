

#include <AllegroFlare/MultitextureModel3DObjLoader.hpp>

#include <AllegroFlare/ConsoleColor.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <iostream>


namespace AllegroFlare
{


MultitextureModel3DObjLoader::MultitextureModel3DObjLoader(AllegroFlare::MultitextureModel3D* model, std::string obj_filename, std::string obj_filename_with_uv2_coordinates, float scale)
   : model(model)
   , obj_filename(obj_filename)
   , obj_filename_with_uv2_coordinates(obj_filename_with_uv2_coordinates)
   , scale(scale)
{
}


MultitextureModel3DObjLoader::~MultitextureModel3DObjLoader()
{
}


void MultitextureModel3DObjLoader::set_model(AllegroFlare::MultitextureModel3D* model)
{
   this->model = model;
}


void MultitextureModel3DObjLoader::set_obj_filename(std::string obj_filename)
{
   this->obj_filename = obj_filename;
}


void MultitextureModel3DObjLoader::set_obj_filename_with_uv2_coordinates(std::string obj_filename_with_uv2_coordinates)
{
   this->obj_filename_with_uv2_coordinates = obj_filename_with_uv2_coordinates;
}


void MultitextureModel3DObjLoader::set_scale(float scale)
{
   this->scale = scale;
}


AllegroFlare::MultitextureModel3D* MultitextureModel3DObjLoader::get_model() const
{
   return model;
}


std::string MultitextureModel3DObjLoader::get_obj_filename() const
{
   return obj_filename;
}


std::string MultitextureModel3DObjLoader::get_obj_filename_with_uv2_coordinates() const
{
   return obj_filename_with_uv2_coordinates;
}


float MultitextureModel3DObjLoader::get_scale() const
{
   return scale;
}


bool MultitextureModel3DObjLoader::load()
{
   if (!model) throw std::runtime_error("Unable to load nullptr model");

   model->clear();

   char buff[256];
   ALLEGRO_FILE* file = al_fopen(obj_filename.c_str(), "r");
   ALLEGRO_COLOR white = al_color_name("white");
   std::vector<ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL> vtxs;
   std::vector<MultitextureModel3D::vt_coord> vt_coords;
   std::vector<vec3d> vt_normals;
   ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL vtx;
   MultitextureModel3D::vt_coord vt_c;
   vec3d vt_normal;
   bool vertex_textures_found = false;
   bool vertex_normals_found = false;
   MultitextureModel3D::named_object *current_named_object = NULL;

   if (!al_filename_exists(obj_filename.c_str()))
   {
      std::cout << CONSOLE_COLOR_RED
                << "Could not load \"" << obj_filename << "\" when creating MultitextureModel3D"
                << CONSOLE_COLOR_DEFAULT
                << std::endl
                ;
   }

   while (al_fgets(file, buff, 256))
   {
      vtx.x = vtx.y = vtx.z = 0;
      vtx.color = white;
      vtx.u1 = vtx.v1 = 0;
      vtx.u2 = vtx.v2 = 0;
      vtx.nx = vtx.nz = 0;
      vtx.ny = 1;

      int face_v1 = 0;
      int face_v2 = 0;
      int face_v3 = 0;
      int face_v4 = 0;

      int face_vt1 = 0;
      int face_vt2 = 0;
      int face_vt3 = 0;
      int face_vt4 = 0;

      int face_vn1 = 0;
      int face_vn2 = 0;
      int face_vn3 = 0;
      int face_vn4 = 0;

      if (strncmp(buff, "v ", 2) == 0)
      {
         sscanf(buff, "v %f %f %f", &vtx.x, &vtx.y, &vtx.z);
         vtxs.push_back(vtx);
      }
      else if (strncmp(buff, "vt ", 3) == 0)
      {
         vertex_textures_found = true;
         sscanf(buff, "vt %f %f", &vt_c.u, &vt_c.v);
         vt_c.u = vt_c.u;
         vt_c.v = 1 - vt_c.v;
         vt_coords.push_back(vt_c);
      }
      else if (strncmp(buff, "vn ", 3) == 0)
      {
         vertex_normals_found = true;
         sscanf(buff, "vn %f %f %f", &vt_normal.x, &vt_normal.y, &vt_normal.z);
         vt_normals.push_back(vt_normal);
      }
      else if (strncmp(buff, "o ", 2) == 0)
      {
         // grab the name of the object
         char namebuff[128];
         sscanf(buff, "o %127s", namebuff); 

         // create a new named object
         MultitextureModel3D::named_object new_named_object;
         new_named_object.identifier = namebuff;
         new_named_object.texture = NULL;
         model->named_objects.push_back(new_named_object);
         current_named_object = &model->named_objects.back();
      }
      else if (strncmp(buff, "f ", 2) == 0)
      {
         int num_vertexes_captured = 0;

         if (vertex_textures_found && vertex_normals_found)
         {
            num_vertexes_captured = 
               sscanf(buff, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &face_v1, &face_vt1, &face_vn1, &face_v2, &face_vt2, &face_vn2, &face_v3, &face_vt3, &face_vn3, &face_v4, &face_vt4, &face_vn4);
            num_vertexes_captured /= 3;
         }
         else if (vertex_textures_found)
         {
            num_vertexes_captured = 
               sscanf(buff, "f %d/%d %d/%d %d/%d %d/%d", &face_v1, &face_vt1, &face_v2, &face_vt2, &face_v3, &face_vt3, &face_v4, &face_vt4);
            num_vertexes_captured /= 2;
         }
         else if (vertex_normals_found)
         {
            num_vertexes_captured = 
               sscanf(buff, "f %d//%d %d//%d %d//%d %d//%d", &face_v1, &face_vn1, &face_v2, &face_vn2, &face_v3, &face_vn3, &face_v4, &face_vn4);
            num_vertexes_captured /= 2;
         }
         else
         {
            num_vertexes_captured = 
               sscanf(buff, "f %d %d %d %d", &face_v1, &face_v2, &face_v3, &face_v4);
         }

         vtx.x = vtxs[face_v1-1].x * scale;
         vtx.y = vtxs[face_v1-1].y * scale;
         vtx.z = vtxs[face_v1-1].z * scale;
         vtx.u1 = (vertex_textures_found ? vt_coords[face_vt1-1].u : 0);
         vtx.v1 = (vertex_textures_found ? vt_coords[face_vt1-1].v : 0);
         vtx.u2 = 0.0f;
         vtx.v2 = 0.0f;
         vtx.nx = (vertex_normals_found ? vt_normals[face_vn1-1].x : 0);
         vtx.ny = (vertex_normals_found ? vt_normals[face_vn1-1].y : 0);
         vtx.nz = (vertex_normals_found ? vt_normals[face_vn1-1].z : 1);
         model->vertexes.push_back(vtx);
         if (current_named_object) current_named_object->index_list.push_back(model->vertexes.size()-1);

         vtx.x = vtxs[face_v2-1].x * scale;
         vtx.y = vtxs[face_v2-1].y * scale;
         vtx.z = vtxs[face_v2-1].z * scale;
         vtx.u1 = (vertex_textures_found ? vt_coords[face_vt2-1].u : 0);
         vtx.v1 = (vertex_textures_found ? vt_coords[face_vt2-1].v : 0);
         vtx.u2 = 0.0f;
         vtx.v2 = 0.0f;
         vtx.nx = (vertex_normals_found ? vt_normals[face_vn2-1].x : 0);
         vtx.ny = (vertex_normals_found ? vt_normals[face_vn2-1].y : 0);
         vtx.nz = (vertex_normals_found ? vt_normals[face_vn2-1].z : 1);
         model->vertexes.push_back(vtx);
         if (current_named_object) current_named_object->index_list.push_back(model->vertexes.size()-1);

         vtx.x = vtxs[face_v3-1].x * scale;
         vtx.y = vtxs[face_v3-1].y * scale;
         vtx.z = vtxs[face_v3-1].z * scale;
         vtx.u1 = (vertex_textures_found ? vt_coords[face_vt3-1].u : 0);
         vtx.v1 = (vertex_textures_found ? vt_coords[face_vt3-1].v : 0);
         vtx.u2 = 0.0f;
         vtx.v2 = 0.0f;
         vtx.nx = (vertex_normals_found ? vt_normals[face_vn3-1].x : 0);
         vtx.ny = (vertex_normals_found ? vt_normals[face_vn3-1].y : 0);
         vtx.nz = (vertex_normals_found ? vt_normals[face_vn3-1].z : 1);
         model->vertexes.push_back(vtx);
         if (current_named_object) current_named_object->index_list.push_back(model->vertexes.size()-1);

         if (num_vertexes_captured == 4)
         {
            vtx.x = vtxs[face_v3-1].x * scale;
            vtx.y = vtxs[face_v3-1].y * scale;
            vtx.z = vtxs[face_v3-1].z * scale;
            vtx.u1 = (vertex_textures_found ? vt_coords[face_vt3-1].u : 0);
            vtx.v1 = (vertex_textures_found ? vt_coords[face_vt3-1].v : 0);
            vtx.u2 = 0.0f;
            vtx.v2 = 0.0f;
            vtx.nx = (vertex_normals_found ? vt_normals[face_vn3-1].x : 0);
            vtx.ny = (vertex_normals_found ? vt_normals[face_vn3-1].y : 0);
            vtx.nz = (vertex_normals_found ? vt_normals[face_vn3-1].z : 1);
            model->vertexes.push_back(vtx);
            if (current_named_object) current_named_object->index_list.push_back(model->vertexes.size()-1);

            vtx.x = vtxs[face_v4-1].x * scale;
            vtx.y = vtxs[face_v4-1].y * scale;
            vtx.z = vtxs[face_v4-1].z * scale;
            vtx.u1 = (vertex_textures_found ? vt_coords[face_vt4-1].u : 0);
            vtx.v1 = (vertex_textures_found ? vt_coords[face_vt4-1].v : 0);
            vtx.u2 = 0.0f;
            vtx.v2 = 0.0f;
            vtx.nx = (vertex_normals_found ? vt_normals[face_vn4-1].x : 0);
            vtx.ny = (vertex_normals_found ? vt_normals[face_vn4-1].y : 0);
            vtx.nz = (vertex_normals_found ? vt_normals[face_vn4-1].z : 1);
            model->vertexes.push_back(vtx);
            if (current_named_object) current_named_object->index_list.push_back(model->vertexes.size()-1);

            vtx.x = vtxs[face_v1-1].x * scale;
            vtx.y = vtxs[face_v1-1].y * scale;
            vtx.z = vtxs[face_v1-1].z * scale;
            vtx.u1 = (vertex_textures_found ? vt_coords[face_vt1-1].u : 0);
            vtx.v1 = (vertex_textures_found ? vt_coords[face_vt1-1].v : 0);
            vtx.u2 = 0.0f;
            vtx.v2 = 0.0f;
            vtx.nx = (vertex_normals_found ? vt_normals[face_vn1-1].x : 0);
            vtx.ny = (vertex_normals_found ? vt_normals[face_vn1-1].y : 0);
            vtx.nz = (vertex_normals_found ? vt_normals[face_vn1-1].z : 1);
            model->vertexes.push_back(vtx);
            if (current_named_object) current_named_object->index_list.push_back(model->vertexes.size()-1);
         }
      }
   }

   if (!vertex_normals_found)
   {
      std::cout << "Vertex normals not found when loading \""
                << obj_filename
                << "\".  Unexpected results may occour with default vertex normal (0, 0, 1)."
                << std::endl;
   }
   if (!vertex_textures_found)
   {
      std::cout << "Vertex textures not found when loading \""
                << obj_filename
                << "\".  Unexpected results may occour."
                << std::endl;
   }
   //std::cout << model->named_objects.size() << " named objects found" << std::endl;

   al_fclose(file);
   return true;
}


} // namespace AllegroFlare


