

#include <AllegroFlare/Elements/Inventory.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Interpolators.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


Inventory::Inventory(AllegroFlare::FontBin* font_bin, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::Inventory* af_inventory, AllegroFlare::InventoryIndex* inventory_index, AllegroFlare::EventEmitter* event_emitter)
   : font_bin(font_bin)
   , bitmap_bin(bitmap_bin)
   , af_inventory(af_inventory)
   , inventory_index(inventory_index)
   , event_emitter(event_emitter)
   , place({ 1920/2, 1080/2, 1300, 700 })
   , cursor_x(0)
   , cursor_y(0)
   , num_columns(4)
   , num_rows(3)
   , active(false)
   , details_reveal_counter(0.0f)
   , details_num_revealed_characters(999)
   , reveal_counter(0)
   , item_in_details_pane(0)
   , item_in_details_pane_set_at(-999)
   , inventory_items_left_padding(80.0f)
   , inventory_items_top_padding(80.0f)
   , inventory_items_box_size_x(150.0)
   , inventory_items_box_size_y(150.0)
   , inventory_items_box_gutter_x(20.0f)
   , inventory_items_box_gutter_y(20.0f)
   , cursor_move_sound_identifier("menu-click-01.ogg")
   , show_background(false)
   , show_backframe(true)
   , show_title_text(true)
   , inventory_show_sound_identifier("")
   , inventory_hide_sound_identifier("")
   , sound_is_disabled(false)
{
}


Inventory::~Inventory()
{
}


void Inventory::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Inventory::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void Inventory::set_af_inventory(AllegroFlare::Inventory* af_inventory)
{
   this->af_inventory = af_inventory;
}


void Inventory::set_inventory_index(AllegroFlare::InventoryIndex* inventory_index)
{
   this->inventory_index = inventory_index;
}


void Inventory::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void Inventory::set_place(AllegroFlare::Placement2D place)
{
   this->place = place;
}


void Inventory::set_inventory_items_left_padding(float inventory_items_left_padding)
{
   this->inventory_items_left_padding = inventory_items_left_padding;
}


void Inventory::set_inventory_items_top_padding(float inventory_items_top_padding)
{
   this->inventory_items_top_padding = inventory_items_top_padding;
}


void Inventory::set_inventory_items_box_size_x(float inventory_items_box_size_x)
{
   this->inventory_items_box_size_x = inventory_items_box_size_x;
}


void Inventory::set_inventory_items_box_size_y(float inventory_items_box_size_y)
{
   this->inventory_items_box_size_y = inventory_items_box_size_y;
}


void Inventory::set_inventory_items_box_gutter_x(float inventory_items_box_gutter_x)
{
   this->inventory_items_box_gutter_x = inventory_items_box_gutter_x;
}


void Inventory::set_inventory_items_box_gutter_y(float inventory_items_box_gutter_y)
{
   this->inventory_items_box_gutter_y = inventory_items_box_gutter_y;
}


void Inventory::set_cursor_move_sound_identifier(std::string cursor_move_sound_identifier)
{
   this->cursor_move_sound_identifier = cursor_move_sound_identifier;
}


void Inventory::set_show_background(bool show_background)
{
   this->show_background = show_background;
}


void Inventory::set_show_backframe(bool show_backframe)
{
   this->show_backframe = show_backframe;
}


void Inventory::set_show_title_text(bool show_title_text)
{
   this->show_title_text = show_title_text;
}


void Inventory::set_inventory_show_sound_identifier(std::string inventory_show_sound_identifier)
{
   this->inventory_show_sound_identifier = inventory_show_sound_identifier;
}


void Inventory::set_inventory_hide_sound_identifier(std::string inventory_hide_sound_identifier)
{
   this->inventory_hide_sound_identifier = inventory_hide_sound_identifier;
}


AllegroFlare::Placement2D Inventory::get_place() const
{
   return place;
}


int Inventory::get_cursor_x() const
{
   return cursor_x;
}


int Inventory::get_cursor_y() const
{
   return cursor_y;
}


int Inventory::get_num_columns() const
{
   return num_columns;
}


int Inventory::get_num_rows() const
{
   return num_rows;
}


