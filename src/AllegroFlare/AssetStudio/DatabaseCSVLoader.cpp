

#include <AllegroFlare/AssetStudio/DatabaseCSVLoader.hpp>

#include <AllegroFlare/CSVParser.hpp>
#include <AllegroFlare/FrameAnimation/SpriteSheet.hpp>
#include <AllegroFlare/FrameAnimation/SpriteStripAssembler.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>


namespace AllegroFlare
{
namespace AssetStudio
{


DatabaseCSVLoader::DatabaseCSVLoader(AllegroFlare::BitmapBin* assets_bitmap_bin)
   : AllegroFlare::CSVParser()
   , assets_bitmap_bin(assets_bitmap_bin)
   , csv_full_path("[unset-csv_full_path]")
   , assets({})
   , records({})
   , sprite_sheets({})
   , sprite_sheet_scale(3)
   , loaded(false)
   , records_loaded(false)
{
}


DatabaseCSVLoader::~DatabaseCSVLoader()
{
}


void DatabaseCSVLoader::set_assets_bitmap_bin(AllegroFlare::BitmapBin* assets_bitmap_bin)
{
   this->assets_bitmap_bin = assets_bitmap_bin;
}


void DatabaseCSVLoader::set_csv_full_path(std::string csv_full_path)
{
   this->csv_full_path = csv_full_path;
}


void DatabaseCSVLoader::set_sprite_sheet_scale(int sprite_sheet_scale)
{
   if (get_initialized()) throw std::runtime_error("[DatabaseCSVLoader::set_sprite_sheet_scale]: error: guard \"get_initialized()\" not met.");
   this->sprite_sheet_scale = sprite_sheet_scale;
}


AllegroFlare::BitmapBin* DatabaseCSVLoader::get_assets_bitmap_bin() const
{
   return assets_bitmap_bin;
}


std::string DatabaseCSVLoader::get_csv_full_path() const
{
   return csv_full_path;
}


int DatabaseCSVLoader::get_sprite_sheet_scale() const
{
   return sprite_sheet_scale;
}


bool DatabaseCSVLoader::get_initialized()
{
   return loaded;
}

bool DatabaseCSVLoader::csv_file_exists()
{
   return std::filesystem::exists(csv_full_path);
}

std::size_t DatabaseCSVLoader::num_records()
{
   if (!(records_loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::DatabaseCSVLoader::num_records]: error: guard \"records_loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::DatabaseCSVLoader::num_records]: error: guard \"records_loaded\" not met");
   }
   return records.size();
}

std::vector<AllegroFlare::AssetStudio::Record> DatabaseCSVLoader::get_records()
{
   if (!(records_loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::DatabaseCSVLoader::get_records]: error: guard \"records_loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::DatabaseCSVLoader::get_records]: error: guard \"records_loaded\" not met");
   }
   return records;
}

bool DatabaseCSVLoader::record_exists(std::string asset_identifier)
{
   if (!(records_loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::DatabaseCSVLoader::record_exists]: error: guard \"records_loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::DatabaseCSVLoader::record_exists]: error: guard \"records_loaded\" not met");
   }
   // TODO: Consider if an index on "Record::identifier" would be helpful
   for (auto &record : records) if (record.identifier == asset_identifier) return true;
   return false;
}

AllegroFlare::AssetStudio::Record DatabaseCSVLoader::obtain_record_as_copy(std::string asset_identifier)
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::DatabaseCSVLoader::obtain_record_as_copy]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::DatabaseCSVLoader::obtain_record_as_copy]: error: guard \"loaded\" not met");
   }
   // TODO: Consider if an index on "Record::identifier" would be helpful
   for (auto &record : records) if (record.identifier == asset_identifier) return record;
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::AssetStudio::DatabaseCSVLoader::obtain_record_as_copy",
      "A record with the asset_identifier \"" + asset_identifier + "\" does not exist."
   );
   return {};
}

AllegroFlare::AssetStudio::Record* DatabaseCSVLoader::find_record(std::string identifier)
{
   if (!(records_loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::DatabaseCSVLoader::find_record]: error: guard \"records_loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::DatabaseCSVLoader::find_record]: error: guard \"records_loaded\" not met");
   }
   // TODO: Test this
   for (auto &record : records) if (record.identifier == identifier) return &record;
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::AssetStudio::DatabaseCSVLoader::find_record",
      "A record with the identifier \"" + identifier + "\" does not exist."
   );
   return nullptr;
}

