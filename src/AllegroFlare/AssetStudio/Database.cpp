

#include <AllegroFlare/AssetStudio/Database.hpp>

#include <AllegroFlare/Errors.hpp>
#include <AllegroFlare/FrameAnimation/SpriteSheet.hpp>
#include <AllegroFlare/FrameAnimation/SpriteStripAssembler.hpp>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace AssetStudio
{


Database::Database(AllegroFlare::BitmapBin* assets_bitmap_bin)
   : global_records({})
   , local_records({})
   , global_assets()
   , local_assets()
   , assets_bitmap_bin(assets_bitmap_bin)
   , sprite_sheets({})
   , sprite_sheet_scale(3)
   , global_identifier_prefix(DEFAULT_GLOBAL_IDENTIFIER_PREFIX)
   , using_global_identifier_prefix(false)
   , all_global_assets_loaded(false)
   , all_local_assets_loaded(false)
{
}


Database::~Database()
{
}


void Database::set_global_records(std::vector<AllegroFlare::AssetStudio::Record> global_records)
{
   this->global_records = global_records;
}


void Database::set_local_records(std::vector<AllegroFlare::AssetStudio::Record> local_records)
{
   this->local_records = local_records;
}


void Database::set_global_assets(std::map<std::string, AllegroFlare::AssetStudio::Asset*> global_assets)
{
   this->global_assets = global_assets;
}


void Database::set_local_assets(std::map<std::string, AllegroFlare::AssetStudio::Asset*> local_assets)
{
   this->local_assets = local_assets;
}


void Database::set_assets_bitmap_bin(AllegroFlare::BitmapBin* assets_bitmap_bin)
{
   this->assets_bitmap_bin = assets_bitmap_bin;
}


void Database::set_sprite_sheets(std::map<std::tuple<std::string, int, int, int>, AllegroFlare::FrameAnimation::SpriteSheet*> sprite_sheets)
{
   this->sprite_sheets = sprite_sheets;
}


void Database::set_sprite_sheet_scale(int sprite_sheet_scale)
{
   this->sprite_sheet_scale = sprite_sheet_scale;
}


std::vector<AllegroFlare::AssetStudio::Record> Database::get_global_records() const
{
   return global_records;
}


std::vector<AllegroFlare::AssetStudio::Record> Database::get_local_records() const
{
   return local_records;
}


std::map<std::string, AllegroFlare::AssetStudio::Asset*> Database::get_global_assets() const
{
   return global_assets;
}


std::map<std::string, AllegroFlare::AssetStudio::Asset*> Database::get_local_assets() const
{
   return local_assets;
}


AllegroFlare::BitmapBin* Database::get_assets_bitmap_bin() const
{
   return assets_bitmap_bin;
}


std::map<std::tuple<std::string, int, int, int>, AllegroFlare::FrameAnimation::SpriteSheet*> Database::get_sprite_sheets() const
{
   return sprite_sheets;
}


int Database::get_sprite_sheet_scale() const
{
   return sprite_sheet_scale;
}


std::string Database::get_global_identifier_prefix() const
{
   return global_identifier_prefix;
}


bool Database::get_using_global_identifier_prefix() const
{
   return using_global_identifier_prefix;
}


bool Database::get_all_global_assets_loaded() const
{
   return all_global_assets_loaded;
}


bool Database::get_all_local_assets_loaded() const
{
   return all_local_assets_loaded;
}


void Database::set_global_identifier_prefix(std::string global_identifier_prefix)
{
   if (!((!using_global_identifier_prefix)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::set_global_identifier_prefix]: error: guard \"(!using_global_identifier_prefix)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::set_global_identifier_prefix]: error: guard \"(!using_global_identifier_prefix)\" not met");
   }
   if (using_global_identifier_prefix) remove_global_identifier_prefixes();
   this->global_identifier_prefix = global_identifier_prefix;
   prefix_global_identifier_prefix_to_identifiers(this->global_identifier_prefix);
   return;
}

void Database::remove_global_identifier_prefix()
{
   if (!(using_global_identifier_prefix))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::remove_global_identifier_prefix]: error: guard \"using_global_identifier_prefix\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::remove_global_identifier_prefix]: error: guard \"using_global_identifier_prefix\" not met");
   }
   if (using_global_identifier_prefix) remove_global_identifier_prefixes();
   return;
}

