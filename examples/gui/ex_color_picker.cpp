

#include <allegro_flare/allegro_flare.h>



#include <allegro_flare/gui/surface_areas/box.h>




class FGUINullWidget : public FGUIWidget
{
public:
   FGUINullWidget(FGUIWidget *parent, float x, float y, float w, float h)
      : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
   {}
   void on_draw() override
   {
      FGUIWidget::on_draw();
      ALLEGRO_FONT *font = af::fonts["DroidSans.ttf 12"];
      al_draw_text(font, color::white, place.size.x/2, place.size.y/2 - al_get_font_line_height(font)/2, ALLEGRO_ALIGN_CENTER, attr.get("id").c_str());
   }
};




class FGUIColorBox : public FGUIWidget
{
private:
   ALLEGRO_COLOR *color1, *color2;

public:
   FGUIColorBox(FGUIWidget *parent, float x, float y, float w, float h, ALLEGRO_COLOR *col1, ALLEGRO_COLOR *col2)
      : FGUIWidget(parent, new FGUISurfaceAreaBox(x, y, w, h))
      , color1(col1)
      , color2(col2)
   {}
   void on_draw() override
   {
      al_draw_filled_rounded_rectangle(0, 0, place.size.x, place.size.y/2, 4, 4, *this->color1);
      al_draw_filled_rounded_rectangle(0, place.size.y/2, place.size.x, place.size.y, 4, 4, *this->color2);
   }
};




class GUIColorField : public FGUIXYController
{
private:
   ALLEGRO_COLOR tl, tr, br, bl;

public:
   using FGUIXYController::FGUIXYController;
   ALLEGRO_COLOR get_color()
   {
      return color::mix(color::mix(tl, tr, marker.x), color::mix(bl, br, marker.x), marker.y);
   }
   void set_colors(ALLEGRO_COLOR tl, ALLEGRO_COLOR tr, ALLEGRO_COLOR br, ALLEGRO_COLOR bl)
   {
      this->tl = tl;
      this->tr = tr;
      this->br = br;
      this->bl = bl;
   }
   void on_draw() override
   {
      float pdg = 7; // padding
      FGUIStyleAssets::draw_inset(-pdg, -pdg, place.size.x+pdg*2, place.size.y+pdg*2, color::color(color::black, 0.1));

      ALLEGRO_VERTEX v[4];
      v[0] = build_vertex(0, 0, 0, tl, 0, 0);
      v[1] = build_vertex(place.size.x, 0, 0, tr, 0, 0);
      v[2] = build_vertex(place.size.x, place.size.y, 0, br, 0, 0);
      v[3] = build_vertex(0, place.size.y, 0, bl, 0, 0);
      al_draw_prim(v, NULL, NULL, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);

      // draw the marker
      float marker_radius = 10.0;
      float marker_thkns = 4.0;
      al_draw_circle(marker.x * place.size.x, marker.y * place.size.y, marker_radius, color::white, marker_thkns);
      al_draw_circle(marker.x * place.size.x, marker.y * place.size.y, marker_radius-marker_thkns/2, color::black, marker_thkns/4);
   }
};




void draw_pointing_triangle(float target_x, float target_y, float rotation, float triangle_height, float distance_from_target, ALLEGRO_COLOR col)
{
   // TODO make this implementation much faster (without the use of placement)
   placement2d place;

   place.position.x = target_x;
   place.position.y = target_y;
   place.rotation = rotation;
   place.anchor.y = distance_from_target;

   std::cout << triangle_height;

   float h_side_length = 2.0 / sqrt(3.0) * triangle_height / 2.0;

   ALLEGRO_VERTEX v[3];
   v[0] = build_vertex(0, 0, 0, col, 0, 0);
   v[1] = build_vertex(h_side_length, triangle_height, 0, col, 0, 0);
   v[2] = build_vertex(-h_side_length, triangle_height, 0, col, 0, 0);

   place.start_transform();
   al_draw_prim(v, NULL, NULL, 0, 3, ALLEGRO_PRIM_TRIANGLE_FAN);
   place.restore_transform();
}





class GUIColorSlider : public FGUIVerticalSlider
{
private:
   class color_stop
   {
   public:
      float pos;
      ALLEGRO_COLOR col;
      color_stop(ALLEGRO_COLOR col, float pos)
         : pos(pos)
         , col(col)
      {}
   };
   std::vector<color_stop> color_stops;

