

#include <AllegroFlare/Screens/Subscreen/Element.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Screens/Subscreen/Panes/Base.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{
namespace Subscreen
{


Element::Element(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , panes()
   , background_bitmap(nullptr)
   , current_pane_cursor_pos(0)
   , pane_camera()
   , pane_camera_edge_bonk_depth(30.0f)
   , pane_camera_dest_x_pos(0)
   , hud_camera()
   , black_bar_opacity(0.7)
   , initialized(false)
{
}


Element::~Element()
{
}


void Element::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (get_initialized()) throw std::runtime_error("[Element::set_bitmap_bin]: error: guard \"get_initialized()\" not met.");
   this->bitmap_bin = bitmap_bin;
}


void Element::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (get_initialized()) throw std::runtime_error("[Element::set_font_bin]: error: guard \"get_initialized()\" not met.");
   this->font_bin = font_bin;
}


void Element::set_panes(std::vector<AllegroFlare::Screens::Subscreen::Panes::Base*> panes)
{
   if (get_initialized()) throw std::runtime_error("[Element::set_panes]: error: guard \"get_initialized()\" not met.");
   this->panes = panes;
}


void Element::set_background_bitmap(ALLEGRO_BITMAP* background_bitmap)
{
   this->background_bitmap = background_bitmap;
}


void Element::set_black_bar_opacity(float black_bar_opacity)
{
   this->black_bar_opacity = black_bar_opacity;
}


AllegroFlare::BitmapBin* Element::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* Element::get_font_bin() const
{
   return font_bin;
}


std::vector<AllegroFlare::Screens::Subscreen::Panes::Base*> Element::get_panes() const
{
   return panes;
}


ALLEGRO_BITMAP* Element::get_background_bitmap() const
{
   return background_bitmap;
}


float Element::get_black_bar_opacity() const
{
   return black_bar_opacity;
}


bool Element::get_initialized() const
{
   return initialized;
}


std::vector<AllegroFlare::Screens::Subscreen::Panes::Base*> &Element::get_panes_ref()
{
   return panes;
}


void Element::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Element::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Element::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Element::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Element::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Element::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Element::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Element::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Element::initialize]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Element::initialize]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Element::initialize]: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Element::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Element::initialize]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Element::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Element::initialize]: error: guard \"font_bin\" not met");
   }
   //rap_sheets_pane = new CatDetective::Chronicle::Panes::RapSheets();
   //rap_sheets_pane->set_bitmap_bin(bitmap_bin);
   //rap_sheets_pane->set_font_bin(font_bin);
   //rap_sheets_pane->set_rap_sheets_inventory(rap_sheets_inventory);
   //rap_sheets_pane->set_rap_sheets_inventory_dictionary(rap_sheets_inventory_dictionary);
   //rap_sheets_pane->initialize();

   //evidence_sheet_pane = new CatDetective::Chronicle::Panes::EvidenceSheet();
   //evidence_sheet_pane->set_bitmap_bin(bitmap_bin);
   //evidence_sheet_pane->set_font_bin(font_bin);
   //evidence_sheet_pane->set_evidence_sheet_inventory(evidence_sheet_inventory);
   //evidence_sheet_pane->set_evidence_sheet_inventory_dictionary(evidence_sheet_inventory_dictionary);
   //evidence_sheet_pane->initialize();

   //crime_summary_pane = new CatDetective::Chronicle::Panes::CrimeSummary();
   //crime_summary_pane->set_bitmap_bin(bitmap_bin);
   //crime_summary_pane->set_font_bin(font_bin);
   //crime_summary_pane->initialize();

   //panes = { rap_sheets_pane, evidence_sheet_pane, crime_summary_pane };

   initialized = true;
   return;
}

void Element::refresh()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Element::refresh]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Element::refresh]: error: guard \"initialized\" not met");
   }
   // TODO: Refresh all panes. This might be used for example when inventory count changes during gameplay, but the
   // UI does not refresh in real-time in the subscreen as a consequence. UI may become stale if its not live-synced.

   //rap_sheets_pane->refresh();
   //evidence_sheet_pane->refresh();
   //crime_summary_pane->reset();
   return;
}

