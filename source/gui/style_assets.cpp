

#include <allegro_flare/gui/style_assets.h>

#include <allegro_flare/generate_textures.h>
#include <allegro_flare/image_processing.h>



UIStyleAssets::UIStyleAssets()
   : shade_down_circle_gradient(NULL)
   , shade_down_gradient(NULL)
   , widget_icon(NULL)
   , pixel_pattern_3(NULL)
   , title_font(NULL)
   , text_font(NULL)
   , ui_font(NULL)
   , mini_font(NULL)
   , micro_font(NULL)
{
}



UIStyleAssets::~UIStyleAssets()
{
   al_destroy_bitmap(shade_down_circle_gradient);
   al_destroy_bitmap(shade_down_gradient);
}



UIStyleAssets *UIStyleAssets::get_instance()
{
   if (!instance) instance = new UIStyleAssets();
   return instance;
}




//
// bitmaps
//


ALLEGRO_BITMAP *UIStyleAssets::get_shade_down_circle_gradient()
{
   UIStyleAssets *inst = get_instance();
   if (!inst->shade_down_circle_gradient)
      inst->shade_down_circle_gradient = generate_circle_gradient_bitmap();
   return inst->shade_down_circle_gradient;
}   



ALLEGRO_BITMAP *UIStyleAssets::get_shade_down_gradient()
{
   UIStyleAssets *inst = get_instance();
   if (!inst->shade_down_gradient)
      inst->shade_down_gradient = generate_gradient_bitmap();
   return inst->shade_down_gradient;
}   



ALLEGRO_BITMAP *UIStyleAssets::get_widget_icon()
{
   UIStyleAssets *inst = get_instance();
   if (!inst->widget_icon)
      inst->widget_icon = generate_widget_icon(64, color::white, color::transparent);
   return inst->widget_icon;
}



ALLEGRO_BITMAP *UIStyleAssets::get_pixel_pattern_3()
{
   UIStyleAssets *inst = get_instance();
   if (!inst->pixel_pattern_3)
      inst->pixel_pattern_3 = create_pixel_pattern_3(color::black, color::transparent);
   return inst->pixel_pattern_3;
}




//
// fonts
//


ALLEGRO_FONT *UIStyleAssets::get_title_font()
{
   UIStyleAssets *inst = get_instance();
   if (!inst->title_font)
   {
      inst->title_font = al_load_font("data/fonts/DroidSans.ttf", 28, 0);
      if (!inst->title_font)
      {
         std::cout << "get_title_font(): Could not load font file. using fallback font." << std::endl;
         inst->title_font = al_create_builtin_font();
      } 
   }
   return inst->title_font;
}



ALLEGRO_FONT *UIStyleAssets::get_text_font()
{
   UIStyleAssets *inst = get_instance();
   if (!inst->text_font)
   {
      inst->text_font = al_load_font("data/fonts/DroidSans.ttf", 18, 0);
      if (!inst->text_font)
      {
         std::cout << "get_text_font(): Could not load font file. using fallback font." << std::endl;
         inst->text_font = al_create_builtin_font();
      }
   }
   return inst->text_font;
}



ALLEGRO_FONT *UIStyleAssets::get_ui_font()
{
   UIStyleAssets *inst = get_instance();
   if (!inst->ui_font)
   {
      inst->ui_font = al_load_font("data/fonts/DroidSans.ttf", 15, 0);
      if (!inst->ui_font)
      {
         std::cout << "get_ui_font(): Could not load font file. using fallback font." << std::endl;
         inst->ui_font = al_create_builtin_font();
      } 
   }
   return inst->ui_font;
}



ALLEGRO_FONT *UIStyleAssets::get_mini_font()
{
   UIStyleAssets *inst = get_instance();
   if (!inst->mini_font)
   {
      inst->mini_font = al_load_font("data/fonts/DroidSans.ttf", 14, 0);
      if (!inst->mini_font)
      {
         std::cout << "get_mini_font(): Could not load font file. using fallback font." << std::endl;
         inst->mini_font = al_create_builtin_font();
      } 
   }
   return inst->mini_font;
}