int DatabaseCSVLoader::toi(std::string value)
{
   if (value.empty()) return 0;
   if (value[0] == '+') value.erase(0, 1); // Pop front on the '+' sign
   return std::atoi(value.c_str());
}

float DatabaseCSVLoader::tof(std::string value)
{
   if (value.empty()) return 0;
   if (value[0] == '+') value.erase(0, 1); // Pop front on the '+' sign
   return std::stof(value.c_str());
}

std::vector<std::string> DatabaseCSVLoader::comma_separated_quoted_strings_to_vector_of_strings(std::string comma_separated_quoted_strings)
{
   std::vector<std::string> result;
   std::stringstream ss(comma_separated_quoted_strings);
   std::string current_element;
   bool in_quotes = false;

   // Parse the CSV list character by character
   for (char ch : comma_separated_quoted_strings)
   {
      if (ch == '"')
      {
         // Toggle quotes state
         in_quotes = !in_quotes;
      }
      else if (ch == ',' && !in_quotes)
      {
         // Found a comma outside quotes, push the current element
         result.push_back(current_element);
         current_element.clear(); // Reset for the next element
      }
      else if (in_quotes)
      {
         current_element += ch;
      }
   }

   // Push the last element if it's not empty
   if (!current_element.empty())
   {
      result.push_back(current_element);
   }

   return result;
}

std::vector<std::string> DatabaseCSVLoader::comma_separated_strings_to_vector_of_strings(std::string comma_separated_strings)
{
   // NOTE: Does not account for nested strings
   return tokenize(comma_separated_strings, ',');
}

std::pair<bool, uint32_t> DatabaseCSVLoader::str_to_playmode(std::string playmode_string)
{
   if (playmode_string == "once")
   {
      return { true, AllegroFlare::FrameAnimation::Animation::PLAYMODE_FORWARD_ONCE };
   }
   else if (playmode_string == "loop")
   {
      return { true, AllegroFlare::FrameAnimation::Animation::PLAYMODE_FORWARD_LOOP };
   }
   else if (playmode_string == "ping_pong_forward")
   {
      return { true, AllegroFlare::FrameAnimation::Animation::PLAYMODE_FORWARD_PING_PONG };
   }

   return { false, 0 };
}

std::string DatabaseCSVLoader::validate_key_and_return(std::map<std::string, std::string>* extracted_row, std::string key)
{
   if (extracted_row->count(key) == 0)
   {
      std::vector<std::string> valid_keys;
      for (const auto& pair : *extracted_row) valid_keys.push_back(pair.first);

      std::stringstream ss;
      ss << "[";
      for (auto &valid_key : valid_keys)
      {
         ss << "\"" << valid_key << "\", ";
      }
      ss << "]";

      AllegroFlare::Logger::throw_error(
         "Robieo::CSVToLevelLoader::validate_key_and_return",
         "key \"" + key + "\" does not exist. The following keys are present: " + ss.str() + "."
      );
   }
   return extracted_row->operator[](key);
}

