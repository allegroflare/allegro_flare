

#include <AllegroFlare/Elements/Storyboard.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Interpolators.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <algorithm>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


Storyboard::Storyboard(AllegroFlare::FontBin* font_bin, std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages, AllegroFlare::Elements::Backgrounds::Base* background)
   : font_bin(font_bin)
   , pages(pages)
   , background(background)
   , button_font_size(-60)
   , current_page_num(0)
   , can_advance_to_next_page(false)
   , can_advance_started_at(0)
   , finished(false)
{
}


Storyboard::~Storyboard()
{
}


void Storyboard::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Storyboard::set_pages(std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages)
{
   this->pages = pages;
}


void Storyboard::set_background(AllegroFlare::Elements::Backgrounds::Base* background)
{
   this->background = background;
}


void Storyboard::set_button_font_size(int button_font_size)
{
   this->button_font_size = button_font_size;
}


std::vector<AllegroFlare::Elements::StoryboardPages::Base *> Storyboard::get_pages() const
{
   return pages;
}


AllegroFlare::Elements::Backgrounds::Base* Storyboard::get_background() const
{
   return background;
}


int Storyboard::get_button_font_size() const
{
   return button_font_size;
}


intptr_t Storyboard::get_current_page_num() const
{
   return current_page_num;
}


bool Storyboard::get_can_advance_to_next_page() const
{
   return can_advance_to_next_page;
}


float Storyboard::get_can_advance_started_at() const
{
   return can_advance_started_at;
}


bool Storyboard::get_finished() const
{
   return finished;
}


void Storyboard::update()
{
   if (background) background->update();

   AllegroFlare::Elements::StoryboardPages::Base* current_page = infer_current_page();
   if (!current_page) return;
   current_page->update();
   if (!can_advance_to_next_page && current_page->get_finished())
   {
      permit_advancing_page();
   }
   return;
}

void Storyboard::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Storyboard::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Storyboard::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Storyboard::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Storyboard::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (background) background->render();

   AllegroFlare::Elements::StoryboardPages::Base* current_page = infer_current_page();
   if (!current_page) return;
   current_page->render();

   if (can_advance_to_next_page) render_next_button();

   return;
}

void Storyboard::reset()
{
   if (background) background->activate(); // TODO: Consider if this needs to be replaced with "show()"

   current_page_num = 0;
   finished = false;
   deny_advancing_page();

   AllegroFlare::Elements::StoryboardPages::Base* current_page = infer_current_page();
   if (current_page) current_page->start();

   return;
}

bool Storyboard::permit_advancing_page()
{
   if (finished) return false;
   if (can_advance_to_next_page) return true;

   can_advance_to_next_page = true;
   can_advance_started_at = al_get_time();
   return true;
}

bool Storyboard::deny_advancing_page()
{
   if (finished) return false;
   can_advance_to_next_page = false;
   can_advance_started_at = 0;
   return true;
}

bool Storyboard::advance()
{
   AllegroFlare::Elements::StoryboardPages::Base* current_page = infer_current_page();
   if (!current_page) return false;
   if (finished) return false;

   if (can_advance_to_next_page)
   {
      if (infer_at_last_page() && current_page->get_finished())
      {
         // Storyboard is finished
         deny_advancing_page();
         finished = true;
         return true;
      }
      else
      {
         advance_page();
         return true;
      }
   }
   else
   {
      // Advance within the current page
      current_page->advance();
      if (current_page->get_finished()) permit_advancing_page();
      return true;
   }

   return false;
}

bool Storyboard::advance_page()
{
   if (!can_advance_to_next_page) return false;
   current_page_num++;
   AllegroFlare::Elements::StoryboardPages::Base* newly_advanced_page = infer_current_page();
   if (newly_advanced_page) newly_advanced_page->start();
   deny_advancing_page();
   return true;
}

void Storyboard::render_next_button()
{
   float x = 1920-400;
   float y = 1080-300;
   float age = al_get_time() - can_advance_started_at;
   ALLEGRO_FONT *next_button_font = obtain_next_button_font();
   ALLEGRO_COLOR button_color = AllegroFlare::Color::PaleGreen;
   std::string text = "NEXT >";
   if (infer_at_last_advance())
   {
      button_color = AllegroFlare::Color::LemonChiffon;
      text = "FINISH";
   }
   float text_width = al_get_text_width(next_button_font, text.c_str());
   float text_height = al_get_font_line_height(next_button_font);
   ALLEGRO_COLOR button_text_color = button_color;
   float button_frame_opacity = ((1.5 - fmod(age, 1.5)) / 1.5) * 0.75 + 0.25;
   ALLEGRO_COLOR button_frame_color = AllegroFlare::color::mix(
         button_color, AllegroFlare::Color::Transparent, 1.0 - button_frame_opacity);
   float thickness = 4.0f;
   float roundness = thickness * 1.5;
   float padding_x = 32.0f;
   float padding_y = 12.0f;
   AllegroFlare::Placement2D button_place;
   button_place.position.x = x;
   button_place.position.y = y;

   float reveal_duration = 0.6f;
   if (age < reveal_duration)
   {
      // modify params by the reveal animation offsets
      float normalized_time = std::max(0.0f, std::min(1.0f, age / reveal_duration));
      float inv_normalized_time = 1.0 - normalized_time;
      float reveal_y_offset = 30;
      //float reveal_opacity = 0.5;
      //ALLEGRO_COLOR reveal_color = AllegroFlare::Color::Indigo;
      ALLEGRO_COLOR reveal_color = AllegroFlare::Color::Transparent;

      button_text_color = AllegroFlare::color::mix(
            reveal_color, button_text_color, normalized_time);
      button_frame_color = AllegroFlare::color::mix(
            reveal_color, button_frame_color, normalized_time);
      button_place.position.y += reveal_y_offset * AllegroFlare::interpolator::tripple_fast_out(inv_normalized_time);
   }

   button_place.start_transform();

   // draw the cursor outline
   al_draw_rounded_rectangle(
      -padding_x,
      -padding_y,
      text_width+padding_x,
      text_height+padding_y,
      roundness,
      roundness,
      button_frame_color,
      thickness
   );

   // draw the text
   al_draw_text(next_button_font, button_text_color, text_width/2, 0, ALLEGRO_ALIGN_CENTER, text.c_str());

   button_place.restore_transform();

   return;
}

bool Storyboard::infer_has_no_pages()
{
   return pages.empty();
}

bool Storyboard::infer_at_last_page()
{
   return (current_page_num == (pages.size()-1));
}

bool Storyboard::infer_at_or_past_last_page()
{
   return (current_page_num >= (pages.size()-1));
}

bool Storyboard::infer_at_last_advance()
{
   AllegroFlare::Elements::StoryboardPages::Base* current_page = infer_current_page();
   if (!current_page) return false;
   return infer_at_last_page() && current_page->get_finished();
}

AllegroFlare::Elements::StoryboardPages::Base* Storyboard::infer_current_page()
{
   if (current_page_num < 0 || current_page_num >= pages.size()) return nullptr;
   return pages[current_page_num];
}

ALLEGRO_FONT* Storyboard::obtain_next_button_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Storyboard::obtain_next_button_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Storyboard::obtain_next_button_font]: error: guard \"font_bin\" not met");
   }
   std::string font_name = "Inter-Regular.ttf";
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << button_font_size+20;
   return font_bin->auto_get(composite_font_str.str());
}


} // namespace Elements
} // namespace AllegroFlare


