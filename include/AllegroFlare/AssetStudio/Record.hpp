#pragma once


#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace AssetStudio
   {
      class Record
      {
      private:

      protected:


      public:
         int id;
         std::string identifier;
         int source_csv_column_num;
         std::string status;
         std::string visibility;
         std::string type;
         std::string asset_pack_identifier;
         std::string intra_pack_identifier;
         int cell_width;
         int cell_height;
         float align_x;
         float align_y;
         float align_in_container_x;
         float align_in_container_y;
         float anchor_x;
         float anchor_y;
         std::string image_filename;
         std::vector<std::string> images_list;
         std::string full_path_to_initial_image;
         std::string playmode;
         std::string notes;
         int frame_data__build_n_frames__num_frames;
         int frame_data__build_n_frames__start_from_frame;
         float frame_data__build_n_frames__each_frame_duration;
         std::string frame_data__in_hash;
         Record();
         ~Record();

      };
   }
}