ALLEGRO_FONT *UIStyleAssets::get_micro_font()
{
   UIStyleAssets *inst = get_instance();
   if (!inst->micro_font)
   {
      inst->micro_font = al_load_font("data/fonts/DroidSans.ttf", 10, 0);
      if (!inst->micro_font)
      {
         std::cout << "get_micro_font(): Could not load font file. Using fallback font." << std::endl;
         inst->micro_font = al_create_builtin_font();
      } 
   }
   return inst->micro_font;
}





//
// shapes
//


void UIStyleAssets::draw_inset(float x, float y, float w, float h, ALLEGRO_COLOR col, float roundness)
{
   float border_thickness = 2.0;
   float texture_inset = border_thickness/2;

   // the button face
   al_draw_filled_rounded_rectangle(x, y, x+w, y+h, roundness, roundness, color::mix(color::black, col, 0.95));

   // the button outline
   al_draw_rounded_rectangle(x, y, x+w, y+h, roundness, roundness, color::color(color::black, 0.2), border_thickness);

   // draw the top line shadow
   al_draw_line(x+roundness, y+0.5, x+w-roundness, y+0.5, color::color(color::black, 0.3), 1.0);

   // draw the bottom line hilight
   ALLEGRO_COLOR hilight_color = color::mix(color::white, color::transparent, 0.6);
   al_draw_line(x+roundness, y+h+1.5, x+w-roundness, y+h+1.5, hilight_color, 1.0);
      // left arc
      float arc_unit_amount = 0.8;
      float arc_roundness = roundness + 0.5;
      al_draw_arc(x+arc_roundness/2 + 0.75, y+h+1-arc_roundness/2-0.75, arc_roundness, FULL_ROTATION*0.25, FULL_ROTATION*0.25*arc_unit_amount, hilight_color, 1.0);
      al_draw_arc(x+w-arc_roundness/2 - 0.75, y+h+1-arc_roundness/2-0.75, arc_roundness, FULL_ROTATION*0.25, -FULL_ROTATION*0.25*arc_unit_amount, hilight_color, 1.0);

   // draw the shaded bitmap
   ALLEGRO_BITMAP *shade_down = UIStyleAssets::get_shade_down_gradient();
   draw_stretched_bitmap(x+texture_inset, y+texture_inset, w-texture_inset*2, std::min(20.0f, h-texture_inset*2), shade_down, ALLEGRO_FLIP_VERTICAL, color::color(color::white, 0.05));

   // draw the shade at the top of the button
   int shade_height = 8;
   draw_stretched_bitmap(x+texture_inset, y+texture_inset, w-texture_inset*2, shade_height, shade_down, ALLEGRO_FLIP_VERTICAL, color::color(color::white, 0.1));
}



void UIStyleAssets::draw_outset(float x, float y, float w, float h, ALLEGRO_COLOR col, float roundness)
{
   float border_thickness = 2.0;
   float texture_inset = border_thickness/2;
   ALLEGRO_BITMAP *shade_down = UIStyleAssets::get_shade_down_gradient();

   // draw the shade cast by the button
   int shade_height = 8;
   draw_stretched_bitmap(x+texture_inset, y+h, w-texture_inset*2, shade_height, shade_down, ALLEGRO_FLIP_VERTICAL, color::color(color::white, 0.2));

   // the button face
   al_draw_filled_rounded_rectangle(x, y, x+w, y+h, roundness, roundness, color::mix(color::white, col, 0.93));//color::hex("575962"));

   // draw a hilight along the top
   al_draw_line(x+1, y+1.5, x+w-1, y+1.5, color::color(color::white, 0.1), 1.0);

   // the button outline
   al_draw_rounded_rectangle(x, y, x+w, y+h, roundness, roundness, color::color(color::black, 0.2), border_thickness);

   // draw the shaded bitmap
   draw_stretched_bitmap(x+texture_inset, y+texture_inset, w-texture_inset*2, h-texture_inset*2, shade_down, 0, color::color(color::white, 0.2));
}