AllegroFlare::Screens::Subscreen::Panes::Base* Element::find_pane_by_name(std::string pane_name)
{
   // TODO: This technique currently works to find the pane by the name (e.g. same variable for title currently).
   // This would break in different languages, eventually an identifier should be used instead, however it's unclear
   // if the identifier should be stored on the pane, or here in the panes<> by changing it to a tsl::ordered_map
   std::vector<AllegroFlare::Screens::Subscreen::Panes::Base*> matching_panes;
   for (auto &pane : panes)
   {
      if (pane->get_name() == pane_name) matching_panes.push_back(pane);
   }
   if (matching_panes.empty()) return nullptr;
   if (matching_panes.size() > 1)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Screens::Subscreen::Screen",
         "When looking for the pane named \"" + pane_name + "\", there was more than one. It's expected that "
            "only one should be present."
      );
   }
   return matching_panes[0];
}

bool Element::move_pane_right()
{
   if (current_pane_cursor_pos >= (panes.size() - 1))
   {
      // do nothing
      // TODO: maybe play a bonk sound or something
      // Have the camera do a "edge bonk" motion
      pane_camera_dest_x_pos = 1920 * (panes.size() - 1);
      pane_camera.position.x = pane_camera_dest_x_pos + pane_camera_edge_bonk_depth;
      return false;
   }

   //CatDetective::Chronicle::Panes::Base* currently_active_pane = nullptr;
   AllegroFlare::Screens::Subscreen::Panes::Base* currently_active_pane = nullptr;
   currently_active_pane = infer_currently_active_pane();
   if (currently_active_pane) currently_active_pane->on_switch_out();
   current_pane_cursor_pos++;
   currently_active_pane = infer_currently_active_pane();
   if (currently_active_pane) currently_active_pane->on_switch_in();

   pane_camera_dest_x_pos += 1920;
   return true;
}

bool Element::move_pane_left()
{
   if (current_pane_cursor_pos <= 0)
   {
      // do nothing
      // TODO: maybe play a bonk sound or something
      // Have the camera do a "edge bonk" motion
      pane_camera_dest_x_pos = 0;
      pane_camera.position.x = pane_camera_dest_x_pos - pane_camera_edge_bonk_depth;
      return false;
   }

   //CatDetective::Chronicle::Panes::Base* currently_active_pane = nullptr;
   AllegroFlare::Screens::Subscreen::Panes::Base* currently_active_pane = nullptr;
   currently_active_pane = infer_currently_active_pane();
   if (currently_active_pane) currently_active_pane->on_switch_out();
   current_pane_cursor_pos--;
   currently_active_pane = infer_currently_active_pane();
   if (currently_active_pane) currently_active_pane->on_switch_in();

   pane_camera_dest_x_pos -= 1920;
   return true;
}

void Element::move_cursor_up()
{
   //CatDetective::Chronicle::Panes::Base* currently_active_pane = infer_currently_active_pane();
   AllegroFlare::Screens::Subscreen::Panes::Base* currently_active_pane = nullptr;
   if (!currently_active_pane) return;

   //if (currently_active_pane->is_type(CatDetective::Chronicle::Panes::RapSheets::TYPE))
   //{
      //CatDetective::Chronicle::Panes::RapSheets *as_rap_sheets_pane = 
         //static_cast<CatDetective::Chronicle::Panes::RapSheets*>(currently_active_pane);
      //as_rap_sheets_pane->move_cursor_up();
   //}
   //else if (currently_active_pane->is_type(CatDetective::Chronicle::Panes::EvidenceSheet::TYPE))
   //{
      //CatDetective::Chronicle::Panes::EvidenceSheet *as_evidence_sheet_pane =
         //static_cast<CatDetective::Chronicle::Panes::EvidenceSheet*>(currently_active_pane);
      //as_evidence_sheet_pane->move_cursor_up();
   //}

   return;
}

void Element::move_cursor_down()
{
   //CatDetective::Chronicle::Panes::Base* currently_active_pane = infer_currently_active_pane();
   AllegroFlare::Screens::Subscreen::Panes::Base* currently_active_pane = nullptr;
   if (!currently_active_pane) return;

   //if (currently_active_pane->is_type(CatDetective::Chronicle::Panes::RapSheets::TYPE))
   //{
      //CatDetective::Chronicle::Panes::RapSheets *as_rap_sheets_pane =
         //static_cast<CatDetective::Chronicle::Panes::RapSheets*>(currently_active_pane);
      //as_rap_sheets_pane->move_cursor_down();
   //}
   //else if (currently_active_pane->is_type(CatDetective::Chronicle::Panes::EvidenceSheet::TYPE))
   //{
      //CatDetective::Chronicle::Panes::EvidenceSheet *as_evidence_sheet_pane =
         //static_cast<CatDetective::Chronicle::Panes::EvidenceSheet*>(currently_active_pane);
      //as_evidence_sheet_pane->move_cursor_down();
   //}

   return;
}

