
#include <Wicked/Entity.hpp>


#include <iostream>


namespace Wicked
{


  int Entity::get_id() { return this->id; }
  int Entity::get_last_id() { return next_id - 1; }
  void Entity::__set_id(int id) { this->id = id; }
  void Entity::__set_next_id(int next_id) { Entity::next_id = next_id; }

  Entity::Entity()
     : id(next_id++) // NOTE: this probably should be last_id++
     , place()
     , velocity()
     , model(nullptr)
     , shader_applies_transform(true)
     , atlas(nullptr)
     , mesh(nullptr)
     , shader(nullptr)
     , diffuse_texture(nullptr)
     , normal_texture(nullptr)
     , specular_texture(nullptr)
     , cube_map_A(nullptr)
     , cube_map_B(nullptr)
     , cube_map_reflecting(true)  // this is "true" for a metalic texture (e.g. the material is "reflecting"), otherwise "false" and the material is a skybox
     , cube_box_color(ALLEGRO_COLOR{1.0, 0.74, 0.0, 1.0})
     , cube_box_opacity(0.6)
     , is_selected_with_cursor(false)
     , name("[Unnamed]")
     , type("unset")
  {}

  void Entity::draw_for_depth_pass(AllegroFlare::Shader *shader_for_depth_pass)
  {
     ALLEGRO_TRANSFORM transform;
     place.build_transform(&transform);
     AllegroFlare::Shader::set_mat4("position_transform", &transform);

     if (model) model->draw();

     return;
  }

  void Entity::draw(AllegroFlare::vec3d camera_position,
      AllegroFlare::vec3d light_position,
      ALLEGRO_TRANSFORM *shadow_map_depth_pass_transform,
      ALLEGRO_BITMAP *shadow_map_depth_pass_surface,
      AllegroFlare::vec2d texture_offset
   )
  {
      ALLEGRO_STATE previous_state;
      ALLEGRO_TRANSFORM transform;

      if (!shader)
      {
         throw std::runtime_error("(!!!) this model expects to have a shader. Make sure one is assigned to it before rendering. you might try the standard compound shader, which is actually just a normal ass vanilla texturing shader.");
      }


      //shader_applies_transform = false;
      if (shader && shader_applies_transform)
      {
         //std::cout << "place (" << place.position.x << ", " << place.position.y << ", " << place.position.z << ")"
                   //<< std::endl;

         // construct our entity's transform
         place.build_transform(&transform);
        //std::cout << "." << std::endl; 


         // Now apply it to the shader
         //shader->use();
         shader->activate();
         AllegroFlare::Shader::set_vec3("camera_position", camera_position);
         AllegroFlare::Shader::set_vec3("light_position", light_position);
         AllegroFlare::Shader::set_mat4("position_transform", &transform);

         AllegroFlare::Shader::set_bool("reflecting", cube_map_reflecting);
         AllegroFlare::Shader::set_bool("is_selected_with_cursor", is_selected_with_cursor);



         //flat_color_shader->use();

         //ALLEGRO_COLOR cube_box_color = al_color_html("fe93f3"); // **excellent** light pink color
         ////ALLEGRO_COLOR cube_box_color = ALLEGRO_COLOR{1.0, 0.74, 0.0, 1.0}; // original golden color
         //float cube_box_opacity = 0.6;// get_identity_tint_intensity();
         
         AllegroFlare::Shader::set_vec3("cube_box_color", cube_box_color.r, cube_box_color.g, cube_box_color.b);
         AllegroFlare::Shader::set_float("cube_box_opacity", cube_box_opacity);


         AllegroFlare::Shader::set_sampler("diffuse_texture", diffuse_texture, 0);

         if (shadow_map_depth_pass_transform && shadow_map_depth_pass_surface)
         {
            AllegroFlare::Shader::set_sampler("depth_pass_surface", shadow_map_depth_pass_surface, 1);
            AllegroFlare::Shader::set_mat4("depth_pass_transform", shadow_map_depth_pass_transform);
            AllegroFlare::Shader::set_float("texture_offset_x", texture_offset.x);
            AllegroFlare::Shader::set_float("texture_offset_y", texture_offset.y);
         }
         //Shader::set_sampler("specular_texture", specular_texture, 3);
         //Shader::set_sampler("normal_texture", normal_texture, 4);
         AllegroFlare::Shader::set_sampler_cube("cube_map_A", cube_map_A, 5);
         AllegroFlare::Shader::set_sampler_cube("cube_map_B", cube_map_B, 6);
         if (diffuse_texture && model) model->set_texture(diffuse_texture);
      }
      else
      {
        //std::cout << "." << std::endl; 
         // when not using the shader, we'll need to 
         // apply the transform directly here
         al_store_state(&previous_state, ALLEGRO_STATE_TRANSFORM);
         al_identity_transform(&transform);
         al_use_transform(&transform);
         place.start_transform();

         std::cout << "place (" << place.position.x << ", " << place.position.y << ", " << place.position.z << ")"
                   << std::endl;

         // also, we set the texture on this model directly
         if (diffuse_texture && model) model->set_texture(diffuse_texture);
      }



      // actually draw our model here
      if (model) model->draw();

      if (mesh) mesh->render();



      if (shader && shader_applies_transform)
      {
         //shader->stop();
         shader->deactivate();
      }
      else
      {
         place.restore_transform();
         al_restore_state(&previous_state);
      }
  }


} // namespace Wicked


int Wicked::Entity::next_id = 1;