bool Inventory::get_active() const
{
   return active;
}


int Inventory::get_item_in_details_pane() const
{
   return item_in_details_pane;
}


float Inventory::get_item_in_details_pane_set_at() const
{
   return item_in_details_pane_set_at;
}


float Inventory::get_inventory_items_left_padding() const
{
   return inventory_items_left_padding;
}


float Inventory::get_inventory_items_top_padding() const
{
   return inventory_items_top_padding;
}


float Inventory::get_inventory_items_box_size_x() const
{
   return inventory_items_box_size_x;
}


float Inventory::get_inventory_items_box_size_y() const
{
   return inventory_items_box_size_y;
}


float Inventory::get_inventory_items_box_gutter_x() const
{
   return inventory_items_box_gutter_x;
}


float Inventory::get_inventory_items_box_gutter_y() const
{
   return inventory_items_box_gutter_y;
}


std::string Inventory::get_cursor_move_sound_identifier() const
{
   return cursor_move_sound_identifier;
}


bool Inventory::get_show_background() const
{
   return show_background;
}


bool Inventory::get_show_backframe() const
{
   return show_backframe;
}


bool Inventory::get_show_title_text() const
{
   return show_title_text;
}


std::string Inventory::get_inventory_show_sound_identifier() const
{
   return inventory_show_sound_identifier;
}


std::string Inventory::get_inventory_hide_sound_identifier() const
{
   return inventory_hide_sound_identifier;
}


bool Inventory::get_sound_is_disabled() const
{
   return sound_is_disabled;
}


AllegroFlare::Placement2D &Inventory::get_place_ref()
{
   return place;
}


void Inventory::update()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "Inventory" << "::" << "update" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "Inventory" << "::" << "update" << ": error: " << "guard \"bitmap_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(af_inventory))
   {
      std::stringstream error_message;
      error_message << "Inventory" << "::" << "update" << ": error: " << "guard \"af_inventory\" not met";
      throw std::runtime_error(error_message.str());
   }
   float reveal_speed = (1.0f/60.0f) * 4;  // 60 fps
   if (active) reveal_counter += reveal_speed;
   else reveal_counter -= reveal_speed;
   if (reveal_counter < 0.0) reveal_counter = 0.0;
   if (reveal_counter >= 1.0) reveal_counter = 1.0;

   float details_reveal_speed = (1.0f/60.0f) * 4;  // 60 fps
   details_reveal_counter += details_reveal_speed;
   if (details_reveal_counter >= 1.0) details_reveal_counter = 1.0;

   details_num_revealed_characters += 2;
   if (details_num_revealed_characters > 999) details_num_revealed_characters = 999;
   return;
}

void Inventory::activate()
{
   active = true;
   reveal_counter = 1.0;
   details_num_revealed_characters = 999;
   details_reveal_counter = 1.0;
   set_details_pane();
   return;
}

void Inventory::deactivate()
{
   active = false;
   reveal_counter = 0.0;
   details_num_revealed_characters = 0;
   details_reveal_counter = 0.0;
   return;
}

bool Inventory::show()
{
   if (active) return false;
   active = true;
   details_reveal_counter = 0.0f;
   details_num_revealed_characters = 0;
   set_details_pane();
   play_hide_inventory_sound();
   return active;
}

bool Inventory::hide()
{
   if (!active) return false;
   active = false;
   play_hide_inventory_sound();
   return active;
}

void Inventory::toggle_show_hide()
{
   if (!active) show();
   else hide();
   return;
}

