

#include <AllegroFlare/Elements/WorldMapViewer.hpp>

#include <AllegroFlare/Random.hpp>
#include <AllegroFlare/Useful.hpp>
#include <AllegroFlare/WorldMapRenderers/Basic.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


WorldMapViewer::WorldMapViewer(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , place()
   , map(nullptr)
   , map_placement()
   , current_page_index_num(0)
   , document_camera()
   , document_camera_target_zoom(0)
   , document_camera_zoom_levels({ 0.5f })
   , document_camera_zoom_level_cursor(0)
   , camera_velocity_magnitude_axis_x(0)
   , camera_velocity_magnitude_axis_y(0)
   , camera_range_x1(-100)
   , camera_range_y1(-200)
   , camera_range_x2(100)
   , camera_range_y2(200)
   , camera_max_velocity(6.5)
   , initialized(false)
{
}


WorldMapViewer::~WorldMapViewer()
{
}


void WorldMapViewer::set_place(AllegroFlare::Placement2D place)
{
   this->place = place;
}


void WorldMapViewer::set_camera_velocity_magnitude_axis_x(float camera_velocity_magnitude_axis_x)
{
   this->camera_velocity_magnitude_axis_x = camera_velocity_magnitude_axis_x;
}


void WorldMapViewer::set_camera_velocity_magnitude_axis_y(float camera_velocity_magnitude_axis_y)
{
   this->camera_velocity_magnitude_axis_y = camera_velocity_magnitude_axis_y;
}


void WorldMapViewer::set_camera_range_x1(float camera_range_x1)
{
   this->camera_range_x1 = camera_range_x1;
}


void WorldMapViewer::set_camera_range_y1(float camera_range_y1)
{
   this->camera_range_y1 = camera_range_y1;
}


void WorldMapViewer::set_camera_range_x2(float camera_range_x2)
{
   this->camera_range_x2 = camera_range_x2;
}


void WorldMapViewer::set_camera_range_y2(float camera_range_y2)
{
   this->camera_range_y2 = camera_range_y2;
}


void WorldMapViewer::set_camera_max_velocity(float camera_max_velocity)
{
   this->camera_max_velocity = camera_max_velocity;
}


AllegroFlare::BitmapBin* WorldMapViewer::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* WorldMapViewer::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::Placement2D WorldMapViewer::get_place() const
{
   return place;
}


AllegroFlare::WorldMaps::Maps::Basic* WorldMapViewer::get_map() const
{
   return map;
}


AllegroFlare::Placement2D WorldMapViewer::get_map_placement() const
{
   return map_placement;
}


float WorldMapViewer::get_camera_velocity_magnitude_axis_x() const
{
   return camera_velocity_magnitude_axis_x;
}


float WorldMapViewer::get_camera_velocity_magnitude_axis_y() const
{
   return camera_velocity_magnitude_axis_y;
}


float WorldMapViewer::get_camera_range_x1() const
{
   return camera_range_x1;
}


float WorldMapViewer::get_camera_range_y1() const
{
   return camera_range_y1;
}


float WorldMapViewer::get_camera_range_x2() const
{
   return camera_range_x2;
}


float WorldMapViewer::get_camera_range_y2() const
{
   return camera_range_y2;
}


float WorldMapViewer::get_camera_max_velocity() const
{
   return camera_max_velocity;
}


void WorldMapViewer::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::set_bitmap_bin: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void WorldMapViewer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::set_font_bin: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   return;
}

void WorldMapViewer::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::initialize: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::initialize]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::initialize: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::initialize: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::initialize: error: guard \"font_bin\" not met");
   }
   // set the "name" property (as expected by the Panes::Base class)
   // HERE: Base::set_name("Crime Summary");

   int margin_x = 100;
   int margin_y = 142;
   place = AllegroFlare::Placement2D(1920/2, 1080/2, 1920-margin_x*2, 1080-margin_y*2);

   fit_and_position_map();
   reset_document_camera();

   initialized = true;
   return;
}