void Element::move_cursor_right()
{
   //CatDetective::Chronicle::Panes::Base* currently_active_pane = infer_currently_active_pane();
   AllegroFlare::Screens::Subscreen::Panes::Base* currently_active_pane = nullptr;
   if (!currently_active_pane) return;

   //if (currently_active_pane->is_type(CatDetective::Chronicle::Panes::RapSheets::TYPE))
   //{
      //CatDetective::Chronicle::Panes::RapSheets *as_rap_sheets_pane =
         //static_cast<CatDetective::Chronicle::Panes::RapSheets*>(currently_active_pane);
      //as_rap_sheets_pane->move_cursor_right();
   //}

   return;
}

void Element::move_cursor_left()
{
   //CatDetective::Chronicle::Panes::Base* currently_active_pane = infer_currently_active_pane();
   AllegroFlare::Screens::Subscreen::Panes::Base* currently_active_pane = nullptr;
   if (!currently_active_pane) return;

   //if (currently_active_pane->is_type(CatDetective::Chronicle::Panes::RapSheets::TYPE))
   //{
      //CatDetective::Chronicle::Panes::RapSheets *as_rap_sheets_pane =
         //static_cast<CatDetective::Chronicle::Panes::RapSheets*>(currently_active_pane);
      //as_rap_sheets_pane->move_cursor_left();
   //}

   return;
}

void Element::pane_camera_zoom_in()
{
   //CatDetective::Chronicle::Panes::Base* currently_active_pane = infer_currently_active_pane();
   AllegroFlare::Screens::Subscreen::Panes::Base* currently_active_pane = nullptr;
   if (!currently_active_pane) return;

   //if (currently_active_pane->is_type(CatDetective::Chronicle::Panes::CrimeSummary::TYPE))
   //{
      //CatDetective::Chronicle::Panes::CrimeSummary *as_crime_summary_pane =
         //static_cast<CatDetective::Chronicle::Panes::CrimeSummary*>(currently_active_pane);
      //as_crime_summary_pane->step_zoom_in();
   //}

   return;
}

void Element::pane_camera_zoom_out()
{
   //CatDetective::Chronicle::Panes::Base* currently_active_pane = infer_currently_active_pane();
   AllegroFlare::Screens::Subscreen::Panes::Base* currently_active_pane = nullptr;
   if (!currently_active_pane) return;

   //if (currently_active_pane->is_type(CatDetective::Chronicle::Panes::CrimeSummary::TYPE))
   //{
      //CatDetective::Chronicle::Panes::CrimeSummary *as_crime_summary_pane =
         //static_cast<CatDetective::Chronicle::Panes::CrimeSummary*>(currently_active_pane);
      //as_crime_summary_pane->step_zoom_out();
   //}

   return;
}

void Element::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Element::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Element::update]: error: guard \"initialized\" not met");
   }
   // update the camera position
   pane_camera.position.x = (pane_camera_dest_x_pos - pane_camera.position.x) * 0.16 + pane_camera.position.x;

   for (auto &pane : panes)
   {
      pane->update();
   }
   return;
}

void Element::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Element::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Element::render]: error: guard \"initialized\" not met");
   }
   ALLEGRO_STATE previous_render_state;
   al_store_state(&previous_render_state, ALLEGRO_STATE_TARGET_BITMAP);

   render_background();
   render_panes();
   render_hud();

   al_restore_state(&previous_render_state);
   return;
}

void Element::render_background()
{
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Element::render_background]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Element::render_background]: error: guard \"al_get_current_display()\" not met");
   }
   if (!background_bitmap) return;
   al_draw_scaled_bitmap(
      background_bitmap,
      0,
      0,
      al_get_bitmap_width(background_bitmap),
      al_get_bitmap_height(background_bitmap),
      0,
      0,
      1920, //al_get_display_width(al_get_current_display()),
      1080, //al_get_bitmap_height(al_get_current_display()),
      0
   );
   return;
}