void Inventory::move_cursor_up()
{
   if (!(has_valid_size()))
   {
      std::stringstream error_message;
      error_message << "Inventory" << "::" << "move_cursor_up" << ": error: " << "guard \"has_valid_size()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!active) return;
   cursor_y--;
   while(cursor_y < 0) cursor_y += num_rows;
   details_reveal_counter = 0.0f;
   details_num_revealed_characters = 0;
   set_details_pane();
   play_move_cursor_sound();
   return;
}

void Inventory::move_cursor_down()
{
   if (!(has_valid_size()))
   {
      std::stringstream error_message;
      error_message << "Inventory" << "::" << "move_cursor_down" << ": error: " << "guard \"has_valid_size()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!active) return;
   cursor_y++;
   cursor_y = cursor_y % num_rows;
   details_reveal_counter = 0.0f;
   details_num_revealed_characters = 0;
   set_details_pane();
   play_move_cursor_sound();
   return;
}

void Inventory::move_cursor_left()
{
   if (!(has_valid_size()))
   {
      std::stringstream error_message;
      error_message << "Inventory" << "::" << "move_cursor_left" << ": error: " << "guard \"has_valid_size()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!active) return;
   cursor_x--;
   while(cursor_x < 0) cursor_x += num_columns;
   details_reveal_counter = 0.0f;
   details_num_revealed_characters = 0;
   set_details_pane();
   play_move_cursor_sound();
   return;
}

void Inventory::move_cursor_right()
{
   if (!(has_valid_size()))
   {
      std::stringstream error_message;
      error_message << "Inventory" << "::" << "move_cursor_right" << ": error: " << "guard \"has_valid_size()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!active) return;
   cursor_x++;
   cursor_x = cursor_x % num_columns;
   details_reveal_counter = 0.0f;
   details_num_revealed_characters = 0;
   set_details_pane();
   play_move_cursor_sound();
   return;
}

void Inventory::disable_sound()
{
   sound_is_disabled = true;
   return;
}

void Inventory::enable_sound()
{
   sound_is_disabled = false;
   return;
}

bool Inventory::is_sound_disabled()
{
   return sound_is_disabled;
}

bool Inventory::is_sound_enabled()
{
   return !sound_is_disabled;
}

void Inventory::set_num_columns(int num_columns)
{
   if (!(num_columns > 0))
   {
      std::stringstream error_message;
      error_message << "Inventory" << "::" << "set_num_columns" << ": error: " << "guard \"num_columns > 0\" not met";
      throw std::runtime_error(error_message.str());
   }
   this->num_columns = num_columns;
   cursor_x = 0;
   cursor_y = 0;
   set_details_pane();
   return;
}

void Inventory::set_num_rows(int num_rows)
{
   if (!(num_rows > 0))
   {
      std::stringstream error_message;
      error_message << "Inventory" << "::" << "set_num_rows" << ": error: " << "guard \"num_rows > 0\" not met";
      throw std::runtime_error(error_message.str());
   }
   this->num_rows = num_rows;
   cursor_x = 0;
   cursor_y = 0;
   set_details_pane();
   return;
}

void Inventory::set_details_pane()
{
   if (!af_inventory) return;
   int cursor_position_abs = cursor_y * num_columns + cursor_x;
   if (cursor_position_abs >= af_inventory->get_items_ref().size()) item_in_details_pane = 0;
   else item_in_details_pane = af_inventory->get_items_ref()[cursor_position_abs];
   item_in_details_pane_set_at = al_get_time();
   return;
}

ALLEGRO_COLOR Inventory::opaquify(ALLEGRO_COLOR color)
{
   float alpha = reveal_counter;
      color.a *= alpha;
      color.r *= color.a;
      color.g *= color.a;
      color.b *= color.a;
   return color;
}

ALLEGRO_COLOR Inventory::change_a(ALLEGRO_COLOR color, float alpha)
{
   color.a *= alpha;
   color.r *= color.a;
   color.g *= color.a;
   color.b *= color.a;
   return color;
}

float Inventory::inv_reveal_counter()
{
   return 1.0 - reveal_counter;
}

void Inventory::render()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "Inventory" << "::" << "render" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "Inventory" << "::" << "render" << ": error: " << "guard \"bitmap_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(af_inventory))
   {
      std::stringstream error_message;
      error_message << "Inventory" << "::" << "render" << ": error: " << "guard \"af_inventory\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (reveal_counter <= 0.001) return;

   AllegroFlare::Placement2D time_based_place = place;
   time_based_place.position.y = place.position.y +
      80 * (1.0 - AllegroFlare::interpolator::fast_in(reveal_counter));

   time_based_place.start_transform();

   if (show_background) draw_background();
   if (show_backframe) draw_backframe();
   if (show_title_text) draw_title_text();
   draw_inventory_boxes();
   draw_item_selection_cursor();
   draw_inventory_items();
   draw_details_frame();

   time_based_place.restore_transform();

   return;
}

void Inventory::draw_background()
{
   al_clear_to_color(al_color_name("dodgerblue"));
   return;
}

void Inventory::draw_backframe()
{
   float o = 0.95f;
   ALLEGRO_COLOR right_backfill_color = opaquify(change_a(al_color_html("11111d"), o));
   ALLEGRO_COLOR left_overbackfill_color = opaquify(change_a(al_color_html("16151c"), o));
   ALLEGRO_COLOR top_and_bottom_pin_line_color = opaquify(change_a(ALLEGRO_COLOR{0.6, 0.6, 0.6, 1.0}, o));

   // backfill
   al_draw_filled_rectangle(800, 0, place.size.x, place.size.y, right_backfill_color);

   // left "overbackfill"
   al_draw_filled_rectangle(0, 0, 800, place.size.y, left_overbackfill_color);

   // top and bottom pin lines
   al_draw_line(0, 0, place.size.x, 0, top_and_bottom_pin_line_color, 2.0);
   al_draw_line(0, place.size.y, place.size.x, place.size.y, top_and_bottom_pin_line_color, 2.0);
   return;
}

void Inventory::draw_title_text()
{
   ALLEGRO_FONT *font = obtain_title_font();
   ALLEGRO_COLOR color = opaquify(ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0});
   al_draw_text(font, color, 0, -50, ALLEGRO_ALIGN_LEFT, "I N V E N T O R Y");
   return;
}

void Inventory::draw_inventory_items()
{
   std::vector<int> items_in_inventory = af_inventory->get_items_ref();

   float x = inventory_items_left_padding;
   float y = inventory_items_top_padding;
   float spacing_x = inventory_items_box_gutter_x + inventory_items_box_size_x;
   float spacing_y = inventory_items_box_gutter_y + inventory_items_box_size_y;

   int inventory_position = 0;
   for (unsigned row=0; row<num_rows; row++)
   {
      for (unsigned column=0; column<num_columns; column++)
      {
         int item_to_draw = 0;
         if (inventory_position >= items_in_inventory.size()) {}
         else { item_to_draw = items_in_inventory[inventory_position]; }

         draw_inventory_item(x + column * spacing_x, y + row * spacing_y, item_to_draw);
         inventory_position++;
      }
   }
   return;
}

void Inventory::draw_inventory_boxes()
{
   std::vector<int> items_in_inventory = af_inventory->get_items_ref();

   float x = inventory_items_left_padding;
   float y = inventory_items_top_padding;
   float spacing_x = inventory_items_box_gutter_x + inventory_items_box_size_x;
   float spacing_y = inventory_items_box_gutter_y + inventory_items_box_size_y;

   for (unsigned row=0; row<num_rows; row++)
   {
      for (unsigned column=0; column<num_columns; column++)
      {
         draw_inventory_box(x + column * spacing_x, y + row * spacing_y);
      }
   }
   return;
}

void Inventory::draw_details_frame()
{
   ALLEGRO_COLOR revealed_white = opaquify(ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0});

   std::tuple<std::string, std::string, std::string> item_definition = get_item_definition(item_in_details_pane);
   bool contains_item = !std::get<0>(item_definition).empty();
   if (!contains_item) return;

   std::string item_name = std::get<0>(item_definition);
   std::string item_bitmap_identifier = std::get<1>(item_definition);
   std::string item_description = std::get<2>(item_definition);


   // draw the item
   //

   ALLEGRO_BITMAP *item_bitmap = bitmap_bin->auto_get(item_bitmap_identifier);
   if (!item_bitmap) {} // TODO: draw missing item graphic

   // setup the graphic positioning and scale
   AllegroFlare::Placement2D box_place;
   box_place.position.x = 1025;
   box_place.position.y = 290;
   box_place.size.x = al_get_bitmap_width(item_bitmap);
   box_place.size.y = al_get_bitmap_height(item_bitmap);
   box_place.scale.x = 1.0f;
   box_place.scale.y = 1.0f;

   // stretch the position to fit the intended width/height
   float intended_width = 380.0f;
   float fit_scale = intended_width / al_get_bitmap_width(item_bitmap);
   box_place.scale.x = fit_scale;
   box_place.scale.y = fit_scale;

   // filter the dimentions for animation
   box_place.position.y = box_place.position.y +
      50 * (1.0 - AllegroFlare::interpolator::fast_in(details_reveal_counter));
   float scale_reveal_multiplier = 0.94 + 0.06 * (AllegroFlare::interpolator::fast_in(details_reveal_counter));
   box_place.scale.x = box_place.scale.x * scale_reveal_multiplier;
   box_place.scale.y = box_place.scale.y * scale_reveal_multiplier;

   // draw the bitmap
   box_place.start_transform();
   al_draw_tinted_bitmap(item_bitmap, revealed_white, 0, 0, 0);
   box_place.restore_transform();


   // draw the item name
   //

   ALLEGRO_FONT* font = obtain_details_header_font();
   float details_header_reveal_offset = 60 * (1.0 - AllegroFlare::interpolator::fast_in(details_reveal_counter));
   al_draw_text(
      font,
      opaquify(ALLEGRO_COLOR{details_reveal_counter, details_reveal_counter, details_reveal_counter, details_reveal_counter}),
      850 + details_header_reveal_offset,
      85,
      ALLEGRO_ALIGN_LEFT,
      item_name.c_str()
   );


   // draw multiline description
   //

   float x = 820;
   float y = 430;
   float width = 1300 - 800- 50 + 5;
   //int dialog_box_num_revealed_characters = 999;
   std::string text = item_description; //"This is the details text that will be shown in the right pane.";
   float text_padding_x = 40.0f;
   float text_padding_y = 30.0f;
   float text_box_max_width = width - (text_padding_x * 2);
   ALLEGRO_FONT* text_font = obtain_description_font();
   float line_height = al_get_font_line_height(text_font) * 1.2;
   ALLEGRO_COLOR text_color = opaquify(al_color_html("ffffff"));

   al_draw_multiline_text(
      text_font,
      text_color,
      x + text_padding_x,
      y + text_padding_y,
      text_box_max_width,
      line_height,
      ALLEGRO_ALIGN_LEFT,
      concat_text(text, details_num_revealed_characters).c_str()
   );
   return;
}

bool Inventory::has_valid_size()
{
   return !(num_columns == 0 || num_rows == 0);
}

void Inventory::draw_item_selection_cursor()
{
   // position
   float x = inventory_items_left_padding;
   float y = inventory_items_top_padding;
   float spacing_x = inventory_items_box_gutter_x + inventory_items_box_size_x;
   float spacing_y = inventory_items_box_gutter_y + inventory_items_box_size_y;

    // color
   ALLEGRO_COLOR color_a = al_color_name("aquamarine");
   ALLEGRO_COLOR color_b = AllegroFlare::color::transparent;
   float speed_multiplier = 0.9;
   float mix_factor = AllegroFlare::interpolator::slow_in(fmod(al_get_time() * speed_multiplier, 1.0));
   ALLEGRO_COLOR color = AllegroFlare::color::mix(color_a, color_b, 0.7 * mix_factor);
   float r = 8;
   float thickness = 6.0;

   al_draw_rounded_rectangle(
      x + cursor_x*spacing_x,
      y + cursor_y*spacing_y,
      x + cursor_x*spacing_x + inventory_items_box_size_x,
      y + cursor_y*spacing_y + inventory_items_box_size_y,
      r,
      r,
      color,
      thickness
   );
   return;
}

void Inventory::draw_inventory_box(float x, float y)
{
   ALLEGRO_COLOR backfill_color = opaquify(ALLEGRO_COLOR{0.0, 0.0, 0.0, 0.4});
   float roundness = 6.0f;

   // draw frame
   al_draw_filled_rounded_rectangle(
         x+0,
         y+0,
         x+inventory_items_box_size_x,
         y+inventory_items_box_size_y,
         roundness,
         roundness,
         backfill_color
      );
   return;
}

void Inventory::draw_inventory_item(float x, float y, int item)
{
   ALLEGRO_COLOR revealed_white = opaquify(ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0});

   std::tuple<std::string, std::string, std::string> item_definition = get_item_definition(item);
   bool contains_item = !std::get<0>(item_definition).empty();
   if (contains_item)
   {
      std::string item_name = std::get<0>(item_definition);
      std::string item_bitmap_identifier = std::get<1>(item_definition); //"watch-01.png";
      ALLEGRO_BITMAP *bitmap = bitmap_bin->auto_get(item_bitmap_identifier);

      if (!bitmap) return; // TODO: draw a [?] placeholder graphic

      //ALLEGRO_COLOR color = ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0};
      //ALLEGRO_FONT *font = obtain_item_name_font();
      //al_draw_text(font, color, x, y + 150 - 20, ALLEGRO_ALIGN_LEFT, item_name.c_str());

      AllegroFlare::Placement2D box_place;
      box_place.position.x = x + inventory_items_box_size_x * 0.5f;
      box_place.position.y = y + inventory_items_box_size_y * 0.5f;
      box_place.size.x = al_get_bitmap_width(bitmap);
      box_place.size.y = al_get_bitmap_height(bitmap);
      box_place.scale.x = 1.0f;
      box_place.scale.y = 1.0f;

      // scale the bitmap to fit the dimentions of the box
      float fit_padding = 3.0f; // extra pixels of padding so the bitmap does not stretch to the whole box
      // NOTE: using "inventory_items_box_size_x" to fit the image to this window for the time beeing. In the future,
      // may select different "fit" strategies, for example, scale-to-fit, stretch-to-fit, etc..
      float fit_scale = (inventory_items_box_size_x-fit_padding*2) / al_get_bitmap_width(bitmap);
      box_place.scale.x = fit_scale;
      box_place.scale.y = fit_scale;

      box_place.start_transform();
      al_draw_tinted_bitmap(bitmap, revealed_white, 0, 0, 0);
      box_place.restore_transform();
   }
   return;
}

std::tuple<std::string, std::string, std::string> Inventory::get_item_definition(int index)
{
   if (!inventory_index) return {};
   if (!inventory_index->exists(index)) return {};
   return inventory_index->at(index).to_tuple();
}

ALLEGRO_FONT* Inventory::obtain_title_font()
{
   return font_bin->auto_get("Inter-Bold.ttf -40");
}

ALLEGRO_FONT* Inventory::obtain_description_font()
{
   return font_bin->auto_get("Inter-Medium.ttf -36");
}

ALLEGRO_FONT* Inventory::obtain_item_name_font()
{
   return font_bin->auto_get("Inter-Bold.ttf -46");
}

ALLEGRO_FONT* Inventory::obtain_details_header_font()
{
   return font_bin->auto_get("Inter-Bold.ttf -48");
}

void Inventory::play_move_cursor_sound()
{
   play_sound(cursor_move_sound_identifier);
   return;
}

void Inventory::play_hide_inventory_sound()
{
   play_sound(inventory_hide_sound_identifier);
   return;
}

void Inventory::play_show_inventory_sound()
{
   play_sound(inventory_show_sound_identifier);
   return;
}

void Inventory::play_sound(std::string sound_identifier)
{
   if (sound_is_disabled) return;
   if (sound_identifier.empty()) return;
   if (!event_emitter)
   {
      std::cout << "[AllegroFlare::Elements::Inventory::play_sound]: ERROR: expecting an event_emitter "
                << "but it is nullptr (when attempting to play \"" << sound_identifier << "\"). You can "
                << "disable sounds with disable_sound() or pass in an event_emitter with set_event_emitter()."
                << std::endl;
   }
   else
   {
      event_emitter->emit_play_sound_effect_event(sound_identifier);
   }
   return;
}

AllegroFlare::InventoryIndex* Inventory::create_placeholder_inventory_index()
{
   AllegroFlare::InventoryIndex *result = new AllegroFlare::InventoryIndex;
   *result = AllegroFlare::InventoryIndex::build_placeholder_inventory_index();
   return result;
}

std::string Inventory::concat_text(std::string source_text, int length)
{
   return source_text.substr(0, length);
}


} // namespace Elements
} // namespace AllegroFlare


