

#include <AllegroFlare/Prototypes/Platforming2D/TMJObjectLoader.hpp>

#include <AllegroFlare/Logger.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <lib/nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{


TMJObjectLoader::TMJObjectLoader(std::string filename)
   : filename(filename)
   , loaded(false)
   , object_parsed_callback({})
   , object_parsed_callback_user_data(nullptr)
{
}


TMJObjectLoader::~TMJObjectLoader()
{
}


void TMJObjectLoader::set_object_parsed_callback(std::function<void(std::string, float, float, float, float, void*)> object_parsed_callback)
{
   this->object_parsed_callback = object_parsed_callback;
}


void TMJObjectLoader::set_object_parsed_callback_user_data(void* object_parsed_callback_user_data)
{
   this->object_parsed_callback_user_data = object_parsed_callback_user_data;
}


std::function<void(std::string, float, float, float, float, void*)> TMJObjectLoader::get_object_parsed_callback() const
{
   return object_parsed_callback;
}


void* TMJObjectLoader::get_object_parsed_callback_user_data() const
{
   return object_parsed_callback_user_data;
}


void TMJObjectLoader::load()
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[TMJObjectLoader::load]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJObjectLoader::load: error: guard \"(!loaded)\" not met");
   }
   if (!file_exists(filename))
   {
      std::stringstream error_message;
      error_message << "[KrampusReturns::TMJObjectLoader::load()]: error: The file "
                    << "\"" << filename << "\" does not exist.";
      throw std::runtime_error(error_message.str());
   }

   // load and validate the json data to variables
   std::ifstream i(filename);
   nlohmann::json source_json;
   try
   {
      i >> source_json;
   }
   catch (const std::exception& e)
   {
      i.close();
      std::stringstream error_message;
      error_message << "The file "
                    << "\"" << filename << "\" appears to have"
                    << " malformed JSON. The following error was thrown by nlohmann::json: \""
                    << e.what() << "\"";
      AllegroFlare::Logger::throw_error("KrampusReturns::TMJObjectLoader", error_message.str());
   }
   i.close();


   // TODO: validate there is one and only "objectgroup" layer

   // get first j["layers"] that is a ["type"] == "objectgroup"
   bool object_layer_type_found = false;
   nlohmann::json object_layer_json;
   for (auto &layer : source_json["layers"].items())
   {
      if (layer.value()["type"] == "objectgroup")
      {
         object_layer_json = layer.value();
         object_layer_type_found = true;
         break;
      }
   }
   if (!object_layer_type_found)
   {
      // TODO: Swap this error message with AllegroFlare::Errors
      throw std::runtime_error("TMJObjectLoader: error: layer of type \"objectgroup\" not found.");
   }


   // load the objects one by one

   if (!object_layer_json.contains("objects"))
   {
      std::stringstream error_message;
      error_message << "Expecting [\"objects\"] to exist in the \"objectgoup\"-type layer, but it does not.";
      AllegroFlare::Logger::throw_error("KrampusReturns::TMJObjectLoader", error_message.str());
   }
   for (auto &object_json : object_layer_json["objects"].items())
   {
      std::string class_property = object_json.value()["class"].get<std::string>();
      float x_property = object_json.value()["x"].get<float>();
      float y_property = object_json.value()["y"].get<float>();
      float width_property = object_json.value()["width"].get<float>();
      float height_property = object_json.value()["height"].get<float>();

      // call the callback (if present)
      if (object_parsed_callback)
      {
         object_parsed_callback(
            class_property,
            x_property,
            y_property,
            width_property,
            height_property,
            object_parsed_callback_user_data
         );
      }
   }



   return;
}

bool TMJObjectLoader::file_exists(std::string filename)
{
   return std::filesystem::exists(filename);
}


} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