void Element::render_panes()
{
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Element::render_panes]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Element::render_panes]: error: guard \"al_get_current_display()\" not met");
   }
   // TODO: Obtain and use a render surface rather than a direct access to the backbuffer

   pane_camera.setup_dimensional_projection(al_get_backbuffer(al_get_current_display()));
   pane_camera.start_reverse_transform();
   AllegroFlare::Placement2D pane_transform;
   for (auto &pane : panes)
   {
      pane_transform.start_transform();
      //pane.second->render();
      pane->render();
      pane_transform.restore_transform();
      pane_transform.position.x += 1920;
   }
   pane_camera.restore_transform();
   return;
}

void Element::render_black_bars()
{
   ALLEGRO_COLOR black_bar_color = ALLEGRO_COLOR{0, 0, 0, black_bar_opacity};
   al_draw_filled_rectangle(0, 0,        1920, BLACK_BARS_HEIGHT,  black_bar_color);
   al_draw_filled_rectangle(0, 1080-BLACK_BARS_HEIGHT, 1920, 1080, black_bar_color);
   return;
}

void Element::render_hud()
{
   // TODO: Obtain and use a render surface rather than a direct access to the backbuffer
   // Setup the projection
   hud_camera.setup_dimensional_projection(al_get_backbuffer(al_get_current_display()));

   render_black_bars();
   render_tabs();

   return;
}

void Element::render_tabs()
{
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Element::render_tabs]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Element::render_tabs]: error: guard \"al_get_current_display()\" not met");
   }
   int num_tabs = infer_num_panes();
   if (num_tabs <= 0) return;

   // render each tab
   ALLEGRO_FONT *tabs_font = obtain_tabs_font();
   int tab_window_padding = 400;
   int text_anchor_x = 1920 / 2 - tab_window_padding;
   int text_anchor_y = 1080 / 32;


   //int tab_spacing = (1920 - tab_window_padding * 2) / num_tabs;
   int tab_spacing = 0;
   if (num_tabs == 1)
   {
      text_anchor_x = 1920 / 2;
   }
   else if (num_tabs > 1)
   {
      tab_spacing = (tab_window_padding * 2) / (num_tabs - 1);
   }


   bool pane_is_focused = false;
   static ALLEGRO_COLOR unfocused_tab_text_color = ALLEGRO_COLOR{0.6, 0.6, 0.6, 0.6};
   static ALLEGRO_COLOR focused_tab_text_color = ALLEGRO_COLOR{1, 1, 1, 1};
   ALLEGRO_COLOR tab_text_color; // no initial assignment necessary
   int tab_num = 0;
   for (auto &pane : panes)
   {
      int this_pane_index = tab_num;
      std::string pane_label = pane->get_name();
      pane_is_focused = (this_pane_index == current_pane_cursor_pos);
      tab_text_color = pane_is_focused ? focused_tab_text_color : unfocused_tab_text_color;

      float x = text_anchor_x + tab_spacing * tab_num;

      al_draw_text(
         tabs_font,
         tab_text_color,
         x,
         text_anchor_y,
         ALLEGRO_ALIGN_CENTER,
         pane_label.c_str()
      );

      //al_draw_line(x, 0, x, 100, ALLEGRO_COLOR{1, 0, 0, 1}, 1.0);

      tab_num++;
   }
   return;
}

AllegroFlare::Screens::Subscreen::Panes::Base* Element::infer_currently_active_pane()
{
   if (current_pane_cursor_pos < 0) return nullptr;
   if (current_pane_cursor_pos >= panes.size()) return nullptr;
   return panes[current_pane_cursor_pos];
}

int Element::infer_num_panes()
{
   return panes.size();
}

void Element::clear_panes()
{
   return panes.clear();
}

ALLEGRO_FONT* Element::obtain_tabs_font()
{
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Element::obtain_tabs_font]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Element::obtain_tabs_font]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Element::obtain_tabs_font]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Element::obtain_tabs_font]: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Subscreen::Element::obtain_tabs_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Subscreen::Element::obtain_tabs_font]: error: guard \"font_bin\" not met");
   }
   static const std::string FONT_IDENTIFIER = "Inter-Medium.ttf -36";
   ALLEGRO_FONT* result_font = font_bin->operator[](FONT_IDENTIFIER);
   return result_font;
}


} // namespace Subscreen
} // namespace Screens
} // namespace AllegroFlare


