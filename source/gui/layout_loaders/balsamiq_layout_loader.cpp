



#include <allegro_flare/gui/layout_loaders/balsamiq_layout_loader.h>
#include <allegro_flare/gui/widgets/button.h>
#include <allegro_flare/gui/widgets/text.h>
#include <allegro_flare/gui/widgets/text_box.h>
#include <allegro_flare/console_color.h>
#include <allegro_flare/json.h>
#include <allegro_flare/useful_php.h>




#define NOT_IMPLEMENTED(object_type) std::cout \
   << CONSOLE_COLOR_YELLOW << "Implementation for \"" \
   << object_type << "\" not finished\n" \
   << CONSOLE_COLOR_DEFAULT << std::endl;




bool BalsamiqLayoutLoader::load_file(UIWidget *parent, std::string filename)
{
   if (!php::file_exists(filename)) return false;
   std::string file_contents = php::file_get_contents(filename);

   // attempt to parse through the file contents
   try
   {
      JSON::Object mockup = json_object(json_object(file_contents).values["mockup"]->toString());
      JSON::Object controls_outer = json_object(mockup.values["controls"]->toString());
      JSON::Array controls = json_array(controls_outer.values["control"]->toString());

      version = json_string(mockup["version"].toString()).stringValue();
      std::cout << CONSOLE_COLOR_GREEN << "Loading balsamiq mockup version " << version << CONSOLE_COLOR_DEFAULT << std::endl;

      // traverse through each control object
      for (auto &value : controls.values)
      {
         JSON::Object object = json_object(value->toString());

         // grab common standard attributes for elements
         std::string this_object_type = json_string(object.values["typeID"]->toString()).stringValue();
         JSON::Object properties
            = object.exists("properties")
            ? json_object(object.values["properties"]->toString())
            : json_object("{}");
         int x = object.exists("x") ? json_int(object.values["x"]->toString()).intValue() : 0;
         int y = object.exists("y") ? json_int(object.values["y"]->toString()).intValue() : 0;
         int w = object.exists("w") ? json_int(object.values["w"]->toString()).intValue() : 0;
         int h = object.exists("h") ? json_int(object.values["h"]->toString()).intValue() : 0;
         int measuredW = object.exists("measuredW") ? json_int(object.values["measuredW"]->toString()).intValue() : 0;
         int measuredH = object.exists("measuredH") ? json_int(object.values["measuredH"]->toString()).intValue() : 0;

         // create the widget
         if (this_object_type == "BlockOfText"
            || this_object_type == "Paragraph")
         {
            std::string text = properties.exists("text") ? json_string(properties.values["text"]->toString()).stringValue() : "";
            UITextBox *text_box_widget = new UITextBox(parent, x, y, w, h, text);
         }
         else if (this_object_type == "Button")
         {
            std::string text = properties.exists("text") ? json_string(properties.values["text"]->toString()).stringValue() : "";
            UIButton *button_widget = new UIButton(parent, x, y, w, h, text);
         }
         else if (this_object_type == "Image")
         {
            NOT_IMPLEMENTED("Image")
         }
         else if (this_object_type == "Label")
         {
            std::string text = properties.exists("text") ? json_string(properties.values["text"]->toString()).stringValue() : "";
            UIText *text_widget = new UIText(parent, x, y, text);
         }
         else if (this_object_type == "Title")
         {
            std::string text = properties.exists("text") ? json_string(properties.values["text"]->toString()).stringValue() : "";
            UIText *text_widget = new UIText(parent, x, y, text);
         }
         else
         {
            std::cout
               << CONSOLE_COLOR_YELLOW << "Balsamiq element \""
               << this_object_type << "\" not supported in BalsamiqLayoutLoader\n"
               << CONSOLE_COLOR_DEFAULT << std::endl;
         }
      }
   }
   catch (const char *m)
   {
      std::cout
         << CONSOLE_COLOR_RED << "BalsamiqLayoutLoader was unable to parse the file \""
         << filename << "\"\n" << m
         << CONSOLE_COLOR_DEFAULT << std::endl;
   }

   return true;
}




std::string BalsamiqLayoutLoader::get_version()
{
   return version;
}




