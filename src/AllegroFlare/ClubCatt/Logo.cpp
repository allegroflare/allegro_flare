

#include <AllegroFlare/ClubCatt/Logo.hpp>

#include <AllegroFlare/Placement3D.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace ClubCatt
{


Logo::Logo(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::ModelBin* model_bin)
   : bitmap_bin(bitmap_bin)
   , model_bin(model_bin)
   , model_identifier("centered_unit_cube-02.obj")
   , cube_texture1_identifier("clubcatt_cube_texture-01.png")
   , cube_texture2_identifier("clubcatt_cube_texture-01b.png")
   , camera()
   , rotation_x_timeline()
   , rotation_y_timeline()
   , camera_spin_timeline()
   , texture_swap_timeline()
   , fade_out_timeline()
   , end_marker_timeline()
   , playback_speed_multiplier(1.65)
   , playing(false)
   , playing_started_at(0.0f)
   , clear_background_to_color(true)
   , finished(false)
   , on_finished_callback()
   , on_finished_callback_user_data(nullptr)
   , initialized(false)
   , destroyed(false)
{
}


Logo::~Logo()
{
}


void Logo::set_clear_background_to_color(bool clear_background_to_color)
{
   this->clear_background_to_color = clear_background_to_color;
}


void Logo::set_on_finished_callback(std::function<void(AllegroFlare::ClubCatt::Logo*, void*)> on_finished_callback)
{
   this->on_finished_callback = on_finished_callback;
}


void Logo::set_on_finished_callback_user_data(void* on_finished_callback_user_data)
{
   this->on_finished_callback_user_data = on_finished_callback_user_data;
}


AllegroFlare::BitmapBin* Logo::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::ModelBin* Logo::get_model_bin() const
{
   return model_bin;
}


bool Logo::get_playing() const
{
   return playing;
}


bool Logo::get_clear_background_to_color() const
{
   return clear_background_to_color;
}


bool Logo::get_finished() const
{
   return finished;
}


std::function<void(AllegroFlare::ClubCatt::Logo*, void*)> Logo::get_on_finished_callback() const
{
   return on_finished_callback;
}


void* Logo::get_on_finished_callback_user_data() const
{
   return on_finished_callback_user_data;
}


bool Logo::get_initialized() const
{
   return initialized;
}


bool Logo::get_destroyed() const
{
   return destroyed;
}


void Logo::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Logo::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logo::set_bitmap_bin: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void Logo::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Logo::set_model_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logo::set_model_bin: error: guard \"(!initialized)\" not met");
   }
   this->model_bin = model_bin;
   return;
}

void Logo::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Logo::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logo::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Logo::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logo::initialize: error: guard \"bitmap_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[Logo::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logo::initialize: error: guard \"model_bin\" not met");
   }
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[Logo::initialize]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logo::initialize: error: guard \"al_get_current_display()\" not met");
   }
   // Setup the camera
   camera.stepout = {0, 0, 80}; // Step back from the origin, note 100 will clip past the far plane
   camera.zoom = 18.0;

   // Preload the model and texture
   // TODO: preload resources
   // TODO: preload with mipmaps and min/mag linear
   ALLEGRO_STATE previous_bitmap_flags_state;
   al_store_state(&previous_bitmap_flags_state, ALLEGRO_STATE_BITMAP);
   al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP);
   //ALLEGRO_BITMAP *texture = bitmap_bin->auto_get("unit_cube-02.png");
   //ALLEGRO_BITMAP *texture = bitmap_bin->auto_get("cube_perfect-01.png");

   // TODO: Validate the models do not already exist

   bitmap_bin->preload(cube_texture1_identifier);
   bitmap_bin->preload(cube_texture2_identifier);
   model_bin->preload(model_identifier);

   al_restore_state(&previous_bitmap_flags_state);

   playback_speed_multiplier = 1.65;

   // Setup timeline keyframes
   rotation_y_timeline.set_keyframes({
      new AllegroFlare::Timeline::Keyframe(0.05, 0),
      new AllegroFlare::Timeline::Keyframe(0.55, 0.25, AllegroFlare::interpolator::slow_in),
   });
   rotation_x_timeline.set_keyframes({
      new AllegroFlare::Timeline::Keyframe(1.05, 0),
      new AllegroFlare::Timeline::Keyframe(1.55, 0.25, AllegroFlare::interpolator::slow_in),
   });
   camera_spin_timeline.set_keyframes({
      new AllegroFlare::Timeline::Keyframe(2.05, 0),
      new AllegroFlare::Timeline::Keyframe(2.55, -3.14159265359/2, AllegroFlare::interpolator::slow_in),
   });
   texture_swap_timeline.set_keyframes({
      new AllegroFlare::Timeline::Keyframe(2.0, 0),
      new AllegroFlare::Timeline::Keyframe(2.00001, 1),
   });
   fade_out_timeline.set_keyframes({
      new AllegroFlare::Timeline::Keyframe(0.0, 0),
      new AllegroFlare::Timeline::Keyframe(4.0, 0),
      new AllegroFlare::Timeline::Keyframe(4.9, 1),
   });
   end_marker_timeline.set_keyframes({
      new AllegroFlare::Timeline::Keyframe(5.2499, 0),
      new AllegroFlare::Timeline::Keyframe(5.25, 1),
   });

   initialized = true;
   destroyed = false;

   return;
}