std::set<std::string> Database::asset_identifiers()
{
   // TODO: Test this
   std::set<std::string> result;
   for (auto &asset : global_assets) result.insert(asset.first);
   for (auto &asset : local_assets) result.insert(asset.first);
   return result;
}

std::set<std::string> Database::global_record_identifiers()
{
   // TODO: Test this
   std::set<std::string> result;
   for (auto &global_record : global_records) result.insert(global_record.identifier);
   return result;
}

std::set<std::string> Database::local_record_identifiers()
{
   // TODO: Test this
   std::set<std::string> result;
   for (auto &local_record : local_records) result.insert(local_record.identifier);
   return result;
}

void Database::remove_global_identifier_prefixes()
{
   if (!(using_global_identifier_prefix))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::remove_global_identifier_prefixes]: error: guard \"using_global_identifier_prefix\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::remove_global_identifier_prefixes]: error: guard \"using_global_identifier_prefix\" not met");
   }
   int prefix_length = global_identifier_prefix.length();

   // Pull out the keys first
   std::vector<std::string> asset_keys;
   for (auto &asset : global_assets)
   {
      asset_keys.push_back(asset.first);
   }

   // Go through each key, and remove n characters from the front of each key
   for (auto &asset_key : asset_keys)
   {
      auto extracted_asset_element = global_assets.extract(asset_key);
      extracted_asset_element.key() = extracted_asset_element.key().substr(prefix_length);
      // TODO: Validate new key does not already exist
      global_assets.insert(std::move(extracted_asset_element));
   }

   using_global_identifier_prefix = false;
   return;
}

void Database::prefix_global_identifier_prefix_to_identifiers(std::string prefix)
{
   if (!((!using_global_identifier_prefix)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::prefix_global_identifier_prefix_to_identifiers]: error: guard \"(!using_global_identifier_prefix)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::prefix_global_identifier_prefix_to_identifiers]: error: guard \"(!using_global_identifier_prefix)\" not met");
   }
   // Pull out the keys first
   std::vector<std::string> asset_keys;
   for (auto &asset : global_assets)
   {
      asset_keys.push_back(asset.first);
   }

   // Go through each key, and rename
   for (auto &asset_key : asset_keys)
   {
      auto extracted_asset_element = global_assets.extract(asset_key);
      extracted_asset_element.key() = prefix + asset_key;
      // TODO: Validate new key does not already exist
      global_assets.insert(std::move(extracted_asset_element));
   }

   global_identifier_prefix = prefix; // TODO: Test this assignment
   using_global_identifier_prefix = true;
   return;
}

bool Database::record_exists(std::string record_identifier)
{
   // TODO: Consider if an index on "Record::identifier" would be helpful
   // TODO: This is not very performant, consider a single index or map
   for (auto &local_record : local_records) if (local_record.identifier == record_identifier) return true;
   for (auto &global_record : global_records) if (global_record.identifier == record_identifier) return true;
   return false;
}

bool Database::record_has_hidden_visibility(std::string record_identifier)
{
   // TODO: Consider if an index on "Record::identifier" would be helpful
   // TODO: This is not very performant, consider a single index or map
   for (auto &local_record : local_records)
   {
      if (local_record.identifier == record_identifier) return local_record.visibility_is_hidden();
   }
   for (auto &global_record : global_records)
   {
      if (global_record.identifier == record_identifier) return global_record.visibility_is_hidden();
   }
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::AssetStudio::DatabaseCSVLoader::record_has_hidden_visibillity",
      "A record with the identifier \"" + record_identifier + "\" does not exist."
   );
   return false;
}

AllegroFlare::AssetStudio::Record* Database::find_record(std::string record_identifier)
{
   // TODO: Test this
   // TODO: This is not very performant, consider a single index or map
   for (auto &local_record : local_records) if (local_record.identifier == record_identifier) return &local_record;
   for (auto &global_record : global_records) if (global_record.identifier == record_identifier) return &global_record;
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::AssetStudio::DatabaseCSVLoader::find_global_record",
      "A global_record with the identifier \"" + record_identifier + "\" does not exist."
   );
   return nullptr;
}