   // TODO: sort color stops

public:
   using FGUIVerticalSlider::FGUIVerticalSlider;
   void set_colors(ALLEGRO_COLOR top_color, ALLEGRO_COLOR bottom_color)
   {
      clear_color_stops();
      color_stops.push_back(color_stop(top_color, 0));
      color_stops.push_back(color_stop(bottom_color, 1.0));
   }
   void set_colors(ALLEGRO_COLOR top_color, ALLEGRO_COLOR middle_color, ALLEGRO_COLOR bottom_color)
   {
      clear_color_stops();
      color_stops.push_back(color_stop(top_color, 0));
      color_stops.push_back(color_stop(middle_color, 0.5));
      color_stops.push_back(color_stop(bottom_color, 1.0));
   }
   void clear_color_stops()
   {
      color_stops.clear();
   }
   void add_color_stop(ALLEGRO_COLOR col, float pos)
   {
      color_stops.push_back(color_stop(col, pos));
   }
   ALLEGRO_COLOR get_color()
   {
      // TODO: Do this part here
      return color::black;
   }
   void on_draw() override
   {
      float pdg = 7; // padding
      FGUIStyleAssets::draw_inset(-pdg, -pdg, place.size.x+pdg*2, place.size.y+pdg*2, color::color(color::black, 0.1));

      ALLEGRO_VERTEX v[16]; // gives a limit of 8 stops
      for (unsigned i=0; i<color_stops.size(); i++)
      {
         int vi = i*2;
         float stop_y = color_stops[i].pos * place.size.y;
         v[vi] = build_vertex(0, stop_y, 0, color_stops[i].col, 0, 0);
         v[vi+1] = build_vertex(place.size.x, stop_y, 0, color_stops[i].col, 0, 0);
      }
      al_draw_prim(v, NULL, NULL, 0, color_stops.size()*2, ALLEGRO_PRIM_TRIANGLE_STRIP);

      // draw the pointer
      float y = place.size.y * (1-val);
      float triangle_height = 7;
      float distance_from_target = -triangle_height;
      draw_pointing_triangle(0, y+2, TAU * 0.25, triangle_height, distance_from_target, color::black);
      draw_pointing_triangle(place.size.x, y+2, -TAU * 0.25, triangle_height, distance_from_target, color::black);
      draw_pointing_triangle(0, y, TAU * 0.25, triangle_height, distance_from_target, color::white);
      draw_pointing_triangle(place.size.x, y, -TAU * 0.25, triangle_height, distance_from_target, color::white);
   }
};




class FGUIColorPicker : public FGUIFramedWindow
{
private:
   ALLEGRO_COLOR picked_color;
   ALLEGRO_COLOR starting_color;

   GUIColorField *xy_color_field;
   GUIColorSlider *color_slider;

   FGUITextInput *r_val;
   FGUITextInput *g_val;
   FGUITextInput *b_val;
   FGUITextInput *hex_val;

public:
   FGUIColorPicker(FGUIWidget *parent, float x, float y)
      : FGUIFramedWindow(parent, x, y, 570, 300)
      , picked_color(color::gray)
      , starting_color(color::gray)
      , r_val(NULL)
      , g_val(NULL)
      , b_val(NULL)
      , hex_val(NULL)
   {
      this->set_title("Pick a color");

      // the color field
      xy_color_field = new GUIColorField(this, 30, 30, 240, 240);
      xy_color_field->set_colors(color::green, color::blue, color::red, color::yellow);

      // the color slider
      color_slider = new GUIColorSlider(this, 300, 30, 30, 240);
      color_slider->set_colors(color::white, color::orange, color::black);

      // the current color
      new FGUIColorBox(this, 360, 30, 60, 90, &picked_color, &starting_color);

      // the RGB inputs
      new FGUIText(this, 465, 65-30, "R");
      r_val = new FGUITextInput(this, 480, 30, 60, 30);
      new FGUIText(this, 465, 110-30, "G");
      g_val = new FGUITextInput(this, 480, 75, 60, 30);
      new FGUIText(this, 465, 155-30, "B");
      b_val = new FGUITextInput(this, 480, 120, 60, 30);

      // the hex input
      new FGUIText(this, 420, 215-30, "#");
      hex_val = new FGUITextInput(this, 435, 180, 105, 30);

      // Cancel and OK Buttons
      new FGUIButton(this, 375, 240, 75, 30, "Cancel");
      new FGUIButton(this, 465, 240, 75, 30, "OK");

      // re-align all the elements
      for (unsigned i=0; i<family.children.size(); i++)
         family.children[i]->place.align = vec2d(0, 0);
   }
   void set_color(ALLEGRO_COLOR col)
   {
      picked_color = col;

      r_val->set_text(tostring((int)(picked_color.r * 255)));
      g_val->set_text(tostring((int)(picked_color.g * 255)));
      b_val->set_text(tostring((int)(picked_color.b * 255)));

      std::string hex_color = "";
      hex_color += as_hex((uint32_t)(picked_color.r * 255));
      hex_color += as_hex((uint32_t)(picked_color.g * 255));
      hex_color += as_hex((uint32_t)(picked_color.b * 255));

      hex_val->set_text(hex_color);

      color_slider->set_colors(color::white, col, color::black);
   }

   void on_message(FGUIWidget *sender, std::string message) override
   {
      if (sender == xy_color_field)
      {
         set_color(xy_color_field->get_color());
      }
      else if (sender == color_slider)
      {
         set_color(color_slider->get_color());
      }
   }
};



class MyProject : public FGUIScreen
{
private:
   FGUIButton *button;

   FGUIColorPicker *color_picker;

public:
   MyProject(Display *display)
      : FGUIScreen(display)
      , button(NULL)
      , color_picker(NULL)
   {
      // create our button
      button = new FGUIButton(this, 200, 200, 140, 70, "Click Me!");

      // create the color picker
      color_picker = new FGUIColorPicker(this, 400, 100);
      color_picker->place.align = vec2d(0, 0);
   }
   void on_message(FGUIWidget *sender, std::string message) override
   {
      if (sender == button) // click is automatic message to parent for FGUIButton
      {
         // animate the button around randomly when it gets clicked
         af::motion.cmove_to(&button->place.position.x, random_float(100, 600), 0.4);
         af::motion.cmove_to(&button->place.position.y, random_float(100, 500), 0.4);
         af::motion.cmove_to(&button->place.rotation, random_float(-0.4, 0.4), 0.4);
      }
   }
};




int main(int argc, char **argv)
{
   af::initialize();
   Display *display = af::create_display();
   MyProject *proj = new MyProject(display);
   af::run_loop();
   return 0;
}




