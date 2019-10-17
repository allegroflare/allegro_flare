



#include <allegro_flare/gui_tool_layout_loader.h>
#include <allegro_flare/box.h>

#include <allegro_flare/json.h>




GUIToolLayoutLoader::GUIToolLayoutLoader(UIWidget *parent, std::string content)
   : UILayoutLoaderBase(parent, content)
{}




bool GUIToolLayoutLoader::load_file()
{
   if (!parent) return false;

   JSON::Value &val = JSON::decode(content);

   JSON::Array widgets = val.as_object()["widgets"].as_array();

   for (auto &_widget : widgets.values)
   {
      JSON::Object widget = _widget->as_object();
      float x = widget.values["position.x"]->as_float();
      float y = widget.values["position.y"]->as_float();
      float w = widget.values["size.x"]->as_float();
      float h = widget.values["size.y"]->as_float();
      new UIWidget(parent, "UIWidget", new UISurfaceAreaBox(x, y, w, h));
   }

   // todo
   return false;
}