bool Database::global_record_exists(std::string record_identifier)
{
   // TODO: Consider if an index on "Record::identifier" would be helpful
   // TODO: This is not very performant, consider a single index or map
   for (auto &global_record : global_records) if (global_record.identifier == record_identifier) return true;
   return false;
}

AllegroFlare::AssetStudio::Record* Database::find_global_record(std::string record_identifier)
{
   // TODO: Test this
   // TODO: This is not very performant, consider a single index or map
   for (auto &global_record : global_records) if (global_record.identifier == record_identifier) return &global_record;
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::AssetStudio::DatabaseCSVLoader::find_global_record",
      "A global_record with the identifier \"" + record_identifier + "\" does not exist."
   );
   return nullptr;
}

bool Database::local_record_exists(std::string record_identifier)
{
   // TODO: Consider if an index on "Record::identifier" would be helpful
   // TODO: This is not very performant, consider a single index or map
   for (auto &local_record : local_records) if (local_record.identifier == record_identifier) return true;
   return false;
}

AllegroFlare::AssetStudio::Record* Database::find_local_record(std::string record_identifier)
{
   // TODO: Test this
   // TODO: This is not very performant, consider a single index or map
   for (auto &local_record : local_records) if (local_record.identifier == record_identifier) return &local_record;
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::AssetStudio::DatabaseCSVLoader::find_local_record",
      "A local_record with the identifier \"" + record_identifier + "\" does not exist."
   );
   return nullptr;
}

bool Database::asset_exists(std::string identifier)
{
   return (local_assets.count(identifier) > 0) || (global_assets.count(identifier) > 0);
}

AllegroFlare::AssetStudio::Asset* Database::find_asset_by_identifier(std::string identifier)
{
   if (local_assets.count(identifier) != 0) return local_assets[identifier];
   if (global_assets.count(identifier) != 0) return global_assets[identifier];

   AllegroFlare::Errors::throw_error(
         "AllegroFlare::AssetStudio::Database::find_asset_by_identifier",
         "No asset exists with the identifier \"" + identifier+ "\""
      );

   return nullptr;
}

bool Database::asset_exists_as_animation(std::string identifier)
{
   if (!asset_exists(identifier)) return false;
   //if (!(local_assets.count(identifier) > 0)) return false;
   //if (!(global_assets.count(identifier) > 0)) return false;
   AllegroFlare::AssetStudio::Asset* asset = find_asset_by_identifier(identifier);
   if (asset->animation) return true;
   return false;
}

AllegroFlare::FrameAnimation::Animation* Database::find_animation_by_identifier(std::string identifier)
{
   if (!asset_exists(identifier))
   {
      AllegroFlare::Errors::throw_error(
            "AllegroFlare::AssetStudio::Database::find_animation_by_identifier",
            "No asset exists for identifier \"" + identifier+ "\" to evaluate for an animation."
         );
   }
   AllegroFlare::AssetStudio::Asset* asset = find_asset_by_identifier(identifier);
   if (!asset->animation)
   {
      AllegroFlare::Errors::throw_error(
            "AllegroFlare::AssetStudio::Database::find_animation_by_identifier",
            "The asset \"" + identifier+ "\" exists but does not contain an animation."
         );
   }
   return asset->animation;
}