void WorldMapViewer::fit_and_position_map()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::fit_and_position_map]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::fit_and_position_map: error: guard \"bitmap_bin\" not met");
   }
   if (!map) return;
   ///* // TODO
   //static AllegroFlare::Random random;
   //random.set_seed(4321);
   // TODO: create aesthetic random positioning of pages
   //int num_pages = pages.size();
   //float page_distance = 40.0f;
   //float rotation_range = 0.3;
   //for (auto &page : pages)
   //{
   //map_placement.fir
      //page.fit_placement_size_to_bitmap(bitmap_bin);
      ALLEGRO_BITMAP *map_image = bitmap_bin->auto_get(map->get_background_image_identifier());
      map_placement.size = { 0.0f, 0.0f };

      if (map_image)
      {
         map_placement.size = { (float)al_get_bitmap_width(map_image), (float)al_get_bitmap_height(map_image) };
      }

      map_placement.position.x = place.size.x * 0.5;
      map_placement.position.y = place.size.y * 0.5;
      map_placement.align.x = 0.5;
      map_placement.align.y = 0.5;
      map_placement.rotation = 0; //random.get_random_float(-0.1, 0.1);
   //}
   //*/

   return;
}

void WorldMapViewer::fit_camera_range_to_first_page_dimensions()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::fit_camera_range_to_first_page_dimensions]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::fit_camera_range_to_first_page_dimensions: error: guard \"initialized\" not met");
   }
   /* TODO
   if (pages.empty()) reset_document_camera_range();
   CatDetective::Chronicle::Panes::CrimeSummaryPage &first_page = pages[0];
   AllegroFlare::Placement2D &first_page_placement = first_page.get_place_ref();

   float h_width = first_page_placement.size.x * 0.5;
   float h_height = first_page_placement.size.y * 0.5;
   camera_range_x1 = -h_width;
   camera_range_y1 = -h_height;
   camera_range_x2 = h_width;
   camera_range_y2 = h_height;
   */

   return;
}

void WorldMapViewer::reset()
{
   reset_document_camera();
   go_to_first_page();
   return;
}

void WorldMapViewer::reset_document_camera()
{
   document_camera_zoom_levels = { 0.5, 0.75, 1.0, 1.25, 1.5, 1.75 };
   document_camera_zoom_level_cursor = 0;
   camera_velocity_magnitude_axis_x = 0;
   camera_velocity_magnitude_axis_y = 0;

   document_camera.size = { place.size.x, place.size.y };
   document_camera.position = { place.size.x * 0.5f, place.size.y * 0.5f };
   document_camera_target_zoom = document_camera_zoom_levels[document_camera_zoom_level_cursor];
   document_camera.set_zoom({document_camera_target_zoom, document_camera_target_zoom});
   return;
}

void WorldMapViewer::reset_document_camera_range()
{
   camera_range_x1 = -100;
   camera_range_y1 = -200;
   camera_range_x2 = 100;
   camera_range_y2 = 200;
   return;
}

void WorldMapViewer::on_switch_out()
{
   unset_camera_moving();
   return;
}

void WorldMapViewer::step_zoom_in()
{
   document_camera_zoom_level_cursor++;
   document_camera_zoom_level_cursor = document_camera_zoom_level_cursor % document_camera_zoom_levels.size();
   document_camera_target_zoom = document_camera_zoom_levels[document_camera_zoom_level_cursor];
   return;
}

void WorldMapViewer::step_zoom_out()
{
   document_camera_zoom_level_cursor--;
   document_camera_zoom_level_cursor += document_camera_zoom_levels.size();
   document_camera_zoom_level_cursor = document_camera_zoom_level_cursor % document_camera_zoom_levels.size();
   document_camera_target_zoom = document_camera_zoom_levels[document_camera_zoom_level_cursor];
   return;
}