void DatabaseCSVLoader::load_records()
{
   if (!((!records_loaded)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::DatabaseCSVLoader::load_records]: error: guard \"(!records_loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::DatabaseCSVLoader::load_records]: error: guard \"(!records_loaded)\" not met");
   }
   if (!std::filesystem::exists(csv_full_path))
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::AssetStudio::DatabaseCSVLoader::load",
         "The file \"" + csv_full_path + "\" does not exist."
      );
   }
   std::string content = AllegroFlare::php::file_get_contents(csv_full_path);
   if (content.empty())
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::AssetStudio::DatabaseCSVLoader::load",
         "The file \"" + csv_full_path + "\" is present but appears to be empty."
      );
   }
   AllegroFlare::CSVParser csv_parser;
   csv_parser.set_raw_csv_content(content);
   csv_parser.parse();
   csv_parser.assemble_column_headers(3);


   //
   // Extract the data from the CSV into "records" (as AssetStudio/Record objects)
   //
   {
      records.clear();
      records.reserve(csv_parser.num_records());

      int first_record_row = csv_parser.get_num_header_rows();
      int row_i = first_record_row;
      int record_index_in_vector = 0;
      for (std::map<std::string, std::string> &extracted_row : csv_parser.extract_all_rows())
      {
         // Load the record data to CSV
         int id = toi(validate_key_and_return(&extracted_row, "id"));
         std::string identifier = validate_key_and_return(&extracted_row, "identifier");
         int source_csv_column_num = row_i;
         std::string status = validate_key_and_return(&extracted_row, "status");
         std::string visibility = validate_key_and_return(&extracted_row, "visibility");
         std::string type = validate_key_and_return(&extracted_row, "type");
         std::string asset_pack_identifier = validate_key_and_return(&extracted_row, "asset_pack_identifier");
         std::string intra_pack_identifier = validate_key_and_return(&extracted_row, "intra_pack_identifier");
         int cell_width = toi(validate_key_and_return(&extracted_row, "cell_width"));
         int cell_height = toi(validate_key_and_return(&extracted_row, "cell_height"));
         float align_x = tof(validate_key_and_return(&extracted_row, "align_x"));
         float align_y = tof(validate_key_and_return(&extracted_row, "align_y"));
         float align_in_container_x = tof(validate_key_and_return(&extracted_row, "align_in_container_x"));
         float align_in_container_y = tof(validate_key_and_return(&extracted_row, "align_in_container_y"));
         float anchor_x = tof(validate_key_and_return(&extracted_row, "anchor_x"));
         float anchor_y = tof(validate_key_and_return(&extracted_row, "anchor_y"));
         std::string image_filename = validate_key_and_return(&extracted_row, "image_filename");
         std::string images_list_raw = validate_key_and_return(&extracted_row, "images_list"); // ***
         std::string full_path_to_initial_image =
            validate_key_and_return(&extracted_row, "full_path_to_initial_image");
         std::string playmode = validate_key_and_return(&extracted_row, "playmode");
         std::string notes = validate_key_and_return(&extracted_row, "notes");
         std::string frame_data__build_n_frames__num_frames =
            validate_key_and_return(&extracted_row, "frame_data__build_n_frames__num_frames");
         std::string frame_data__build_n_frames__start_from_frame =
            validate_key_and_return(&extracted_row, "frame_data__build_n_frames__start_from_frame");
         std::string frame_data__build_n_frames__each_frame_duration =
            validate_key_and_return(&extracted_row, "frame_data__build_n_frames__each_frame_duration");
         std::string frame_data__in_hash = validate_key_and_return(&extracted_row, "frame_data__in_hash");

         // Create the record
         AllegroFlare::AssetStudio::Record record;

         record.id = id;
         record.identifier = identifier;
         record.source_csv_column_num = source_csv_column_num;
         record.status = status;
         record.visibility = visibility;
         record.type = type;
         record.asset_pack_identifier = asset_pack_identifier;
         record.intra_pack_identifier = intra_pack_identifier;
         record.cell_width = cell_width;
         record.cell_height = cell_height;
         record.align_x = align_x;
         record.align_y = align_y;
         record.align_in_container_x = align_in_container_x;
         record.align_in_container_y = align_in_container_y;
         record.anchor_x = anchor_x;
         record.anchor_y = anchor_y;
         record.image_filename = image_filename;
         record.images_list = comma_separated_strings_to_vector_of_strings(images_list_raw);
         record.full_path_to_initial_image = full_path_to_initial_image;
         record.playmode = playmode;
         record.notes = notes;
         // TODO: Test this is int
         record.frame_data__build_n_frames__num_frames = toi(frame_data__build_n_frames__num_frames);
         // TODO: Test this is int
         record.frame_data__build_n_frames__start_from_frame = toi(frame_data__build_n_frames__start_from_frame);
         // TODO: Test this is float
         record.frame_data__build_n_frames__each_frame_duration =
            tof(frame_data__build_n_frames__each_frame_duration);
         record.frame_data__in_hash = frame_data__in_hash;

         // Add the record
         records.push_back(record);

         row_i++;
      }
   }

   records_loaded = true;
   return;
}