void Database::load_asset(std::string identifier)
{
   if (asset_exists(identifier)) return; // Asset already exists and is loaded

   if (!record_exists(identifier))
   {
      AllegroFlare::Errors::throw_error(
         "AllegroFlare::AssetStudio::Database::load_asset",
         "The asset \"" + identifier+ "\" cannot be loaded because there is no record with that identifier."
      );
   }

   bool record_exists_as_local = local_record_exists(identifier);
   bool record_exists_as_global = global_record_exists(identifier);

   if (!record_exists_as_local && !record_exists_as_global)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::AssetStudio::DatabaseCSVLoader::load_asset",
         "When attempting to load an asset from the record \"" + identifier + "\", this record was not found."
      );
   }
   else if (record_exists_as_local && record_exists_as_global)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::AssetStudio::DatabaseCSVLoader::load_asset",
         "When attempting to load an asset from the record \"" + identifier + "\", this identifier was found in "
            "both the local_assets and global_assets, leading to a (possible) conflict. This may be intentional, "
            "and it may be that the local asset is expected to override the global one in usage. However, at the "
            "time of this writing, this design usage is unclear and this error is being thrown. Hopefully your "
            "usage provides some clarity on what behavior should be expected here."
      );
   }
   else
   {
      if (record_has_hidden_visibility(identifier))
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::AssetStudio::DatabaseCSVLoader::load_asset",
            "Cannot load asset \"" + identifier + "\" from the records. Note that there is a record present for "
               "this identifier that is present, but it is marked as \"hidden\", indicating that it should be "
               "ignored."
         );
      }
      else
      {
         AllegroFlare::AssetStudio::Asset *asset = create_asset_from_record_identifier(identifier);
         if (record_exists_as_local)
         {
            local_assets.insert({ asset->identifier, asset });
         }
         else if (record_exists_as_global)
         {
            global_assets.insert({ asset->identifier, asset });
         }
         else
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::AssetStudio::DatabaseCSVLoader::load_asset",
               "Logic path error 23487583"
            );
         }
      }
   }

   return;
}

void Database::load_all_global_assets_from_all_global_records()
{
   if (!((!all_global_assets_loaded)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::load_all_global_assets_from_all_global_records]: error: guard \"(!all_global_assets_loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::load_all_global_assets_from_all_global_records]: error: guard \"(!all_global_assets_loaded)\" not met");
   }
   if (!(assets_bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::load_all_global_assets_from_all_global_records]: error: guard \"assets_bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::load_all_global_assets_from_all_global_records]: error: guard \"assets_bitmap_bin\" not met");
   }
   // Load global assets
   std::set<std::string> hidden_global_assets;
   for (auto &record : global_records)
   {
      if (record.visibility_is_hidden())
      {
         // TODO: Report the hidden assets at end of loading process
         hidden_global_assets.insert(record.identifier);
         continue;
      }

      // Create the asset
      AllegroFlare::AssetStudio::Asset *asset = create_asset_from_record_identifier(record.identifier);

      // Add the asset to the assets
      global_assets.insert({ asset->identifier, asset });
   }

   all_global_assets_loaded = true;
   return;
}

void Database::load_all_local_assets_from_all_local_records()
{
   if (!((!all_local_assets_loaded)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::load_all_local_assets_from_all_local_records]: error: guard \"(!all_local_assets_loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::load_all_local_assets_from_all_local_records]: error: guard \"(!all_local_assets_loaded)\" not met");
   }
   if (!(assets_bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::load_all_local_assets_from_all_local_records]: error: guard \"assets_bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::load_all_local_assets_from_all_local_records]: error: guard \"assets_bitmap_bin\" not met");
   }
   // Load local assets
   std::set<std::string> hidden_local_assets;
   for (auto &record : local_records)
   {
      if (record.visibility_is_hidden())
      {
         // TODO: Report the hidden assets at end of loading process
         hidden_local_assets.insert(record.identifier);
         continue;
      }

      // Create the asset
      AllegroFlare::AssetStudio::Asset *asset = create_asset_from_record_identifier(record.identifier);

      // Add the asset to the assets
      local_assets.insert({ asset->identifier, asset });
   }

   all_local_assets_loaded = true;
   return;
}

std::vector<AllegroFlare::FrameAnimation::Frame> Database::build_n_frames(uint32_t num_frames, uint32_t start_frame_num, float each_frame_duration, float each_frame_align_x, float each_frame_align_y, float each_frame_align_in_container_x, float each_frame_align_in_container_y, float each_frame_anchor_x, float each_frame_anchor_y)
{
   if (!((num_frames >= 1)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::build_n_frames]: error: guard \"(num_frames >= 1)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::build_n_frames]: error: guard \"(num_frames >= 1)\" not met");
   }
   if (!((start_frame_num >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::build_n_frames]: error: guard \"(start_frame_num >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::build_n_frames]: error: guard \"(start_frame_num >= 0)\" not met");
   }
   if (!((each_frame_duration >= 0.0001)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::build_n_frames]: error: guard \"(each_frame_duration >= 0.0001)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::build_n_frames]: error: guard \"(each_frame_duration >= 0.0001)\" not met");
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