void WorldMapViewer::set_camera_moving_up()
{
   camera_velocity_magnitude_axis_y = -camera_max_velocity;
   return;
}

void WorldMapViewer::set_camera_moving_down()
{
   camera_velocity_magnitude_axis_y = camera_max_velocity;
   return;
}

void WorldMapViewer::unset_camera_moving_vertical()
{
   camera_velocity_magnitude_axis_y = 0.0f;
   return;
}

void WorldMapViewer::set_camera_moving_left()
{
   camera_velocity_magnitude_axis_x = -camera_max_velocity;
   return;
}

void WorldMapViewer::set_camera_moving_right()
{
   camera_velocity_magnitude_axis_x = camera_max_velocity;
   return;
}

void WorldMapViewer::unset_camera_moving_horizontal()
{
   camera_velocity_magnitude_axis_x = 0.0f;
   return;
}

void WorldMapViewer::unset_camera_moving()
{
   unset_camera_moving_vertical();
   unset_camera_moving_horizontal();
}

void WorldMapViewer::set_pages(std::vector<std::string> pages)
{
   /* // HERE
   current_page_index_num = 0;
   this->pages = pages;
   */
   fit_and_position_map();
   reset_document_camera();
   return;
}

void WorldMapViewer::set_map(AllegroFlare::WorldMaps::Maps::Basic* map)
{
   /* // HERE
   current_page_index_num = 0;
   this->pages = pages;
   */
   this->map = map; // NEW
   fit_and_position_map();
   reset_document_camera();
   return;
}

void WorldMapViewer::go_to_first_page()
{
   int attempts_remaining = 999;
   while (current_page_index_num != 0)
   {
      page_next(false);

      attempts_remaining--;
      if (attempts_remaining <= 0)
      {
         std::stringstream error_message;
         error_message << "CatDetective::Chronicle::Panes::CrimeSummary::go_to_first_page error: "
                       << "Stuck in while loop; Ran out of attempts, aborting.";
         throw std::runtime_error(error_message.str());
         break;
      }
   }
   return;
}

void WorldMapViewer::page_next(bool play_and_show_effects)
{
   /* // HERE
   if (pages.empty()) return;
   current_page_index_num += 1;
   current_page_index_num = current_page_index_num % pages.size();
   std::rotate(pages.begin(), pages.begin()+1, pages.end());
   */
   // TODO: play "page flip" sound effect, account for "play_and_show_effects" parameter
   return;
}

void WorldMapViewer::page_previous(bool play_and_show_effects)
{
   /* // HERE
   if (pages.empty()) return;
   // TODO: add tests to ensure this will work
   current_page_index_num -= 1;
   current_page_index_num += pages.size();
   current_page_index_num = current_page_index_num % pages.size();
   std::rotate(pages.begin(), pages.begin()+(pages.size()-1), pages.end());
   */
   // TODO: play "page flip" sound effect, account for "play_and_show_effects" parameter
   return;
}

