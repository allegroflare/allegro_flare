#pragma once


#include <AllegroFlare/AssetStudio/Asset.hpp>
#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/CSVParser.hpp>
#include <AllegroFlare/FrameAnimation/Frame.hpp>
#include <AllegroFlare/FrameAnimation/SpriteSheet.hpp>
#include <cstdint>
#include <map>
#include <string>
#include <tuple>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace AssetStudio
   {
      class DatabaseCSVLoader : public AllegroFlare::CSVParser
      {
      private:
         AllegroFlare::BitmapBin* assets_bitmap_bin;
         std::string csv_full_path;
         std::map<std::string, AllegroFlare::AssetStudio::Asset*> assets;
         std::map<std::tuple<std::string, int, int, int>, AllegroFlare::FrameAnimation::SpriteSheet*> sprite_sheets;
         bool loaded;
         AllegroFlare::FrameAnimation::SpriteSheet* create_sprite_sheet_from_individual_images(std::vector<std::string> individual_frame_image_filenames={}, int cell_width=16, int cell_height=16, int sprite_sheet_scale=2);
         AllegroFlare::FrameAnimation::SpriteSheet* obtain_sprite_sheet(std::string filename="[unset-filename]", int cell_width=16, int cell_height=16, int sprite_sheet_scale=2);
         static std::vector<std::string> split(std::string string="", char delimiter=' ');
         static std::vector<std::string> tokenize(std::string str="", char delim='|');
         static std::string trim(std::string s="");

      protected:


      public:
         DatabaseCSVLoader(AllegroFlare::BitmapBin* assets_bitmap_bin=nullptr);
         ~DatabaseCSVLoader();

         void set_assets_bitmap_bin(AllegroFlare::BitmapBin* assets_bitmap_bin);
         void set_csv_full_path(std::string csv_full_path);
         AllegroFlare::BitmapBin* get_assets_bitmap_bin() const;
         std::string get_csv_full_path() const;
         std::map<std::string, AllegroFlare::AssetStudio::Asset*> get_assets();
         bool level_exists(std::string level_identifier="[unset-level_identifier]");
         static int toi(std::string value="[unset-value]");
         static float tof(std::string value="[unset-value]");
         static std::vector<std::string> comma_separated_quoted_strings_to_vector_of_strings(std::string comma_separated_quoted_strings="[unset-comma_separated_quoted_strings]");
         static std::vector<std::string> comma_separated_strings_to_vector_of_strings(std::string comma_separated_strings="[unset-comma_separated_strings]");
         std::pair<bool, uint32_t> str_to_playmode(std::string playmode_string="[unset-playmode_string]");
         AllegroFlare::AssetStudio::Asset* find_level(std::string level_identifier="[unset-level_identifier]");
         static std::string validate_key_and_return(std::map<std::string, std::string>* extracted_row=nullptr, std::string key="[unset-key]");
         std::vector<AllegroFlare::FrameAnimation::Frame> build_n_frames(uint32_t num_frames=1, uint32_t start_frame_num=0, float each_frame_duration=0.08f);
         std::vector<AllegroFlare::FrameAnimation::Frame> build_frames_from_hash(std::string frame_data_hash="[unset-frame_data_hash]");
         void load();
      };
   }
}