std::vector<AllegroFlare::FrameAnimation::Frame> Database::build_frames_from_hash(std::string frame_data_hash)
{
   AllegroFlare::Logger::throw_error(
      "AllegroFlare::AssetStudio::DatabaseCSVLoader::build_frames_from_hash",
      "This feature is not yet supported. The following \"frame_data_hash\" was present and expected to load: \""
         + frame_data_hash + "\""
   );

   std::vector<AllegroFlare::FrameAnimation::Frame> result;
   // TODO: If frame animation and alignment data is incuded in the hash, parse and use it here
   return result;
}

AllegroFlare::FrameAnimation::SpriteSheet* Database::obtain_sprite_sheet(std::string filename, int cell_width, int cell_height, int _sprite_sheet_scale, bool preload_bitmap_silently)
{
   if (!(assets_bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::obtain_sprite_sheet]: error: guard \"assets_bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::obtain_sprite_sheet]: error: guard \"assets_bitmap_bin\" not met");
   }
   if (!(assets_bitmap_bin->is_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::obtain_sprite_sheet]: error: guard \"assets_bitmap_bin->is_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::obtain_sprite_sheet]: error: guard \"assets_bitmap_bin->is_initialized()\" not met");
   }
   std::tuple<std::string, int, int, int> sprite_sheet_key(filename, cell_width, cell_height, _sprite_sheet_scale);
   if (sprite_sheets.find(sprite_sheet_key) == sprite_sheets.end())
   {
      // Create the sprite sheet

      // Load the bitmap from the bitmap bin
      // TODO: Consider new bitmap flags when loading

      if (preload_bitmap_silently)
      {
         assets_bitmap_bin->preload(filename);
      }

      // Create sprite sheet
      // TODO: Check this duplication proceedure does not leave dangling bitmaps

      // Clone the bitmap sheet
      ALLEGRO_BITMAP* sprite_sheet_atlas = al_clone_bitmap(assets_bitmap_bin->auto_get(filename));

      AllegroFlare::FrameAnimation::SpriteSheet *result_sprite_sheet =
         new AllegroFlare::FrameAnimation::SpriteSheet( // HERE
            sprite_sheet_atlas,
            cell_width,
            cell_height,
            _sprite_sheet_scale
         );
      result_sprite_sheet->initialize();

      // Destroy the cloned bitmap that was added to the sprite sheet
      al_destroy_bitmap(sprite_sheet_atlas);

      // Destroy the bitmap loaded by the asset_bitmap_bin
      // TODO: Allow destroying bitmaps silently
      // TODO: Test proper destruction of bitmap
      assets_bitmap_bin->destroy(filename);

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

std::pair<bool, uint32_t> Database::str_to_playmode(std::string playmode_string)
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

AllegroFlare::FrameAnimation::SpriteSheet* Database::create_sprite_sheet_from_individual_images(std::vector<std::string> individual_frame_image_filenames, int cell_width, int cell_height, int _sprite_sheet_scale)
{
   if (!(assets_bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::create_sprite_sheet_from_individual_images]: error: guard \"assets_bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::create_sprite_sheet_from_individual_images]: error: guard \"assets_bitmap_bin\" not met");
   }
   if (!((!individual_frame_image_filenames.empty())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::create_sprite_sheet_from_individual_images]: error: guard \"(!individual_frame_image_filenames.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::create_sprite_sheet_from_individual_images]: error: guard \"(!individual_frame_image_filenames.empty())\" not met");
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

AllegroFlare::AssetStudio::Asset* Database::create_asset_from_record_identifier(std::string identifier_, bool preload_bitmap_silently)
{
   if (!(record_exists(identifier_)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AssetStudio::Database::create_asset_from_record_identifier]: error: guard \"record_exists(identifier_)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AssetStudio::Database::create_asset_from_record_identifier]: error: guard \"record_exists(identifier_)\" not met");
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
      sprite_sheet = obtain_sprite_sheet(
         full_path_to_image_file,
         cell_width,
         cell_height,
         sprite_sheet_scale,
         preload_bitmap_silently
      );
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


