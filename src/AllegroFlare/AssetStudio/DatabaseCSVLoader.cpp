

#include <AllegroFlare/AssetStudio/DatabaseCSVLoader.hpp>

#include <AllegroFlare/FrameAnimation/Animation.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>


namespace AllegroFlare
{
namespace AssetStudio
{


DatabaseCSVLoader::DatabaseCSVLoader()
   : AllegroFlare::CSVParser()
   , csv_full_path("[unset-csv_full_path]")
   , records({})
   , loaded(false)
   , records_loaded(false)
{
}


DatabaseCSVLoader::~DatabaseCSVLoader()
{
}


void DatabaseCSVLoader::set_csv_full_path(std::string csv_full_path)
{
   this->csv_full_path = csv_full_path;
}


std::string DatabaseCSVLoader::get_csv_full_path() const
{
   return csv_full_path;
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


} // namespace AssetStudio
} // namespace AllegroFlare


