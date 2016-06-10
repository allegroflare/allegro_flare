



#include <allegro_flare/gui/widgets/text_box.h>

#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/allegro_flare.h> // for Framework::fonts




UITextBox::UITextBox(UIWidget *parent, float x, float y, float w, float h, std::string text)
   : UIWidget(parent, new UISurfaceAreaBox(x, y, w, h))
   , font(Framework::font("DroidSans.ttf 20"))
   , text(text)
   , text_color(color::black)
{
   attr.set(UI_ATTR__UI_WIDGET_TYPE, "UITextBox");
   attr.set("id", "TextBox" + tostring(get_num_created_widgets()));

   no_focus = true;
}




void UITextBox::set_font(ALLEGRO_FONT *font)
{
   this->font = font;
}




void UITextBox::set_text(std::string text)
{
   this->text = text;
}




std::string UITextBox::get_text()
{
   return this->text;
}




void UITextBox::set_text_color(ALLEGRO_COLOR col)
{
   this->text_color = col;
}




void UITextBox::on_draw()
{
   if (font) al_draw_multiline_text(font, text_color, 0, 0, place.size.x, al_get_font_line_height(font), ALLEGRO_ALIGN_LEFT, text.c_str());
}