void DatabaseCSVLoader::load()
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::DatabaseCSVLoader::load]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::DatabaseCSVLoader::load]: error: guard \"(!loaded)\" not met");
   }
   if (!(assets_bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::DatabaseCSVLoader::load]: error: guard \"assets_bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::DatabaseCSVLoader::load]: error: guard \"assets_bitmap_bin\" not met");
   }
   // Load the records (if they have not been loaded already)
   if (!records_loaded) load_records();

   // Iterate over every record and load it into "assets"
   std::set<std::string> hidden_assets;
   for (auto &record : records)
   {
      if (record.visibility_is_hidden())
      {
         // TODO: Report the hidden assets at end of loading process
         hidden_assets.insert(record.identifier);
         continue;
      }

      // Create the asset
      AllegroFlare::AssetStudio::Asset *asset = create_asset_from_record_identifier(record.identifier);

      // Add the asset to the assets
      assets.insert({ asset->identifier, asset });

      continue;
   }

   loaded = true;
   return;
}

std::vector<std::string> DatabaseCSVLoader::split(std::string string, char delimiter)
{
   std::vector<std::string> elems;
   auto result = std::back_inserter(elems);
   std::stringstream ss(string);
   std::string item;
   while (std::getline(ss, item, delimiter)) { *(result++) = item; }
   return elems;
}

std::vector<std::string> DatabaseCSVLoader::tokenize(std::string str, char delim)
{
   std::vector<std::string> tokens = split(str, delim);
   for (auto &token : tokens) token = trim(token);
   return tokens;
}

std::string DatabaseCSVLoader::trim(std::string s)
{
   // ltrim
   s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c);}));
   // rtrim
   s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) {return !std::isspace(c);}).base(), s.end());
   return s;
}

std::map<std::string, AllegroFlare::AssetStudio::Asset*> DatabaseCSVLoader::get_assets()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::DatabaseCSVLoader::get_assets]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::DatabaseCSVLoader::get_assets]: error: guard \"loaded\" not met");
   }
   return assets;
}

bool DatabaseCSVLoader::asset_exists(std::string asset_identifier)
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::DatabaseCSVLoader::asset_exists]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::DatabaseCSVLoader::asset_exists]: error: guard \"loaded\" not met");
   }
   return (assets.find(asset_identifier) != assets.end());
}

AllegroFlare::AssetStudio::Asset* DatabaseCSVLoader::find_asset(std::string asset_identifier)
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::DatabaseCSVLoader::find_asset]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::DatabaseCSVLoader::find_asset]: error: guard \"loaded\" not met");
   }
   if (!(asset_exists(asset_identifier)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::DatabaseCSVLoader::find_asset]: error: guard \"asset_exists(asset_identifier)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::DatabaseCSVLoader::find_asset]: error: guard \"asset_exists(asset_identifier)\" not met");
   }
   return assets[asset_identifier];
}

std::vector<AllegroFlare::FrameAnimation::Frame> DatabaseCSVLoader::build_n_frames(uint32_t num_frames, uint32_t start_frame_num, float each_frame_duration, float each_frame_align_x, float each_frame_align_y, float each_frame_align_in_container_x, float each_frame_align_in_container_y, float each_frame_anchor_x, float each_frame_anchor_y)
{
   if (!((num_frames >= 1)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::DatabaseCSVLoader::build_n_frames]: error: guard \"(num_frames >= 1)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::DatabaseCSVLoader::build_n_frames]: error: guard \"(num_frames >= 1)\" not met");
   }
   if (!((start_frame_num >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::DatabaseCSVLoader::build_n_frames]: error: guard \"(start_frame_num >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::DatabaseCSVLoader::build_n_frames]: error: guard \"(start_frame_num >= 0)\" not met");
   }
   if (!((each_frame_duration >= 0.0001)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::DatabaseCSVLoader::build_n_frames]: error: guard \"(each_frame_duration >= 0.0001)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::DatabaseCSVLoader::build_n_frames]: error: guard \"(each_frame_duration >= 0.0001)\" not met");
   }
   std::vector<AllegroFlare::FrameAnimation::Frame> result;
   for (uint32_t i=0; i<num_frames; i++)
   {
      AllegroFlare::FrameAnimation::Frame result_frame(start_frame_num + i, each_frame_duration);
      result_frame.set_align_x(each_frame_align_x);
      result_frame.set_align_y(each_frame_align_y);
      result_frame.set_align_in_container_x(each_frame_align_in_container_x);
      result_frame.set_align_in_container_y(each_frame_align_in_container_y);
      result_frame.set_anchor_x(each_frame_anchor_x);
      result_frame.set_anchor_y(each_frame_anchor_y);
      
      //result.push_back({ start_frame_num + i, each_frame_duration });
      result.push_back(result_frame);
   }
   return result;
}