void Logo::destroy()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Logo::destroy]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logo::destroy: error: guard \"initialized\" not met");
   }
   // TODO: free up bin objects
   bitmap_bin->destroy(cube_texture1_identifier);
   bitmap_bin->destroy(cube_texture2_identifier);
   model_bin->destroy(model_identifier);

   // TODO: free up the keyframes
   for (auto &keyframe : rotation_x_timeline.get_keyframes()) { delete keyframe; }
   for (auto &keyframe : rotation_y_timeline.get_keyframes()) { delete keyframe; }
   for (auto &keyframe : camera_spin_timeline.get_keyframes()) { delete keyframe; }
   for (auto &keyframe : texture_swap_timeline.get_keyframes()) { delete keyframe; }
   for (auto &keyframe : fade_out_timeline.get_keyframes()) { delete keyframe; }
   for (auto &keyframe : end_marker_timeline.get_keyframes()) { delete keyframe; }

   initialized = false;
   destroyed = true;

   return;
}

void Logo::reset()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Logo::reset]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logo::reset: error: guard \"initialized\" not met");
   }
   // TODO: Test this function (it wouldn't be used anywhere as far as I known of)
   playing = false;
   finished = false;
   playing_started_at = 0.0f;
   return;
}

void Logo::play(float time_now)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Logo::play]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logo::play: error: guard \"initialized\" not met");
   }
   playing = true;
   playing_started_at = time_now;
   return;
}

void Logo::update(float time_now)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Logo::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logo::update: error: guard \"initialized\" not met");
   }
   float local_time_now = calc_local_time_now(time_now);

   if (!finished && end_marker_timeline.get(local_time_now) > 0.999)
   {
      finished = true;
      if (on_finished_callback) on_finished_callback(this, on_finished_callback_user_data);
   }
   return;
}

void Logo::draw(float time_now)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Logo::draw]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Logo::draw: error: guard \"initialized\" not met");
   }
   float local_time_now = calc_local_time_now(time_now);

   // Declare our objects

   AllegroFlare::Placement3D object_placement;
   AllegroFlare::Model3D *model = nullptr;
   ALLEGRO_COLOR vertices_color = ALLEGRO_COLOR{1, 1, 1, 1};

   // Modify the objects based on timelines

   camera.spin = camera_spin_timeline.get(local_time_now);

   std::string cube_texture_identifier_for_this_frame = (texture_swap_timeline.get(local_time_now) > 0.999)
                                                      ? cube_texture2_identifier
                                                      : cube_texture1_identifier
                                                      ;

   object_placement.rotation.x = rotation_x_timeline.get(local_time_now);
   object_placement.rotation.y = rotation_y_timeline.get(local_time_now);

   model = model_bin->auto_get(model_identifier);
   model->texture = bitmap_bin->auto_get(cube_texture_identifier_for_this_frame);
   float fade = 1.0 - fade_out_timeline.get(local_time_now);
   vertices_color = ALLEGRO_COLOR{fade, fade, fade, 1.0};

   for (auto &vertex : model->vertices)
   {
      vertex.color = vertices_color;
   }

   // Render the scene

   // grab the current projection transform
   // TODO: Check the restoration of the previous transform with a test
   const ALLEGRO_TRANSFORM *transform_before_render = al_get_current_projection_transform();
   ALLEGRO_TRANSFORM previous_transform;
   if (transform_before_render) al_copy_transform(&previous_transform, transform_before_render);

   camera.setup_projection_on(get_display_backbuffer());
   al_clear_depth_buffer(1);
   if (clear_background_to_color) al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1.0});

   object_placement.start_transform();
   model->draw();
   object_placement.restore_transform();

   // restore previous transform
   if (transform_before_render) al_use_projection_transform(&previous_transform);

   return;
}

ALLEGRO_BITMAP* Logo::get_display_backbuffer()
{
   // TODO: Validate backbuffer has depth
   return al_get_backbuffer(al_get_current_display());
}

float Logo::calc_local_time_now(float time_now)
{
   if (!playing) return 0.0f;
   float age = time_now - playing_started_at;
   float local_time_now = (age * playback_speed_multiplier);
   return local_time_now;
}


} // namespace ClubCatt
} // namespace AllegroFlare