void UIStyleAssets::draw_flatset(float x, float y, float w, float h, ALLEGRO_COLOR col, float roundness)
{
   float border_thickness = 2.0;
   al_draw_filled_rounded_rectangle(x, y, x+w, y+h, roundness, roundness, col);
   al_draw_rounded_rectangle(x, y, x+w, y+h, roundness, roundness, color::color(color::black, 0.1), border_thickness);
}




//
// text
//

void UIStyleAssets::draw_styled_text(std::string style, float x, float y, float align_x, float align_y, std::string text)
{

   if (style=="ui" || style=="ui_disabled")
   {
      ALLEGRO_FONT *font = UIStyleAssets::get_ui_font();

      float w = al_get_text_width(font, text.c_str()); // < not ideal or optimum for speed
                                                            //   consider some alternatives.
      float h = al_get_font_line_height(font);

      // draw the dropshadow
      if (style!="ui_disabled")
         al_draw_text(font, color::color(color::black, 0.4), x-w*align_x, y-h*align_y-1+2, 0, text.c_str());

      // and finally draw the text
      al_draw_text(font, color::mix(color::hex("EFEFEF"), color::transparent, (style=="ui_disabled") ? 0.6 : 0.0),
            x-w*align_x, y-h*align_y-1, 0, text.c_str());
   }
   else
      // draw the default style, default text
   {
      ALLEGRO_FONT *font = UIStyleAssets::get_text_font();

      float w = al_get_text_width(font, text.c_str()); // < not ideal or optimum for speed
                                                            //   consider some alternatives.
      float h = al_get_font_line_height(font);

      al_draw_text(font, color::white, x-w*align_x, y-h*align_y-1, 0, text.c_str());
   }
}





//
// colors
//

ALLEGRO_COLOR UIStyleAssets::get_surface_color()
{
   return color::hex("575962");
}

ALLEGRO_COLOR UIStyleAssets::get_hilight_color()
{
   return color::dodgerblue;
}





//
// internal
//


ALLEGRO_BITMAP *UIStyleAssets::generate_widget_icon(int size, ALLEGRO_COLOR front_color, ALLEGRO_COLOR back_color)
{
   float scale = 4.0; // 4.0 is essentially equivelent to 4x FSAA
   size *= scale;

   ALLEGRO_BITMAP *surface = al_create_bitmap(size, size);
   ALLEGRO_STATE state;
   al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
   al_set_target_bitmap(surface);
   al_clear_to_color(back_color);

   // draw stuff here
   float gear_scale = size / 64.0;
   float gear_radius = size/2;
   float inner_gear_thickness = 10.5 * gear_scale;
   float hw = 4 * gear_scale;
   float hh = 2.5 * gear_scale;

   int num_gears = 9;

   placement2d gear_place;
   gear_place.position = vec2d(size/2, size/2);
   gear_place.anchor = vec2d(0, gear_radius);

   al_draw_circle(size/2, size/2, gear_radius-hh*2-inner_gear_thickness/2, front_color, inner_gear_thickness);
   for (auto i=0; i<num_gears; i++)
   {
      gear_place.start_transform();
      al_draw_filled_rectangle(-hw, -hh*2-inner_gear_thickness*0.05, hw, 0, front_color);
      gear_place.restore_transform();
      gear_place.rotation += TAU/num_gears;
   }

   al_restore_state(&state);

   ALLEGRO_BITMAP *scaled = create_scaled_render(surface, size/scale, size/scale);

   al_destroy_bitmap(surface);

   return scaled;
}




UIStyleAssets *UIStyleAssets::instance = NULL;