std::vector<AllegroFlare::FrameAnimation::Frame> DatabaseCSVLoader::build_frames_from_hash(std::string frame_data_hash)
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::AssetStudio::DatabaseCSVLoader::build_frames_from_hash",
      "This feature is not yet supported."
   );

   std::vector<AllegroFlare::FrameAnimation::Frame> result;
   // TODO: If frame animation and alignment data is incuded in the hash, parse and use it here
   return result;
}

AllegroFlare::FrameAnimation::SpriteSheet* DatabaseCSVLoader::obtain_sprite_sheet(std::string filename, int cell_width, int cell_height, int _sprite_sheet_scale)
{
   if (!(assets_bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::DatabaseCSVLoader::obtain_sprite_sheet]: error: guard \"assets_bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::DatabaseCSVLoader::obtain_sprite_sheet]: error: guard \"assets_bitmap_bin\" not met");
   }
   // TODO: Guard after assets_bitmap_bin is initialized

   //std::map<std::tuple<filename, int, int, int>, AllegroFlare::FrameAnimation::SpriteSheet*> cache;
   std::tuple<std::string, int, int, int> sprite_sheet_key(filename, cell_width, cell_height, _sprite_sheet_scale);
   if (sprite_sheets.find(sprite_sheet_key) == sprite_sheets.end())
   {
      // Create sprite sheet
      ALLEGRO_BITMAP* sprite_sheet_atlas = al_clone_bitmap(
            assets_bitmap_bin->auto_get(filename)
         );
      AllegroFlare::FrameAnimation::SpriteSheet *result_sprite_sheet =
         new AllegroFlare::FrameAnimation::SpriteSheet(sprite_sheet_atlas, cell_width, cell_height, _sprite_sheet_scale);
      result_sprite_sheet->initialize();

      al_destroy_bitmap(sprite_sheet_atlas);

      // Add the sprite sheet to the list of sprite sheets
      sprite_sheets[sprite_sheet_key] = result_sprite_sheet;
   }

   return sprite_sheets[sprite_sheet_key];

   //ALLEGRO_BITMAP* sprite_sheet_atlas = al_clone_bitmap(
         //assets_bitmap_bin->auto_get(filename)
         ////assets_bitmap_bin.auto_get("grotto_escape_pack/Base pack/graphics/player.png")
      //);
   //AllegroFlare::FrameAnimation::SpriteSheet *result_sprite_sheet =
      //new AllegroFlare::FrameAnimation::SpriteSheet(sprite_sheet_atlas, cell_width, cell_height, _sprite_sheet_scale);

   //al_destroy_bitmap(sprite_sheet_atlas);

   //return result_sprite_sheet;
}

AllegroFlare::FrameAnimation::SpriteSheet* DatabaseCSVLoader::create_sprite_sheet_from_individual_images(std::vector<std::string> individual_frame_image_filenames, int cell_width, int cell_height, int _sprite_sheet_scale)
{
   if (!(assets_bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::DatabaseCSVLoader::create_sprite_sheet_from_individual_images]: error: guard \"assets_bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::DatabaseCSVLoader::create_sprite_sheet_from_individual_images]: error: guard \"assets_bitmap_bin\" not met");
   }
   if (!((!individual_frame_image_filenames.empty())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::DatabaseCSVLoader::create_sprite_sheet_from_individual_images]: error: guard \"(!individual_frame_image_filenames.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::DatabaseCSVLoader::create_sprite_sheet_from_individual_images]: error: guard \"(!individual_frame_image_filenames.empty())\" not met");
   }
   // TODO: Consider caching the created result_sprite_sheet;

   std::vector<ALLEGRO_BITMAP*> bitmaps;
   for (auto &individual_frame_image_filename : individual_frame_image_filenames)
   {
      bitmaps.push_back(assets_bitmap_bin->auto_get(individual_frame_image_filename));
   }

   AllegroFlare::FrameAnimation::SpriteStripAssembler sprite_strip_assembler;
   sprite_strip_assembler.set_bitmaps(bitmaps);
   sprite_strip_assembler.assemble();
   ALLEGRO_BITMAP* sprite_strip = sprite_strip_assembler.get_sprite_strip();

   // Given the newly assembled sprite_strip (aka atlas), build the sprite_sheet
   AllegroFlare::FrameAnimation::SpriteSheet *result_sprite_sheet =
      new AllegroFlare::FrameAnimation::SpriteSheet(sprite_strip, cell_width, cell_height, _sprite_sheet_scale);
   result_sprite_sheet->initialize();

   // Cleanup
   al_destroy_bitmap(sprite_strip);
   // Cleanup the individual frame images in the bin here
   for (auto &individual_frame_image_filename : individual_frame_image_filenames)
   {
      // TODO: This could wierdly clobber, consider checking all the image frames do *not* already exist in the
      // bin at the beginning of the method before continuing.
      assets_bitmap_bin->destroy(individual_frame_image_filename);
   }

   return result_sprite_sheet;
}