void WorldMapViewer::render_pages()
{
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::render_pages]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::render_pages: error: guard \"al_get_current_display()\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::render_pages]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::render_pages: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::render_pages]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::render_pages: error: guard \"font_bin\" not met");
   }
   if (infer_no_pages_are_present())
   {
      // draw some placeholder text when there are no pages
      draw_empty_state(font_bin, "No Crime Summary Report");
   }
   else
   {
      // TODO: add extra scroll offset so clipping travels along with external camera movement
      int clip_x, clip_y, clip_w, clip_h;
      clip_x = (place.position.x - place.size.x * place.align.x);
      clip_y = (place.position.y - place.size.y * place.align.y);
      clip_w = place.size.x;
      clip_h = place.size.y;

      // Scale the clipping points to match the actual resolution of the display, rather than the 
      // surface virtual resolution which is 1920x1080.
      // NOTE: The technique for retrieving physical surface dimentions here feels a bit sloppy because it's
      // requesting hardware state/data (which is not the purview of this component) from deep within this
      // omponent which feels out of scope, but, it's probably fine tbh because I think this information is
      // already actively stored in the allegro state.

      ALLEGRO_DISPLAY *current_display = al_get_current_display();
      int physical_surface_width = al_get_display_width(current_display);
      int physical_surface_height = al_get_display_height(current_display);
      int virtual_surface_width = 1920;
      int virtual_surface_height = 1080;

      if (virtual_surface_width == physical_surface_width && virtual_surface_height == physical_surface_height)
      {
         // do no scaling, the physical and virtual dimensions are identical
      }
      else
      {
         float x_scale_change = physical_surface_width / (float)virtual_surface_width;
         float y_scale_change = physical_surface_height / (float)virtual_surface_height;
         clip_x *= x_scale_change;
         clip_y *= y_scale_change;
         clip_w *= x_scale_change;
         clip_h *= y_scale_change;
      }

      al_set_clipping_rectangle(clip_x, clip_y, clip_w, clip_h);
      document_camera.start_reverse_transform();

      // render pages in reverse order from back to front
      /* // HERE
      for (int i=(pages.size()-1); i>=0; i--)
      {
         HERE: pages[i].render(bitmap_bin);
      }
      */

      // NEW:
      AllegroFlare::WorldMapRenderers::Basic renderer(bitmap_bin, font_bin, map);
      renderer.render();

      document_camera.restore_transform();

      al_reset_clipping_rectangle(); // TODO: revert to previous clipping instead
   }

   return;
}

bool WorldMapViewer::infer_no_pages_are_present()
{
   return map == nullptr;
   //return pages.empty();
}

void WorldMapViewer::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::update: error: guard \"initialized\" not met");
   }
   // update camera position by the velocity
   document_camera.position.x += camera_velocity_magnitude_axis_x;
   document_camera.position.y += camera_velocity_magnitude_axis_y;

   // ensure the camera does not extand beyond the constraints
   document_camera.position.x -= place.size.x * 0.5;
   document_camera.position.x =
      AllegroFlare::clamp<float>(camera_range_x1, camera_range_x2, document_camera.position.x)
      + place.size.x * 0.5;
   document_camera.position.y -= place.size.y * 0.5;
   document_camera.position.y =
      AllegroFlare::clamp<float>(camera_range_y1, camera_range_y2, document_camera.position.y)
      + place.size.y * 0.5;

   // update camera zoom
   float f_zoom = document_camera.get_zoom().x;
   float next_zoom = (document_camera_target_zoom - f_zoom) * 0.175 + f_zoom;
   document_camera.set_zoom({next_zoom, next_zoom});
   return;
}

void WorldMapViewer::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::render: error: guard \"initialized\" not met");
   }
   if (infer_no_pages_are_present())
   {
      //draw_empty_state(font_bin, "No Crime Summary Report");
      draw_empty_state(font_bin, "No Map");
   }
   else
   {
      place.start_transform();

      // draw an arbitrary frame
      al_draw_rectangle(0, 0, place.size.x, place.size.y, ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2}, 2.0f);
      // render the elements
      render_pages();
      render_page_numbers();
      render_zoom_scale();

      place.restore_transform();
   }

   return;
}