AllegroFlare::AssetStudio::Asset* DatabaseCSVLoader::create_asset_from_record_identifier(std::string identifier_)
{
   if (!(record_exists(identifier_)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::DatabaseCSVLoader::create_asset_from_record_identifier]: error: guard \"record_exists(identifier_)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::DatabaseCSVLoader::create_asset_from_record_identifier]: error: guard \"record_exists(identifier_)\" not met");
   }
   AllegroFlare::AssetStudio::Record &record = *find_record(identifier_);


   int &csv_row = record.source_csv_column_num;
   std::string visibility = record.visibility;
   std::string identifier = record.identifier;
   std::string asset_pack_identifier = record.asset_pack_identifier;
   std::string intra_pack_identifier = record.intra_pack_identifier;
   int id = record.id;
   std::string type = record.type;
   int cell_width = record.cell_width;
   int cell_height = record.cell_height;
   std::string playmode = record.playmode;
   float align_x = record.align_x;
   float align_y = record.align_y;
   float align_in_container_x = record.align_in_container_x;
   float align_in_container_y = record.align_in_container_y;
   float anchor_x = record.anchor_x;
   float anchor_y = record.anchor_y;
   std::string image_filename = record.image_filename;
   std::vector<std::string> images_list = record.images_list;
   std::string frame_data__in_hash = record.frame_data__in_hash;
   int frame_data__build_n_frames__num_frames = record.frame_data__build_n_frames__num_frames;
   int frame_data__build_n_frames__start_from_frame = record.frame_data__build_n_frames__start_from_frame;
   float frame_data__build_n_frames__each_frame_duration = record.frame_data__build_n_frames__each_frame_duration;


   // Build the frame

   bool using_build_n_frames_frame_data = 
      !(
          frame_data__build_n_frames__num_frames == 0
         //frame_data__build_n_frames__num_frames.empty()
         //&& frame_data__build_n_frames__start_from_frame.empty()
         //&& frame_data__build_n_frames__each_frame_duration.empty()
      );
   bool using_in_hash_frame_data = !frame_data__in_hash.empty();

   std::vector<AllegroFlare::FrameAnimation::Frame> frame_data;

   if (using_build_n_frames_frame_data && using_in_hash_frame_data)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::AssetStudio::DatabaseCSVLoader::load",
         "When loading row " + std::to_string(csv_row) + ", both \"build_n_frames\" and \"in_hash\" sections "
            "contain data. Either one section or the other should be used, but not both."
      );
   }
   else if (!using_build_n_frames_frame_data && !using_in_hash_frame_data)
   {
      // NOTE: Here, assume this is a tileset
      // TODO: Consider guarding with a type==tileset or something.
      AllegroFlare::Logger::warn_from(
         "AllegroFlare::AssetStudio::DatabaseCSVLoader::load",
         "When loading row " + std::to_string(csv_row) + ", there is empty data in the \"frame_data__\" columns. "
            "If this is a tilemap, please discard this message. Note that there are currently no features "
            "implemented for tilemaps."
      );
   }
   else if (using_build_n_frames_frame_data)
   {
      frame_data = build_n_frames(
            //toi(frame_data__build_n_frames__num_frames), // TODO: Test this int
            //toi(frame_data__build_n_frames__start_from_frame), // TODO: Test this int
            //tof(frame_data__build_n_frames__each_frame_duration), // TODO: Test this float
            frame_data__build_n_frames__num_frames, // TODO: Test this int
            frame_data__build_n_frames__start_from_frame, // TODO: Test this int
            frame_data__build_n_frames__each_frame_duration, // TODO: Test this float
            align_x, // TODO: Test this float
            align_y, // TODO: Test this float
            align_in_container_x, // TODO: Test this float
            align_in_container_y, // TODO: Test this float
            anchor_x, // TODO: Test this float
            anchor_y  // TODO: Test this float
         );
   }
   else if (using_in_hash_frame_data)
   {
      frame_data = build_frames_from_hash(frame_data__in_hash);
   }
   else
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::AssetStudio::DatabaseCSVLoader::load",
         "Weird error in unexpected code path."
      );
   }

   // Load the image (or images) data
   //
   // Typically, artists will provide their animations either as a collection of individual image files, or
   // a single file sprite sheet strip. In the assets.db CSV file, there are two columns "images_list"
   // and "image_filename" to represent either type of resource. Either one or the other should be present,
   // but not both (or neither).

   // For an animation, the final FrameAnimation/Animation will need a sprite sheet.  In the case where there are
   // multiple images, a sprite sheet will be created (as asn ALLEGRO_BITMAP).  There may be a case where a sprite
   // sheet already exists, and the asset shares it with other assets.  In this case, created sprite sheets are
   // stored here (though this "sprite sheet bin" should be moved elsewhere else).

   AllegroFlare::FrameAnimation::SpriteSheet* sprite_sheet = nullptr;

   if (image_filename.empty() && images_list.empty())
   {
      // Both "image_filename" and "images_list" columns erroneously have data in them
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::AssetStudio::DatabaseCSVLoader::load",
         "When loading row " + std::to_string(csv_row) + ", there is data in both the \"images_list\" and "
            " \"image_filename\" columns. Data should exist in either one or the other, but not both."
      );
   }
   else if (!image_filename.empty() && !images_list.empty())
   {
      // Neither "image_filename" and "images_list" columns have data in them
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::AssetStudio::DatabaseCSVLoader::load",
         "When loading row " + std::to_string(csv_row) + ", there no data in either the \"images_list\" and "
            " \"image_filename\" columns. Data should be present in or the other (but not both)."
      );
   }
   else if (!image_filename.empty())
   {
      // NOTE: MOST COMMON USE CASE
      // There is "image_filename" data present on this record.
      std::string full_path_to_image_file = asset_pack_identifier + "/extracted/" + image_filename;
      sprite_sheet = obtain_sprite_sheet(full_path_to_image_file, cell_width, cell_height, sprite_sheet_scale);
   }
   else if (!images_list.empty())
   {
      // TODO: Handle this case:
      // TODO: Split
      //std::string full_path_to_image_file = asset_pack_identifier + "/extracted/" + image_filename;
      //images_list = comma_separated_strings_to_vector_of_strings(images_list_raw);

      //std::cout << "*** images_list detected ***" << std::endl;
      //std::cout << "  - images_list.size(): " << images_list.size() << std::endl;
      //std::cout << "  - frame_data.size(): " << frame_data.size() << std::endl;
      //std::cout << "  - images_list_raw: ###" << images_list_raw << "###" << std::endl;

      if (images_list.size() != frame_data.size())
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::AssetStudio::DatabaseCSVLoader::load",
            "When processing asset \"" + identifier + "\", the number of images in "
               "the \"images_list\" (" + std::to_string(images_list.size()) + ") was not the same as the "
               "\"frame_data\"'s \"num_frames\" "
               "(" + std::to_string(frame_data.size()) + ")"
         );
      }

      //AllegroFlare::Logger::warn_from(
         //"AllegroFlare::AssetStudio::DatabaseCSVLoader::load",
         //"When processing asset \"" + identifier + "\", an \"images_list\" was supplied. This feature is "
            //"not yet implemented (you should add it in now, tho). For now, skipping this asset."
      //);

      // Build the extended path_to_image_file
      for (auto &image_list_item : images_list)
      {
         image_list_item = asset_pack_identifier + "/extracted/" + image_list_item;
      }

      sprite_sheet = create_sprite_sheet_from_individual_images(
            images_list,
            cell_width,
            cell_height,
            sprite_sheet_scale
         );
      //using_single_image_file = false;
      //continue;
        //asset_pack_identifier + "/extracted/" + image_filename;
      //AllegroFlare::Logger::throw_error(
         //"AllegroFlare::AssetStudio::DatabaseCSVLoader::load",
         //"foofoo2"
      //);
   }
   //std::string full_path_to_image_file = asset_pack_identifier + "/extracted/" + image_filename;



   // Parse the "playmode"

   std::pair<bool, uint32_t> playmode_parsed_data =
         { true, AllegroFlare::FrameAnimation::Animation::PLAYMODE_FORWARD_ONCE };

   if (!playmode.empty())
   {
      playmode_parsed_data = str_to_playmode(playmode);
   }
   //else
   //{
      //std::cout << "- identifier: \"" << identifier << "\"" << std::endl;
      //std::cout << "    playmode: \"" << playmode << "\" -> " << playmode_parsed_data.second << std::endl;
   //}

   if (playmode_parsed_data.first == false)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::AssetStudio::DatabaseCSVLoader::load",
         "Unrecognized playmode \"" + playmode + "\" when loading row " + std::to_string(csv_row) + "."
      );
   }


   // Build the sprite sheet
   //AllegroFlare::FrameAnimation::SpriteSheet* sprite_sheet =
      //obtain_sprite_sheet(full_path_to_image_file, cell_width, cell_height, 2);

   // Build the animation
   AllegroFlare::FrameAnimation::Animation *animation =
      new AllegroFlare::FrameAnimation::Animation(
         sprite_sheet,
         identifier,
         frame_data,
         playmode_parsed_data.second
      );

   // NOTE: The animation is not initialized. This is because at *use* time, the animation is copied from the
   // database into the using object's posession, at which point that animation is then initialized.

   // Load the data into the asset
   AllegroFlare::AssetStudio::Asset *asset = new AllegroFlare::AssetStudio::Asset;
   asset->id = id;
   asset->identifier = identifier;
   asset->animation = animation;
   asset->cell_width = cell_width;
   asset->cell_height = cell_height;
   // TODO: Look into if these properties should only exist in the animation's frame_data (and not the asset)
   {
      asset->align_x = align_x;
      asset->align_y = align_y;
      asset->align_in_container_x = align_in_container_x;
      asset->align_in_container_y = align_in_container_y;
      asset->anchor_x = anchor_x;
      asset->anchor_y = anchor_y;
   }
   asset->asset_pack_identifier = asset_pack_identifier;
   asset->intra_pack_identifier = intra_pack_identifier;
   asset->type = type;
   asset->image_filename = image_filename;
   asset->images_list = images_list;

   //assets.insert({ asset->identifier, asset });

   // Showing loaded asset
   std::cout << "Asset \"" << asset->identifier << "\" created. "
             << "Dimensions: (" << asset->cell_width << ", " << asset->cell_height << "), "
             << "Frames: " << animation->get_num_frames() << std::endl;

   // TODO: Load an "icon_set" type
   // If it's an "icon_set", then consider building unique assets for each icon
   //int icon_id = 1;
   //if (type == "icon_set")
   //{
      //std::cout << "Building \"icon_set\" for \"" << identifier << "\"" << std::endl;

      //for (int i=0; i<sprite_sheet->get_num_sprites(); i++)
      //{
         //std::string icon_identifier = identifier + "-icon_" + std::to_string(icon_id);

         //AllegroFlare::AssetStudio::Asset *icon_asset = new AllegroFlare::AssetStudio::Asset;
         //icon_asset->id = id + i + 10000; // TODO: Figure out some way to create unique names and ids from icons
         //icon_asset->identifier = icon_identifier;
         //icon_asset->bitmap = sprite_sheet->get_cell(i);
         //icon_asset->cell_width = cell_width;
         //icon_asset->cell_height = cell_height;
         //icon_asset->type = "icon";

         //assets.insert({ icon_asset->identifier, icon_asset });

         //icon_id++;
      //}
   //}

   return asset;
}


} // namespace AssetStudio
} // namespace AllegroFlare