void WorldMapViewer::render_page_numbers()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::render_page_numbers]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::render_page_numbers: error: guard \"initialized\" not met");
   }
   std::string page_numbers_text = "[unset-page_numbers_text]";
   /*
      = "page "
      + (std::to_string(pages.empty() ? 0 : current_page_index_num + 1))
      + " of "
      + std::to_string(pages.size());
   */

   float x = place.size.x * 0.5;
   float y = place.size.y;

   ALLEGRO_FONT *font = obtain_font();
   float text_width = al_get_text_width(font, page_numbers_text.c_str());
   float text_height = al_get_font_line_height(font);
   float h_text_width = text_width/2;
   float h_text_height = text_height/2;
   AllegroFlare::Vec2D padding = {30, 20};

   al_draw_filled_rounded_rectangle(
      x-h_text_width - padding.x,
      y-h_text_height - padding.y,
      x+h_text_width + padding.x,
      y+h_text_height + padding.y,
      8.0f,
      8.0f,
      ALLEGRO_COLOR{0, 0, 0, 0.5}
   );
   al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, x, y-h_text_height, ALLEGRO_ALIGN_CENTER, page_numbers_text.c_str());
   return;
}

void WorldMapViewer::render_zoom_scale()
{
   float height = 380;
   float x_pos = place.size.x;
   float y_pos = place.size.y * 0.5 - height / 2;
   float zoom_cursor_pos = 1.0 - calc_zoom_position_relative_min_max();
   float padding_x = 32;
   float padding_y = 48;
   float roundness = padding_x;

   // draw background rectangle, same as "render_page_numbers"
   al_draw_filled_rounded_rectangle(
      x_pos - padding_x,
      y_pos - padding_y,
      x_pos + padding_x,
      y_pos + padding_y + height,
      roundness,
      roundness,
      ALLEGRO_COLOR{0, 0, 0, 0.5}
   );

   // draw the meter
   al_draw_line(x_pos, y_pos, x_pos, y_pos+height, ALLEGRO_COLOR{1,1,1,1}, 4.0);

   // draw the head on the bar
   al_draw_filled_circle(x_pos, y_pos + height * zoom_cursor_pos, 12, ALLEGRO_COLOR{1, 1, 1, 1});

   // draw the "zoom" label
   // TODO
   return;
}

void WorldMapViewer::draw_empty_state(AllegroFlare::FontBin* font_bin, std::string placeholder_text)
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::draw_empty_state]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::draw_empty_state: error: guard \"font_bin\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::draw_empty_state]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::draw_empty_state: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   static constexpr float frame_width = 1920;
   static constexpr float frame_height = 1080;
   static constexpr float width = frame_width - 100 * 2;
   static constexpr float height = frame_height - 142 * 2;
   static constexpr float cx = frame_width / 2;
   static constexpr float cy = frame_height / 2;

   static constexpr float x1 = cx - width * 0.5;;
   static constexpr float y1 = cy - height * 0.5;
   static constexpr float x2 = cx + width * 0.5;
   static constexpr float y2 = cy + height * 0.5;

   al_draw_rectangle(x1, y1, x2, y2, ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2}, 2.0f);

   // draw the text
   static const std::string FONT_IDENTIFIER = "Inter-Medium.ttf -36";
   ALLEGRO_FONT* font = font_bin->operator[](FONT_IDENTIFIER);

   al_draw_text(
         font,
         ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2},
         1920 * 0.5,
         1080 * 0.5,
         ALLEGRO_ALIGN_CENTER,
         placeholder_text.c_str()
      );

   return;
}

float WorldMapViewer::calc_zoom_position_relative_min_max()
{
   if (document_camera_zoom_levels.empty()) return 0.0f;
   auto [min, max] = std::minmax_element(begin(document_camera_zoom_levels), end(document_camera_zoom_levels));
   float range = *max - *min;
   return (document_camera.get_zoom().x - *min) / (range);
}

ALLEGRO_FONT* WorldMapViewer::obtain_font()
{
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::obtain_font]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::obtain_font: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::obtain_font]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::obtain_font: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[WorldMapViewer::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapViewer::obtain_font: error: guard \"font_bin\" not met");
   }
   static const std::string FONT_IDENTIFIER = "Inter-Medium.ttf -36";
   ALLEGRO_FONT* result_font = font_bin->operator[](FONT_IDENTIFIER);
   return result_font;
}


} // namespace Elements
} // namespace AllegroFlare


